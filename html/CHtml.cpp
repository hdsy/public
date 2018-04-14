// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#include "CHtml.h"


//##ModelId=49D06D01002E
int CHtml::Parse(const std::string &cont, int mode)
{
	switch(mode)
	{
	case CONTEXT_FIRST:
	case CONTEXT_WHOLE:
		Init();
		break;
	case CONTEXT_MIDDLE:
	case CONTEXT_LAST:
		if(m_pCurNode == NULL) Init();
		break;
	}

	string::const_iterator iterBegin,iterEnd,iterCur;
	iterBegin = cont.begin();
	iterEnd = cont.end();

	iterCur = iterBegin;

	/*
	考虑到局部性的支持，对于"与<!--必须保存最后状态
	*/
	while(iterCur != iterEnd)
	{
		switch(m_eCurState)
		{
		case STATE_UNKNOWN:
			IdentifyUnkwown(cont,iterCur);break;
		case STATE_MAYBE_ELEMENT:
			IdentifyMayBeElement(cont,iterCur);break;		
		case STATE_TEXT: // 当前分析为：文本节点状态
			IdentifyText(cont,iterCur);break;	
    
		case STATE_ELEMENT: // 当前分析状态为：ELEMENT读取状态
			IdentifyElement(cont,iterCur);break;	
			break;
		case STATE_ELEMENT_ATTR_NAME:// 当前分析状态为：ATTR_NAME读取状态
			IdentifyElementAttrName(cont,iterCur);
			break;
		case STATE_MAYBE_ELEMENT_ATTR_VALUE: 
			IdentifyElementAttrMayBeValue(cont,iterCur);
			break;
		case STATE_ELEMENT_ATTR_VALUE:// 当前分析状态为：ATTR_VALUE读取状态
			IdentifyElementAttrValue(cont,iterCur);
			break;
		case STATE_ELEMENT_ATTR_NAME_QUOTE:// 当前分析状态为：ATTR_QUOTE读取状态
			IdentifyElementAttrNameQuote(cont,iterCur);
			break;
		case STATE_ELEMENT_ATTR_VALUE_QUOTE:
			IdentifyElementAttrValueQuote(cont,iterCur);
			break;
		case STATE_COMMENT:
			IdentifyComment(cont,iterCur);
			break;
		case STATE_CDATA:
			IdentifyCDATA(cont,iterCur);
			break;
		default:
			//AfxMessageBox("error");
			return 1;
			break;
		}
	}



	
	switch(mode)
	{
	case CONTEXT_WHOLE:
	case CONTEXT_LAST:
		EnClosed();
		break;
	case CONTEXT_MIDDLE:
	case CONTEXT_FIRST:
		break;
	}
	return 0;
}

//##ModelId=49D06E560109
int CHtml::ParseFile(const std::string &fname)
{
	string cnt;
	char c;
/*
	CFile f;
	f.Open(fname.c_str(),CFile::modeRead);

	cnt.reserve(f.GetLength());

	for(int i=0;i<f.GetLength();i++)
	{
		f.Read(&c,1);
		cnt.append(1,c);
	}
	
	f.Close();  */

	FILE *stream;
	if( (stream  = fopen( fname.c_str(), "r" )) == NULL )
		return false;
	
	fseek(stream,0,SEEK_END);

	typedef unsigned long LONG ;
	
	LONG fLength = ftell(stream);

	fseek(stream,0,SEEK_SET);

	//cnt.reserve(fLength);

	for(LONG i=0;i<fLength;i++)
	{
		if( fread( &c, sizeof( char ), 1, stream ) != 1)
			break;

	//	c = fgetc(stream);
		cnt.append(1,c);
	}


	/* Close stream */
	fclose( stream ) ;



	return Parse(cnt,CONTEXT_WHOLE);
}

//##ModelId=49D4770F0167
const char *CHtml::GetVer() const
{
    return m_szVersion;
}


//##ModelId=49D4838A00CB
enum ESYMBOL CHtml::GetSymbolType(char const &c)
{
	enum ESYMBOL res = SYMBOL_UNKNOWN;

	switch(c)
	{
	case '<': 
		res = SYMBOL_TAG_BEGIN;
		break;
	case '>': 
		res = SYMBOL_TAG_END;
		break;
	case ' ':case '\t':case '\r':case '\n':
		res = SYMBOL_SPACE;
		break;
	case '=': 
		res = SYMBOL_TAG_ATTR_ASIGN;
		break;
	case '"':case '\'':
		res = SYMBOL_TAG_ATTR_QUTOE;
		break;
	case '/':
		res = SYMBOL_ALPHA;
		break;
	case '!':
		res = SYMBOL_DOCTYPE_HEADER;
		break;
	default:
		if(('0'<=c) && (c <='9'))
			res = SYMBOL_NUMBER;
		else if((('a'<=c)&& (c<='z'))|| (('A'<=c) && (c<='Z')))
			res = SYMBOL_ALPHA;

		break;
	}
	return res;
}

//##ModelId=49D483D701C5
enum ESYMBOL CHtml::GetSymbolType(const char *p)
{
	return GetSymbolType(*p);
}

//##ModelId=49D48403034B
enum ESYMBOL CHtml::GetSymbolType(std::string::const_iterator &iter)
{
	return GetSymbolType(*iter);
}


/*初始化节点*/
void CHtml::Init()
{
	Clear();

	m_pCurNode = this;
	m_eCurState = STATE_UNKNOWN;
	m_sTmp = "";
}

void CHtml::IdentifyUnkwown(const string &src, string::const_iterator &pos)
{
	if(pos == src.end())
		return;
	switch(GetSymbolType(*pos))
	{
	case SYMBOL_TAG_BEGIN:
		m_eCurState = STATE_MAYBE_ELEMENT;
		m_sTmp.append(1,*pos++);
		break;
	case SYMBOL_SPACE:
		pos++;
		break;
	default:
		m_eCurState = STATE_TEXT;		
		break;
	}

}


void CHtml::IdentifyMayBeElement(const string &src, string::const_iterator &pos)
{
	switch(GetSymbolType(*pos))
	{
	case SYMBOL_TAG_BEGIN:
		m_sTmp.append(1,*pos++);
		m_eCurState = STATE_MAYBE_ELEMENT;
		break;
	case SYMBOL_SPACE:
		m_sTmp.append(1,*pos++);
		while((GetSymbolType(*pos) == SYMBOL_SPACE) && (pos!=src.end())) pos++;

		break;
	case SYMBOL_ALPHA:
		m_sTmp = "";
		if((m_pCurNode->GetTagName() == "script") && (*pos != '/'))
			m_eCurState = STATE_TEXT;
		else
			m_eCurState = STATE_ELEMENT;
		break;
	case SYMBOL_DOCTYPE_HEADER:
		m_sTmp = "";
		//comment
		if((*(pos+1) == '-') && (*(pos+2) == '-'))
		{
			pos+=3;
			m_eCurState = STATE_COMMENT;			
		}
		//<![CDATA[
		else if((*(pos+1) == '[') && (*(pos+2) == 'C') && (*(pos+3) == 'D') && (*(pos+4) == 'A')
			&& (*(pos+5) == 'T')&& (*(pos+6) == 'A')&& (*(pos+7) == '['))
		{
			pos+= 8;			
			m_eCurState = STATE_CDATA;			
		}
		//doctype
		else
		{
			m_eCurState = STATE_ELEMENT;
		}
		break;
	default:
		m_eCurState = STATE_TEXT;
		break;
	}
}

void CHtml::IdentifyText(const string  & src,string::const_iterator & pos)
{
	CText *m_pText = NULL;

	if(m_pTmpNode != NULL)
	{
		m_pText = dynamic_cast<CText *>(m_pTmpNode);   
	}

	if(!m_pText)
	{
		m_pText = new CText(m_pCurNode);
		m_pTmpNode =  m_pText;
	}

	m_pText->Append(m_sTmp);


	switch(GetSymbolType(*pos))
	{
	case SYMBOL_TAG_BEGIN:
		m_sTmp.append(1,*pos++);
		m_eCurState = STATE_MAYBE_ELEMENT;
		break;
	case SYMBOL_SPACE:
		m_pText->Append(' ');pos++;
		while((GetSymbolType(*pos) == SYMBOL_SPACE) && (pos!=src.end())) pos++;
		break;
	default:
		m_pText->Append(*pos++);	
		break;
	}
}
void CHtml::IdentifyElementAttrNameQuote(const string  & src,string::const_iterator & pos)
{
	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);

	ASSERT(mpElement) ;


	

	while((pos != src.end()) && (*pos!=m_cQuote)) 
		m_sTmp.append(1,*pos++);

	if(pos != src.end())
	{
		mpElement->AppendAttr(m_sTmp);

		pos++;

		m_sTmp = "";

		m_eCurState = STATE_ELEMENT_ATTR_NAME;
	}

}
void CHtml::IdentifyElementAttrValueQuote(const string  & src,string::const_iterator & pos)
{
	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);

	ASSERT(mpElement) ;
	

	
		
	while((pos != src.end()) && (*pos!=m_cQuote)) 
		m_sTmp.append(1,*pos++);

	if(pos != src.end())
	{
		if(m_eCurState != STATE_ELEMENT_ATTR_NAME)
		{
			mpElement->SetAttrValue(m_sTmp);

			pos++;
			m_eCurState = STATE_ELEMENT_ATTR_NAME;
		}
	}
}
void CHtml::IdentifyComment(const string  & src,string::const_iterator & pos)
{
	CText *m_pText = NULL;
	CComment *m_pComm = NULL;
	CElement *mpElement = NULL;
	

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);



	if(m_pText)
	{
		m_sTmp = m_sTmp.substr(0,m_sTmp.size() -1);
		m_pText->Append(m_sTmp);

		m_pCurNode->AppendTextChild(m_pText);
		
		
	//	delete m_pTmpNode;
		m_pTmpNode = NULL;
	}

	if(!m_pComm)
	{
		m_pComm = new CComment(m_pCurNode);
		m_pTmpNode =  mpElement;
	}




	while(pos != src.end())
	{
		if((*pos == '-') && (*(pos+1) == '-')&& (*(pos+2) == '>'))
		{
			pos += 3;
			if(m_sTmp.size() > 0)
			{
				m_sTmp = "<!--" + m_sTmp;
				m_sTmp.append("-->",3);
				m_pComm->Append(m_sTmp);
				m_pCurNode->AppendTextChild(m_pComm);
			}
			m_eCurState = STATE_UNKNOWN;
			break;
			
		}
		else
		{
			m_sTmp.append(1,*pos++);
		}
	}
}
void CHtml::IdentifyCDATA(const string  & src,string::const_iterator & pos)
{
	CText *m_pText = NULL;
	CComment *m_pComm = NULL;
	CElement *mpElement = NULL;
	

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);


	if(!m_pText)
	{
		m_pText = new CText(m_pCurNode);
		m_pTmpNode =  m_pText;
	}




	while(pos != src.end())
	{
		if((*pos == ']') && (*(pos+1) == ']')&& (*(pos+2) == '>'))
		{
			
			pos += 3;
			if(m_sTmp.size() > 0)
			{
				m_sTmp = "<![CDATA[" + m_sTmp;
				m_sTmp.append("]]>",3);
				m_pText->Append(m_sTmp);
				m_pCurNode->AppendTextChild(m_pText);
				m_pTmpNode = NULL;
			}
			m_eCurState = STATE_UNKNOWN;
			break;
			
		}
		else
		{
			m_sTmp.append(1,*pos++);
		}
	}
}
void CHtml::IdentifyElement(const string  & src,string::const_iterator & pos)
{
	CText *m_pText = NULL;
	CComment *m_pComm = NULL;
	CElement *mpElement = NULL;
	

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);


	if(m_pText)
	{
		m_sTmp = m_sTmp.substr(0,m_sTmp.size() -1);
		m_pText->Append(m_sTmp);

		m_pCurNode->AppendTextChild(m_pText);
		
		
	//	delete m_pTmpNode;
		m_pTmpNode = NULL;
	}
	if(m_pComm)
	{
		m_sTmp = m_sTmp.substr(0,m_sTmp.size() -1);
		m_pText->Append(m_sTmp);

		m_pCurNode->AppendTextChild(m_pText);
		
		
	//	delete m_pTmpNode;
		m_pTmpNode = NULL;
	}


	if(!mpElement)
	{
		mpElement = new CElement(m_pCurNode);
		m_pTmpNode =  mpElement;
	}

	switch(GetSymbolType(*pos))
	{
	case SYMBOL_TAG_END:
		pos++;
		m_pCurNode->AppendElementChild(mpElement,this->m_pCurNode);
		m_pTmpNode = NULL;
		m_eCurState = STATE_UNKNOWN;
		break;
	case SYMBOL_SPACE:
		m_eCurState = STATE_ELEMENT_ATTR_NAME;
		pos++;
		while((GetSymbolType(*pos) == SYMBOL_SPACE) && (pos!=src.end())) pos++;
		break;
	default:
		mpElement->NameAppend(*pos++);	
		break;
	}
}

	
void CHtml::IdentifyElementAttrValue(const string  & src,string::const_iterator & pos)
{
	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);

	ASSERT(mpElement) ;

	switch(GetSymbolType(*pos))
	{
	case SYMBOL_TAG_END:
		pos++;
		mpElement->SetAttrValue(m_sTmp);
		m_sTmp = "";

		m_pCurNode->AppendElementChild(mpElement,this->m_pCurNode);
		m_pTmpNode = NULL;
		m_eCurState = STATE_UNKNOWN;
		break;
	case SYMBOL_TAG_ATTR_QUTOE:
		if(m_sTmp.size() != 0)
		{
			mpElement->SetAttrValue(m_sTmp);
			m_eCurState = STATE_ELEMENT_ATTR_NAME;
		}
		m_sTmp = "";

		m_cQuote = *pos++;

		m_eCurState = STATE_ELEMENT_ATTR_VALUE_QUOTE;

		break;
	case SYMBOL_SPACE:
		if(m_sTmp.size() != 0)
		{
			mpElement->SetAttrValue(m_sTmp);
			m_eCurState = STATE_ELEMENT_ATTR_NAME;
		}
		pos++;
		while((GetSymbolType(*pos) == SYMBOL_SPACE) && (pos!=src.end())) pos++;
		break;
	default:
		m_sTmp.append(1,*pos++);
		break;
	}

}

void CHtml::IdentifyElementAttrMayBeValue(const string  & src,string::const_iterator & pos)
{
	
	if(pos == src.end())
		return;
		
	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);

	ASSERT(mpElement) ;

	switch(GetSymbolType(*pos))
	{
	case SYMBOL_TAG_ATTR_ASIGN:
		//mpElement->AppendAttr(m_sTmp);
		m_eCurState = STATE_ELEMENT_ATTR_VALUE;
		pos++;
		break;
	default:
		m_eCurState = STATE_ELEMENT_ATTR_NAME;
		break;
	}
}
void CHtml::IdentifyElementAttrName(const string  & src,string::const_iterator & pos)
{
	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);

	ASSERT(mpElement) ;

	switch(GetSymbolType(*pos))
	{
	case SYMBOL_TAG_END:
		pos++;
		mpElement->AppendAttr(m_sTmp);
		m_pCurNode->AppendElementChild(mpElement,this->m_pCurNode);
		m_pTmpNode = NULL;
		m_eCurState = STATE_UNKNOWN;
		break;
	case SYMBOL_TAG_ATTR_QUTOE:		
		mpElement->AppendAttr(m_sTmp);
		m_cQuote = *pos++;
		m_eCurState = STATE_ELEMENT_ATTR_NAME_QUOTE;
		break;
	case SYMBOL_SPACE:
		if(m_sTmp.size() != 0)
			mpElement->AppendAttr(m_sTmp);
		
		m_eCurState = STATE_MAYBE_ELEMENT_ATTR_VALUE;
		pos++;
		while((GetSymbolType(*pos) == SYMBOL_SPACE) && (pos!=src.end())) pos++;
		break;
	case SYMBOL_TAG_ATTR_ASIGN:
		mpElement->AppendAttr(m_sTmp);
		m_sTmp="";
		m_eCurState = STATE_ELEMENT_ATTR_VALUE;
		pos++;
		break;
	default:
		m_sTmp.append(1,*pos++);
		break;
	}

}

void CHtml::AssertValid(const CNode *pnode, CText *&pText, CElement *&pEle,CComment * & pComment)
{
	CNode * TmpNode = (CNode *) pnode;

	if(TmpNode)
	{
		pText = dynamic_cast<CText *>(TmpNode);   
		pEle = dynamic_cast<CElement *>(TmpNode); 
		pComment = dynamic_cast<CComment *>(TmpNode);  
		
		ASSERT(pText || pEle || pComment);
	}
	/*
	if(pnode)
	{
		pText = dynamic_cast<CText *>(m_pTmpNode);   
		pEle = dynamic_cast<CElement *>(m_pTmpNode); 
		pComment = dynamic_cast<CComment *>(m_pTmpNode);  
		
		ASSERT(pText || pEle || pComment);
	}
	*/
}

void CHtml::EnClosed()
{
	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	AssertValid(m_pTmpNode,m_pText,mpElement,m_pComm);


	if(m_pText)
	{
		m_sTmp = m_sTmp.substr(0,m_sTmp.size() -1);
		m_pText->Append(m_sTmp);

		m_pCurNode->AppendTextChild(m_pText);
		
		
	//	delete m_pTmpNode;
		m_pTmpNode = NULL;
	}
	if(m_pComm)
	{
		m_sTmp = m_sTmp.substr(0,m_sTmp.size() -1);
		m_pComm->Append(m_sTmp);

		m_pCurNode->AppendTextChild(m_pComm);
		
		
	//	delete m_pTmpNode;
		m_pTmpNode = NULL;
	}


	if(mpElement)
	{
		m_pCurNode->AppendElementChild(mpElement,this->m_pCurNode);
		m_pTmpNode = NULL;
	}

	m_eCurState = STATE_UNKNOWN;

}
