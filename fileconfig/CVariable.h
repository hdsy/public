// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#ifndef CVARIABLE_H_HEADER_INCLUDED_B3F0A987
#define CVARIABLE_H_HEADER_INCLUDED_B3F0A987

#include "mysoft_config.h"

namespace MyConfig {

//##ModelId=4BF6674F01F1
class CVariable
{
  public:
    //##ModelId=4C0F120F02CF
    CVariable();

    //##ModelId=4C0F120F030E
    virtual ~CVariable();

	CVariable& operator=(const CVariable& right)
	{
		m_sName = right.m_sName;
		m_sDesc = right.m_sDesc;
		m_sValue = right.m_sValue;
		
		return *this;
	};

    //##ModelId=4C0F1F23029E
    CVariable(const std::string &inName, const std::string &inValue, const std::string &inDesc = "");

    //##ModelId=4C0F39B70215
    std::string const& GetDesc() const;

    //##ModelId=4C0F39B70254
    void SetDesc(std::string& left);

    //##ModelId=4C0F39B70300
    std::string const& GetName() const;

    //##ModelId=4C0F39B7034E
    void SetName(std::string& left);

    //##ModelId=4C0F39B80012
    std::string const& GetValue() const;

    //##ModelId=4C0F39B80060
    void SetValue(std::string& left);

    //##ModelId=4C0C5D7200B9
    std::string m_sName;

    //##ModelId=4C0C5D74030A
    std::string m_sValue;

    //##ModelId=4C0C5D77033A
    std::string m_sDesc;

};

} // namespace MyConfig



#endif /* CVARIABLE_H_HEADER_INCLUDED_B3F0A987 */
