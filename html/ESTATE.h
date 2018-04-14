// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#ifndef ESTATE_H_HEADER_INCLUDED_B62B75EF
#define ESTATE_H_HEADER_INCLUDED_B62B75EF

#include "mysoft_html.h"

// 状态枚举
//##ModelId=49D1B5F902EE
enum ESTATE { 
    // 当前分析为：未知状态
    // 
    // 
    //  
    STATE_UNKNOWN, 
    // 当前分析为：文本节点状态
    STATE_TEXT, 
    // 当前分析状态为：ELEMENT读取状态
    STATE_ELEMENT, 
    // 当前分析状态为：ATTR_NAME读取状态
    STATE_ELEMENT_ATTR_NAME, 
    // 当前分析状态为：ATTR_VALUE读取状态
    STATE_ELEMENT_ATTR_VALUE, 
    // 当前分析状态为：ATTR_QUOTE读取状态
    STATE_ELEMENT_ATTR_NAME_QUOTE, 
	STATE_ELEMENT_ATTR_VALUE_QUOTE, 
	// 注释状态
	STATE_COMMENT,
	// <![CDATA[    ......     ]]>
	STATE_CDATA,
	// 
	STATE_MAYBE_ELEMENT, 
	//
	STATE_MAYBE_ELEMENT_ATTR_VALUE };



#endif /* ESTATE_H_HEADER_INCLUDED_B62B75EF */
