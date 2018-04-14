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

#ifndef MYFLOW_CMYHTML2XMLWORKER_H_HEADER_INCLUDED_B4F34000
#define MYFLOW_CMYHTML2XMLWORKER_H_HEADER_INCLUDED_B4F34000

#include "myflow_macro.h"

#include <map>

#include <vector>

#include <string>

#include "CMyWorker.h"
class CMyAny;

using namespace std;

// 将Html转化为xml的工作者
// 
// 选择器： 
// 		批量节点
// 			按照节点名检索
// 				tag(para_tag_name)
// 			按照属性检索	
// 				id(para_id_value)
// 				name(para_name_value)
// 				nv(para_attr_name_name,attr_name_value)
// 		批量节点值
// 			count
// 			
// 		单个节点	
// 			按照数组序号检索
// 				item(index)
// 	
// 		单个值
// 			取节点相应属性的值
// 				attr(para_attr_name_name)
// 			取节点中间文本
// 				text 
// 				
// 	
// 	运算器
// 		left是否包含right
// 			bool has(left,right)  
// 			bool head_has(left,right)  
// 			bool tail_has(left,right)  			
// 		left是否等于right
// 			bool equ(left,right)
// 		left是否大于right
// 			bool big(left,rigth)
// 		left是否小于right
// 			bool little(left,right)
// 		left减去right
// 			int minus(left,right)
// 		left加上right
// 			int add(left,right)
// 
// 
// 输出器
// 		echo
// 	赋值器
// 		assign
// 		定义的变量可以在下面用$identify引用
// 		
// 		类型：integer,string
//##ModelId=4B0CB36B00B6
#include "EVarType.h"
#include "CMyVarSpace.h"

class CMyHtml2XmlWorker : public CMyWorker
{
private:
	typedef struct ST_CSAIR_LOGIN_COOKIE
	{
		char          szChnID[8]; //渠道标记
		char szUin[72];       //财付通登陆名
		char szIp[16];	//用户IP
		time_t        tmStamp;    //时间戳，网络字节序
		char szAlign[4]; //使结构保持
	}SUnionLoginCookie;

//{{
	string Env_GetEmbVarValue(vector <string > & para_list);
//}}

//{{map function
	string Map_GetValueByKey(vector <string > & para_list);
	string Map_Size(vector <string > & para_list);
	string Map_Split(vector <string > & para_list);
	string Map_At(vector <string > & para_list);
	string Map_Join(vector <string > & para_list);
//}}map function
//{{vector function
	string Vector_At(vector <string > & para_list);
	string Vector_Size(vector <string > & para_list);
	string Vector_Split(vector <string > & para_list);
	string Vector_Join(vector <string > & para_list);
//}}vector function
//{{string function	
	string String_SubStr(vector <string > & para_list);
	string String_Cat(vector <string > & para_list);
	string String_Trim(vector <string > & para_list);
	string String_Has(vector <string > & para_list);
	string String_Find(vector <string > & para_list);
	
	string String_ToHex(vector <string > & para_list);
	string String_ToChar(vector <string > & para_list);

	string String_ReadInt(vector <string > & para_list);
	string String_ReadCString(vector <string > & para_list);
	
	string String_XmlDecode(vector <string > & para_list);
	string String_XmlEncode(vector <string > & para_list);
	string String_UrlDecode(vector <string > & para_list);
	string String_UrlEncode(vector <string > & para_list);
	
	string String_ToUpper(vector <string > & para_list);
	string String_ToLower(vector <string > & para_list);
	string VcdImg_Check(vector <string > & para_list);

//}}string function

//{{HTML 解析与遍历函数
	string Html_Parse(vector <string > & para_list);
	string Html_GetElementByAttrNV(vector <string > & para_list);
	string Html_Count(vector <string > & para_list);
	string Html_GetResult(vector <string > & para_list);
	string Html_GetAttrValue(vector <string > & para_list);
	string Html_GetInnerText(vector <string > & para_list);
	string Html_GetElementByTagName(vector <string > & para_list);
	string Html_Child(vector <string > & para_list);
//}}HTML 解析与遍历函数


//{{算术表达式:  大于    小于  等于
	string Math_GT(vector <string > & para_list);
	string Math_LT(vector <string > & para_list);
	string Math_EQU(vector <string > & para_list);
	string Math_AND(vector <string > & para_list);
	string Math_OR(vector <string > & para_list);
	
	string Math_Inc(vector <string > & para_list);
	string Math_Sub(vector <string > & para_list);
	string Math_Mod(vector <string > & para_list);


	//double
	string Math_Double_Add(vector <string > & para_list);
	string Math_Double_Sub(vector <string > & para_list);
	string Math_Double_Mul(vector <string > & para_list);
	string Math_Double_Div(vector <string > & para_list);

	// math
	string Math_Md5(vector <string > & para_list);
	string Math_Sha1(vector <string > & para_list);
	string Math_3Des(vector <string > & para_list);
	string Math_Un3Des(vector <string > & para_list);
	string Math_AlipayNotifyVerifySign(vector <string > & para_list);
	
//}}算术表达式:  大于    小于  等于


//{{文件操作函数
	string File_Store(vector <string > & para_list);
	string File_Read(vector <string > & para_list);
	string File_Delete(vector <string > & para_list);
	//gen_file_name
	string File_GenCachName(vector <string > & para_list);
	
//}}文件操作函数

//{{ 系统帮助函数
	string Sys_GetHelp(vector <string > & para_list);



//}}系统帮助函数

  //返回字串长度
  string String_GetLength(vector <string > & para_list);
  
  string String_ToInt(vector <string > & para_list);

  //返回当前日期yyyymmddhhMMss
  string Date_GetDatetime(vector <string > & para_list);

  //转码GBK/utf-8
  string String_ConvertCode(vector <string > & para_list);


  

/*
  //检查B账户商户登录
  string CheckUnionMchLogin(vector <string > & para_list);
  
  //B账户商户登录cookie
  string WriteUnionMchLoginCookie(vector <string > & para_list);
*/

  public:
    //##ModelId=4B0CB42302E8
    string Call(
        // 函数名称
        const string &func_name, 
        // 参数列表
        vector <string > & para_list);

    // 取变量值，先局部后全局
    // 
    // 如果取值成功则返回0
    // 否则返回其他值
    // 1 变量不存在
    //##ModelId=4B0CB6B103A4
    int FetchVarValue(const string &var, 
        // 变量的值
        CMyAny &val);

    CMyAny FetchVarValue(const string &var);
    //##ModelId=4B0CB4D80048
    CMyHtml2XmlWorker();
    CMyHtml2XmlWorker(CMyVarSpace * global_var_space);

    //##ModelId=4B0CB4D80087
    virtual ~CMyHtml2XmlWorker();

  private:
	  void ClearLocalVarSpace();
	  void InitFunctionMap();
	  string GetTmpVarName();

	 void InitFunctionDesc();
    
	  int m_iTmpVar;
    //##ModelId=4B0CB49501BF
    CMyVarSpace *m_gpVar;

    // 局部变量空间
    //##ModelId=4B0CB4B70087
    CMyVarSpace m_mVar;

	map<string,int> m_mFunction;
	MyUtility::CStringMap m_mFunctionDesc;

	//从第3位算起的报文
	//void parseRequestInfo_1009(vector <string > & para_list, string &strParam);

};



#endif /* MYFLOW_CMYHTML2XMLWORKER_H_HEADER_INCLUDED_B4F34000 */
