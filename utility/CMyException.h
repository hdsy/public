// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#ifndef CMYEXCEPTION_H_HEADER_INCLUDED_B3F0B521
#define CMYEXCEPTION_H_HEADER_INCLUDED_B3F0B521

#include "mysoft_utility.h"

namespace MyUtility {

//##ModelId=4C0F3CCC0212
class CMyException
{
  public:
    //##ModelId=4C0F3EAF03B1
    CMyException();

    //##ModelId=4C0F3EB00008
    virtual ~CMyException();

    //##ModelId=4C0F3EB6020B
    CMyException(const std::string  &inUserMsg, long inErrcd = 0, const std::string  &inReason = "", const std::string  &inDebug = "");

    // 将此异常信息转换为可打印字符串
    //##ModelId=4C0F46E1032D
    std::string ToString() const ;

    //##ModelId=4C0F47220006
    long const& GetErrcode() const;

    //##ModelId=4C0F47220054
    std::string const& GetDebug() const;

    //##ModelId=4C0F472200A2
    std::string const& GetReason() const;

    //##ModelId=4C0F47220100
    std::string const& GetUserMsg() const;

  private:
    // 异常原因,供管理员快速了解模块故障
    //##ModelId=4C0F3D630253
    std::string m_sReason;

    // 错误编码:统一定义的
    //##ModelId=4C0F3DA301D7
    long m_iErrcd;

    // 异常时展现给客户的相应信息
    //##ModelId=4C0F3DC00264
    std::string m_sUserMsg;

    // 便于开发人员调试用的信息
    //##ModelId=4C0F3DF502B4
    std::string m_sDebug;

};

} // namespace MyUtility



#endif /* CMYEXCEPTION_H_HEADER_INCLUDED_B3F0B521 */
