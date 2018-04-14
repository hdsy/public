// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#ifndef CSTRINGMAP_H_HEADER_INCLUDED_B3FA04FE
#define CSTRINGMAP_H_HEADER_INCLUDED_B3FA04FE

#include "mysoft_utility.h"
#include "CStdMapString.h"

namespace MyUtility {

typedef std::string FILTER (const std::string &);
// 可将字符串按照特定的分隔符予以拆分，形成数组；并对形成的数组中的每项值进行二次拆分，形成map。同名值只出现一次
//##ModelId=4BFF287E02AD
class CStringMap : public CStdMapString
{
  public:
    // 输入参数：
    //     inStr 待拆分的字符串
    //     inEleSep 元素分隔符字符串
    //     inNVSep  元素名值分隔符字符串
    //     inFlg 分隔模式：分组内容长度为空，是否作为要素之一，默认是否
    // 
    // 返回参数：
    //     CStringVector &
    // 
    // 示例：Split("123",2) = > [1,3]
    //##ModelId=4C032D85028A
    CStringMap& Split(
        // 待拆分的字符串
        const std::string  &inStr, 
        // 元素分隔符
        const std::string &inEleSep="&", 
        // 名字值分隔符
        const std::string & inNVSep="=", 
        // 单值是否添加进MAP
        bool inFlg = true,
        FILTER * filter=NULL);

    // 组合成一个字串,inflg 0 raw   1 url编码, 
    //##ModelId=4C032D8502C8
    std::string Join(const char *inEleSep="&", const char *inNVSeq="=",FILTER* filter=NULL) const;
	std::string Join(const std::string & inEleSep, const std::string &  inNVSeq,FILTER* filter=NULL) const;

    //##ModelId=4C0332AC01D3
    CStringMap();

    //##ModelId=4C0332AC0202
    virtual ~CStringMap();

    // 输入参数：
    //     inStr 待拆分的字符串
    //     inEleSep 元素分隔符字符串
    //     inNVSep  元素名值分隔符字符串
    //     inFlg 分隔模式：分组内容长度为空，是否作为要素之一，默认是否
    // 
    // 返回参数：
    //     CStringVector &
    // 
    // 示例：Split("123",2) = > [1,3]
    //##ModelId=4C05C91F00F8
    CStringMap& Split(
        // 待拆分的字符串
        const char *inStr, 
        // 元素分隔符
        const char *inEleSep="&", 
        // 名字值分隔符
        const char *inNVSep="=", 
        // 单值是否添加进MAP
        bool inFlg = true,FILTER* filter=NULL);

};

} // namespace MyUtility



#endif /* CSTRINGMAP_H_HEADER_INCLUDED_B3FA04FE */
