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
#ifdef WIN32
#include "stdafx.h"
#endif
#include "CMyVarSpace.h"
#include "CMyAny.h"



//##ModelId=4B0B8FB4006A
void CMyVarSpace::SetVarValue(const string  &var_name, CMyAny & var_value)
{
	CMyVarSpace::iterator theIterator;

	theIterator = find(var_name);

	if( theIterator != end())
		erase(theIterator);

	insert(value_type(var_name,var_value));
}

//##ModelId=4B0B8FB3022F
CMyAny *CMyVarSpace::GetVarValue(const string &var_name)
{
	CMyVarSpace::iterator  pos;

	pos = find(var_name);

	if(pos == end())
		return NULL;

	else
		return &(pos->second);
}

//##ModelId=4B0B8FB40174
void CMyVarSpace::SetVarValue(const string &var_name, CMyAny *var_value)
{

	CMyVarSpace::iterator theIterator;

	theIterator = find(var_name);

	if( theIterator != end())
		erase(theIterator);

	insert(value_type(var_name,*var_value));
}

