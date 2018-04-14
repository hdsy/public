// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#ifndef CSTRINGVECTORMAP_H_HEADER_INCLUDED_B3FA21CE
#define CSTRINGVECTORMAP_H_HEADER_INCLUDED_B3FA21CE

#include "mysoft_utility.h"
#include "CStdMapCStringVector.h"
#include "CStringMap.h"

namespace MyUtility {

//##ModelId=4C05C83E001A
class CStringVectorMap : public CStdMapCStringVector
{
  private:
	CStringVectorMap& AddElement(const std::string & key,const std::string & val);
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
    //##ModelId=4C05C99A005D
    CStringVectorMap& Split(
        // 待拆分的字符串
        const std::string  &inStr, 
        // 元素分隔符
        const std::string &inEleSep="&", 
        // 名字值分隔符
        const std::string & inNVSep="=", 
        // 单值是否添加进MAP
        bool inFlg = true,
        FILTER * filter=NULL);

    // 组合成一个字串
    //##ModelId=4C05C99A007C
    std::string Join(const char *inEleSep, const char *inNVSeq,FILTER * filter=NULL) const;
    std::string Join(const std::string & inEleSep, const std::string & inNVSeq,FILTER * filter=NULL) const;

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
    //##ModelId=4C05C99A008C
    CStringVectorMap& Split(
        // 待拆分的字符串
        const char *inStr, 
        // 元素分隔符
        const char *inEleSep="&", 
        // 名字值分隔符
        const char *inNVSep="=", 
        // 单值是否添加进MAP
        bool inFlg = true,
        FILTER * filter=NULL);

    //##ModelId=4C05C9BF01B5
    CStringVectorMap();

    //##ModelId=4C05C9BF01E4
    virtual ~CStringVectorMap();

    //##ModelId=4C05C9BF0222
    std::string GetFirst(const std::string &inKey);
    std::string GetFirst(const char *inKey);
    std::string GetFirst(const std::string &inKey)const ;
    std::string GetFirst(const char *inKey)const ;

};

} // namespace MyUtility



#endif /* CSTRINGVECTORMAP_H_HEADER_INCLUDED_B3FA21CE */
