// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************
 
#include "CText.h"

//##ModelId=49D08994000F
string CText::ToString() const
{
	return m_sContent;
}

//##ModelId=49D4883B01B5
int CText::Clear()
{
	m_sContent ="";
	return 0;
}

//##ModelId=49D48B5C00EA
//DEL CNode * CText::Identify(const string &src, string::const_iterator &pos,enum ESTATE &state)
//DEL {
//DEL 	CNode *pResult = m_pParent;
//DEL 
//DEL 	
//DEL 
//DEL 	return pResult;
//DEL }

