// ***********************************************
// 
// 创建日期： 2009-11-18
// 
// 作    者： gaoyong
// 
// 电子邮件： gaoyong@my-soft.net.cn
// 
// 主要功能： 实现对html文件的格式化输出，以及类似
// 
//            BPEL的流程控制。
// 
// ***********************************************
#ifdef WIN32
#include "stdafx.h"
#endif

#include "CMyAny.h"



map <void * ,int>  CMyAny:: m_mPtrRefCnt;

//##ModelId=4B0B566E00F4
CMyAny::operator int()
{
	switch(GetType())
	{
	case VT_INTEGER:
			return m_int;
	case VT_DOUBLE:
			return (int)m_double;
	case VT_STRING:
		return CBaseEncode::StringToInt(m_string);
	default:
		return 0;
	}
}
CMyAny::operator double()
{
	switch(GetType())
	{
	case VT_INTEGER:
			return m_int;
	case VT_DOUBLE:
			return m_double;
	case VT_STRING:
		return CBaseEncode::StringToDouble(m_string);
	default:
		return 0;
	}
}

//##ModelId=4B0B567B02F8
CMyAny::operator string &()
{
	switch(GetType())
	{
	case VT_INTEGER:
		m_string =CBaseEncode::IntToString(m_int);
		break;
	case VT_DOUBLE:
		m_string =CBaseEncode::DoubleToString(m_double);
		break;
	case VT_STRING:
		break;
	default:
		m_string =  "";
	}
	return m_string;
}
CMyAny::operator CStringVector &()
{	
	return m_stringvector;
}
CMyAny::operator CStringMap &()
{	
	return m_stringmap;
}
CMyAny::operator CStringVectorMap &()
{	
	return m_stringvectormap;
}

//##ModelId=4B0B56830104
CMyAny::operator CHtml *()
{
	switch(GetType())
	{
	case VT_P_CELEMENT:
		m_pCHtml = (CHtml *) m_pCElement;
	}
	return m_pCHtml;
}

//##ModelId=4B0B57F802BC
CMyAny::operator CElement *()
{
	switch(GetType())
	{
	case VT_P_CHTML:
		m_pCElement = (CHtml *) m_pCHtml;
	}
	return m_pCElement;
}

CMyAny::operator CNode *()
{
	switch(GetType())
	{
	case VT_P_CHTML:
		m_pCNode = (CNode *) m_pCHtml;
		break;
	case VT_P_CELEMENT:
		m_pCNode = (CNode *) m_pCElement;
		break;
	}
	return m_pCNode;
}

//##ModelId=4B0B59AF0156
CMyAny::CMyAny()
{
	Init();
}


//##ModelId=4B0B59AF0165
CMyAny::CMyAny(const CMyAny& right)
{
	Init();
	*this = right;
}

//##ModelId=4B0B59AF01C3
CMyAny::~CMyAny()
{
	Release();
}

//##ModelId=4B0B59AF01E3
CMyAny& CMyAny::operator=(const CMyAny& right)
{
	this->m_eType = right.m_eType;

	switch(right.GetType())
	{
	case VT_INTEGER:
		this->m_int = right.m_int;
		break;
	case VT_DOUBLE:
		this->m_double = right.m_double;
		break;
	case VT_STRING:
		this->m_string = right.m_string;
		break;
//2010新增字符串处理类
	case VT_STRINGVECTOR:
		this->m_stringvector = right.m_stringvector;
		break;
	case VT_STRINGVECTORMAP:
		this->m_stringvectormap = right.m_stringvectormap;
		break;
	case VT_STRINGMAP:
		this->m_stringmap = right.m_stringmap;
		break;




		
	case VT_P_CHTML:
		this->m_pCHtml = right.m_pCHtml;
		break;
	case VT_P_CELEMENT:
		this->m_pCElement = right.m_pCElement;
		break;
	case VT_P_CNODE:
		this->m_pCNode = right.m_pCNode;
		break;
	}
	AddRef();
	return *this;
}

//##ModelId=4B0B59AF0250
int CMyAny::operator==(const CMyAny& right)
{
	int res = 0;

	switch(right.GetType())
	{
	case VT_INTEGER:
		res = (this->m_int == right.m_int);
		break;
	case VT_DOUBLE:
		res = (this->m_double == right.m_double);
		break;
	case VT_STRING:
		res = (this->m_string == right.m_string);
		break;
	case VT_P_CHTML:
		res = (this->m_pCHtml == right.m_pCHtml);
		break;
	case VT_P_CELEMENT:
		res = (this->m_pCElement == right.m_pCElement);
		break;
	case VT_P_CNODE:
		res = (this->m_pCNode == right.m_pCNode);
		break;
	}

	return res;
}

//##ModelId=4B0B59AF02BD
int CMyAny::operator!=(const CMyAny& right)
{
	int res = 0;

	switch(right.GetType())
	{
	case VT_INTEGER:
		res = (this->m_int != right.m_int);
		break;
	case VT_DOUBLE:
		res = (this->m_double != right.m_double);
		break;
	case VT_STRING:
		res = (this->m_string != right.m_string);
		break;
	case VT_P_CHTML:
		res = (this->m_pCHtml != right.m_pCHtml);
		break;
	case VT_P_CELEMENT:
		res = (this->m_pCElement != right.m_pCElement);
		break;
	case VT_P_CNODE:
		res = (this->m_pCNode != right.m_pCNode);
		break;
	}

	return res;
}

//##ModelId=4B0B59AF032A
int CMyAny::operator<(const CMyAny& right)
{
	int res = 0;

	switch(right.GetType())
	{
	case VT_INTEGER:
		res = (this->m_int < right.m_int);
		break;
	case VT_DOUBLE:
		res = (this->m_double < right.m_double);
		break;
	case VT_STRING:
		res = (this->m_string < right.m_string);
		break;
	case VT_P_CHTML:
		res = (this->m_pCHtml < right.m_pCHtml);
		break;
	case VT_P_CELEMENT:
		res = (this->m_pCElement < right.m_pCElement);
		break;
	case VT_P_CNODE:
		res = (this->m_pCNode < right.m_pCNode);
		break;
	}

	return res;
}

//##ModelId=4B0B59AF03C7
int CMyAny::operator<=(const CMyAny& right)
{
	
	int res = 0;

	switch(right.GetType())
	{
	case VT_INTEGER:
		res = (this->m_int <= right.m_int);
		break;
	case VT_DOUBLE:
		res = (this->m_double <= right.m_double);
		break;
	case VT_STRING:
		res = (this->m_string <= right.m_string);
		break;
	case VT_P_CHTML:
		res = (this->m_pCHtml <= right.m_pCHtml);
		break;
	case VT_P_CELEMENT:
		res = (this->m_pCElement <= right.m_pCElement);
		break;
	case VT_P_CNODE:
		res = (this->m_pCNode <= right.m_pCNode);
		break;
	}

	return res;
}

//##ModelId=4B0B59B000C9
int CMyAny::operator>(const CMyAny& right)
{
	
	int res = 0;

	switch(right.GetType())
	{
	case VT_INTEGER:
		res = (this->m_int > right.m_int);
		break;
	case VT_DOUBLE:
		res = (this->m_double > right.m_double);
		break;
	case VT_STRING:
		res = (this->m_string > right.m_string);
		break;
	case VT_P_CHTML:
		res = (this->m_pCHtml > right.m_pCHtml);
		break;
	case VT_P_CELEMENT:
		res = (this->m_pCElement > right.m_pCElement);
		break;
	case VT_P_CNODE:
		res = (this->m_pCNode > right.m_pCNode);
		break;
	}

	return res;
}

//##ModelId=4B0B59B00136
int CMyAny::operator>=(const CMyAny& right)
{
	
	int res = 0;

	switch(right.GetType())
	{
	case VT_INTEGER:
		res = (this->m_int >= right.m_int);
		break;
	case VT_DOUBLE:
		res = (this->m_double >= right.m_double);
		break;
	case VT_STRING:
		res = (this->m_string >= right.m_string);
		break;
	case VT_P_CHTML:
		res = (this->m_pCHtml >= right.m_pCHtml);
		break;
	case VT_P_CELEMENT:
		res = (this->m_pCElement >= right.m_pCElement);
		break;
	case VT_P_CNODE:
		res = (this->m_pCNode >= right.m_pCNode);
		break;
	}

	return res;
}

//##ModelId=4B0B68720286
CMyAny::CMyAny(int intVal)
{
	Init();
	m_eType = VT_INTEGER;

	m_int = intVal;
}
CMyAny::CMyAny(double dblVal)
{
	Init();
	m_eType = VT_DOUBLE;

	m_double = dblVal;
}


//##ModelId=4B0B68940380
CMyAny::CMyAny(const string &stringVal)
{
	Init();
	m_eType = VT_STRING;

	m_string = stringVal;
}
CMyAny::CMyAny(string &stringVal)
{
	Init();
	m_eType = VT_STRING;

	m_string = stringVal;
}

CMyAny::CMyAny(const CStringVector &stringvectorVal)
{
	Init();
	m_eType = VT_STRINGVECTOR;

	m_stringvector= stringvectorVal;
}
CMyAny::CMyAny(CStringVector &stringvectorVal)
{
	Init();
	m_eType = VT_STRINGVECTOR;

	m_stringvector = stringvectorVal;
}

CMyAny::CMyAny(const CStringMap &stringmapVal)
{
	Init();
	m_eType = VT_STRINGMAP;

	m_stringmap= stringmapVal;
}
CMyAny::CMyAny(CStringMap &stringmapVal)
{
	Init();
	m_eType = VT_STRINGMAP;

	m_stringmap = stringmapVal;
}
CMyAny::CMyAny(const CStringVectorMap &stringvectormapVal)
{
	Init();
	m_eType = VT_STRINGVECTORMAP;

	m_stringvectormap = stringvectormapVal;
}
CMyAny::CMyAny(CStringVectorMap &stringvectormapVal)
{
	Init();
	m_eType = VT_STRINGVECTORMAP;

	m_stringvectormap = stringvectormapVal;
}
//##ModelId=4B0B68C30015
CMyAny::CMyAny(CElement *elementVal)
{
	Init();
	m_eType = VT_P_CELEMENT;

	m_pCElement = elementVal;

	AddRef();
}
CMyAny::CMyAny(CNode *nodeVal)
{
	Init();
	m_eType = VT_P_CNODE;

	m_pCNode = nodeVal;

	AddRef();
}

//##ModelId=4B0B68EE00D1
CMyAny::CMyAny(CHtml *htmlVal)
{
	Init();
	m_eType = VT_P_CHTML;

	m_pCHtml = htmlVal;
	AddRef();
}


//##ModelId=4B0B693F02B5
EVarType CMyAny::GetType()
{
	return m_eType;
}
//##ModelId=4B0B693F02B5
EVarType CMyAny::GetType() const
{
	return m_eType;
}

