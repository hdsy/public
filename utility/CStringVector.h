// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#ifndef CSTRINGVECTOR_H_HEADER_INCLUDED_B3FA62D9
#define CSTRINGVECTOR_H_HEADER_INCLUDED_B3FA62D9

#include "mysoft_utility.h"
#include "CStdVectorString.h"

namespace MyUtility {

typedef std::string FILTER (const std::string &);

// 可将字符串按照特定的分隔符予以拆分，形成数组
//##ModelId=4BFF2857022F
class CStringVector : public CStdVectorString
{
  public:
    // 输入参数：
    //     inStr 待拆分的字符串
    //     inSep 分隔符字符串
    //     inFlg 分隔模式：分组内容长度为空，是否作为要素之一，默认是否
    // 
    // 返回参数：
    //     CStringVector &
    // 
    // 示例：Split("123",2) = > [1,3]
    //##ModelId=4BFF2CAC000F
    CStringVector& Split(
        // 待拆分的字符串
        const std::string  &inStr, 
        // 分隔符
        const std::string &inSep, 
        // 空值是否添加进数组
        bool inFlg = false,
        FILTER *filter=NULL);

    // 输入参数：
    //     inStr 待拆分的字符串
    //     inSep 分隔符字符串
    //     inFlg 分隔模式：分组内容长度为空，是否作为要素之一，默认是否
    // 
    // 返回参数：
    //     CStringVector &
    // 
    // 示例：Split("123",2) = > [1,3]
    //##ModelId=4BFF2EA60338
    CStringVector& Split(
        // 待拆分的字符串
        const char *inStr, 
        // 分隔符
        const char *inSep="=", 
        // 空值是否添加进数组
        bool inFlg = false,
        FILTER *filter=NULL);

    //##ModelId=4C032750028D
    CStringVector();

    //##ModelId=4C03275002BC
    virtual ~CStringVector();

    // 组合成一个字串
    //##ModelId=4C03275A009A
    std::string Join(const char *inSep = "",FILTER *filter=NULL) const;
    std::string Join(const std::string &inSep ,FILTER *filter=NULL) const;

};

} // namespace MyUtility



#endif /* CSTRINGVECTOR_H_HEADER_INCLUDED_B3FA62D9 */

