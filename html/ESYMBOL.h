// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#ifndef ESYMBOL_H_HEADER_INCLUDED_B62B1551
#define ESYMBOL_H_HEADER_INCLUDED_B62B1551

#include "mysoft_html.h"

// 符号类型枚举
//##ModelId=49D1D27F0119
enum ESYMBOL { 
    // 空白符号：空格，TAB，换行符等
    SYMBOL_SPACE, 
    // 标签开始符号：<
    SYMBOL_TAG_BEGIN, 
    // 标签结束符号：>
    SYMBOL_TAG_END, 
    // 属性赋值符号：=
    SYMBOL_TAG_ATTR_ASIGN, 
    // 属性引号：',"
    SYMBOL_TAG_ATTR_QUTOE, 
	//a-zA-Z
	SYMBOL_ALPHA, 
	//0-9
	SYMBOL_NUMBER, 
	//!
	SYMBOL_DOCTYPE_HEADER,
	//...
	SYMBOL_UNKNOWN };



#endif /* ESYMBOL_H_HEADER_INCLUDED_B62B1551 */
