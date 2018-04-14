// ***********************************************
// 
// 创建日期： 2009-11-18
// 
// 作    者： gaoyong
// 
// 电子邮件： gaoyong@my-soft.net.cn
// 
// 主要功能： 实现对html文件的格式化输出，以及类似
// 
//            BPEL的流程控制。
// 
// ***********************************************
#ifdef WIN32
#include "stdafx.h"
#endif
#include "CMyExpression.h"


//CMyExpression* CMyExpression::m_pCurrent = NULL;
//##ModelId=4B038C6E00C8
CMyExpression::CMyExpression():m_pParent(NULL),m_sName(""),m_eType(TYPE_UNKNOWN),m_eState(STATE_BEGIN) 
{
//	m_pCurrent = NULL;
}

//##ModelId=4B038C63023F
CMyExpression::CMyExpression(CMyExpression* pParent):m_pParent(pParent),m_sName(""),m_eType(TYPE_UNKNOWN),m_eState(STATE_BEGIN) 
{
//	m_pCurrent = NULL;
}

//##ModelId=4B03903000E4
CMyExpression::CMyExpression(const string &sExpr, CMyExpression* pParent):m_pParent(pParent),m_sName(""),m_eType(TYPE_UNKNOWN),m_eState(STATE_BEGIN) 
{
//	m_pCurrent = NULL;
	Identify(sExpr);
}

//##ModelId=4B04DFA10369
//DEL CMyExpression::CMyExpression(const string &sExpr, string::const_iterator & pos, CMyExpression* pParent):m_pParent(pParent),m_sName(""),m_eType(TYPE_UNKNOWN),m_eState(STATE_BEGIN) 
//DEL {
//DEL 	Identify(sExpr,pos);
//DEL }

//##ModelId=4B03907803D3
enum EERROR CMyExpression::Identify(const string &sExpr)
{
	CMyExpression* m_pCurrent = this;

	string::const_iterator iterBegin;
	iterBegin = sExpr.begin();
	
	return Identify(sExpr,iterBegin,m_pCurrent);
}

//##ModelId=4B038D5F01D5
enum EERROR CMyExpression::Identify(const string &sExpr, string::const_iterator &pos,CMyExpression* &m_pCurrent)
{
	EERROR err = SUCCESS;

	/*
	if(m_pCurrent == NULL)
		m_pCurrent = this;
		*/

	for(pos;pos != sExpr.end();pos++)
	{
		switch(m_pCurrent->m_eState)
		{
		case STATE_BEGIN:
			{
				err = m_pCurrent->Identify_STATE_BEGIN(sExpr,pos,m_pCurrent);
				if(err != SUCCESS ) return err;
			}
			break;
		case STATE_BUF_READING:
			{
				err = m_pCurrent->Identify_STATE_BUF_READING(sExpr,pos,m_pCurrent);
				if(err != SUCCESS ) return err;
			}
			break;
		case STATE_BUF_END:
			{
				err = m_pCurrent->Identify_STATE_BUF_END(sExpr,pos,m_pCurrent);
				if(err != SUCCESS ) return err;
			}
			break;
		case STATE_BROTHER:
			{
				err = m_pCurrent->Identify_STATE_BROTHER(sExpr,pos,m_pCurrent);
				if(err != SUCCESS ) return err;
			}
			break;
		case STATE_CHILD:
			{
				err = m_pCurrent->Identify_STATE_CHILD(sExpr,pos,m_pCurrent);
				if(err != SUCCESS ) return err;
			}
			break;
		case STATE_PARENT:
			{
				err = m_pCurrent->Identify_STATE_PARENT(sExpr,pos,m_pCurrent);
				if(err != SUCCESS ) return err;
			}
			break;
		default:
			{
				if(GetSymbolType(*pos) != SYMBOL_EOF)
					m_pCurrent->m_eState = STATE_BEGIN;
				else
					m_pCurrent->m_eState = STATE_END;
			}
			break;		
		}

		if(m_pCurrent == NULL)
			m_pCurrent = this;
	}
	
	if( pos == sExpr.end() )
	{
		err = m_pCurrent->Identify_STATE_END(sExpr,pos,m_pCurrent);
		if(err != SUCCESS ) return err;
	}

	return err;
}

//##ModelId=4B038F08015D
void CMyExpression::Clear()
{
	for_each(m_vChild.begin(),m_vChild.end(),CMyExpression::Delete);
		
	m_vChild.clear();

	m_sName = "" ;
	m_eType = TYPE_UNKNOWN;
	m_eState = STATE_BEGIN;
}

//##ModelId=4B038F1D0073
CMyExpression::~CMyExpression()
{
	Clear();
}

//##ModelId=4B0500630296
void CMyExpression::Delete(CMyExpression* pExpr)
{
	if(pExpr != NULL)
	{
		delete pExpr;
		pExpr = NULL;	
	}
}

//##ModelId=4B050360023D
enum EERROR CMyExpression::Identify_STATE_BEGIN(const string &m_sExpr, string::const_iterator & pos ,CMyExpression* &m_pCurrent)
{
	EERROR err = SUCCESS;
	
	switch(GetSymbolType(pos))
	{
	case SYMBOL_BLANK:
		break;
	case SYMBOL_UNKNOWN:
		return ERROR_SYMBOL;
		break;
	default:
		pos-- ;
		m_pCurrent->m_eState = STATE_BUF_READING;
		break;
	}
	
	return err;
}

//##ModelId=4B0507720189
enum EERROR CMyExpression::Identify_STATE_BUF_READING(const string &m_sExpr, string::const_iterator &       pos ,CMyExpression* &m_pCurrent)
{
	EERROR err = SUCCESS;
	
	switch(GetSymbolType(pos))
	{
	case SYMBOL_OP_BEGIN:
	case SYMBOL_OP_END:
	case SYMBOL_COMMA:
		pos--;
		m_pCurrent->m_eState = STATE_BUF_END;
		break;
	case SYMBOL_BLANK:
		m_pCurrent->m_eState = STATE_BUF_END;
		break;
	case SYMBOL_ID:
	case SYMBOL_CONST_ONLY:
	case SYMBOL_VAR_FIRST:
		m_pCurrent->m_sName.append(1,*pos);
		break;
	case SYMBOL_UNKNOWN:
		return ERROR_SYMBOL;
		break;
	default:
		return ERROR_BUF_READING;
		break;
	}
	
	return err;
}

//##ModelId=4B050CDB01B1
enum EERROR CMyExpression::Identify_STATE_BUF_END(const string &m_sExpr, string::const_iterator &      pos,CMyExpression* &m_pCurrent)
{
	EERROR err = SUCCESS;
	
	switch(GetSymbolType(pos))
	{
	case SYMBOL_BLANK:
		break;
	case SYMBOL_OP_BEGIN:
		pos--;
		m_pCurrent->m_eState = STATE_CHILD;
		break;
	case SYMBOL_OP_END:
		pos--;
		m_pCurrent->m_eState = STATE_PARENT;
		break;
	case SYMBOL_COMMA:
		pos--;
		m_pCurrent->m_eState = STATE_BROTHER;
		break;
	case SYMBOL_UNKNOWN:
		return ERROR_SYMBOL;
		break;
	default:
		return ERROR_BUF_END;
		break;
	}
	
	return err;
}

//##ModelId=4B050E2F02EB
enum EERROR CMyExpression::Identify_STATE_BROTHER(const string &m_sExpr, string::const_iterator & pos,CMyExpression* &m_pCurrent)
{
	EERROR err = SUCCESS;

	if(!m_pCurrent->m_pParent)
		return ERROR_BROTHER;
	
	CMyExpression * pExpr =  new CMyExpression(m_pCurrent->m_pParent);
	
	m_pCurrent->m_pParent->m_vChild.push_back(pExpr);

//	this->m_eState = STATE_BUF_END;

	m_pCurrent = pExpr;
	
//	pExpr->Identify(m_sExpr,pos);
		
	return err;
}

//##ModelId=4B068C6D0203
enum EERROR CMyExpression::Identify_STATE_CHILD(const string &m_sExpr, string::const_iterator &   pos,CMyExpression* &m_pCurrent)
{
	EERROR err = SUCCESS;
	
	CMyExpression * pExpr =  new CMyExpression(m_pCurrent);
	
	m_pCurrent->m_vChild.push_back(pExpr);

	//this->m_eState = STATE_BUF_END;
	
	//pExpr->Identify(m_sExpr,pos);

	m_pCurrent = pExpr;
		
	return err;
}

//##ModelId=4B068E88004E
enum EERROR CMyExpression::Identify_STATE_PARENT(const string &m_sExpr, string::const_iterator &   pos,CMyExpression* &m_pCurrent)
{
	EERROR err = SUCCESS;
	
	switch(m_pParent->GetSymbolType(pos))
	{
	case SYMBOL_BLANK:
		break;
	case SYMBOL_OP_END:
		{
				CMyExpression * pParent = m_pCurrent->m_pParent;

				if(! pParent)
					return ERROR_OP_END;
				
				//pParent = pParent->m_pParent;
				if(pParent->m_eState != STATE_CHILD )
					return ERROR_OP_END;

				pParent->m_eState = STATE_PARENT;

				m_pCurrent = pParent;
		}
		break;
	case SYMBOL_COMMA:
		pos--;
		m_pCurrent->m_eState = STATE_BROTHER;
		break;
	case SYMBOL_UNKNOWN:
		return ERROR_SYMBOL;
		break;
	default:
		return ERROR_PARENT;
		break;
	}
	

		
	return err;
}

//##ModelId=4B06B2190177
//enum EERROR Identify_STATE_END(const string &sExpr, string::const_iterator & pos)
enum EERROR CMyExpression::Identify_STATE_END(const string &m_sExpr, string::const_iterator & pos,CMyExpression *& m_pCurrent)
{
	EERROR err = SUCCESS;

	//如果当前节点状态为 BEGIN,则应该报错

	//如果当前节点状态为 READING,则父节点必须为空

	//如果当前节点状态为 END,则父节点必须为空

	//如果当前节点状态为 CHILD,PARENT

	//如果当前节点状态为 BROTHER


	return err;
}


string & CMyExpression::Print(string &a,const string & idt)
{
	static int si = 0 ;

	string indent;

	for(int j=0;j<si;j++) 
	{
		indent += idt;
	}

	a +=  indent +"[" + m_sName+ "]\r\n";

	for(int i=0;i<m_vChild.size();i++)
	{
	si++;
		m_vChild.at(i)->Print(a,idt);
	si--;
	}

	return a;
}

string CMyExpression::Execute(CMyWorker *pWorker)
{
	string res("NULL");

	

	if(m_vChild.size() == 0)
	{
		// {{20170428 this will make data tye change ,such as int to string ,or the others
			/*CMyAny tmpAny;
			if((int)pWorker->FetchVarValue(m_sName,tmpAny) == 0)
			{
				res = (string &)tmpAny;		
			}*/
		res = m_sName;
		// }}
	}
	else
	{
		vector<string > m_vPara;

		string eleRes;
		for(int i=0;i<m_vChild.size();i++)
		{
			if(m_vChild.at(i)->m_vChild.size() != 0)
			{
				eleRes = m_vChild.at(i)->Execute(pWorker);
			}
			else
			{
				eleRes = m_vChild.at(i)->m_sName;
			}
			m_vPara.push_back(eleRes);
		}

		res = pWorker->Call(m_sName,m_vPara);
	}

	return res;
}
