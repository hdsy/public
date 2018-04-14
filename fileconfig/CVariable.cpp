// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#include "CVariable.h"

//##ModelId=4C0F120F02CF
MyConfig::CVariable::CVariable()
	:m_sName(""),m_sValue(""),m_sDesc("")
{
}


//##ModelId=4C0F120F030E
MyConfig::CVariable::~CVariable()
{
}

//##ModelId=4C0F1F23029E
MyConfig::CVariable::CVariable(const std::string &inName, const std::string &inValue, const std::string &inDesc)
	:m_sName(inName),m_sValue(inValue),m_sDesc(inDesc)
{
}


//##ModelId=4C0F39B70215
std::string const& MyConfig::CVariable::GetDesc() const
{
    return m_sDesc;
}


//##ModelId=4C0F39B70254
void MyConfig::CVariable::SetDesc(std::string& left)
{
    m_sDesc = left;
}


//##ModelId=4C0F39B70300
std::string const& MyConfig::CVariable::GetName() const
{
    return m_sName;
}


//##ModelId=4C0F39B7034E
void MyConfig::CVariable::SetName(std::string& left)
{
    m_sName = left;
}


//##ModelId=4C0F39B80012
std::string const& MyConfig::CVariable::GetValue() const
{
    return m_sValue;
}


//##ModelId=4C0F39B80060
void MyConfig::CVariable::SetValue(std::string& left)
{
    m_sValue = left;
}


