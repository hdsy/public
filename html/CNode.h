// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#ifndef CNODE_H_HEADER_INCLUDED_B62B42AB
#define CNODE_H_HEADER_INCLUDED_B62B42AB

#include "mysoft_html.h"
#include "CBase.h"

//##ModelId=49CC7BF003C8
class CNode : public CBase
{
  public:

	CNode(CNode*parent,CNode*next,CNode*prev,int depth):m_pParent(parent),m_pNext(next),m_pPrev(prev),m_iDepth(depth){};
	CNode(CNode*parent,int depth):m_pParent(parent),m_pNext(NULL),m_pPrev(NULL),m_iDepth(depth){};
	CNode(CNode*parent):m_pParent(parent),m_pNext(NULL),m_pPrev(NULL),m_iDepth(0){};
	CNode():m_pParent(NULL),m_pNext(NULL),m_pPrev(NULL),m_iDepth(0){};
    // 将对象转换为string
    //##ModelId=49D089BC0251
    virtual string ToString() const = 0;

    // 当接到新的解析任务时，对旗下的子数清缓存
    //##ModelId=49D4881503D8
    virtual int Clear() = 0;

	virtual string Append(string & str){return str;}
	
	virtual CNode * GetParent()
	{
		return m_pParent;
	}

  protected:
    //##ModelId=49CC7C39001F
    CNode* m_pParent;

    //##ModelId=49D063E40109
    CNode* m_pNext;

    //##ModelId=49D063E801E4
    CNode* m_pPrev;

    // 深度：从0开始
    //##ModelId=49D06893006D
    int m_iDepth;

};



#endif /* CNODE_H_HEADER_INCLUDED_B62B42AB */
