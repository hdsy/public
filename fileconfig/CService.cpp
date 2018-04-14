// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#include "CService.h"

static  MyConfig::CVariable varBlank;
static  MyConfig::CVariableVector varVectorBlank;
static  MyConfig::CParameter paraBlank;

//##ModelId=4C0F11E8030D
MyConfig::CService::CService()
	:m_sName(""),m_sType(""),m_sDesc("")
{
	m_mvParameter.clear();
	m_mvVariable.clear();
}


//##ModelId=4C0F11E8034B
MyConfig::CService::~CService()
{
}

//##ModelId=4C0F33A302EE
MyConfig::CService::CService(const std::string &inName, const std::string &inType, const std::string &inDesc)
	:m_sName(inName),m_sType(inType),m_sDesc(inDesc)
{
	m_mvParameter.clear();
	m_mvVariable.clear();
}


//##ModelId=4C0F342B02DA
const std::string &MyConfig::CService::GetVarVal(const std::string &inName) const
{
	const MyConfig::CVariable  *res = &varBlank;
	
	MyConfig::CVariableVectorMap::const_iterator iter = m_mvVariable.find(inName);
	
	if(m_mvVariable.end() != iter )
	{
		if(iter->second.size() != 0)
			res = &iter->second.at(0);
	}
	
	return res->GetValue();
}

//##ModelId=4C0F347F007D
const MyConfig::CParameter &MyConfig::CService::GetParaObj(const std::string &inName) const
{
	const MyConfig::CParameter * res =&paraBlank;
	
	MyConfig::CParameterVectorMap::const_iterator iter = m_mvParameter.find(inName);
	
	if(m_mvParameter.end() != iter )
	{
		if(iter->second.size() != 0)
			res = &iter->second.at(0);
	}
	
	return *res;
}

//##ModelId=4C0F34B900C3
const MyConfig::CVariable &MyConfig::CService::GetVarObj(const std::string &inName) const
{
	const MyConfig::CVariable *res = &varBlank;
	
	MyConfig::CVariableVectorMap::const_iterator iter = m_mvVariable.find(inName);
	
	if(m_mvVariable.end() != iter )
	{
		if(iter->second.size() != 0)
			res = &iter->second.at(0);
	}
	
	return *res;
}
const MyConfig::CVariableVector &MyConfig::CService::GetVarVectorObj(const std::string &inName) const
{
	const MyConfig::CVariableVector *res = &varVectorBlank;
	
	MyConfig::CVariableVectorMap::const_iterator iter = m_mvVariable.find(inName);
	
	if(m_mvVariable.end() != iter )
	{
		if(iter->second.size() != 0)
			res = &iter->second;
	}
	
	return *res;
}

//##ModelId=4C0F39E90284
std::string const& MyConfig::CService::GetDesc() const
{
    return m_sDesc;
}


//##ModelId=4C0F39E902D3
void MyConfig::CService::SetDesc(std::string& left)
{
    m_sDesc = left;
}


//##ModelId=4C0F39E9038E
std::string const& MyConfig::CService::GetName() const
{
    return m_sName;
}


//##ModelId=4C0F39E903DC
void MyConfig::CService::SetName(std::string& left)
{
    m_sName = left;
}


//##ModelId=4C0F39EA00BF
std::string const& MyConfig::CService::GetType() const
{
    return m_sType;
}


//##ModelId=4C0F39EA011D
void MyConfig::CService::SetType(std::string& left)
{
    m_sType = left;
}

/*
//##ModelId=4C0F39FD0043
const MyConfig::CParameterMap & MyConfig::CService::GetParameterMap() const
{
    return m_mParameter;
}


//##ModelId=4C0F39FD00B0
const MyConfig::CVariableMap & MyConfig::CService::GetVariableMap() const
{
    return m_mVariable;
}

//##ModelId=4C0F39FD0043
MyConfig::CParameterMap & MyConfig::CService::GetParameterMap() 
{
    return m_mParameter;
}


//##ModelId=4C0F39FD00B0
MyConfig::CVariableMap & MyConfig::CService::GetVariableMap() 
{
    return m_mVariable;
}

//*/

const MyConfig::CParameterVectorMap & MyConfig::CService::GetParameterVectorMap() const
{
    return m_mvParameter;
}


//##ModelId=4C0F39FD00B0
const MyConfig::CVariableVectorMap & MyConfig::CService::GetVariableVectorMap() const
{
    return m_mvVariable;
}

//##ModelId=4C0F39FD0043
MyConfig::CParameterVectorMap & MyConfig::CService::GetParameterVectorMap() 
{
    return m_mvParameter;
}


//##ModelId=4C0F39FD00B0
MyConfig::CVariableVectorMap & MyConfig::CService::GetVariableVectorMap() 
{
    return m_mvVariable;
}
