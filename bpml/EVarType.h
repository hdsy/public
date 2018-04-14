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

#ifndef MYFLOW_EVARTYPE_H_HEADER_INCLUDED_B4F4790A
#define MYFLOW_EVARTYPE_H_HEADER_INCLUDED_B4F4790A

#include "myflow_macro.h"

#include <map>

#include <vector>

#include <string>

using namespace std;

// 枚举类，表示变量类型
//##ModelId=4B0B5901009A
enum EVarType { VT_INTEGER, //int
	VT_DOUBLE, //double
	VT_STRING, //string

	VT_STRINGVECTOR,
	VT_STRINGVECTORMAP,
	VT_STRINGMAP,

	VT_P_CHTML, //chtml
	VT_P_CELEMENT ,//celement
	VT_P_CNODE //cnode
	};



#endif /* MYFLOW_EVARTYPE_H_HEADER_INCLUDED_B4F4790A */
