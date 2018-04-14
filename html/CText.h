// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#ifndef CTEXT_H_HEADER_INCLUDED_B62B24D0
#define CTEXT_H_HEADER_INCLUDED_B62B24D0

#include "mysoft_html.h"
#include "CNode.h"

//##ModelId=49CC7C0703B9
class CText : public CNode
{
  public:
	CText(CNode*parent,string &cont,int depth,int t=0):CNode(parent,depth),m_sContent(cont),m_iType(t){cont = "";};
	CText(CNode*parent,string &cont,int t=0):CNode(parent),m_sContent(cont),m_iType(t){cont = "";};
	CText(CNode*parent,int t=0):CNode(parent),m_sContent(""),m_iType(t){};

	string Append(string & str)
	{
		m_sContent.append(str);
		str = "";
		return m_sContent;
	}
	string Append(char const & c)
	{
		m_sContent.append(1,c);
		return m_sContent;
	}
    // 将对象转换为string
    //##ModelId=49D08994000F
    virtual string ToString() const;

    //##ModelId=49D08E4A02BF

    // 当接到新的解析任务时，对旗下的子数清缓存
    //##ModelId=49D4883B01B5
    virtual int Clear();

   private:
    // 文本内容
    //##ModelId=49CC7CBA006D
    std::string m_sContent;

	//0 text  1 comment
	int m_iType;

};
class CComment : public CNode
{
  public:
	CComment(CNode*parent,string &cont,int depth):CNode(parent,depth),m_sContent(cont){cont = "";};
	CComment(CNode*parent,string &cont):CNode(parent),m_sContent(cont){cont = "";};
	CComment(CNode*parent):CNode(parent),m_sContent(""){};

	string Append(string & str)
	{
		m_sContent.append(str);
		str = "";
		return m_sContent;
	}
	string Append(char const & c)
	{
		m_sContent.append(1,c);
		return m_sContent;
	}
    // 将对象转换为string
    //##ModelId=49D08994000F
    virtual string ToString() const
	{
		return m_sContent;
	}

    // 当接到新的解析任务时，对旗下的子数清缓存
    //##ModelId=49D4883B01B5
    virtual int Clear()
	{
		m_sContent ="";
		return 0;
	}

   private:
    // 文本内容
    //##ModelId=49CC7CBA006D
    std::string m_sContent;

};

#endif /* CTEXT_H_HEADER_INCLUDED_B62B24D0 */
