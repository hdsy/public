// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#include "CParamerter.h"

//##ModelId=4C0F12090000
MyConfig::CParameter::CParameter()
	:m_sName(""),m_sInExistMode(""),m_sOutExistMode(""),m_sDefault(""),m_sDesc("")
{
}


//##ModelId=4C0F1209003F
MyConfig::CParameter::~CParameter()
{
}

//##ModelId=4C0F1EA802F9
MyConfig::CParameter::CParameter(const std::string &inName, const std::string &inInMode, const std::string &inOutMode, const std::string &inDefault, const std::string &inDesc)
	:m_sName(inName),m_sInExistMode(inInMode),m_sOutExistMode(inOutMode),m_sDefault(inDefault),m_sDesc(inDesc)
{
}


//##ModelId=4C0F39A10244
std::string const& MyConfig::CParameter::GetDefault() const
{
    return m_sDefault;
}


//##ModelId=4C0F39A10292
std::string const& MyConfig::CParameter::GetDesc() const
{
    return m_sDesc;
}


//##ModelId=4C0F39A102F0
std::string const& MyConfig::CParameter::GetInExistMode() const
{
    return m_sInExistMode;
}


//##ModelId=4C0F39A1033E
std::string  const& MyConfig::CParameter::GetName() const
{
    return m_sName;
}


//##ModelId=4C0F39A1039B
std::string const& MyConfig::CParameter::GetOutExistMode() const
{
    return m_sOutExistMode;
}


//##ModelId=4C0F39C1039C
void MyConfig::CParameter::SetDefault(std::string& left)
{
    m_sDefault = left;
}


//##ModelId=4C0F39C20080
void MyConfig::CParameter::SetDesc(std::string& left)
{
    m_sDesc = left;
}


//##ModelId=4C0F39C2016A
void MyConfig::CParameter::SetInExistMode(std::string& left)
{
    m_sInExistMode = left;
}


//##ModelId=4C0F39C20245
void MyConfig::CParameter::SetName(std::string &left)
{
    m_sName = left;
}


//##ModelId=4C0F39C2031F
void MyConfig::CParameter::SetOutExistMode(std::string& left)
{
    m_sOutExistMode = left;
}


