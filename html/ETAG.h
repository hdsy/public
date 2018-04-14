// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#ifndef ETAG_H_HEADER_INCLUDED_B62B6A5E
#define ETAG_H_HEADER_INCLUDED_B62B6A5E

#include "mysoft_html.h"

// 标签类型：根据语义定义
// 
// 类型	说明
// 1	类似xml的结束方式，可以用<tag></tag>结束，也可以用<tag .../>
// 2	必须用</tag>结束，比如html的script
// 3	根据级别来结束，比如html的p可以被包括p在内的开始标签结束
// 4	叶TAG。无结束符，比如html的br,hr,img
//##ModelId=49D2E574003E
enum ETAG { 
    // 使用标准XML的标签的结束机制。如下：
    // 
    // 1.<input .....   />
    // 2.<input ... > </input>
    TAG_FORCE_XML, 
    // 必须使用严密的符号对结束TAG
    // 
    // <SCRIPT> ...... </SCRIPT>
    TAG_FORCE_SELF, 
    // 无字节点，无结束符。如
    // 
    // <br>
    TAG_NONE, 
    // 根据优先级别来，可以被其他优先级高的TAG结束掉
    TAG_PRIORITY, 
    // 仅可以被特殊的几个TAG结束
    TAG_SPECIAL };



#endif /* ETAG_H_HEADER_INCLUDED_B62B6A5E */
