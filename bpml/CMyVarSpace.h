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

#ifndef MYFLOW_CMYVARSPACE_H_HEADER_INCLUDED_B4F41EB6
#define MYFLOW_CMYVARSPACE_H_HEADER_INCLUDED_B4F41EB6

#include "myflow_macro.h"

#include <map>

#include <vector>

#include <string>
#include "CMyAnyMap.h"
class CMyAny;

using namespace std;

//##ModelId=4B0B6BA903CE
class CMyVarSpace : public CMyAnyMap
{
  public:
 
	  CMyVarSpace()
	  {

	  };
	  ~CMyVarSpace()
	  {
		  clear();
	  };

    // 取变量值，可以循环。
    // 
    // 比如$$varname,可先取$varname的值 value1
    // 
    // 再去$value1的值
    //##ModelId=4B0B8FB4006A
    void SetVarValue(
        // 变量名
        const string  &var_name, CMyAny & var_value);
    // 取变量值，可以循环。
    // 
    // 比如$$varname,可先取$varname的值 value1
    // 
    // 再去$value1的值
    //##ModelId=4B0B8FB3022F
    CMyAny *GetVarValue(
        // 变量名
        const string &var_name);


    // 取变量值，可以循环。
    // 
    // 比如$$varname,可先取$varname的值 value1
    // 
    // 再去$value1的值
    //##ModelId=4B0B8FB40174
    void SetVarValue(
        // 变量名
        const string &var_name, CMyAny *var_value);
		
		

};



#endif /* MYFLOW_CMYVARSPACE_H_HEADER_INCLUDED_B4F41EB6 */
