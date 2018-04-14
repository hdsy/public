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

#ifndef MYFLOW_MYFLOW_MACRO_H_HEADER_INCLUDED_B4F4790A
#define MYFLOW_MYFLOW_MACRO_H_HEADER_INCLUDED_B4F4790A

#define MYFLOW_TAG_HEADER "my-soft::"



#include "CBaseEncode.h"
#include "CStringVector.h"
#include "CStringVectorMap.h"
#include "CStringMap.h"


#include "HttpClient.h"

using namespace MyUtility;

#ifndef WIN32
#define DeleteFile remove
#endif

#endif /* MYFLOW_MYFLOW_MACRO_H_HEADER_INCLUDED_B4F4790A */
