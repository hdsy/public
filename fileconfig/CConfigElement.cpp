// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#include "CConfigElement.h"

//##ModelId=4C0F11E1006C
MyConfig::CConfigElement::CConfigElement()
	:m_sName(""),m_sFormat(""),m_sChecker("null"),m_sTranslator("null"),m_sDesc("")
{
}


//##ModelId=4C0F11E1009B
MyConfig::CConfigElement::~CConfigElement()
{
}

//##ModelId=4C0F12170178
MyConfig::CConfigElement::CConfigElement(const std::string &inName, const std::string &inFormat, const std::string &inChecker, const std::string &inTranslator, const std::string &inDesc)
	:m_sName(inName),m_sFormat(inFormat),m_sChecker(inChecker),m_sTranslator(inTranslator),m_sDesc(inDesc)
{
}


//##ModelId=4C0F39D10236
std::string const& MyConfig::CConfigElement::GetChecker() const
{
    return m_sChecker;
}


//##ModelId=4C0F39D10284
void MyConfig::CConfigElement::SetChecker(std::string& left)
{
    m_sChecker = left;
}


//##ModelId=4C0F39D1033F
std::string const& MyConfig::CConfigElement::GetDesc() const
{
    return m_sDesc;
}


//##ModelId=4C0F39D1038D
void MyConfig::CConfigElement::SetDesc(std::string& left)
{
    m_sDesc = left;
}


//##ModelId=4C0F39D20070
std::string const& MyConfig::CConfigElement::GetFormat() const
{
    return m_sFormat;
}


//##ModelId=4C0F39D200CE
void MyConfig::CConfigElement::SetFormat(std::string& left)
{
    m_sFormat = left;
}


//##ModelId=4C0F39D201A9
std::string const& MyConfig::CConfigElement::GetName() const
{
    return m_sName;
}


//##ModelId=4C0F39D20207
void MyConfig::CConfigElement::SetName(std::string& left)
{
    m_sName = left;
}


//##ModelId=4C0F39D202E1
std::string const& MyConfig::CConfigElement::GetTranslator() const
{
    return m_sTranslator;
}


//##ModelId=4C0F39D2034F
void MyConfig::CConfigElement::SetTranslator(std::string& left)
{
    m_sTranslator = left;
}


