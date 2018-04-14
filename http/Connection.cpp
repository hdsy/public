// Connection.cpp: implementation of the CConnection class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32
#include "StdAfx.h"
#endif
#include "Connection.h"

#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnection::CConnection()
{

	m_pszHost = NULL;
	conn = NULL;
	ctx = NULL;
	ssl = NULL;
	
	m_bOpened = FALSE;

	m_iState = 0;

	if(InitOpenssl()) {m_iState = 1;};
}

CConnection::~CConnection()
{
	Close();
}

BOOL CConnection::Open(const char *host, short port, short flag,const char * root_cert_file_path, const char *cert_file_path,const char *pwd,const char * szDomain)
{
	if (szDomain != NULL)
		m_pszHost = szDomain;

	Close();
	
	switch(flag)
	{
	case HTTP:
		m_bOpened = OpenHttp(host,port);
		break;
	case HTTPS_NO_VALID:
		m_bOpened = OpenHttpsWithoutCheck(host,port);
		break;
	case HTTPS_SERVER_VALID:
		m_bOpened = OpenHttpsCheckServer(host,port,root_cert_file_path);
		break;
	case HTTPS_BOTH_VALID:		
		m_bOpened = OpenHttpsCheckBoth(host,port,root_cert_file_path,cert_file_path,pwd);;
		break;
	default:
		break;
	}
	
	return m_bOpened;
}

BOOL CConnection::InitOpenssl()
{
	if ( /*!THREAD_setup () || */ !SSL_library_init ())
	{
		return FALSE;
	}
	SSL_load_error_strings ();
	
//	ERR_load_BIO_strings();
	
//	OpenSSL_add_all_algorithms();
	
	
	return TRUE;
}

BOOL CConnection::OpenHttp(const char * host ,short port)
{
	char szConn[256] = {0};
	sprintf(szConn,"%s:%d",host,port);
	
	conn = BIO_new_connect (szConn);
	
	if ((!conn) || (BIO_do_connect (conn) <= 0))
	{
		Close();
		return FALSE;
	}
	
	return TRUE;
}

BOOL CConnection::OpenHttpsWithoutCheck(const char *host, short port)
{
	ctx = SSL_CTX_new (SSLv23_method ());


	
	if(!OpenHttp(host,port))
		return FALSE;
	
	ssl = SSL_new (ctx);
	if(!ssl)
		return FALSE;
	
	SSL_set_bio (ssl, conn, conn);
	
	if (SSL_connect (ssl) <= 0)
		return FALSE;
	
	return TRUE;
}

BOOL CConnection::OpenHttpsCheckServer(const char *host, short port,const char * root_cert_file_path)
{
	int i = 0;
	
	if(root_cert_file_path && strlen(root_cert_file_path))
		i = SSL_CTX_load_verify_locations(ctx,root_cert_file_path,NULL);

	if(!OpenHttpsWithoutCheck(host,port))
		return FALSE;

	if(m_pszHost == NULL)
		return PostConnectionServerCheck(host);
	else
		return PostConnectionServerCheck(m_pszHost);
		
}

BOOL CConnection::OpenHttpsCheckBoth(const char *host, short port,const char * root_cert_file_path, const char *cert_file_path,const char *pwd)
{
	ctx = SSL_CTX_new (SSLv23_method ());

	int i = 0;
	
	if(root_cert_file_path && strlen(root_cert_file_path))
		i = SSL_CTX_load_verify_locations(ctx,root_cert_file_path,NULL);
	
	if(pwd && strlen(pwd)!=0)
		SSL_CTX_set_default_passwd_cb_userdata(ctx, (void *)pwd);
	
	if (SSL_CTX_use_certificate_chain_file (ctx, cert_file_path) != 1)
		return FALSE;

	if (SSL_CTX_use_PrivateKey_file (ctx, cert_file_path, SSL_FILETYPE_PEM) != 1)
		return FALSE;

	
	if(!OpenHttp(host,port))
		return FALSE;
	
	ssl = SSL_new (ctx);
	if(!ssl)
	{
		Close();
		return FALSE;
	}
	
	SSL_set_bio (ssl, conn, conn);
	
	if (SSL_connect (ssl) <= 0)
	{
		Close();
		return FALSE;
	}

	if(m_pszHost == NULL)
	{
	
		if(!PostConnectionServerCheck(host))
		{
			Close();
			return FALSE;
		}
	}
	else
	{
		if(!PostConnectionServerCheck(m_pszHost))
		{
			Close();
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CConnection::PostConnectionServerCheck(const char *host)
{
	long a,b;
	BOOL c;


	X509 *cert;
	X509_NAME *subj;
	char data[256];
	int extcount;
	int ok = 0;
	/* 
	* Checking the return from SSL_get_peer_certificate here is not
	* strictly necessary. With our example programs, it is not
	* possible for it to return NULL. However, it is good form to
	* check the return since it can return NULL if the examples are
	* modified to enable anonymous ciphers or for the server to not
	* require a client certificate.
	*/
	cert = SSL_get_peer_certificate (ssl);
	if (!cert || !host)
		goto err_occured;
	
	if ((extcount = X509_get_ext_count (cert)) > 0)
	{
		int i;
		for (i = 0; i < extcount; i++)
		{
			const char *extstr ;
			X509_EXTENSION *ext;
			
			ext = X509_get_ext (cert, i);
			
			extstr = OBJ_nid2sn (OBJ_obj2nid(X509_EXTENSION_get_object(ext)));
						
			if (!strcmp (extstr, "subjectAltName"))
			{				
				int j;
				const unsigned char *data;
				STACK_OF (CONF_VALUE) * val;
				CONF_VALUE *nval;
				const X509V3_EXT_METHOD *meth;
			
				meth = X509V3_EXT_get (ext);
				if (!meth || !meth->d2i)
					break;
			
				data = ext->value->data;
			
				val = meth->i2v (meth,meth->d2i(NULL, &data, ext->value->length), NULL);

				for (j = 0; j < sk_CONF_VALUE_num (val);j++)
				{
					nval = sk_CONF_VALUE_value (val, j);
					if (!strcmp (nval->name, "DNS")
						&& !strcmp (nval->value, host))
					{
						ok = 1;
						break;
					}
				}
			}
			
			if (ok)
				break;
		}
	}
	
	subj = X509_get_subject_name (cert);
	if (!ok && subj && 	X509_NAME_get_text_by_NID (subj, NID_commonName, data, 256) > 0)
	{
		data[255] = 0;
		if (stricmp (data, host) != 0)
		{
				goto err_occured;
		}
	}
	
	X509_free (cert);

	a = SSL_get_verify_result (ssl);
	b = X509_V_OK;

	c = (b == a);
	
	return (SSL_get_verify_result (ssl) == X509_V_OK);

err_occured:
	if (cert)
		X509_free (cert);
	return (X509_V_ERR_APPLICATION_VERIFICATION == X509_V_OK);
}

void CConnection::Close()
{
	if(ssl) 
	{
		SSL_free (ssl);
		ssl = NULL;
		conn = NULL;
	}
	if(conn)
	{
		BIO_free_all(conn);
		conn = NULL;
	}
	if(ctx)
	{
		SSL_CTX_free(ctx);
		ctx =NULL;
	}

	m_bOpened = FALSE;

}

int CConnection::Send(const char *szReq, int size)
{
	if(!m_bOpened) return 0;

	int nwritten = 0;

	int res = 0;

	if(ssl)
	{
		for (nwritten; nwritten < size; nwritten += res)
		{
			res = SSL_write (ssl, szReq + nwritten,size - nwritten);
			if (res <= 0) break;
		}
	}
	else
	{
		for (nwritten; nwritten < size; nwritten += res)
		{
			res = BIO_write (conn, szReq + nwritten,size - nwritten);
			if (res <= 0) break;
		}
	}

	return nwritten;
}
/*缺乏超时机制,缺乏服务响应结束标记*/
int CConnection::Read(char *szRes, int size)
{
	if(!m_bOpened) return 0;

	int nread = 0;

	int res = 0;

	if(ssl)
	{
		for (nread; nread < size; nread += res)
		{
			res = SSL_read (ssl, szRes + nread,size - nread);
			if (res <= 0) break;
		}
	}
	else
	{
		for (nread; nread < size; nread += res)
		{
			res = BIO_read (conn, szRes + nread,size - nread);
			if ((res <= 0) && (!BIO_should_retry(conn))) break;
		}
	}

	return nread;
	
}
