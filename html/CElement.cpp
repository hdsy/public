// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#include "CElement.h"
#include "CAttribute.h"
#include "CHtmlTagMap.h"

#include "CText.h"

//##ModelId=49D0891503A9
int CElement::GetElementByID(const std::string &id)
{
	m_vResult.clear();

	int resCount = 0;

	if(IsExistThisAttr("id",id))
	{
		m_vResult.push_back(this);
		resCount++;
	}

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(!pEle )
			continue;
		if(pEle->IsExistThisAttr("id",id))
		{
			m_vResult.push_back(pEle);
			resCount++;
		}
		
		resCount += pEle->GetElementByID(id,this);
	}


	return resCount;
}

//##ModelId=49D0891503A9
int CElement::GetElementByAttrNV(const std::string &n,const std::string &v)
{
	m_vResult.clear();

	int resCount = 0;

	if(IsExistThisAttr(n,v))
	{
		m_vResult.push_back(this);
		resCount++;
	}

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(!pEle )
			continue;
		if(pEle->IsExistThisAttr(n,v))
		{
			m_vResult.push_back(pEle);
			resCount++;
		}
		
		resCount += pEle->GetElementByAttrNV(n,v,this);
	}


	return resCount;
}
//##ModelId=49D08925007D
int CElement::GetElementByID(const char *id)
{
	return GetElementByID(string(id));
}

//##ModelId=49D08925007D
int CElement::GetElementByAttrNV(const char *n,const char *v)
{
	return GetElementByAttrNV(string(n),string(v));
}

//##ModelId=49D0891503D8
int CElement::GetElementByTagName(const std::string &tagname,int mode)
{
	m_vResult.clear();

	int resCount = 0;

	if(m_sName == tagname)
	{
		m_vResult.push_back(this);
		resCount++;
	}

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(!pEle )
			continue;

		switch(mode)
		{
		case 0://绝对匹配
			{
				if(pEle->m_sName == tagname)
				{
					m_vResult.push_back(pEle);
					resCount++;
				}
				break;
			}
		case 1://首部匹配
			{
				if(pEle->m_sName.find(tagname) == 0)
				{
					m_vResult.push_back(pEle);
					resCount++;
				}
				break;
			}
		case 2://包含
			{
				if(pEle->m_sName.find(tagname) != string::npos)
				{
					m_vResult.push_back(pEle);
					resCount++;
				}
				break;
			}
		case 3://被
			{
				if(tagname.find(pEle->m_sName) != string::npos)
				{
					m_vResult.push_back(pEle);
					resCount++;
				}
				break;
			}


		}
		
		resCount += pEle->GetElementByTagName(tagname,this,mode);
		
	}


	return resCount;
}
int CElement::GetElementByTagName(const std::string &tagname,CElement *resEle,int mode) const
{
	//resEle->m_vResult.clear();

	int resCount = 0;
/*
	if(m_sName == tagname)
	{
		resEle->m_vResult.push_back(this);
		resCount++;
	}*/

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(!pEle )
			continue;
		switch(mode)
		{
		case 0://绝对匹配
			{
				if(pEle->m_sName == tagname)
				{
					resEle->m_vResult.push_back(pEle);
					resCount++;
				}
				break;
			}
		case 1://首部匹配
			{
				//int pos = pEle->m_sName.find(tagname);
				if(pEle->m_sName.find(tagname) == 0)
				{
					resEle->m_vResult.push_back(pEle);
					resCount++;
				}
				break;
			}
		case 2://包含
			{
				if(pEle->m_sName.find(tagname) != string::npos)
				{
					resEle->m_vResult.push_back(pEle);
					resCount++;
				}
				break;
			}
		case 3://被
			{
				if(tagname.find(pEle->m_sName) != string::npos)
				{
					resEle->m_vResult.push_back(pEle);
					resCount++;
				}
				break;
			}


		}
		
		resCount += pEle->GetElementByTagName(tagname,resEle,mode);
	}


	return resCount;
}

//##ModelId=49D08925009C
int CElement::GetElementByTagName(const char *tagname,int mode)
{
	return GetElementByTagName(string(tagname),mode);
}
//##ModelId=49D08925007D
int CElement::GetElementByName(const std::string &name)
{
	m_vResult.clear();

	int resCount = 0;

	if(IsExistThisAttr("name",name))
	{
		m_vResult.push_back(this);
		resCount++;
	}

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(!pEle )
			continue;
		if(pEle->IsExistThisAttr("name",name))
		{
			m_vResult.push_back(pEle);
			resCount++;
		}
		
		resCount += pEle->GetElementByName(name,this);
	}


	return resCount;
}
int CElement::GetElementByName(const std::string &name,CElement *resEle) const
{
	int resCount = 0;

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(!pEle )
			continue;
		if(pEle->IsExistThisAttr("name",name))
		{
			resEle->m_vResult.push_back(pEle);
			resCount++;
		}
		
		resCount += pEle->GetElementByName(name,resEle);
	}


	return resCount;
}
int CElement::GetElementByID(const std::string &id,CElement *resEle)
{
	int resCount = 0;

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(!pEle )
			continue;
		if(pEle->IsExistThisAttr("id",id))
		{
			resEle->m_vResult.push_back(pEle);
			resCount++;
		}
		
		resCount += pEle->GetElementByID(id,resEle);
	}


	return resCount;
}
int CElement::GetElementByAttrNV(const std::string &n,const std::string &v,CElement *resEle)
{
	int resCount = 0;

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(!pEle )
			continue;
		if(pEle->IsExistThisAttr(n,v))
		{
			resEle->m_vResult.push_back(pEle);
			resCount++;
		}
		
		resCount += pEle->GetElementByAttrNV(n,v,resEle);
	}


	return resCount;
}
//##ModelId=49D08925009C
int CElement::GetElementByName(const char *name)
{
	return GetElementByName(string(name));
}


//##ModelId=49D0894802EE
string CElement::GetInnerText() const
{
	string res;

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{
		CText * pTxt = dynamic_cast<CText *>(m_vpChild[i]);
		CElement * pEle = dynamic_cast<CElement *>(m_vpChild[i]);
		if(pTxt ) 
		{
			res += pTxt->ToString();
			continue;
		}

		if(pEle)
		{
			res += pEle->GetInnerText();
		}
		
		
	}

	return res;
}
string CElement::GetInnerHTML() const
{
	string res;

	for(unsigned int i = 0 ;i<m_vpChild.size();i++)
	{		
		res += m_vpChild[i]->ToString();		
	}

	return res;
}

//##ModelId=49D089C8001F
string CElement::ToString() const
{
	string res("<");

	res += m_sName;

		for(unsigned int i=0;i<m_vpAttr.size();i++)
		{
			res +=" ";
			res += m_vpAttr[i]->ToString();
		}
	res += ">";

	return res;
}


void CElement::Del(CBase * itm)
{
	if(itm != NULL)
	{
		delete itm;itm = NULL;
	}
}
//##ModelId=49D488CE00DA
/*vc6的mem_fun不能使用返回值为void的函数*/
int CElement::Clear()
{
	m_vResult.clear();

	for_each(m_vpAttr.begin(),m_vpAttr.end(),CElement::Del);
	m_vpAttr.clear();
	
	for_each(m_vpChild.begin(),m_vpChild.end(),mem_fun(&CNode::Clear));

	for_each(m_vpChild.begin(),m_vpChild.end(),CElement::Del);
	m_vpChild.clear();

	m_sName = "" ;
	m_iEndType = 0;


	return 0;
	
}

//##ModelId=49D48A760119
CElement::~CElement()
{
	Clear();
}

//##ModelId=49D48B0800CB
/*
CNode * CElement::Identify(const string &src, string::const_iterator &pos,enum ESTATE &state)
{

	return 0;
}
*/

void CElement::AppendTextChild(CNode *pnode)
{
	m_vpChild.push_back(pnode);
}

void CElement::AppendElementChild(CNode *pnode,CElement* &pCur )
{
	ASSERT(pCur);

	bool bEnd = false;

	const CHtmlTagMap &m = CHtmlTagMap::GetInstance();

	CElement *pNode = (CElement *) pnode;

	string adding = pNode->GetTagName();

	CHtmlTagMap::const_iterator iter;

	while((iter = m.find(pCur->GetTagName())) != m.end())
	{
		if((*iter).second.CanEndTHisTag(adding))
		{
			ASSERT(pCur->GetParent());
			
			pCur = (CElement *)pCur->GetParent();
			bEnd = true;
		}
		else
		{
			break;
		}
	}

	
	if(adding.at(0) == '/')
	{
		if(pCur->GetTagName() == adding.substr(1,adding.size()-1))
		{
			pCur = (CElement *)pCur->GetParent();
			bEnd = true;
		}

		if(bEnd)
			return;	
		else
		{
			m_vpChild.push_back(pnode);
		}
	}
	else
	{
		if(bEnd)
			pCur->AppendElementChild(pnode,pCur);
		else
		{
			m_vpChild.push_back(pnode);
			if((iter = m.find(pNode->GetTagName())) != m.end())
			{
				if((*iter).second.SingleTag())
				{//如果是单节点则不需要改变当前父节点
					return;
				}
				
			}
			else  // xml <... />
			{
				if(pNode->m_vpAttr.size() >= 1)
				{
					CAttribute * p = pNode->m_vpAttr.at(pNode->m_vpAttr.size()-1);

					if((p->GetType() == 2) &&(p->GetName() == "/"))
					{
						//pNode->m_vpAttr.pop_back();

						return;
					}
				}
				else
				{

					int iFlag = 0;
					while(pNode->m_sName.size() > 1)
					{
						if(pNode->m_sName.at(pNode->m_sName.size()  - 1) == '/')
						{
							pNode->m_sName = pNode->m_sName.substr(0,pNode->m_sName.size()  - 1);
							iFlag = 1;
						}
						else
						{
							break;
						}

					}

					if(iFlag == 1)
					{
						//pNode->m_vpAttr.pop_back();

						return;
					}
				}

			}
			pCur = (CElement *)pnode;
		}
	}	
}

bool CElement::IsExistThisAttr(const string &name, const string &value,int mode)
{
	for(unsigned int i = 0; i < m_vpAttr.size(); i++)
	{
		if(m_vpAttr[i]->IsEqual(name,value,mode))
			return true;
	}

	return false;
}
