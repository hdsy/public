// author      :  gaussgao
// create date :  2011-03-02
// modify date :  2011-03-02
// descriptor  :  qzone feeds format dll  

#include "CLinuxDll.h"
#include <dlfcn.h>

#include "CStringVector.h"

//##ModelId=4D6EF98001A2
int CLinuxDll::Load(const std::string & inDir, const std::string &inMatch)
{
	int ret = 0;
	void * m_dlib;
	std::string fname;
	
	FILE *dl;	//list all *trans.so in fdir	
	
	char szCmd[1024],szRes[1024];
	memset(szCmd,0,sizeof(szCmd));
	memset(szRes,0,sizeof(szRes));
	
	sprintf(szCmd,"ls -1 %s/%s 2>/dev/null ",inDir.c_str(),inMatch.c_str());
	
	
	dl = popen(szCmd, "r"); 
	if(!dl)
	{
		ret = -1;return ret;
	}
	while(fgets(szRes, sizeof(szRes), dl))
	{
		char *ws = strpbrk(szRes, " \t\n"); 
		if(ws) *ws = '\0';
		fname = /*fdir + "/" +*/ std::string(szRes);
		std::map<std::string, void *, less<std::string> >::iterator iter ;
		iter = m_mdlib.find(fname);	
		if(iter != m_mdlib.end()) 
		{
			continue;
		}
		m_dlib = dlopen(fname.c_str(), RTLD_NOW );
		if(NULL != m_dlib)
		{
			MyUtility::CStringVector vs;
			vs.Split(fname,"/");
			
			m_mdlib[vs[vs.size()-1]] = m_dlib;
		}
		else
		{
			m_sLastError +="\r\n load file :" +fname + dlerror();
		}
	}
	pclose(dl);
	return ret;
}

//##ModelId=4D6EFA6C0062
int CLinuxDll::Free(const std::string & inFileName)
{
	int ret = 0;
	
	map<string, void *>::iterator p;
	
	if(inFileName == "all")
	{					
		
		for(p = m_mdlib.begin();p != m_mdlib.end();p++)
		{
			if(p->second != NULL)		
			{
				dlclose(p->second);
				p->second = NULL;
			}
		}
		
		m_mdlib.clear();
		
	}
	else
	{
		p = m_mdlib.find(inFileName);
		
		if(p != m_mdlib.end())
		{
			dlclose(p->second);
			p->second = NULL;
			
			m_mdlib.erase (p);
		}
	}
	return ret;
}

//##ModelId=4D6EFB51026A
CLinuxDll::CLinuxDll()
{
	m_sLastError = "";
}


//##ModelId=4D6EFB51028C
CLinuxDll::~CLinuxDll()
{
	Free("all");
}

int CLinuxDll::GenSymbolMap(const std::string & inFunctionName)
{
	int ret = 0;

	void * m_sym;
	
	map<string, void *>::iterator p;
	
	for(p=m_mdlib.begin();p != m_mdlib.end();p++)
	{
		if(p->second != NULL)		
		{
			m_sym = dlsym(p->second,inFunctionName.c_str());
			
			if(NULL != m_sym)
			{
				m_msym[p->first] = m_sym;
				ret++;
			}
		}			
		
	}

	return ret;
}

 void * CLinuxDll::GetSymbol(const std::string & inSoName)
{
	void * res = NULL;

	map<string, void *>::iterator p;

	p = m_msym.find(inSoName);

	if(p !=  m_msym.end())
		res = p->second;

	return res;
}

 void CLinuxDll::Dump(std::string & ostr)
{
	map<string, void *>::iterator p;

	ostr = "Loaded dll filename list:\r\n";
	for(p=m_mdlib.begin();p != m_mdlib.end();p++)
	{
		ostr += "\t" + p->first + "\r\n";
	}

	
	ostr += "Loaded dll symbol  filename list:\r\n";
	for(p=m_msym.begin();p != m_msym.end();p++)
	{
		ostr += "\t" + p->first + "\r\n";
	}

	ostr += "Last Error in Loading :\r\n";
	ostr += m_sLastError;
	ostr += "\r\n";
}

CLinuxDll g_CLinuxDll;

