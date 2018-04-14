// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#ifndef CATTRIBUTE_H_HEADER_INCLUDED_B62B12BA
#define CATTRIBUTE_H_HEADER_INCLUDED_B62B12BA

#include "mysoft_html.h"
#include "CBase.h"

//##ModelId=49CC7BE70138
class CAttribute : public CBase
{
  public:
	  bool IsEqual(const string &n,const string &v,int mode = 1);
	  CAttribute(const string & sn,const string & sv):m_sName(sn),m_sValue(sv),m_iType(1){};
	  CAttribute(const string & sn):m_sName(sn),m_sValue(""),m_iType(2){};
    // 将对象转换为string
    //##ModelId=49D089B10290
    virtual string ToString() const;

  
	void AddValue(const string & v)
	{
		m_sValue = v;
		m_iType = 1;
	}

	const string & GetName()
	{
		return m_sName;
	}
	const string & GetValue()
	{
		return m_sValue;
	}
	int GetType()
	{
		return m_iType;
	}

  private:
    // 属性名
    //##ModelId=49CC7D490000
    std::string m_sName;

    // 属性值，单值时始终为TRUE
    //##ModelId=49CC7D5303A9
    std::string m_sValue;

    // 1 双值。通过=号赋值
    // 2 单值。如enabel
    //##ModelId=49CC7D5802EE
    int m_iType;

};



#endif /* CATTRIBUTE_H_HEADER_INCLUDED_B62B12BA */
