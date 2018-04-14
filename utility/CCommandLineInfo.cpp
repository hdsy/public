// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#include "CCommandLineInfo.h"

static const char * pszSwitchOn = "on";
//static const char * pszSwitchOff = "off";


std::string MyUtility::CCommandLineInfo::GetPrompt()
{
	CStringMap t_mss;
	
	CStringMap::const_iterator iterAliasName;
	CStringMap::iterator iter;
	
	for(iterAliasName = m_mAlias2Name.begin(); iterAliasName != m_mAlias2Name.end();iterAliasName++)
	{
		t_mss[iterAliasName->second] += iterAliasName->first + " \t";
	}
	
	for(iter = t_mss.begin(); iter != t_mss.end();iter++)
	{
		iter->second += "\r\n\t" + m_mName2Desc[iter->first];
		iter->second += "\r\n\t" + m_mName2Default[iter->first];
		
		if(m_mNameSingle[iter->first] == true)
			iter->second += "\r\n\t single" ;
	}
	
	return t_mss.Join("\r\n",":");
	
}

//##ModelId=4C0CA4C903C8
void MyUtility::CCommandLineInfo::AddEntry(const std::string &inName, const std::string &inAlias, const std::string &inDefault, bool inSingle, bool inFlag,const std::string &inDesc)
{
	if(inFlag)
		m_sDefaultName = inName;
	
	m_mAlias2Name[inAlias] = inName;
	
	m_mName2Default[inName] = inDefault;
	
	m_mNameSingle[inName] = inSingle;
	
	m_mName2Desc[inName] = inDesc;
}

//##ModelId=4C0CAF4D0156
void MyUtility::CCommandLineInfo::Clear()
{
	m_sDefaultName = "";
	
	m_mAlias2Name.clear();
	
	m_mName2Default.clear();
	
}

//##ModelId=4C0CAF7601C5
const std::string MyUtility::CCommandLineInfo::GetArgVal(const std::string &inName)
{
	return GetArgVal(inName,0);
}

//##ModelId=4C0CB0D502FC
int MyUtility::CCommandLineInfo::GetArgSize(const std::string &inName)
{
	CStringVectorMap::const_iterator iterV;
	
	iterV = m_mvNameVal.find(inName);
	
	int result = 0;
	
	
	if(iterV != m_mvNameVal.end())
	{
		result =  iterV->second.size();
	}
	
	return result;
}

//##ModelId=4C0CB10400BC
const std::string MyUtility::CCommandLineInfo::GetArgVal(const std::string &inName, int inIndex)
{
	CStringVectorMap::const_iterator iterV;
	
	iterV = m_mvNameVal.find(inName);
	
	std::string result = "";
	
	if(iterV != m_mvNameVal.end())
	{
		if(iterV->second.size() > (unsigned int )inIndex )
		{
			result = iterV->second.at(inIndex);
		}		
	}
	else
	{
		CStringMap::const_iterator iter;
		iter = m_mName2Default.find(inName);
		if(iter != m_mName2Default.end())
		{
			result = iter->second;
		}
	}
	
	return result;
}
const std::string &MyUtility::CCommandLineInfo::GetBinDir()
{
	return m_sBinDir;
}
const std::string &MyUtility::CCommandLineInfo::GetCnfDir()
{
	return m_sCnfDir;
}
const std::string &MyUtility::CCommandLineInfo::GetLogDir()
{
	return m_sLogDir;
}
const std::string &MyUtility::CCommandLineInfo::GetTmpDir()
{
	return m_sTmpDir;
}
const std::string &MyUtility::CCommandLineInfo::GetDatDir()
{
	return m_sDatDir;
}
const std::string &MyUtility::CCommandLineInfo::GetLibDir()
{
	return m_sLibDir;
}
const std::string &MyUtility::CCommandLineInfo::GetExePath()
{
	return m_sExePath;
}
const std::string &MyUtility::CCommandLineInfo::GetExeName()
{
	return m_sExeName;
}
const std::string &MyUtility::CCommandLineInfo::GetCmdLine()
{
	return m_sExec;
}
//##ModelId=4C0CBCF502DE
int MyUtility::CCommandLineInfo::MatchName(const std::string &inDat, std::string & outName, std::string & outValue)
{
	int result = 0;
	
	//std::string tmp;
	
	CStringMap::const_iterator iter;
	
	iter = m_mAlias2Name.begin();
	
	while(iter != m_mAlias2Name.end())
	{
		//tmp = string("--")+iter->first+string("=");
		
		if(inDat.find(iter->first) == 0)
		{
			outName = iter->second;		
			result = 1;
			if(inDat.size() > iter->first.size() )
			{
				outValue = inDat.substr(iter->first.size());
				result = 2;
			}
			else
			{
				if(m_mNameSingle[outName] == true)
				{
					outValue = pszSwitchOn;
					result = 2;
				}
			}
		}
		
		iter++;
	}
	
	if((result == 0)&&(m_sDefaultName != "" ))
	{
		result = 2;
		outName = m_sDefaultName;
		outValue = inDat;
	}
	
	return result;
	
}

void MyUtility::CCommandLineInfo::AddValue(const std::string & inName, const std::string & inValue)
{
	CStringVectorMap::iterator iterV;
	
	CStringVector tmpV;
	
	iterV = m_mvNameVal.find(inName);
		
	if(iterV != m_mvNameVal.end())
	{
		iterV->second.push_back(inValue);
	}
	else
	{
		tmpV.push_back(inValue);
		
		m_mvNameVal.insert(CStringVectorMap::value_type(inName,tmpV));
	}
}



//##ModelId=4C0CB2BA0280
int MyUtility::CCommandLineInfo::Parse(int argc, const char ** argv)
{
	std::string n,v;
	
	int tmp,state = 0; // 1 vale 0 name
	
	if(argc == 0)
		return 0;
		
	string t_sAgrv0 = argv[0];
	
	
	//
	if(t_sAgrv0.at(0) == '/')
	{
		m_sExec = t_sAgrv0;
	}
	else 
	{
		m_sExec  = get_current_dir_name();
		m_sExec += "/";
		m_sExec += t_sAgrv0;
	}
	
	
	MyUtility::CStringVector vs,vs1;
	
	vs.Split(m_sExec,"/");
	
	for(int i=0;i<vs.size();i++)
	{
		if(vs[i] == "..") i++;
		else if(vs[i] == ".") continue;
		else vs1.push_back(vs[i]);
	}
	
	m_sExePath = "/" + vs1.Join("/");
	
	m_sExeName = vs1.back();	vs1.pop_back();
	
	if((vs1.size() >= 1) && (vs1.back() == "bin")) 
	{
		vs1.pop_back();
		
		m_sBinDir = "/" + vs1.Join("/") + "/bin/";
		m_sCnfDir = "/" + vs1.Join("/") + "/cnf/";
		m_sLogDir = "/" + vs1.Join("/") + "/log/";
		m_sTmpDir = "/" + vs1.Join("/") + "/tmp/";
		m_sDatDir = "/" + vs1.Join("/") + "/dat/";
		m_sLibDir = "/" + vs1.Join("/") + "/lib/";
	}
	else
	{
		m_sTmpDir = m_sBinDir = m_sLogDir = m_sCnfDir = "./";
	}
	
	//////////////...........................................................
	
	for( int i =1; i < argc ;  i++)
	{
		m_sExec += " ";
		m_sExec += argv[i];
		switch(state)
		{
		case 0 :// name
		{
			tmp = MatchName(argv[i],n,v);
			if(2 == tmp)
			{
				AddValue(n,v);
			}
			else if(1 == tmp)
			{
				state = 1;
			}
			else
				;
			
		}break;
		case 1://value
		{
			AddValue(n,argv[i]);
			
			state = 0;
		}break;
		}
		
		
	}
	
	return m_mvNameVal.size();
}

//##ModelId=4C0CB2FD007F
MyUtility::CCommandLineInfo::CCommandLineInfo()
{
}


//##ModelId=4C0CB2FD00AD
MyUtility::CCommandLineInfo::~CCommandLineInfo()
{
	Clear();
}

namespace MyUtility {
MyUtility::CCommandLineInfo g_objCCommandLineInfo;
};

