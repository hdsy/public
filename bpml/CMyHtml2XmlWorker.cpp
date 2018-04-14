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

#include <iconv.h>
#include "CMyHtml2XmlWorker.h"
#include "CMyAny.h"
#include "myEncrypt.h"


 
#include <string>
#include <sstream>
#include <iostream> 


/****************************************************************
 * 功能:读取指定字符串中的一部分字符串\0结尾
 * 输入: 
 *	para1  -M string 源字符串
 *	para2  -M string|int  偏移量
 *	para3  -M string|int 输入输出长度，如果是变量则会输出实际长度
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_ReadCString(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;

	//执行函数

	string p1 = para1;
	int p2 = para2;
	int p3 = para3;

	

	string tmp = MyUtility::CMemString::ReadCString(p1,p2,p3);
	
	//输出结果
	//ClearLocalVarSpace();
	
	{
		CMyAny resVarValue(tmp);
		string resVarName = "String_UrlDecode" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}

	//输出结果
	return res;
}

/****************************************************************
 * 功能:读取指定字符串中的一个整数
 * 输入: 
 *	para1  -M string 源字符串
 *	para2  -M string|int  偏移量
 *	para3  -M string|int 长度，仅输出
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_ReadInt(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;
	if((para3.GetType() != VT_STRING) && (para3.GetType() != VT_INTEGER))
		return res;

	//执行函数

	string p1 = para1;
	int p2 = para2;
	int p3 = para3;

	int r = MyUtility::CMemString::ReadInt(p1,p2,p3);

	//输出结果
	//ClearLocalVarSpace();
	CMyAny resVarValue(r);
	string resVarName = "MemString_ReadInt_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);

	//设置输出参数值
	string iopara = para_list.at(2);
	if(iopara.at(0) == '$')
	{
		CMyAny ioPara(p3);
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(iopara.substr(1,iopara.size()-1),ioPara);
		}
		else
		{
			m_mVar.SetVarValue(iopara.substr(1,iopara.size()-1),ioPara);
		}
	}
	

	res = "$" +resVarName;
	return res;
}
string CMyHtml2XmlWorker::String_ToInt(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数

	string p1 = para1;

	int r = MyUtility::CBaseEncode::StringToInt(p1);

	//输出结果
	//ClearLocalVarSpace();
	CMyAny resVarValue(r);
	string resVarName = "String_ToInt_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);

	res = "$" +resVarName;
	return res;
}

/****************************************************************
 * 功能:实现HTML查找算法之后，看结果集的个数
 * 输入: 
 *	para1  -M CElement|CHtml|CNode  html解析后的节点
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Html_Count(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if((para1.GetType() != VT_P_CELEMENT) && (para1.GetType() != VT_P_CHTML) && (para1.GetType() != VT_P_CNODE) )
		return res;

	//执行函数

	CNode * pNode = para1;

	CElement * pElement = dynamic_cast<CElement * > (pNode);

	if(!pElement) return res;

	//输出结果
	//ClearLocalVarSpace();
	CMyAny resVarValue((int)pElement->GetResult().size());
	string resVarName = "count_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);

	res = "$" +resVarName;
	return res;
}
/****************************************************************
 * 功能:实现HTML查找算法之后，返回指定的结果集中一个
 * 输入: 
 *	para1  -M CElement|CHtml|CNode  html解析后的节点
 *	para1  -M string|int  指定第几个
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Html_GetResult(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;

	if((para1.GetType() != VT_P_CELEMENT) && (para1.GetType() != VT_P_CHTML)  && (para1.GetType() != VT_P_CNODE))
		return res;
	if((para2.GetType() != VT_INTEGER) &&  (para2.GetType() != VT_STRING))
		return res;

	//执行函数
	
	CNode * pNode = para1;

	CElement * pElement = dynamic_cast<CElement * > (pNode);

	if(!pElement) return res;

	int idx = para2;

	//输出结果
	//ClearLocalVarSpace();
	if(idx < pElement->GetResult().size())
	{
		CMyAny resVarValue((CElement * )pElement->GetResult(idx));
		string resVarName = "item_" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	return res;
}

/****************************************************************
 * 功能:获取系统函数帮助
 * 输入: 
 *	para1  -O 函数名，如果不填则输出所有的 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Sys_GetHelp(vector <string > & para_list)
{
	string funname = "";
	//检查参数
	CMyAny para1;
	if((para_list.size() == 1) && (FetchVarValue(para_list.at(0),para1) == 0) && (para1.GetType() == VT_STRING))
	{		
		funname =(string &) para1;
	}
	string  res = ("");


	MyUtility::CStringMap::const_iterator iter;
	if(funname != "")
	{
		iter = m_mFunctionDesc.find(funname);

		res += funname + "\r\n";

		if(iter == m_mFunctionDesc.end())
			res += "不支持的函数." ;
		else
			res += iter->second+ "\r\n";
	}
	else
	{
		for(iter = m_mFunctionDesc.begin(); iter != m_mFunctionDesc.end(); iter++)
		{
			res += iter->first + "\r\n";
			res += iter->second;
			res += "\r\n";
		}
	}


	return res;
}

/****************************************************************
 * 功能:获取map的指定序号的元素
 * 输入: 
 *	para1  -M CStringMap|CStringVectorMap 节点名
 *	para2  -M int|string 序号
 *	para3  -M string value or name 指定是返回first还是second
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Map_At(vector <string > & para_list)
{
	string res("NULL");

	

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if((para2.GetType() != VT_STRING)  && (para2.GetType() != VT_INTEGER))
		return res;
	if((para3.GetType() != VT_STRING)  )
		return res;

	int index = para2;

	string vi = para3;

	//执行函数
	CMyAny resVarValue;
	
	if(para1.GetType() == VT_STRINGMAP) 
	{
	
		CStringMap &sm = para1;

		CStringMap::const_iterator iter ;
		iter = sm.begin();

		if(index < sm.size())
		{
			for(int i = 0; i <index;i++)
				iter++;

			if(vi == "name")
				resVarValue = iter->first;
			else if(vi == "value")
				resVarValue = iter->second;
			else
				resVarValue = iter->first;
		}
		else
			return res;
	}
	else if(para1.GetType() == VT_STRINGVECTORMAP) 
	{
	
		CStringVectorMap &svm = para1;

		CStringVectorMap::const_iterator iter ;
		iter = svm.begin();

	
		if(index < svm.size())
		{
			for(int i = 0; i <index;i++)
				iter++;


			
			if(vi == "name")
				resVarValue = iter->first;
			else if(vi == "value")
				resVarValue = iter->second;
			else
				resVarValue = iter->first;
		}
		else
		{
			return res;
		}
	}
	else
	{
	
		return res;
	}


	//输出结果
	//ClearLocalVarSpace();
	
	{
		string resVarName = "map_at_" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	
	return res;
}
/****************************************************************
 * 功能:获取map的指定key对应的value
 * 输入: 
 *	para1  -M CStringMap|CStringVectorMap 节点名
 *	para2  -M string key
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Map_GetValueByKey(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;

	if(para2.GetType() != VT_STRING)
		return res;

	string name = para2;

	//执行函数
	CMyAny resVarValue;
	
	if(para1.GetType() == VT_STRINGMAP) 
	{
		CStringMap &sm = para1;

		CStringMap::const_iterator iter ;
		iter = sm.find(name);
		if(iter != sm.end())
			resVarValue = iter->second;
		else
			return res;
	}
	else if(para1.GetType() == VT_STRINGVECTORMAP) 
	{
		CStringVectorMap &sm = para1;

		CStringVectorMap::const_iterator iter ;
		iter = sm.find(name);
		if(iter != sm.end())
			resVarValue = iter->second;
		else
			return res;
	}
	else
		return res;

	

	//输出结果
	//ClearLocalVarSpace();
	
	{
		string resVarName = "map_nv_" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	return res;
}
/****************************************************************
 * 功能:取map的大小
 * 输入: 
 *	para1  -M CStringVectormap|CStringMap 节点名
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Map_Size(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	CMyAny resVarValue;
		
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if((para1.GetType() == VT_STRINGVECTORMAP) )
	{
		CStringVectorMap &sm = para1;
		resVarValue = (int)sm.size();
	}
	else if(para1.GetType() == VT_STRINGMAP)
	{
		CStringMap &sm = para1;
		resVarValue = (int)sm.size();
	}
	else
		return res;

	//输出结果
	//ClearLocalVarSpace();
	
	string resVarName = "count_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);

	res = "$" +resVarName;
	return res;
}

/****************************************************************
 * 功能:取数组的指定序号的元素
 * 输入: 
 *	para1  -M CStringVector 
 *	para2  -M string|int 需要
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Vector_At(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;

	if(para1.GetType() != VT_STRINGVECTOR)
		return res;
	if((para2.GetType() != VT_INTEGER) &&  (para2.GetType() != VT_STRING))
		return res;

	//执行函数
	
	CStringVector &sv = para1;

	int idx = para2;

	//输出结果
	//ClearLocalVarSpace();
	if(idx < sv.size())
	{
		CMyAny resVarValue(sv.at(idx));
		string resVarName = "item_" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	return res;
}
/****************************************************************
 * 功能:将字符串切割为map
 * 输入: 
 *	para1  -M string 节点名
 *	para2  -M string 元素间分隔符
 *	para3  -M string 元素内名值分隔符
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Map_Split(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3,para4;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;


	if((para1.GetType() != VT_STRING))
		return res;
	if((para2.GetType() != VT_STRING) )
		return res;
	if((para3.GetType() != VT_STRING) )
		return res;

	//执行函数
	string p1 = para1;
	string p2 = para2;

	string p3 = para3;

	MyUtility::CStringMap sm;
	MyUtility::CStringVectorMap svm;

	sm.Split(p1,p2,p3,true,MyUtility::CBaseEncode::UrlDecode);
	svm.Split(p1,p2,p3,true,MyUtility::CBaseEncode::UrlDecode);


	//输出结果:如果有参数3，则表示指定结束idx
	//ClearLocalVarSpace();

	string p4("null");

	if((para_list.size() == 4) && (FetchVarValue(para_list.at(3),para4) == 0) && (para4.GetType() == VT_STRING) )
	{
		p4 = (string &)para4;		
	}
	string resVarName = "str_split_to_map_" + GetTmpVarName();

	if("vectormap" == p4)
	{
		CMyAny resVarValue(svm);

		m_mVar.SetVarValue(resVarName,resVarValue);
	}
	else
	{

		CMyAny resVarValue(sm);

		m_mVar.SetVarValue(resVarName,resVarValue);
	}
	res = "$" + resVarName;

	return res;
}

/****************************************************************
 * 功能:将map组装成字符串
 * 输入: 
 *	para1  -M CStringMap|CStringVectorMap 节点名
 *	para2  -M string 元素间分隔符
 *	para2  -M string 元素内名值分隔符
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Map_Join(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;


	if((para2.GetType() != VT_STRING) )
		return res;
	if((para3.GetType() != VT_STRING) )
		return res;

	string p2 = para2;

	string p3 = para3;
	//执行函数
	if(para1.GetType() == VT_STRINGMAP) 
	{
		MyUtility::CStringMap p1 = para1;
		res = p1.Join(p2,p3,MyUtility::CBaseEncode::UrlEncode);		
	}
	else if(para1.GetType() == VT_STRINGVECTORMAP)
	{
		MyUtility::CStringVectorMap p1 = para1;
		res = p1.Join(p2,p3,MyUtility::CBaseEncode::UrlEncode);		
	}
	else
	{
		return res;
	}

	return res;
}

/****************************************************************
 * 功能:将vector组装成字符串
 * 输入: 
 *	para1  -M CStringVector 节点名
 *	para2  -M string 元素间分隔符
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Vector_Join(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para2.GetType() != VT_STRING) )
		return res;

	string p2 = para2;

	//执行函数
	if(para1.GetType() == VT_STRINGVECTOR) 
	{
		MyUtility::CStringVector p1 = para1;
		res = p1.Join(p2,MyUtility::CBaseEncode::UrlEncode);		
	}
	else
	{
		return res;
	}

	return res;
}
/****************************************************************
 * 功能:将字符串切割为数组
 * 输入: 
 *	para1  -M string 节点名
 *	para2  -M string 元素间分隔符
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Vector_Split(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() < 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING))
		return res;
	if((para2.GetType() != VT_STRING) )
		return res;

	//执行函数
	string p1 = para1;
	string p2 = para2;


	MyUtility::CStringVector sv;

	sv.Split(p1,p2,true,MyUtility::CBaseEncode::UrlDecode);


	//输出结果:如果有参数3，则表示指定结束idx
	//ClearLocalVarSpace();

	CMyAny resVarValue(sv);
	string resVarName = "str_split_to_map_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);

	res = "$" + resVarName;

	return res;
}
/****************************************************************
 * 功能:取数组的大小
 * 输入: 
 *	para1  -M CStringVector 节点名
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Vector_Size(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRINGVECTOR)
		return res;

	//执行函数

	CStringVector &sv = para1;

	//输出结果
	//ClearLocalVarSpace();
	CMyAny resVarValue((int)sv.size());
	string resVarName = "count_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);

	res = "$" +resVarName;
	return res;
}


/****************************************************************
 * 功能:读取指定字符串中的一部分字符串
 * 输入: 
 *	para1  -M string 源字符串
 *	para2  -M string|int  偏移量
 *	para3  -O string|int 长度，不填则渠道字符串尾部
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_SubStr(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 2)  && (para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING))
		return res;
	if((para2.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER))
		return res;

	//执行函数
	string p1 = para1;
	int p2 = para2;

	int p3 = p1.size() - p2;

	if(p3 <= 0)
		return res;

	//输出结果:如果有参数3，则表示指定结束idx
	if(para_list.size() ==  3)
	{
		if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;
		if((para3.GetType() != VT_STRING) && (para3.GetType() != VT_INTEGER))
			return res;

		int tmp = para3;

		if(tmp < p3)
			p3 = tmp;
	}

	res = p1.substr(p2,p3);

	//ClearLocalVarSpace();

	return res;
}


string  CMyHtml2XmlWorker::String_ToUpper(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	string p1 = para1;
	

	
	string tmp ;

	string::iterator iter = p1.begin();
	
	for(iter;iter != p1.end(); iter++)
		tmp.append(1,(char)::toupper(*iter));
	
	//输出结果
	//ClearLocalVarSpace();
	
	{
		CMyAny resVarValue(tmp);
		string resVarName = "String_UrlDecode" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	
	return res;
}
string  CMyHtml2XmlWorker::String_ToLower(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	string p1 = para1;
	

	string tmp ;

	string::iterator iter = p1.begin();
	
	for(iter;iter != p1.end(); iter++)
		tmp.append(1,(char)::tolower(*iter));
	
	//输出结果
	//ClearLocalVarSpace();
	
	{
		CMyAny resVarValue(tmp);
		string resVarName = "String_UrlDecode" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	
	return res;
}
/****************************************************************
 * 功能:按照顺序连接一组字符串
 * 输入: 不许大于等于1个
 *	para...  -M string|int 节点名
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_Cat(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() < 1)
		return res;
	
	//执行函数
	CMyAny para;
	string tmp;
	for(int i=0;i<para_list.size();i++)
	{
		if(0 == FetchVarValue(para_list.at(i),para))
		{
			if((para.GetType() == VT_STRING) || (para.GetType() == VT_INTEGER))
				tmp += (string &)para;
		}
	}

	//输出结果
	//ClearLocalVarSpace();
	
	{
		CMyAny resVarValue(tmp);
		string resVarName = "String_UrlDecode" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}


	return res;
}

/****************************************************************
 * 功能:将字符串左右两边指定的字符串去掉
 * 输入: 
 *	para1 -M string 待处理字符串
 *	para2  -M string左边需要去掉的字符集合
 *	para3 -M string 右边需要去掉的字符集合
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_Trim(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() !=3)
		return res;
	//
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;


	if((para1.GetType() != VT_STRING))
		return res;
	if((para2.GetType() != VT_STRING))
		return res;
	if((para3.GetType() != VT_STRING))
		return res;

	//执行函数
	string p1 = para1;
	string p2 = para2;
	string p3 = para3;

	CBaseEncode::TrimLeft(p1,p2);
	CBaseEncode::TrimRight(p1,p3);


	//ClearLocalVarSpace();
	res = p1;


	return res;
}

/****************************************************************
 * 功能:实现HTML节点子节点的个数，或者指定序号的子节点
 * 输入: 
 *	para1  -M CElement|CHtml|CNode  html解析后的节点
 *	para2 -O string|int  指定第几个
 *    NULL 失败，其他为运算的结果
****************************************************************/

string CMyHtml2XmlWorker::Html_Child(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 1) && (para_list.size() != 2))
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;


	if((para1.GetType() != VT_P_CELEMENT) && (para1.GetType() != VT_P_CHTML) && (para1.GetType() != VT_P_CNODE) )
		return res;

	//执行函数
	CNode * pNode = para1;

	CElement * pElement = dynamic_cast<CElement * > (pNode);

	if(!pElement) return res;


	if(para_list.size() == 2)
	{
		if(FetchVarValue(para_list.at(1),para2) != 0)
			return res;

		if((para2.GetType() != VT_INTEGER) &&  (para2.GetType() != VT_STRING))
			return res;


		int idx = para2;

		//输出结果
	//ClearLocalVarSpace();
		if(idx < pElement->Child().size())
		{
			CMyAny resVarValue((CNode * )pElement->Child(idx));
			string resVarName = "child_" + GetTmpVarName();

			m_mVar.SetVarValue(resVarName,resVarValue);

			res = "$" + resVarName;
		}
	}
	else
	{
		CMyAny resVarValue((int)pElement->Child().size());
		string resVarName = "child_" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	return res;
}
/****************************************************************
 * 功能:取指定节点的指定属性名的属性值
 * 输入: 
 *	para1  -M CElement|CHtml|CNode  html解析后的节点
 *	para2  -M string  属性名
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Html_GetAttrValue(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;

	if((para1.GetType() != VT_P_CELEMENT) && (para1.GetType() != VT_P_CHTML) && (para1.GetType() != VT_P_CNODE))
		return res;
	if((para2.GetType() != VT_STRING))
		return res;

	//执行函数
	CNode * pNode = para1;

	CElement * pElement = dynamic_cast<CElement * > (pNode);

	if(!pElement) return res;

	string attrVal,attrName = para2;

	//输出结果
	//ClearLocalVarSpace();
	res = pElement->GetAttrValue(attrName,attrVal);

	return res;
}

/****************************************************************
 * 功能:取指定节点下的所有指定标签名的节点
 * 输入: 
 *	para1  -M CElement|CHtml|CNode  html解析后的节点
 *	para2  -M string 表签名
 *	para3  -M string|int 指定匹配规则
 				0 精确匹配
 				1 首部匹配
 				2 包含:节点名包含para2
 				3 被包含: para2 包含接点名
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Html_GetElementByTagName(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if((para1.GetType() != VT_P_CELEMENT) && (para1.GetType() != VT_P_CHTML) && (para1.GetType() != VT_P_CNODE) )
		return res;
	if((para2.GetType() != VT_STRING))
		return res;
	if((para3.GetType() != VT_STRING) && (para3.GetType() != VT_INTEGER))
		return res;

	//执行函数
	
	CNode * pNode = para1;

	CElement * pElement = dynamic_cast<CElement * > (pNode);

	if(!pElement) return res;

	string tagName = para2;

	int mode = para3;


	pElement->GetElementByTagName(tagName,mode);

	//输出结果	
	//ClearLocalVarSpace();
	CMyAny resVarValue(pElement);
	string resVarName = "tag_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);


	res = "$" +resVarName;
	return res;
}
/****************************************************************
 * 功能:实现整数与字符串的对比
 * 输入: 
 *	para1  -M string|int 左参数
 *    para2  -M string|int 右参数
 *    para3  -O string|int 如果为0，表示仅大于，如果为1 表示可等于
 * 返回:
 *    bool  fasle 失败，true表示para1 >= para2
****************************************************************/
string CMyHtml2XmlWorker::Math_GT(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;
	if((para3.GetType() != VT_STRING) && (para3.GetType() != VT_INTEGER))
		return res;

	//执行函数
	int mode = para3;

	string sTmp = para2;

	int iTmp = para2;

	if(para1.GetType() == VT_STRING)
		para2 = sTmp;
	else
		para2 = iTmp;




	switch(mode)
	{
	case 0://绝对匹配
		{
			if(para1 > para2)
			{
				res = "true";
			}
			else
			{
				res = "false";
			}
			break;
		}
	case 1://可以等于
		{
			if(para1 >= para2)
			{
				res = "true";
			}
			else
			{
				res = "false";
			}
			break;
		}

	}
		

	//ClearLocalVarSpace();
	return res;
}

/****************************************************************
 * 功能:实现整数与字符串的对比
 * 输入: 
 *	para1  -M string|int 左参数
 *    para2  -M string|int 右参数
 *    para3  -O string|int 如果为0，表示仅大于，如果为1 表示可等于
 * 返回:
 *    bool  fasle 失败，true表示para1 <= para2
****************************************************************/
string CMyHtml2XmlWorker::Math_LT(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;
	if((para3.GetType() != VT_STRING) && (para3.GetType() != VT_INTEGER))
		return res;

	//执行函数
	int mode = para3;

	string sTmp = para2;

	int iTmp = para2;

	if(para1.GetType() == VT_STRING)
		para2 = sTmp;
	else
		para2 = iTmp;


	switch(mode)
	{
	case 0://绝对匹配
		{
			if(para1 < para2)
			{
				res = "true";
			}
			else
			{
				res = "false";
			}
			break;
		}
	case 1://可以等于
		{
			if(para1 <= para2)
			{
				res = "true";
			}
			else
			{
				res = "false";
			}
			break;
		}

	}
		
	//ClearLocalVarSpace();

	return res;
}

/****************************************************************
 * 功能:实现整数与字符串的对比
 * 输入: 
 *	para1  -M string|int 左参数
 *    para2  -M string|int 右参数
 * 返回:
 *    bool  fasle 失败，true表示相等
****************************************************************/
string CMyHtml2XmlWorker::Math_EQU(vector <string > & para_list)

{
	string res("false");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;

	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;

	//执行函数

	string sTmp = para2;

	int iTmp = para2;

	if(para1.GetType() == VT_STRING)
		para2 = sTmp;
	else
		para2 = iTmp;

	if(para1 == para2)
	{
		res = "true";
	}
	else
	{
		res = "false";
	}
	//ClearLocalVarSpace();

	return res;
}

string CMyHtml2XmlWorker::Math_AND(vector <string > & para_list)
{
	string res("false");

	CMyAny para;
	string spara;

	for(int i=0;i<para_list.size();i++)
	{
		//检查参数
		if(FetchVarValue(para_list.at(i),para) != 0)
			return res;
		if(para.GetType() != VT_STRING) 
			return res;
		spara = (string &)para;

		if(spara != "true")
			return res;
		//执行函数
	}

	return "true";	
}
string CMyHtml2XmlWorker::Math_OR(vector <string > & para_list)
{
	string res("false");

	CMyAny para;
	string spara;

	for(int i=0;i<para_list.size();i++)
	{
		//检查参数
		if(FetchVarValue(para_list.at(i),para) != 0)
			return res;
		if(para.GetType() != VT_STRING) 
			return res;
		spara = (string &)para;

		if(spara == "true")
			return "true";
		//执行函数
	}

	return res;	
}
/****************************************************************
 * 功能:实现整数的加法运算
 * 输入: 
 *	para1  -M string|int 左参数
 *    para2  -M string|int 右参数
 *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Inc(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 2)  && (para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;

	//执行函数
	int p1 = para1;
	int p2 = para2;


	CMyAny resTmp =  p1+p2;

	//输出结果:如果有参数3，则表示将结果也输出到此变量中
	if(para_list.size() ==  3)
	{
		if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;
		if((para3.GetType() != VT_STRING))
			return res;

	//ClearLocalVarSpace();
	string varname = para3;
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(varname,resTmp);
		}
		else
		{
			m_mVar.SetVarValue(varname,resTmp);
		}
	}

	res = (string &)resTmp;

	return res;
}
/****************************************************************
 * 功能:实现double类型数的加法运算
 * 输入: 
 *	para1  -M string|int|double 左参数
 *    para2  -M string|int|double 右参数
 *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Double_Add(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 2)  && (para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER)&& (para2.GetType() != VT_DOUBLE))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER)&& (para2.GetType() != VT_DOUBLE))
		return res;

	//执行函数
	double p1 = para1;
	double p2 = para2;


	CMyAny resTmp =  p1+p2;

	//输出结果:如果有参数3，则表示将结果也输出到此变量中
	if(para_list.size() ==  3)
	{
		if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;
		if((para3.GetType() != VT_STRING))
			return res;

		string varname = para3;
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(varname,resTmp);
		}
		else
		{
			m_mVar.SetVarValue(varname,resTmp);
		}
	}

	res = (string &)resTmp;

	return res;
}
/****************************************************************
 * 功能:实现double类型数的减法运算
 * 输入: 
 *	para1  -M string|int|double 左参数
 *    para2  -M string|int|double 右参数
 *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Double_Sub(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 2)  && (para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER)&& (para2.GetType() != VT_DOUBLE))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER)&& (para2.GetType() != VT_DOUBLE))
		return res;

	//执行函数
	double p1 = para1;
	double p2 = para2;


	CMyAny resTmp =  p1-p2;

	//输出结果:如果有参数3，则表示将结果也输出到此变量中
	if(para_list.size() ==  3)
	{
		if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;
		if((para3.GetType() != VT_STRING))
			return res;

		string varname = para3;
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(varname,resTmp);
		}
		else
		{
			m_mVar.SetVarValue(varname,resTmp);
		}
	}

	res = (string &)resTmp;

	return res;
}
/****************************************************************
 * 功能:实现double类型数的乘法运算
 * 输入: 
 *	para1  -M string|int|double 左参数
 *    para2  -M string|int|double 右参数
 *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Double_Mul(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 2)  && (para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER)&& (para2.GetType() != VT_DOUBLE))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER)&& (para2.GetType() != VT_DOUBLE))
		return res;

	//执行函数
	double p1 = para1;
	double p2 = para2;


	CMyAny resTmp =  p1*p2;

	//输出结果:如果有参数3，则表示将结果也输出到此变量中
	if(para_list.size() ==  3)
	{
		if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;
		if((para3.GetType() != VT_STRING))
			return res;

		string varname = para3;
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(varname,resTmp);
		}
		else
		{
			m_mVar.SetVarValue(varname,resTmp);
		}
	}

	res = (string &)resTmp;

	return res;
}
/****************************************************************
 * 功能:实现double类型数的除法运算
 * 输入: 
 *	para1  -M string|int|double 左参数
 *    para2  -M string|int|double 右参数
 *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Double_Div(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 2)  && (para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER)&& (para2.GetType() != VT_DOUBLE))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER)&& (para2.GetType() != VT_DOUBLE))
		return res;

	//执行函数
	double p1 = para1;
	double p2 = para2;

	if(p2 == 0.0)  return res;

	CMyAny resTmp =  p1/p2;

	//输出结果:如果有参数3，则表示将结果也输出到此变量中
	if(para_list.size() ==  3)
	{
		if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;
		if((para3.GetType() != VT_STRING))
			return res;

		string varname = para3;
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(varname,resTmp);
		}
		else
		{
			m_mVar.SetVarValue(varname,resTmp);
		}
	}

	res = (string &)resTmp;

	return res;
}
/****************************************************************
 * 功能:实现Un3des算法
 * 输入: 
 *	para1  -M string 待加密字符串
 *	para2  -M string 加密密钥
 
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Un3Des(vector <string > & para_list)
{
	string res("");

	//检查参数
	if(para_list.size() != 2)  
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) )
		return res;
	if((para2.GetType() != VT_STRING) )
		return res;

	//执行函数
	string p1 = para1;
	string p2 = para2;

	CMyEncrypt::UnDes3(p1,p2,res);

	return res;
}
/****************************************************************
 * 功能:实现3des算法
 * 输入: 
 *	para1  -M string 待加密字符串
 *	para2  -M string 加密密钥
 
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_3Des(vector <string > & para_list)
{
	string res("");

	//检查参数
	if(para_list.size() != 2)  
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) )
		return res;
	if((para2.GetType() != VT_STRING) )
		return res;

	//执行函数
	string p1 = para1;
	string p2 = para2;

	CMyEncrypt::Des3(p1,p2,res);

	return res;
}
/****************************************************************
 * 功能:实现md5算法
 * 输入: 
 *	para1  -M string 输入参数
 
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Md5(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)  
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;


	if((para1.GetType() != VT_STRING) )
		return res;

	//执行函数
	string p1 = para1;

	CMyEncrypt::md5(p1,res);

	return res;
}
/****************************************************************
 * 功能:实现sha1算法
 * 输入: 
 *	para1  -M string 输入参数
 
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Sha1(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)  
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;


	if((para1.GetType() != VT_STRING) )
		return res;

	//执行函数
	string p1 = para1;

	CMyEncrypt::sha1(p1,res);

	return res;
}

/****************************************************************
 * 功能:实现sha1算法
 * 输入: 
 *	para1  -M string 签名原始字符串
	para2  -M string alipay的签名值
	para3  -M string 签名算法RSA RSA2
	para4  -M string alipay的公钥
 
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_AlipayNotifyVerifySign(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 4)  
		return res;
	
	CMyAny para1,para2,para3,para4;
	if( (FetchVarValue(para_list.at(0),para1) != 0) ||(para1.GetType() != VT_STRING)||
		(FetchVarValue(para_list.at(1),para2) != 0)||(para2.GetType() != VT_STRING)||
		(FetchVarValue(para_list.at(2),para3) != 0)||(para3.GetType() != VT_STRING)||
		(FetchVarValue(para_list.at(3),para4) != 0)||(para4.GetType() != VT_STRING))
		return res;


	//执行函数
	string p1 = para1,p2=para2,p3=para3,p4=para4;

	if(CMyEncrypt::AlipayNotifyVerifySign(p1,p2,p3,p4) == 0)
		res =  "true";
	else
		res = "false";

	return res;
}
/****************************************************************
 * 功能:实现mod算法
 * 输入: 
 *	para1  -M int 输入参数用来取模的数
 *  para2  -M int 模数
 
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Mod(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 2)  && (para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;

	//执行函数
	int p1 = para1;
	int p2 = para2;


	CMyAny resTmp =  p1%p2;


	//输出结果:如果有参数3，则表示将结果也输出到此变量中
	if(para_list.size() ==  3)
	{
		if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;
		if(para3.GetType() != VT_STRING) 
			return res;

		//ClearLocalVarSpace();
		string varname = para3;
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(varname,resTmp);
		}
		else
		{
			m_mVar.SetVarValue(varname,resTmp);
		}
	}

	res = (string &)resTmp;

	return res;
}
/****************************************************************
 * 功能:实现整数的减法运算
 * 输入: 
 *	para1  -M string|int 左参数
 *    para2  -M string|int 右参数
 *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中
 * 返回:
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Math_Sub(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if((para_list.size() != 2)  && (para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if((para1.GetType() != VT_STRING) && (para1.GetType() != VT_INTEGER))
		return res;
	if((para2.GetType() != VT_STRING) && (para2.GetType() != VT_INTEGER))
		return res;

	//执行函数
	int p1 = para1;
	int p2 = para2;


	CMyAny resTmp =  p1-p2;

	//输出结果:如果有参数3，则表示将结果也输出到此变量中
	if(para_list.size() ==  3)
	{
		if(FetchVarValue(para_list.at(2),para3) != 0)
			return res;
		if(para3.GetType() != VT_STRING) 
			return res;

	//ClearLocalVarSpace();
		string varname = para3;
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(varname,resTmp);
		}
		else
		{
			m_mVar.SetVarValue(varname,resTmp);
		}
	}

	res = (string &)resTmp;

	return res;
}
/****************************************************************
 * 功能:将指定内容存放到指定的路径的文件中 
 * 输入: 
 *	para1  -M string 文件名
 *    para2  -M string 写入文件的内容
 *    para3  -O string 文件的打开模式wb a+ 等等
 * 返回:
 *    bool  false 写失败，true写成功
****************************************************************/
string CMyHtml2XmlWorker::File_Store(vector <string > & para_list)
{
	string res("false");

	//检查参数
	if((para_list.size() != 2)&&(para_list.size() != 3))
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if(para1.GetType() != VT_STRING)
		return res;
	if(para2.GetType() != VT_STRING)
		return res;

	//执行函数
	string p1 = para1;
	string p2 = para2;

	string mode = "wb";

	if((para_list.size() == 3) && (FetchVarValue(para_list.at(2),para3) == 0)&&(para3.GetType() == VT_STRING))
	{
		mode = (string &)para3;
	}

/*	
	CFile file1;
	file1.Open("G:\\1114.gif",CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite  );
	file1.Write(p2.data(),p2.size());
	file1.Close();
*/
	FILE *stream;
	//没有b的时候，会转换,比如0a ->  0d0a
	if( (stream  = fopen( p1.c_str(), mode.c_str() )) != NULL )
	{
		long sz = fwrite(p2.data(),sizeof(char),p2.size(),stream);

		if(sz == p2.size() )
			res = "true";
		/* Close stream */
		fclose( stream ) ;
	}
	

	//ClearLocalVarSpace();
	return res;
}


/****************************************************************
* 功能:按照时间戳生成特定的文件名
* 输入: p1+midName+"_"+tmMark+p3;
*	  para1  -M string 文件名前缀
*	  para2  -M string 文件名中间名，md5(para2)
*	  para3  -M string 文件名后缀
*	  para4  -M string|int 时间间隔now/p4
* 返回:
*    NULL 失败，其他为文件名
****************************************************************/
string CMyHtml2XmlWorker::File_GenCachName(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 4)
		return res;
	
	CMyAny para1,para2,para3,para4;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;
	if(FetchVarValue(para_list.at(3),para4) != 0)
		return res;


	if(para1.GetType() != VT_STRING)
		return res;
	if(para2.GetType() != VT_STRING)
		return res;
	if(para3.GetType() != VT_STRING)
		return res;
	if((para4.GetType() != VT_INTEGER)&&(para4.GetType() != VT_STRING))
		return res;

	//执行函数
	string p1 = para1;
	string p2 = para2;
	string p3 = para3;
	int p4 = para4;

	//1.   md5(midEle)
	string midName ;
	CMyEncrypt::md5(p2,midName);


	//2.取当前时间
	string tmMark;

	time_t now;    time( &now );

	int a = now/p4;

	tmMark = CBaseEncode::IntToString(a);



	//3.生成名字
	res = p1+midName+"_"+tmMark+p3;

	//返回结果
	//ClearLocalVarSpace();
	return res;
}

/****************************************************************
* 功能:读取指定文件的内容
* 输入: 
*	  para1  -M string 文件名
*	  para2  -M string 文件内容存放的参数名
* 返回:
*    bool fale 失败，true 成功
****************************************************************/
string CMyHtml2XmlWorker::File_Read(vector <string > & para_list)
{
	string res("false");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if(para1.GetType() != VT_STRING)
		return res;
	if(para2.GetType() != VT_STRING)
		return res;

	//执行函数
	string p1 = para1;
	string p2 = para2;

	string cnt;  char c;

	FILE *stream;
	if( (stream  = fopen( p1.c_str(), "r" )) == NULL )
		return res;
	
	fseek(stream,0,SEEK_END);
	
	LONG fLength = ftell(stream);

	fseek(stream,0,SEEK_SET);

	cnt.reserve(fLength);

	int actReadCount = 0;

	for(LONG i=0;i<fLength;i++)
	{
		actReadCount = fread( &c, sizeof( char ), 1, stream );

		if(actReadCount != 1)
			break;

		cnt.append(1,c);
		
	}


	/* Close stream */
	fclose( stream ) ;

	CMyAny resTmp =  cnt;

	//输出结果:
	//ClearLocalVarSpace();
	{
		string varname = p2;
		if(m_gpVar)
		{
			m_gpVar->SetVarValue(varname,resTmp);
		}
		else
		{
			m_mVar.SetVarValue(varname,resTmp);
		}
	}

	res = "true";
	

	return res;
}

/****************************************************************
 * 功能:删除指定的路径的文件
 * 输入: 
 *	  para1  -M string 文件名
 * 返回:
 *    bool  false 失败，true成功
****************************************************************/
string CMyHtml2XmlWorker::File_Delete(vector <string > & para_list)
{
	string res("false");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;


	if(para1.GetType() != VT_STRING)
		return res;

	//执行函数
	string p1 = para1;

	if(DeleteFile(p1.c_str()))
		res = "true";


	//输出结果:
	//ClearLocalVarSpace();

	return res;
}

/****************************************************************
 * 功能:将字符串进行URL解码
 * 输入: 
 *	para1  -M string 源字符串

 	   "%25"->"%" 
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_UrlDecode(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	string p1 = para1;
	

	string tmp = CBaseEncode::UrlDecode(p1);
	
	//输出结果
	//ClearLocalVarSpace();
	
	{
		CMyAny resVarValue(tmp);
		string resVarName = "String_UrlDecode" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	
	return res;
}
/****************************************************************
 * 功能:将字符串进行URL编码
 * 输入: 
 *	para1  -M string 源字符串

 	   "%" ->"%25"
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_UrlEncode(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	string p1 = para1;
	
	string tmp = CBaseEncode::UrlEncode(p1);
	
	//输出结果
	//ClearLocalVarSpace();
	
	{
		CMyAny resVarValue(tmp);
		string resVarName = "String_UrlEncode" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" + resVarName;
	}
	
	return res;
}

/****************************************************************
 * 功能:将字符串进行xml解码
 * 输入: 
 *	para1  -M string 源字符串

 	    "&gt;"->">"
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_XmlDecode(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	string p1 = para1;
	
	res = CBaseEncode::XmlDecode(p1);
	
	//ClearLocalVarSpace();
	return res;
}
/****************************************************************
 * 功能:将字符串进行xml编码
 * 输入: 
 *	para1  -M string 源字符串

 	   ">" ->"&gt;"
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_XmlEncode(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	string p1 = para1;
	
	res = CBaseEncode::XmlEncode(p1);
	

	return res;
}
/****************************************************************
 * 功能:将BCD字符串转换为普通CHAR字符串
 * 输入: 
 *	para1  -M string 源字符串

 	"31"  ->  "1"
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_ToChar(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	string p1 = para1;
	
	res = CBaseEncode::HexStrToCharStr(p1);
	

	return res;
}
/****************************************************************
 * 功能:将char字符串转换为BCD字符串
 * 输入: 
 *	para1  -M string 源字符串

 	   "1"->"31" 
 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_ToHex(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	string p1 = para1;
	
	res = CBaseEncode::CharStrToHexStr(p1);
	

	return res;
}

/***************************************************************
 * 功能: 从指定字符串中搜寻第一个匹配的字符串位置
 * 输入: 
 *	para1  -M string 源字符串
 *	para2  -M string 待匹配的字符串?
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_Find(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;

	if((para1.GetType() != VT_STRING) )
		return res;
	if((para2.GetType() != VT_STRING))
		return res;

	//执行函数
	string src = para1;

	string tag = para2;


	int idx = src.find(tag);

	//ClearLocalVarSpace();

	if(idx != string::npos)
	{
		//输出结果
		CMyAny resVarValue((int)idx);
		string resVarName = "String_Find_" + GetTmpVarName();

		m_mVar.SetVarValue(resVarName,resVarValue);

		res = "$" +resVarName;
	}

	return res;
}
/***************************************************************
 * 功能:取指定节点下的所有指定标签名的节点
 * 输入: 
 *	para1  -M string 源字符串
 *	para2  -M string 对比字符串
 *	para3  -M string|int 指定匹配规则
 				0 精确匹配
 				1 首部匹配
 				2 包含:para1 包含para2
 				3 被包含: para2 包含para1
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_Has(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if((para1.GetType() != VT_STRING) )
		return res;
	if((para2.GetType() != VT_STRING))
		return res;
	if((para3.GetType() != VT_STRING) && (para3.GetType() != VT_INTEGER))
		return res;

	//执行函数
	string src = para1;

	string tag = para2;

	int mode = para3;


	switch(mode)
	{
	case 0://绝对匹配
		{
			if(src == tag)
			{
				res = "true";
			}
			else
			{
				res = "false";
			}
			break;
		}
	case 1://首部匹配
		{
			if(src.find(tag) == 0)
			{
				res = "true";
			}
			else
			{
				res = "false";
			}
			break;
		}
	case 2://包含
		{
			if(src.find(tag) != string::npos)
			{
				res = "true";
			}
			else
			{
				res = "false";
			}
			break;
		}
	case 3://被
		{
			if(tag.find(src) != string::npos)
			{
				res = "true";
			}
			else
			{
				res = "false";
			}
			break;
		}


	}
		

	//ClearLocalVarSpace();
	return res;
}
/****************************************************************
 * 功能:获取节点的innerText
 * 输入: 
 *	para1  -M CElement|CHtml|CNode 节点名
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Html_GetInnerText(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if((para1.GetType() != VT_P_CELEMENT) && (para1.GetType() != VT_P_CHTML) && (para1.GetType() != VT_P_CNODE))
		return res;

	//执行函数


	//输出结果
	////ClearLocalVarSpace();
	if(para1.GetType() != VT_P_CNODE)
	{
		CElement * pElement = para1;
		res = pElement->GetInnerText();
	}
	else
	{
		CNode * pNode = para1;

		CElement * pElement = dynamic_cast<CElement * > (pNode);
		if(pElement)
			res = pElement->GetInnerText();
		else
			res = pNode->ToString();
	}

	return res;
}

/****************************************************************
 * 功能:取指定节点下的所有含有属性名值的节点
 * 输入: 
 *	para1  -M CElement|CHtml|CNode  html解析后的节点
 *	para2  -M string 属性名
 *	para3  -M string 属性值
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Html_GetElementByAttrNV(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1,para2,para3;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if((para1.GetType() != VT_P_CELEMENT) && (para1.GetType() != VT_P_CHTML)  && (para1.GetType() != VT_P_CNODE))
		return res;

	if(para2.GetType() != VT_STRING)
		return res;

	if(para3.GetType() != VT_STRING)
		return res;

	//执行函数
	
	CNode * pNode = para1;

	CElement * pElement = dynamic_cast<CElement * > (pNode);

	if(!pElement) return res;
	string n = para2;
	string v = para3;

	pElement->GetElementByAttrNV(n,v);

	//输出结果
	//ClearLocalVarSpace();
	CMyAny resVarValue(pElement);
	string resVarName = "nv_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);

	res = "$" + resVarName;
	return res;
}

/****************************************************************
 * 功能:解析html
 * 输入: 
 *	para1  -M 内容或者是文件名
 *	para2  -M string|int  指定para1的形式
                      1 是html文件
                      2 是html字符串
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Html_Parse(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 2)
		return res;
	
	CMyAny para1,para2;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;

	if((para1.GetType() != VT_INTEGER) && (para1.GetType() != VT_STRING) )
		return res;

	if(para2.GetType() != VT_STRING)
		return res;

	//执行函数
	CHtml * pHtml = new CHtml;

	if(1 == (int)para1)
	{
		pHtml->ParseFile(para2);
	}
	else
	{
		pHtml->Parse(para2);
	}

	//输出结果
	//ClearLocalVarSpace();
	CMyAny resVarValue(pHtml);
	string resVarName = "parse_html_" + GetTmpVarName();

	m_mVar.SetVarValue(resVarName,resVarValue);

	res = "$" + resVarName;
	return res;
}
//##ModelId=4B0CB42302E8
string CMyHtml2XmlWorker::Call(const string &func_name, vector <string > & para_list)
{
	CMyAny tmp;

	string res("NULL"),func;
	if(FetchVarValue(func_name,tmp) != 0)
		return res;

	func = (string &)tmp;

	switch(m_mFunction[func])
	{
	case 10000:
		res = Sys_GetHelp(para_list);
		break;
	case 1://parse_html
		res = Html_Parse(para_list);
		break;
	case 2://nv
		res = Html_GetElementByAttrNV(para_list);
		break;
	case 3://item
		res = Html_GetResult(para_list);
		break;
	case 4://count
		res = Html_Count(para_list);
		break;
	case 5://attr
		res = Html_GetAttrValue(para_list);
		break;
	case 6://text
		res = Html_GetInnerText(para_list);
		break;
	case 7://tag
		res = Html_GetElementByTagName(para_list);
		break;
	case 8://has
		res = String_Has(para_list);
		break;
	case 9://gt
		res = Math_GT(para_list);
		break;
	case 10://lt
		res = Math_LT(para_list);
		break;
	case 11://equ
		res = Math_EQU(para_list);
		break;
	case 12://inc
		res = Math_Inc(para_list);
		break;
	case 13://sub
		res = Math_Sub(para_list);
		break;
	case 14://store
		res = File_Store(para_list);
		break;
	case 15://xmlDecode
		res = String_XmlDecode(para_list);
		break;
	case 23://xmlEncode
		res = String_XmlEncode(para_list);
		break;
	case 16://child
		res = Html_Child(para_list);
		break;
	case 17://read
		res = File_Read(para_list);
		break;
	case 18://strcat
		res = String_Cat(para_list);
		break;
	case 19://strsub
		res = String_SubStr(para_list);
		break;
	case 20://del
		res = File_Delete(para_list);
		break;
	case 21://string gen_file_name(string prefix,string midEle,string postfix,int intval)
		res = File_GenCachName(para_list);
		break;
	case 22://string strtrim(string src,string left,string rigth)
		res = String_Trim(para_list);
		break;
	case 24://dbl_add
		res = Math_Double_Add(para_list);
		break;
	case 25://dbl_sub
		res = Math_Double_Sub(para_list);
		break;
	case 26://dbl_mul
		res = Math_Double_Mul(para_list);
		break;
	case 27://dbl_div
		res = Math_Double_Div(para_list);
		break;
	case 28://m_mFunction["map_size"] = 28;
		res = Map_Size(para_list);
		break;
	case 29://m_mFunction["map_nv"] = 29;
		res = Map_GetValueByKey(para_list);
		break;
	case 30://m_mFunction["vector_size"] = 30;
		res = Vector_Size(para_list);
		break;
	case 31 ://m_mFunction["vector_at"] = 31;
		res = Vector_At(para_list);
		break;
	case 32: //m_mFunction["str_split_to_vector"] = 32;
		res = Vector_Split(para_list);
		break;
	case 33 ://m_mFunction["str_split_to_map"] = 33;
		res = Map_Split(para_list);
		break;
	case 34://m_mFunction["map_at"] = 34;
		res = Map_At(para_list);
		break;
	case 35://m_mFunction["urllDecode"] = 35;	
		res = String_UrlDecode(para_list);
		break;
	case 36://m_mFunction["urlEncode"] = 36;
		res = String_UrlEncode(para_list);
		break;
	case 37://m_mFunction["MemString.ReadInt"] = 37;	
		res = String_ReadInt(para_list);
		break;
	case 38://m_mFunction["MemString.ReadCString"] = 38;
		res = String_ReadCString(para_list);
		break;
		break;
	case 39://
	/*m_mFunction["MemString.CharToHex"] = 39;
	m_mFunction["MemString.HexToChar"] = 40;
	string CharStrToHexStr(vector <string > & para_list);
	string HexStrToCharStr(vector <string > & para_list);	*/
		res = String_ToHex(para_list);
		break;
	case 40://m_mFunction["MemString.ReadCString"] = 38;
		res = String_ToChar(para_list);
		break;
	case 41://m_mFunction["Map.Join"] = 41;
		res = Map_Join(para_list);
		break;
	case 42://m_mFunction["Vector.Join"] = 42;
		res = Vector_Join(para_list);
		break;
	case 43://m_mFunction["String.ToUpper"] = 43;
		res = String_ToUpper(para_list);
		break;
	case 44://m_mFunction["String.ToLower"] = 44;
		res = String_ToLower(para_list);
		break;
	case 45://	m_mFunction["Math.Md5"] = 45;
		res = Math_Md5(para_list);
		break;
	case 46://	m_mFunction["String.Find"] = 46;
		res = String_Find(para_list);
		break;
	case 47://	m_mFunction["Math.3Des"] = 47;
		res = Math_3Des(para_list);
		break;
	case 48://	m_mFunction["Math.Un3Des"] = 48;
		res = Math_Un3Des(para_list);
		break;
	case 49://	m_mFunction["String.GetLength"] = 49;
		res = String_GetLength(para_list);
		break;	
	case 50://	m_mFunction["String.GetDatetime"] = 50;
		res = Date_GetDatetime(para_list);
		break;		
	case 51://	m_mFunction["String.ConvertCode"] = 51;
		res = String_ConvertCode(para_list);
		break;
	case 52://	m_mFunction["Math.Sha1"] = 52;
		res = Math_Sha1(para_list);
		break;
	case 53://	m_mFunction["Math.Sha1"] = 53;
		res = String_ToInt(para_list);
		break;
	case 54://	m_mFunction["Math.Sha1"] = 54;
		res = Math_Mod(para_list);
		break;
	case 55://	m_mFunction["Math.OR"] = 55;
		res = Math_OR(para_list);
		break;
	case 56://	m_mFunction["Math.AND"] = 56;
		res = Math_AND(para_list);
		break;
	case 57://	m_mFunction["Env.GetEmbVarValue"] = 57;
		res = Env_GetEmbVarValue(para_list);
		break;
	case 58://	m_mFunction["Math.AlipayNotifyVerifySign"] = 57;
		res = Math_AlipayNotifyVerifySign(para_list);
		break;
	default:
		break;
	}

	return res;

	
}

//##ModelId=4B0CB4D80048
CMyHtml2XmlWorker::CMyHtml2XmlWorker():m_gpVar(NULL)
{
	InitFunctionMap();
}
CMyHtml2XmlWorker::CMyHtml2XmlWorker(CMyVarSpace * global_var_space):m_gpVar(global_var_space)
{
	InitFunctionMap();
}

//##ModelId=4B0CB4D80087
CMyHtml2XmlWorker::~CMyHtml2XmlWorker()
{
	
}

//##ModelId=4B0CB6B103A4
CMyAny CMyHtml2XmlWorker::FetchVarValue(const string &var)
{
	CMyAny val;

	if( 0 == FetchVarValue(var,val))
		return val;

	else
		return val;

}

int CMyHtml2XmlWorker::FetchVarValue(const string &var, CMyAny &val)
{
	CMyAny * pTmpAny = NULL;
	int res = 1;

	if(var.empty())
		return 1;
	if(var.at(0) == '$')
	{
		if(var.size() > 1)
		{
			string tmpVar = var.substr(1,var.size()-1);

			if(tmpVar.at(0) == '$')
			{
				res = FetchVarValue(tmpVar,val);
				if(  res != 0) return res;

				if(val.GetType() == VT_STRING)
				{
					tmpVar = (string &)val;
				}
				else
				{
					return 1;// 无效参数
				}
			}

			//局部空间查找
			pTmpAny = m_mVar.GetVarValue(tmpVar);
			
			if(pTmpAny )
			{
				val = *pTmpAny;
				res = 0;
			}
			else
			{
				//全局查找
				if(m_gpVar)
				{
					pTmpAny = m_gpVar->GetVarValue(tmpVar);

					if(pTmpAny )
					{
						val = *pTmpAny;
						res = 0;
					}

				}

			}		
		}		

	}
	else
	{
		val = CBaseEncode::UrlDecode (var);
		res = 0;
	}
	return res;
}




string CMyHtml2XmlWorker::GetTmpVarName()
{
//	static int m_iTmpVar = 1;

	char szSid[10] = {0};

	sprintf(szSid,"%d",m_iTmpVar++);


	return string(szSid);


}
void CMyHtml2XmlWorker::InitFunctionDesc()
{
m_mFunctionDesc["Math.Un3Des"] =
"/****************************************************************\r\n"
" * 功能:实现Un3Des算法\r\n"
" * 输入: \r\n"
" *	  para1  -M string  待加密字符串\r\n"
" *	  para1  -M string  加密密钥\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.3Des"] =
"/****************************************************************\r\n"
" * 功能:实现3Des算法\r\n"
" * 输入: \r\n"
" *	  para1  -M string  待加密字符串\r\n"
" *	  para1  -M string  加密密钥\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.Md5"] =
"/****************************************************************\r\n"
" * 功能:实现md5算法\r\n"
" * 输入: \r\n"
" *	  para1  -M string  输入参数\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.Sha1"] =
"/****************************************************************\r\n"
" * 功能:实现sha1算法\r\n"
" * 输入: \r\n"
" *	  para1  -M string  输入参数\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";

m_mFunctionDesc["File.Delete"] =
"/****************************************************************\r\n"
" * 功能:删除指定的路径的文件\r\n"
" * 输入: \r\n"
" *	  para1  -M string 文件名\r\n"
" * 返回:\r\n"
" *    bool  false 失败，true成功\r\n"
"****************************************************************/\r\n";

m_mFunctionDesc["File.GenCachName"]=
"/****************************************************************\r\n"
"* 功能:按照时间戳生成特定的文件名\r\n"
"* 输入: p1+midName+\"_\"+tmMark+p3;\r\n"
"*	  para1  -M string 文件名前缀\r\n"
"*	  para2  -M string 文件名中间名，md5(para2)\r\n"
"*	  para3  -M string 文件名后缀\r\n"
"*	  para4  -M string|int 时间间隔now/p4\r\n"
"* 返回:\r\n"
"*    NULL 失败，其他为文件名\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["File.Read"] = 
"/****************************************************************\r\n"
"* 功能:读取指定文件的内容\r\n"
"* 输入: \r\n"
"*	  para1  -M string 文件名\r\n"
"*	  para2  -M string 文件内容存放的参数名\r\n"
"* 返回:\r\n"
"*    bool fale 失败，true 成功\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["File.Store"]=
"/****************************************************************\r\n"
" * 功能:将指定内容存放到指定的路径的文件中 \r\n"
" * 输入: \r\n"
" *	  para1  -M string 文件名\r\n"
" *    para2  -M string 写入文件的内容\r\n"
" *    para3  -O string 文件的打开模式wb a+ 等等\r\n"
" * 返回:\r\n"
" *    bool  false 写失败，true写成功\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Html.Child"]=
"/****************************************************************\r\n"
" * 功能:实现HTML节点子节点的个数，或者指定序号的子节点\r\n"
" * 输入: \r\n"
" *	para1  -M CElement|CHtml|CNode  html解析后的节点\r\n"
" *	para1  -O string|int  指定第几个\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Html.GetAttrValue"]=
"/****************************************************************\r\n"
" * 功能:取指定节点的指定属性名的属性值\r\n"
" * 输入: \r\n"
" *	para1  -M CElement|CHtml|CNode  html解析后的节点\r\n"
" *	para1  -M string  属性名\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Html.GetElementByAttrNV"]=
"/****************************************************************\r\n"
" * 功能:取指定节点下的所有含有属性名值的节点\r\n"
" * 输入: \r\n"
" *	para1  -M CElement|CHtml|CNode  html解析后的节点\r\n"
" *	para2  -M string 属性名\r\n"
" *	para3  -M string 属性值\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Html.GetElementByTagName"]=
"/****************************************************************\r\n"
" * 功能:取指定节点下的所有指定标签名的节点\r\n"
" * 输入: \r\n"
" *	para1  -M CElement|CHtml|CNode  html解析后的节点\r\n"
" *	para2  -M string 表签名\r\n"
" *	para3  -M string|int 指定匹配规则\r\n"
" 				0 精确匹配\r\n"
" 				1 首部匹配\r\n"
" 				2 包含:节点名包含para2\r\n"
" 				3 被包含: para2 包含接点名\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Html.GetInnerText"]=
"/****************************************************************\r\n"
" * 功能:获取节点的innerText\r\n"
" * 输入: \r\n"
" *	para1  -M CElement|CHtml|CNode 节点名\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Html.GetResult"]=
"/****************************************************************\r\n"
" * 功能:实现HTML查找算法之后，返回指定的结果集中一个\r\n"
" * 输入: \r\n"
" *	para1  -M CElement|CHtml|CNode  html解析后的节点\r\n"
" *	para2  -M string|int  指定第几个\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Html.Parse"]=
"/****************************************************************\r\n"
" * 功能:解析html\r\n"
" * 输入: \r\n"
" *	para1  -M 内容或者是文件名\r\n"
" *	para2  -M string|int  指定para1的形式\r\n"
"                      1 是html文件\r\n"
"                      2 是html字符串\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Html.Count"]=
"/****************************************************************\r\n"
" * 功能:实现HTML查找算法之后，看结果集的个数\r\n"
" * 输入: \r\n"
" *	para1  -M CElement|CHtml|CNode  html解析后的节点\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Map.At"]=
"/****************************************************************\r\n"
" * 功能:获取map的指定序号的元素\r\n"
" * 输入: \r\n"
" *	para1  -M CStringMap|CStringVectorMap 节点名\r\n"
" *	para2  -M int|string 序号\r\n"
" *	para3  -M string value or name 指定是返回first还是second\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Map.GetValueByKey"]=
"/****************************************************************\r\n"
" * 功能:获取map的指定key对应的value\r\n"
" * 输入: \r\n"
" *	para1  -M CStringMap|CStringVectorMap 节点名\r\n"
" *	para2  -M string key\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Map.Join"]=
"/****************************************************************\r\n"
" * 功能:将map组装成字符串\r\n"
" * 输入: \r\n"
" *	para1  -M CStringMap|CStringVectorMap 节点名\r\n"
" *	para2  -M string 元素间分隔符\r\n"
" *	para2  -M string 元素内名值分隔符\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Map.Size"]=
"/****************************************************************\r\n"
" * 功能:取map的大小\r\n"
" * 输入: \r\n"
" *	para1  -M CStringVectormap|CStringMap 节点名\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Map.Split"]=
"/****************************************************************\r\n"
" * 功能:将字符串切割为map\r\n"
" * 输入: \r\n"
" *	para1  -M string 节点名\r\n"
" *	para2  -M string 元素间分隔符\r\n"
" *	para3  -M string 元素内名值分隔符\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.Double_Add"]=
"/****************************************************************\r\n"
" * 功能:实现double类型数的加法运算\r\n"
" * 输入: \r\n"
" *	para1  -M string|int|double 左参数\r\n"
" *    para2  -M string|int|double 右参数\r\n"
" *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.Double_Div"]=
"/****************************************************************\r\n"
" * 功能:实现double类型数的除法运算\r\n"
" * 输入: \r\n"
" *	para1  -M string|int|double 左参数\r\n"
" *    para2  -M string|int|double 右参数\r\n"
" *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.Double_Mul"]=
"/****************************************************************\r\n"
" * 功能:实现double类型数的乘法运算\r\n"
" * 输入: \r\n"
" *	para1  -M string|int|double 左参数\r\n"
" *    para2  -M string|int|double 右参数\r\n"
" *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.Double_Sub"]=
"/****************************************************************\r\n"
" * 功能:实现double类型数的减法运算\r\n"
" * 输入: \r\n"
" *	para1  -M string|int|double 左参数\r\n"
" *    para2  -M string|int|double 右参数\r\n"
" *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.EQU"]=
"/****************************************************************\r\n"
" * 功能:实现整数与字符串的对比\r\n"
" * 输入: \r\n"
" *	para1  -M string|int 左参数\r\n"
" *    para2  -M string|int 右参数\r\n"
" * 返回:\r\n"
" *    bool  fasle 失败，true表示相等\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.GT"]=
"/****************************************************************\r\n"
" * 功能:实现整数与字符串的对比\r\n"
" * 输入: \r\n"
" *	para1  -M string|int 左参数\r\n"
" *    para2  -M string|int 右参数\r\n"
" *    para3  -O string|int 如果为0，表示仅大于，如果为1 表示可等于\r\n"
" * 返回:\r\n"
" *    bool  fasle 失败，true表示para1 >= para2\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.Inc"]=
"/****************************************************************\r\n"
" * 功能:实现整数的加法运算\r\n"
" * 输入: \r\n"
" *	para1  -M string|int 左参数\r\n"
" *    para2  -M string|int 右参数\r\n"
" *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.LT"]=
"/****************************************************************\r\n"
" * 功能:实现整数与字符串的对比\r\n"
" * 输入: \r\n"
" *	para1  -M string|int 左参数\r\n"
" *    para2  -M string|int 右参数\r\n"
" *    para3  -O string|int 如果为0，表示仅大于，如果为1 表示可等于\r\n"
" * 返回:\r\n"
" *    bool  fasle 失败，true表示para1 小于等于 para2\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Math.Sub"]=
"/****************************************************************\r\n"
" * 功能:实现整数的减法运算\r\n"
" * 输入: \r\n"
" *	para1  -M string|int 左参数\r\n"
" *    para2  -M string|int 右参数\r\n"
" *    para3  -O string 如果给出，则将运算结果设置到此参数命名的变量中\r\n"
" * 返回:\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.Cat"]=
"/****************************************************************\r\n"
" * 功能:按照顺序连接一组字符串\r\n"
" * 输入: 不许大于等于1个\r\n"
" *	para...  -M string|int 节点名\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.Find"]=
"/****************************************************************\r\n"
" * 功能: 查找字符串所在位置 \r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
" *	para2  -M string 对比字符串\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.Has"]=
"/****************************************************************\r\n"
" * 功能:取指定节点下的所有指定标签名的节点\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
" *	para2  -M string 对比字符串\r\n"
" *	para3  -M string|int 指定匹配规则\r\n"
" 				0 精确匹配\r\n"
" 				1 首部匹配\r\n"
" 				2 包含:para1 包含para2\r\n"
" 				3 被包含: para2 包含para1\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.ReadCString"]=
"/****************************************************************\r\n"
" * 功能:读取指定字符串中的一部分字符串\0结尾\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
" *	para2  -M string|int  偏移量\r\n"
" *	para3  -M string|int 输入输出长度，如果是变量则会输出实际长度\r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.ReadInt"]=
"/****************************************************************\r\n"
" * 功能:读取指定字符串中的一个整数\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
" *	para2  -M string|int  偏移量\r\n"
" *	para3  -M string|int 长度，仅输出\r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.SubStr"]=
"/****************************************************************\r\n"
" * 功能:读取指定字符串中的一部分字符串\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
" *	para2  -M string|int  偏移量\r\n"
" *	para3  -O string|int 长度，不填则渠道字符串尾部\r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.ToChar"]=
"/****************************************************************\r\n"
" * 功能:将BCD字符串转换为普通CHAR字符串\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
"\r\n"
" 	\"31\"  ->  \"1\"\r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.ToHex"]=
"/****************************************************************\r\n"
" * 功能:将BCD字符串转换为普通CHAR字符串\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
"\r\n"
" 	   \"1\"->\"31\" \r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.Trim"]=
"/****************************************************************\r\n"
" * 功能:将字符串左右两边指定的字符串去掉\r\n"
" * 输入: \r\n"
" *	para1 -M string 待处理字符串\r\n"
" *	para2  -M string左边需要去掉的字符集合\r\n"
" *	para3 -M string 右边需要去掉的字符集合\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.ToUpper"] = 
"/****************************************************************\r\n"
" * 功能:将字符串进行大写转换\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
"\r\n"
" 	   \"%25\"->\"%\" \r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.ToLower"] = 
"/****************************************************************\r\n"
" * 功能:将字符串进行小写转换\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
"\r\n"
" 	   \"%25\"->\"%\" \r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.UrlDecode"]=
"/****************************************************************\r\n"
" * 功能:将字符串进行URL解码\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
"\r\n"
" 	   \"%25\"->\"%\" \r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.UrlEncode"]=
"/****************************************************************\r\n"
" * 功能:将字符串进行URL编码\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
"\r\n"
" 	   \"%\" ->\"%25\"\r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.XmlDecode"]=
"/****************************************************************\r\n"
" * 功能:将字符串进行xml解码\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
"\r\n"
" 	    \"&gt;\"->\">\"\r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["String.XmlEncode"]=
"/****************************************************************\r\n"
" * 功能:将字符串进行xml编码\r\n"
" * 输入: \r\n"
" *	para1  -M string 源字符串\r\n"
"\r\n"
" 	  \">\" ->\"&gt;\"\r\n"
" 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Sys.GetHelp"]=
"/****************************************************************\r\n"
" * 功能:获取系统函数帮助\r\n"
" * 输入: \r\n"
" *	para1  -O 函数名，如果不填则输出所有的 				\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Vector.At"]=
"/****************************************************************\r\n"
" * 功能:取数组的指定序号的元素\r\n"
" * 输入: \r\n"
" *	para1  -M CStringVector \r\n"
" *	para2  -M string|int 需要\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Vector.Join"]=
"/****************************************************************\r\n"
" * 功能:将vector组装成字符串\r\n"
" * 输入: \r\n"
" *	para1  -M CStringVector 节点名\r\n"
" *	para2  -M string 元素间分隔符\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Vector.Size"]=
"/****************************************************************\r\n"
" * 功能:取数组的大小\r\n"
" * 输入: \r\n"
" *	para1  -M CStringVector 节点名\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
m_mFunctionDesc["Vector.Split"]=
"/****************************************************************\r\n"
" * 功能:将字符串切割为数组\r\n"
" * 输入: \r\n"
" *	para1  -M string 节点名\r\n"
" *	para2  -M string 元素间分隔符\r\n"
" *    NULL 失败，其他为运算的结果\r\n"
"****************************************************************/\r\n";
}

void CMyHtml2XmlWorker::InitFunctionMap()
{
	ClearLocalVarSpace();
	InitFunctionDesc();
	m_mFunction["Sys.GetHelp"] = 10000;


	//解析html:string parse_html(int type,string cnt)
	m_mFunction["Html.Parse"] = 1;

	//按照属性选择:string nv(CElement * p,string name,string value) 
	m_mFunction["Html.GetElementByAttrNV"] = 2;

	//按照属性选择:item(CElement * p,int idx) 
	m_mFunction["Html.GetResult"] = 3;

	//按照属性选择:count(CElement * p) 
	m_mFunction["Html.Count"] = 4;

	//按照属性选择:attr(CElement * p,string name) 
	m_mFunction["Html.GetAttrValue"] = 5;

	//按照属性选择:text(CElement * p) 
	m_mFunction["Html.GetInnerText"] = 6;

	//按照属性选择:tag(CElement * p,string tagname,int type mode) 
	m_mFunction["Html.GetElementByTagName"] = 7;



	//逻辑比较:bool has(string src,string tagname,int type mode) 
	m_mFunction["String.Has"] = 8;
	//逻辑比较:bool gt(string src,string tagname,int type mode) 
	m_mFunction["Math.GT"] = 9;
	//逻辑比较:bool lt(string src,string tagname,int type mode) 
	m_mFunction["Math.LT"] = 10;
	//逻辑比较:bool equ(string src,string tagname,int type mode) 
	m_mFunction["Math.EQU"] = 11;


	//算数运算:bool inc(string src,string tag) 
	m_mFunction["Math.Inc"] = 12;
	//算数运算:bool sub(string src,string tag) 
	m_mFunction["Math.Sub"] = 13;


	//文件操作:
	//int store(string path,string content)
	m_mFunction["File.Store"] = 14;
	//bool read(string filepath,string content)
	m_mFunction["File.Read"] = 17;
	//bool del(string filepath)
	m_mFunction["File.Delete"] = 20;
	//生成文件名，以支持永久性 string gen_file_name(string prefix,string midEle,string postfix,int intval)
	m_mFunction["File.GenCachName"] = 21;

	//写文件:string xmlDecode(string src)
	m_mFunction["String.XmlDecode"] = 15;
	m_mFunction["String.XmlEncode"] = 23;

	//选择子节点:CNode* child(CElement* p,int i)
	m_mFunction["Html.Child"] = 16;

	m_mFunction["String.Cat"] = 18;
	m_mFunction["String.SubStr"] = 19;
	m_mFunction["String.Trim"] = 22;

	
	m_mFunction["Math.Double_Add"] = 24;
	m_mFunction["Math.Double_Sub"] = 25;
	m_mFunction["Math.Double_Mul"] = 26;
	m_mFunction["Math.Double_Div"] = 27;
	
	//28
	
	m_mFunction["Map.Size"] = 28;
	m_mFunction["Map.GetValueByKey"] = 29;
	m_mFunction["Vector.Size"] = 30;
	m_mFunction["Vector.At"] = 31;


	//32
	m_mFunction["Vector.Split"] = 32;
	m_mFunction["Map.Split"] = 33;

	//34
	m_mFunction["Map.At"] = 34;


	//35string urllDecode(vector <string > & para_list);
	//string urlEncode(vector <string > & para_list);
	m_mFunction["String.UrlDecode"] = 35;
	m_mFunction["String.UrlEncode"] = 36;

	//37
	m_mFunction["String.ReadInt"] = 37;
	m_mFunction["String.ReadCString"] = 38;

	//39
	m_mFunction["String.ToHex"] = 39;
	m_mFunction["String.ToChar"] = 40;

	//41
	m_mFunction["Map.Join"] = 41;
	m_mFunction["Vector.Join"] = 42;
	
	//43
	m_mFunction["String.ToUpper"] = 43;
	m_mFunction["String.ToLower"] = 44;

	//45 
	m_mFunction["Math.Md5"] = 45;

	//46
	m_mFunction["String.Find"] = 46;

	//47 
	m_mFunction["Math.3Des"] = 47;
	//48 
	m_mFunction["Math.Un3Des"] = 48;
	//49
	m_mFunction["String.GetLength"] = 49;
	//50
	m_mFunction["Date.GetDatetime"] = 50;
	//51	转码
	m_mFunction["String.ConvertCode"] = 51;
	// 52
	m_mFunction["Math.Sha1"] = 52;
	// 53
	m_mFunction["String.ToInt"] = 53;
	// 52
	m_mFunction["Math.Mod"] = 54;

	m_mFunction["Math.AND"] = 56;
	m_mFunction["Math.OR"] = 55;
	m_mFunction["Env.GetEmbVarValue"] = 57;
	
	m_mFunction["Math.AlipayNotifyVerifySign"] = 58;
	
}

void CMyHtml2XmlWorker::ClearLocalVarSpace()
{
	m_iTmpVar = 0;

	m_mVar.clear();

}

/****************************************************************
 * 功能:返回字段的长度
 * 输入: 
 *	para1  -M string 源字符串 				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_GetLength(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;

	if(para1.GetType() != VT_STRING) 
		return res;

	//执行函数
	char szlength[32] = {0};
	string stmp = para1;
	sprintf(szlength,"%d",stmp.length());
	
	res = szlength;
	
	return res;
}


/****************************************************************
 * 功能:返回yyyymmddhhMMss
 * 输入:  				
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::Date_GetDatetime(vector <string > & para_list)
{
	char szdt[32] = {0};
	
	time_t	cNow;
	struct tm	*pcNow;	
	time(&cNow);
	pcNow=localtime(&cNow);

	
	CMyAny para1;
	if((para_list.size()>0) &&(FetchVarValue(para_list.at(0),para1) == 0)&&(para1.GetType() == VT_STRING) )
	{
		string fmt = para1;
		if(fmt == "yyyy-mm-dd")
			sprintf(szdt, "%04d-%02d-%02d",
			pcNow->tm_year+1900,
			pcNow->tm_mon+1,
			pcNow->tm_mday);	
		else if(fmt == "yyyy-mm-dd hh:mm:ss")
			sprintf(szdt, "%04d-%02d-%02d %02d:%02d:%02d",
			pcNow->tm_year+1900,
			pcNow->tm_mon+1,
			pcNow->tm_mday,
			pcNow->tm_hour,
			pcNow->tm_min,
			pcNow->tm_sec);	
		else
			sprintf(szdt, "%04d%02d%02d%02d%02d%02d",
			pcNow->tm_year+1900,
			pcNow->tm_mon+1,
			pcNow->tm_mday,
			pcNow->tm_hour,
			pcNow->tm_min,
			pcNow->tm_sec);	
	}
	else	
		sprintf(szdt, "%04d%02d%02d%02d%02d%02d",
			pcNow->tm_year+1900,
			pcNow->tm_mon+1,
			pcNow->tm_mday,
			pcNow->tm_hour,
			pcNow->tm_min,
			pcNow->tm_sec);	

	
	return string(szdt);
}

string CMyHtml2XmlWorker::Env_GetEmbVarValue(vector <string > & para_list)
{
	string res("NULL");
	
	//检查参数
	if(para_list.size() != 1)
		return res;
	
	CMyAny para1,paraTmp;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;


	if(para1.GetType() != VT_STRING) 
		return para_list.at(0);
	
	string para = (string &)para1;

	while((para.size()>1) && (para.at(0) == '$'))
	{
		if((FetchVarValue(para,paraTmp) != 0) || (paraTmp.GetType() != VT_STRING) )
			return res;

		para = (string &)paraTmp;		
	}

	return para;
}

inline int my_codeConvertUnix(const char* src_page, const char* dst_page,
                const char* szSourceText, int inLength,
                char* szDestBuff, int bufSize)
{
    iconv_t conv;
    conv = iconv_open(dst_page, src_page);
    if (conv == (iconv_t)-1)
        return -1;
    
    char* ptrInput = (char*)szSourceText;
    char* ptrOutput = szDestBuff;
    
    size_t nInLeft = inLength;
    size_t nOutLeft = bufSize;
    
    size_t ret;
    ret = iconv(conv, &ptrInput, &nInLeft, &ptrOutput, &nOutLeft);
    iconv_close(conv);
    
    if (ret == (size_t)-1)
        return -1;
    
    return (bufSize - nOutLeft);
}


/****************************************************************
 * 功能://转码GBK/utf-8
 * 输入:  				
 *1:srccode 
 *2:desccode
 *3:srcstring
 *    NULL 失败，其他为运算的结果
****************************************************************/
string CMyHtml2XmlWorker::String_ConvertCode(vector <string > & para_list)
{
	string res("NULL");

	//检查参数
	if(para_list.size() != 3)
		return res;
	
	CMyAny para1;
	if(FetchVarValue(para_list.at(0),para1) != 0)
		return res;
	
	if(para1.GetType() != VT_STRING) 
		return res;

	
	string srccode = para1;
	if (srccode!="GBK" && srccode!="UTF-8")
	{
		return res;
	}

	CMyAny para2;
	if(FetchVarValue(para_list.at(1),para2) != 0)
		return res;


	if(para2.GetType() != VT_STRING) 
		return res;

	string desccode = para2;
	if (desccode!="GBK" && desccode!="UTF-8")
	{
		return res;

	}
	

	CMyAny para3;
	if(FetchVarValue(para_list.at(2),para3) != 0)
		return res;

	if(para3.GetType() != VT_STRING) 
		return res;


	string stmp = para3;
	

    char descBuff[3072] = {0};
    int ndescBuff = sizeof(descBuff) - 1;

	if (stmp.length()> ndescBuff || stmp.length() < 1)
	{
		return res;
	}
	

	int ret =my_codeConvertUnix(srccode.c_str(),desccode.c_str(),
		stmp.c_str(),stmp.length(),descBuff,ndescBuff);
	
	if (-1 == ret)
	{
		return res;	
	}

	descBuff[ret] = '\n';	
	res=descBuff;
	
	return res;

}

/*/从第3位算起的报文
void CMyHtml2XmlWorker::parseRequestInfo_1009(vector <string > & para_list, string &strParam)
{
	typedef struct {
       	const char* param_id;
        	const char* param_name;        	
   	}Trinity;

	Trinity triNodes[] = 
	{	
		{"sp_domain",   "技术联系人姓名"},
		{"sp_name",   "技术联系人电话"},
		{"sp_address",   "技术联系人QQ"},
		{"sp_postalcode",   "技术联系人EMAIL"},
		{"sp_contact",   "结算联系人姓名"},
		{"sp_tel",   "结算联系人电话"},
		{"sp_mobile",   "结算联系人QQ"},
        	{"sp_qqid",   "qq号码"},
        	{"sp_email",   "结算联系人EMAIL"},
		{"sp_tradetype",   "客服联系人姓名"},
		{"sp_suggestuser",   "推荐人ID"},
		{"sp_type",   ""},	
		{"sp_id_card",   ""},	
		{"sp_bank_acct_no",   ""},	
		{"sp_bank_acct_name",   ""},	
		{"sp_bank_code",   ""},	
		{"sp_bank_loc_province",   ""},	
		{"sp_bank_loc_city",   ""},	
		{"sp_bank_name",   ""},	
		{"sp_contact_busi_name",   ""},	
		{"sp_contact_busi_tel",   ""},	
		{"sp_contact_busi_qq",   ""},	
		{"sp_contact_busi_email",   ""},	
		{"sp_contact_tec_name",   ""},	
		{"sp_contact_tec_tel",   ""},	
		{"sp_contact_tec_qq",   ""},	
		{"sp_contact_tec_email",   ""},	
		{"sp_contact_balance_name",   ""},	
		{"sp_contact_balance_tel",   ""},	
		{"sp_contact_balance_qq",   ""},	
		{"sp_contact_balance_email",   ""},	
		{"sp_contact_client_name",   ""},	
		{"sp_contact_client_tel",   ""},	
		{"sp_contact_client_qq",   ""},	
		{"sp_contact_client_email",   ""},	
		{"sp_contact_operator_name",   ""},	
		{"sp_contact_operator_tel",   ""},	
		{"sp_contact_operator_qq",   ""},	
		{"sp_contact_operator_email",   ""},	

		{"sp_agentid",   "所属系统商的商户号"},	
		{"sp_spid_js",   "商户的结算类型"},	
		{"sp_jsqqid",   "结算使用的C帐号"},	
		{"sp_jsqqid_auflag",   "是否修改C帐号权限"},	

		{NULL,  NULL}
	};

	std::stringstream ssParam;

	//增加SPID
	ssParam <<"<sp_id>" << "" <<"</sp_id>";
	for (int i = 0; triNodes[i].param_id != NULL; ++i)
	{
		const Trinity& tri = triNodes[i];
		int nsize = para_list.size();
		string srccode = para1;
		for(int npos =3;npos < nsize; npos++)
		{
			CMyAny para1;
			if(FetchVarValue(para_list.at(npos),para1) != 0)
			{
				break;
			}
	
			if(para1.GetType() != VT_STRING) 
			{
				break;
			}
		}

	
	
	if (srccode!="GBK" && srccode!="UTF-8")
	{
		return res;
	}
	
		string val = iodat[tri.param_id];
		
		 ssParam  << "<" << tri.param_id << ">"
		 	<< val << 
		 	"</" << tri.param_id << ">";             
	}
	
	strParam=ssParam.str();
}
*/

int myfindxmlvalue(string &node,string & context,string & val)
{
	string lnode = "<" +node+ ">";
	string rnode = "</" +node+ ">";
	string::size_type pos_l = context.find(lnode,0);
	string::size_type pos_r = context.find(rnode,0);
	string::size_type pos_offset = lnode.length();

	if( pos_l == string::npos || pos_l == string::npos)
	{   
		val="";
		return -1;
	} 
	
	val=context.substr(pos_l + pos_offset,pos_r -  pos_r + pos_offset-1);
	
	return 0;
}

