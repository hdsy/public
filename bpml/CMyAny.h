// ***********************************************
// 
// 创建日期： 2009-11-18
// 
// 作    者： gaoyong
// 
// 电子邮件： gaoyong@my-soft.net.cn
// 
// 主要功能： 实现对html文件的格式化输出，以及类似
// 
//            BPEL的流程控制。
// 
// ***********************************************

#ifndef MYFLOW_CMYANY_H_HEADER_INCLUDED_B4F4DCAC
#define MYFLOW_CMYANY_H_HEADER_INCLUDED_B4F4DCAC
#pragma warning(disable:4786)
#include "myflow_macro.h"

#include <map>

#include <vector>

#include <string>
class CMyAny;

using namespace std;




// 数据类型，类似CORBA中any的定义，以及COM中VARIANT的定义。
// 
// 用以统一表示支持的变量类型。目前计划支持的有
// int
// string
// CHtml *
// CElement * 
//##ModelId=4B0B50A80117

#include "CHtml.h"
#include "CElement.h"

#include "EVarType.h"
class CMyAny
{
	static map <void * ,int>  m_mPtrRefCnt;

	void Release()
	{
		switch(GetType())
		{
		case VT_P_CHTML:
			{
				m_mPtrRefCnt[m_pCHtml]--;

				if(m_mPtrRefCnt[m_pCHtml] <= 0)
				{
					m_mPtrRefCnt.erase(m_pCHtml);
					delete m_pCHtml;
					m_pCHtml = NULL;
				}
			}
			break;
		case VT_P_CELEMENT:
			{
				m_mPtrRefCnt[m_pCElement]--;

				if(m_mPtrRefCnt[m_pCElement] <= 0)
				{
					m_mPtrRefCnt.erase(m_pCElement);					
					//delete m_pCElement;
					m_pCElement = NULL;
	
				}
			}
			break;
		case VT_P_CNODE:
			{
				m_mPtrRefCnt[m_pCNode]--;

				if(m_mPtrRefCnt[m_pCNode] <= 0)
				{
					m_mPtrRefCnt.erase(m_pCNode);					
					//delete m_pCElement;
					m_pCNode = NULL;
	
				}
			}
			break;
		}
	}
	void AddRef()
	{
		switch(GetType())
		{
		case VT_P_CHTML:
			{
				m_mPtrRefCnt[m_pCHtml]++;
			}
			break;
		case VT_P_CNODE:
			{
				m_mPtrRefCnt[m_pCNode]++;
			}
			break;
		case VT_P_CELEMENT:
			{
				m_mPtrRefCnt[m_pCElement]++;
			}
			break;
		}
	}

	void Init()
	{	
		m_int = 0;
		m_double = 0.0;
		m_string = "";
		m_pCHtml = NULL;
		m_pCElement = NULL;
		m_pCNode = NULL;
	};
  public:
    // 类型转换函数，将any转换为int
    //##ModelId=4B0B566E00F4
     operator int();
     operator double();

    // 类型转换函数，将any转换为string
    //##ModelId=4B0B567B02F8
    operator string &();
    operator CStringVector &();	
    operator CStringMap &();	
    operator CStringVectorMap &();	

    // 类型转换函数，将any转换为CHtml*
    //##ModelId=4B0B56830104
    operator CHtml* ();
    // 类型转换函数，将any转换为CElement *
    //##ModelId=4B0B57F802BC
    operator CElement* ();
    operator CNode* ();
    //##ModelId=4B0B59AF0156
    CMyAny();


    //##ModelId=4B0B59AF0165
    CMyAny(const CMyAny& right);

  
    //##ModelId=4B0B59AF01C3
    virtual ~CMyAny();

  
    //##ModelId=4B0B59AF01E3
    CMyAny& operator=(const CMyAny& right);

  
    //##ModelId=4B0B59AF0250
    int operator==(const CMyAny& right);

  
    //##ModelId=4B0B59AF02BD
    int operator!=(const CMyAny& right);

  
    //##ModelId=4B0B59AF032A
    int operator<(const CMyAny& right);

  
    //##ModelId=4B0B59AF03C7
    int operator<=(const CMyAny& right);

  
    //##ModelId=4B0B59B000C9
    int operator>(const CMyAny& right);

  
    //##ModelId=4B0B59B00136
    int operator>=(const CMyAny& right);
    //##ModelId=4B0B68720286
    CMyAny(
        // 初始化int类型的数据
        int intVal);
    CMyAny(
        // 初始化double类型的数据
        double dblVal);


    //##ModelId=4B0B68940380
    CMyAny(
        // 初始化string类型的数据
        const string &stringVal);
    CMyAny(
        // 初始化string类型的数据
        string &stringVal);


    CMyAny(
        // 初始化CStringVector类型的数据
        const CStringVector &stringvectorVal);
    CMyAny(
        // 初始化CStringVector类型的数据
        CStringVector &stringvectorVal);
    CMyAny(
        // 初始化CStringVector类型的数据
        const CStringMap &stringmapVal);
    CMyAny(
        // 初始化CStringVector类型的数据
        CStringMap&stringmapVal);
    CMyAny(
        // 初始化CStringVector类型的数据
        const CStringVectorMap &stringvectormapVal);
    CMyAny(
        // 初始化CStringVector类型的数据
        CStringVectorMap &stringvectormapVal);

	

	CMyAny(CNode *nodeVal);
  
    //##ModelId=4B0B68C30015
    CMyAny(
        // 初始化CElement * 类型的数据
        CElement *elementVal);

  
    //##ModelId=4B0B68EE00D1
    CMyAny(
        // 初始化CHtml * 类型的数据
        CHtml *htmlVal);
    // 返回变量当前正确的类型
    //##ModelId=4B0B693F02B5
    EVarType GetType();
    EVarType GetType() const;


  private:
    //##ModelId=4B0B5831022F
    int m_int;
	double m_double;


    //##ModelId=4B0B583800C8
    string m_string;

    CStringVector m_stringvector;
    CStringVectorMap m_stringvectormap;
    CStringMap m_stringmap;	

    //##ModelId=4B0B584D0349
    CHtml *m_pCHtml;

    //##ModelId=4B0B5862027E
    CElement *m_pCElement;

	CNode * m_pCNode;
    // 当前的变量原始类型
    //##ModelId=4B0B58BD00D9
    EVarType m_eType;


};



#endif /* MYFLOW_CMYANY_H_HEADER_INCLUDED_B4F4DCAC */
