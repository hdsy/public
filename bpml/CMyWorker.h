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

#ifndef MYFLOW_CMYWORKER_H_HEADER_INCLUDED_B4F338D9
#define MYFLOW_CMYWORKER_H_HEADER_INCLUDED_B4F338D9
#pragma warning(disable:4786)
#include "myflow_macro.h"

#include <map>

#include <vector>

#include <string>

#include "CMyAny.h"


using namespace std;
#include "EVarType.h"
//##ModelId=4B0BA6030200
class CMyWorker
{
  public:
    //##ModelId=4B0BAD97007A
    virtual string  Call(
        // 函数名称
        const string &func_name, 
        // 参数列表
        vector <string > &  para_list) = 0;

	// 取变量值，先局部后全局
    // 
    // 如果取值成功则返回0
    // 否则返回其他值
    // 1 变量不存在
    //##ModelId=4B0CB6B103A4
    virtual int FetchVarValue(const string &var, 
        // 变量的值
        CMyAny &val) = 0;

	virtual CMyAny FetchVarValue(const string &var) = 0;
// 全局变量空间，用以获取输入和输出
};



#endif /* MYFLOW_CMYWORKER_H_HEADER_INCLUDED_B4F338D9 */
