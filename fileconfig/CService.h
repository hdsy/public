// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#ifndef CSERVICECONFIG_H_HEADER_INCLUDED_B3F0E9B4
#define CSERVICECONFIG_H_HEADER_INCLUDED_B3F0E9B4

#include "mysoft_config.h"
#include "CParamerter.h"
#include "CParameterMap.h"
#include "CVariable.h"
#include "CVariableMap.h"

namespace MyConfig {

//##ModelId=4BF664ED0366
class CService
{
  public:
    //##ModelId=4C0F11E8030D
    CService();

    //##ModelId=4C0F11E8034B
    virtual ~CService();

    //##ModelId=4C0F33A302EE
    CService(const std::string &inName, const std::string &inType, const std::string &inDesc);

    // 取根据变量名取变量值
    //##ModelId=4C0F342B02DA
    const std::string &GetVarVal(const std::string &inName) const;

    // 根据参数名，取参数对象
    //##ModelId=4C0F347F007D
    const CParameter &GetParaObj(const std::string &inName) const;

    // 取根据变量名取变量对象
    //##ModelId=4C0F34B900C3
    const CVariable &GetVarObj(const std::string &inName) const;
    const CVariableVector &GetVarVectorObj(const std::string &inName) const;

    //##ModelId=4C0F39E90284
    std::string const& GetDesc() const;

    //##ModelId=4C0F39E902D3
    void SetDesc(std::string& left);

    //##ModelId=4C0F39E9038E
    std::string const& GetName() const;

    //##ModelId=4C0F39E903DC
    void SetName(std::string& left);

    //##ModelId=4C0F39EA00BF
    std::string const& GetType() const;

    //##ModelId=4C0F39EA011D
    void SetType(std::string& left);
/*
    //##ModelId=4C0F39FD0043
    const CParameterMap & GetParameterMap() const;
    CParameterMap & GetParameterMap() ;
    //##ModelId=4C0F39FD00B0
    const CVariableMap & GetVariableMap() const;
    CVariableMap & GetVariableMap() ;
	
//*/    
    const CParameterVectorMap & GetParameterVectorMap() const;
    CParameterVectorMap & GetParameterVectorMap() ;

	
    const CVariableVectorMap & GetVariableVectorMap() const;
    CVariableVectorMap & GetVariableVectorMap() ;

    //##ModelId=4C0C5F2B0358
    std::string m_sName;

    //##ModelId=4C0F325B005E
    std::string m_sType;

    //##ModelId=4C0C5F4A03A7
    std::string m_sDesc;

    //##ModelId=4C0C60390030
    //CParameterMap m_mParameter;
    CParameterVectorMap m_mvParameter;

    //##ModelId=4C0C6042015A
    //CVariableMap m_mVariable;
    CVariableVectorMap m_mvVariable;

};

} // namespace MyConfig



#endif /* CSERVICECONFIG_H_HEADER_INCLUDED_B3F0E9B4 */
