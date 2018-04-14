// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#include "CMyException.h"
#include "CBaseEncode.h"


//##ModelId=4C0F3EAF03B1
MyUtility::CMyException::CMyException():m_sReason(""),m_iErrcd(0),m_sUserMsg(""),m_sDebug("")
{
}


//##ModelId=4C0F3EB00008
MyUtility::CMyException::~CMyException()
{
}

//##ModelId=4C0F3EB6020B
MyUtility::CMyException::CMyException(const std::string  &inUserMsg, long inErrcd, const std::string  &inReason, const std::string  &inDebug)
	:m_sReason(inReason),m_iErrcd(inErrcd),m_sUserMsg(inUserMsg),m_sDebug(inDebug)
{
}


//##ModelId=4C0F46E1032D
std::string MyUtility::CMyException::ToString() const
{
	string res;
	
	res  = "[";
	res += CBaseEncode::ULongToString(m_iErrcd);
	res += "] ";
	res += m_sUserMsg;
	res += "  ";
	res += m_sReason;
	res += " ";
	res += m_sDebug;
	
	return res;
}

//##ModelId=4C0F47220006
long const& MyUtility::CMyException::GetErrcode() const
{
    return m_iErrcd;
}


//##ModelId=4C0F47220054
std::string const& MyUtility::CMyException::GetDebug() const
{
    return m_sDebug;
}


//##ModelId=4C0F472200A2
std::string const& MyUtility::CMyException::GetReason() const
{
    return m_sReason;
}


//##ModelId=4C0F47220100
std::string const& MyUtility::CMyException::GetUserMsg() const
{
    return m_sUserMsg;
}


