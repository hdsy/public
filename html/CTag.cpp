// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************



#include "CTag.h"

//##ModelId=49D47D45029F
CTag::CTag(const char * name, enum ETAG endstyle, int priority, const char * endtags)
	:m_sName(name),m_eEndStyle(endstyle),m_iPriority(priority)
{
	m_vEndTag.SetCommaText(endtags,",");
}

