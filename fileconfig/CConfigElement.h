// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#ifndef CConfigElement_H_HEADER_INCLUDED_B3F0A54D
#define CConfigElement_H_HEADER_INCLUDED_B3F0A54D

#include "mysoft_config.h"

namespace MyConfig {

//##ModelId=4C0C5D0D0085
class CConfigElement
{
  public:
    //##ModelId=4C0F11E1006C
    CConfigElement();

    //##ModelId=4C0F11E1009B
    virtual ~CConfigElement();

    //##ModelId=4C0F12170178
    CConfigElement(const std::string &inName, const std::string &inFormat = "", const std::string &inChecker = "reg:single", const std::string &inTranslator = "null", const std::string &inDesc = "");

    //##ModelId=4C0F39D10236
    std::string const& GetChecker() const;

    //##ModelId=4C0F39D10284
    void SetChecker(std::string& left);

    //##ModelId=4C0F39D1033F
    std::string const& GetDesc() const;

    //##ModelId=4C0F39D1038D
    void SetDesc(std::string& left);

    //##ModelId=4C0F39D20070
    std::string const& GetFormat() const;

    //##ModelId=4C0F39D200CE
    void SetFormat(std::string& left);

    //##ModelId=4C0F39D201A9
    std::string const& GetName() const;

    //##ModelId=4C0F39D20207
    void SetName(std::string& left);

    //##ModelId=4C0F39D202E1
    std::string const& GetTranslator() const;

    //##ModelId=4C0F39D2034F
    void SetTranslator(std::string& left);

    // 元素的名字
    //##ModelId=4C0C5D2403C2
    std::string m_sName;

    // 与检查工具一起工作
    //##ModelId=4C0C5D310009
    std::string m_sFormat;

    // 参数格式检查，预定义如下检查类型：
    // 
    // null 不检查
    // checker:single 单值独立检查
    // checker:complex 多值联合检查
    // 
    // CChecker* pCChecker =
    //      CChecker::CreateHander(checker);
    // 
    // 如果是单值
    // pCChecker->DoSingle(value_of_element);
    // 如果是多值
    // pCChecker->DoComplex(
    //   value_of_element,
    //   map_of_parameter);
    // 
    // 
    // 已经实现的就是一个基于正则表达式的单值检查
    // reg:single
    //##ModelId=4C0C5D3902C9
    std::string m_sChecker;

    // 预定义的转换器：
    // 
    // null 不做转换
    // translator:single 单值检查
    // translator:complex 多值检查
    // 
    // CTranslator* pCurTranslator =
    //      CTranslator::CreateHander(translator);
    // 
    // 如果是单值
    // pCurTranslator->DoSingle(value_of_element);
    // 如果是多值
    // pCurTranslator->DoComplex(
    //   value_of_element,
    //   map_of_parameter);
    //##ModelId=4C0C5D430078
    std::string m_sTranslator;

    // 元素的描述
    //##ModelId=4C0C5D350038
    std::string m_sDesc;

};

} // namespace MyConfig



#endif /* CConfigElement_H_HEADER_INCLUDED_B3F0A54D */
