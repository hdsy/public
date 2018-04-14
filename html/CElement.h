// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#ifndef CELEMENT_H_HEADER_INCLUDED_B62B2467
#define CELEMENT_H_HEADER_INCLUDED_B62B2467

#include "mysoft_html.h"
#include "CNode.h"
#include "CAttribute.h"

//##ModelId=49CC7C000138
class CElement : public CNode
{
  public:
	CElement(CNode*parent,string &cont,int depth):CNode(parent,depth),m_sName(cont){cont = "";};
	CElement(CNode*parent,string &cont):CNode(parent),m_sName(cont){cont = "";};
	CElement(CNode*parent):CNode(parent),m_sName(""){};
	CElement():CNode(NULL),m_sName(""){};
	
	void AppendAttr(string & str)
	{
		if(str.size() == 0)
			return ;

		CAttribute * p = new CAttribute(str);

		str = "";
		m_vpAttr.push_back(p);
	}

	void SetAttrValue( string & val)
	{
		CAttribute * p = m_vpAttr.at(m_vpAttr.size()-1);


		p->AddValue(val);
		val ="";
	}
	string& GetAttrValue(const string &name, string & val) const
	{
		val = "";
		std::vector<CAttribute *>::const_iterator cur = m_vpAttr.begin();

		while(cur!= m_vpAttr.end())
		{
			if((*cur)->GetName() == name)
			{
				val = (*cur)->GetValue();
				break;
			}
			cur++;
		}
		return val;
	}

	string& NameAppend(string & s)
	{
		string res;
		string::const_iterator iter;

		for(iter = s.begin();iter !=s.end();iter++)
			res += (*iter);

		m_sName.append(res);
		s="";
		return m_sName;
	}
	string NameAppend(char const & c)
	{
#ifdef 	WIN32
		m_sName.append(1,(c));
#else
//gcc 3.x 版本不支持append(int,char) 类型		
		char lc[2]={0};
		lc[0] = (c);
		m_sName.append(lc);
#endif		
		return m_sName;
	}
	  void AppendTextChild(CNode *pnode);
	  void AppendElementChild(CNode *pnode,CElement* &pCur);

	  static void Del(CBase * itm);
    // 返回值：满足条件的节点数组
    //##ModelId=49D0891503A9
    int GetElementByID(
        // 指定的ID名
        const std::string &id);
    // 返回值：满足条件的节点数组
    //##ModelId=49D08925007D
    int GetElementByID(
        // 指定的ID名
        const char *id);
    // 返回值：满足条件的节点数组
    //##ModelId=49D0891503A9
    int GetElementByAttrNV(
        // 指定的ID名
        const std::string &n,const std::string &v);
    // 返回值：满足条件的节点数组
    //##ModelId=49D08925007D
    int GetElementByAttrNV(
        // 指定的ID名
        const char *n,const char *v);

    // 返回值：满足条件的节点数组
    //##ModelId=49D0891503D8
	// mode = 0 精确匹配,tagname ==
	// mode = 1 首部匹配,tagname 
	// mode = 2 包含
	// mode = 3 被包含
    int GetElementByTagName(
        // 指定的TAG名称
        const std::string &tagname,int mode=0);
    // 返回值：满足条件的节点数组
    //##ModelId=49D08925009C
    int GetElementByTagName(
        // 指定的TAG名称
        const char *tagname,int mode=0);

    // 返回值：满足条件的节点数组
    //##ModelId=49D0891503D8
	int GetElementByName(const std::string &name);
    // 返回值：满足条件的节点数组
    //##ModelId=49D08925009C
    int GetElementByName(
        // 指定的TAG名称
        const char *tagname);

    //##ModelId=49D08916000F
    const std::vector<CNode *>& GetResult() const
	{
		return m_vResult;
	}

    const CNode * GetResult(int i) const
	{
		return m_vResult[i];
	}


    // 返回值：满足条件的节点数组
    //##ModelId=49D0894802EE
    string GetInnerText() const;
	string GetInnerHTML() const;

    // 将对象转换为string
    //##ModelId=49D089C8001F
    virtual string ToString() const;

    //##ModelId=49D08EA30399
    //virtual CNode *Identify(const string &src, string::const_iterator &pos,enum ESTATE &state);

    // 当接到新的解析任务时，对旗下的子数清缓存
    //##ModelId=49D488CE00DA
    virtual int Clear();


    //##ModelId=49D48A760119
    virtual ~CElement();    

	std::vector<CNode *> Child() const
	{
		return m_vpChild;
	}

	
	CNode * Child(int i) const
	{
		return m_vpChild.at(i);
	}
	string GetTagName() const
	{
		return m_sName;
	}
	string GetTagName() 
	{
		return m_sName;
	}

	bool IsExistThisAttr(const string & name,const string &value,int mode=1);
	int GetElementByName(const std::string &name,CElement *resEle) const;
	int GetElementByTagName(const std::string &tagname,CElement * resEle,int mode=0) const;
	int GetElementByID(const std::string &id,CElement * resEle);
	int GetElementByAttrNV(const std::string &n,const std::string &v,CElement * resEle);

  private:
    // TAG名称
    //##ModelId=49CC7CE60203
    std::string m_sName;
	
    // 子节点数组
    //##ModelId=49CC7D07034B
    std::vector<CNode *> m_vpChild;

	
    // 结束类型
    // 
    // 1. 自动结束，录入解析串正确，或者符合配置规则
    // 2. 强制结束，录入串错误，系统纠正
    //##ModelId=49CC7DD7009C
    int m_iEndType;

    //##ModelId=49D0641D031C
    std::vector<CAttribute *> m_vpAttr;

    //##ModelId=49D474970186
    std::vector<CNode *> m_vResult;

};



#endif /* CELEMENT_H_HEADER_INCLUDED_B62B2467 */
