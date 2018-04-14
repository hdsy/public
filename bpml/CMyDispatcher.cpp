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
#include "CMyDispatcher.h"
#include "CMyHtml2XmlWorker.h"

#include "CMyExpression.h"

//##ModelId=4B14894401E3
CMyDispatcher::CMyDispatcher()
{
	InitMyKey();

	InitSysVar();

	m_pMyWorker = new CMyHtml2XmlWorker(&m_mVar);


}


//##ModelId=4B1489440212
CMyDispatcher::~CMyDispatcher()
{
	delete m_pMyWorker;
}

//##ModelId=4B1489650146
const string s_row_request_name("_RAW_REQUEST_STRING");
const string s_row_request_name_vector("_RAW_REQUEST_STRING_VECTOR");
const string s_row_request_name_vector_map("_RAW_REQUEST_STRING_VECTOR_MAP");
const string s_row_request_name_map("_RAW_REQUEST_STRING_MAP");
void CMyDispatcher::InitParameters(const std::string & inParas,int parse)
{
	CMyAny tmp ;	
	if(inParas.size() != 0)
	{
		tmp = inParas;
		m_mVar.SetVarValue(s_row_request_name,tmp);

		if(parse == 0)
			return ;
		CStringVector arr;

		arr.Split(inParas,"&");
		
		for(int i =0;i<arr.size();i++)
		{
			if(arr.at(i).size() >= 3)
			{
				CStringVector nv;
				nv.Split(arr.at(i),"=");
	
				if(nv.size() == 2)
				{
					tmp = nv[1];
					m_mVar.SetVarValue(nv[0],tmp);
				}
			}
		}

	}

}
void CMyDispatcher::InitParameters(const CStringVectorMap & inParas)
{
	CMyAny tmp ;	

	tmp = inParas;
	m_mVar.SetVarValue(s_row_request_name_vector_map,tmp);
}
int CMyDispatcher::StartWork(const string &flowFile, string &res,const CStringVectorMap & inParas)
{
	int result = 0;
	

	//准备输入参数
	InitParameters(inParas);
	
	
	result = m_htmlFlow.ParseFile(flowFile);

	if(result == 0)
	{
		for(int i=0; i < m_htmlFlow.Child().size();i++)
		{
			result = Run(m_htmlFlow.Child(i),res);
			if(result != 0)
				break;
		}
	}

	return result;
}

void CMyDispatcher::InitParameters(const CStringVector & inParas)
{
	CMyAny tmp ;	

	tmp = inParas;
	m_mVar.SetVarValue(s_row_request_name_vector,tmp);
}
int CMyDispatcher::StartWork(const string &flowFile, string &res,const CStringVector & inParas)
{
	int result = 0;
	

	//准备输入参数
	InitParameters(inParas);
	
	
	result = m_htmlFlow.ParseFile(flowFile);

	if(result == 0)
	{
		for(int i=0; i < m_htmlFlow.Child().size();i++)
		{
			result = Run(m_htmlFlow.Child(i),res);
			if(result != 0)
				break;
		}
	}

	return result;
}

void CMyDispatcher::InitParameters(const CStringMap & inParas)
{
	CMyAny tmp ;	

	tmp = inParas;
	m_mVar.SetVarValue(s_row_request_name_map,tmp);
}
int CMyDispatcher::StartWork(const string &flowFile, string &res,const CStringMap & inParas)
{
	int result = 0;
	

	//准备输入参数
	InitParameters(inParas);
	
	
	result = m_htmlFlow.ParseFile(flowFile);

	if(result == 0)
	{
		for(int i=0; i < m_htmlFlow.Child().size();i++)
		{
			result = Run(m_htmlFlow.Child(i),res);
			if(result != 0)
				break;
		}
	}

	return result;
}

int CMyDispatcher::StartWork(const string &flowFile, string &res,const string & inParas,int parse)
{
	int result = 0;
	

	//准备输入参数
	InitParameters(inParas,parse);
	
	
	result = m_htmlFlow.ParseFile(flowFile);

	if(result == 0)
	{
		for(int i=0; i < m_htmlFlow.Child().size();i++)
		{
			result = Run(m_htmlFlow.Child(i),res);
			if(result != 0)
				break;
		}
	}

	return result;
}

int CMyDispatcher::Do_KEY_SWITCH(const CNode *pCurNode, string &res)
{
	int result = 0,i = 0 ;

	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;
//	TRACE("%s:%d ",__FILE__,__LINE__);

	m_htmlFlow.AssertValid(pCurNode,m_pText,mpElement,m_pComm);

	//确认节点名
	if( (!mpElement) || ( m_mKey[mpElement->GetTagName()] != KEY_SWITCH )) 
	{
		result = 1;
		return result;
	}

	//取属性参数 id expr
	string expr;
	
	mpElement->GetAttrValue("expr",expr);

	CMyExpression  myexpr;
	//TRACE("%s:%d %s",__FILE__,__LINE__,expr.c_str());

//	AfxMessageBox("1");
//	AfxMessageBox(expr.c_str());
	
	myexpr.Identify(expr);
//	AfxMessageBox("1.1");

	string varExprRes = myexpr.Execute(m_pMyWorker);
//	AfxMessageBox("2");

	string valExprRes = m_pMyWorker->FetchVarValue(varExprRes);
//	AfxMessageBox("3");

//	TRACE("%s:%d %s",__FILE__,__LINE__,valExprRes.c_str());

	//m_mVar.SetVarValue(id,m_pMyWorker->FetchVarValue(a));

	//取子节点 case与default
	CElement *mpElementCASE = NULL; // 符合条件的CASE
	CElement *mpElementDEFAULT = NULL;//DEFAULT
	CElement *mpElementTMP = NULL;
	CElement *mpElementEXEC = NULL;//将执行的分支

	for(i= 0;i< mpElement->Child().size(); i++)
	{
		CNode * pNode = mpElement->Child(i);

		m_htmlFlow.AssertValid(pNode,m_pText,mpElementTMP,m_pComm);

		if(mpElementTMP)
		{
			switch(m_mKey[mpElementTMP->GetTagName()])
			{
			case KEY_CASE:
				{
					string value;
					mpElementTMP->GetAttrValue("value",value);

					if( valExprRes == value)
					{
						mpElementCASE = mpElementTMP;
						i = mpElement->Child().size();
						break;
					}

				}
				break;
			case KEY_DEFAULT:
				mpElementDEFAULT = mpElementTMP;
				break;
			}
		}
	}

	if(mpElementCASE )
	{
		mpElementEXEC = mpElementCASE;
	}
	else if(mpElementDEFAULT)
	{
		mpElementEXEC = mpElementDEFAULT;
	}

	if(mpElementEXEC)
	{
		for(i=0; i < mpElementEXEC->Child().size();i++)
		{
			result = Run(mpElementEXEC->Child(i),res);
			if(result != 0)
				break;
		}
	
	}

	return result;		

}
//##ModelId=4B1491690175
int CMyDispatcher::Run(const CNode *pCurNode, string &res)
{
	int result = 0;

	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	m_htmlFlow.AssertValid(pCurNode,m_pText,mpElement,m_pComm);

	if(mpElement)
	{
		//如果不是关键字
		if(m_mKey.find(mpElement->GetTagName()) == m_mKey.end())
		{
			res += mpElement->ToString();
			int j = mpElement->Child().size();

			for(int i = 0 ;i<j;i++)
			{
				CNode *p = mpElement->Child(i);

				result = Run(p,res);
				if(result != 0) return result;
			}

			res += "</";
			res += mpElement->GetTagName();
			res += ">";
		}
		//如果是关键字
		else
		{
			switch(m_mKey[mpElement->GetTagName()])
			{
			case KEY_ASSIGN:
				result = Do_KEY_ASSIGN(mpElement);
				if(result != 0) return result;
				break;
			case KEY_SWITCH:
				result = Do_KEY_SWITCH(mpElement,res);
				if(result != 0) return result;
				break;
			case KEY_ECHO:
				result = Do_KEY_ECHO(mpElement,res);
				if(result != 0) return result;
				break;
			case KEY_FOR:
				result = Do_KEY_FOR(mpElement,res);
				if(result != 0) return result;
				break;
			case KEY_INVOKE:
				result = Do_KEY_INVOKE(mpElement);
				if(result != 0) return result;
				break;

			default:
				break;
			}
		}
		
	}
	else if(m_pText)
	{
		res += pCurNode->ToString();
	}
	else
	{
		;
	}


	return result;
}

//##ModelId=4B148C8D028F
//DEL UINT CMyDispatcher::WorkThread(LPVOID data)
//DEL {
//DEL 	CMyDispatcher * pMyDispatcher = (CMyDispatcher *)data;
//DEL 
//DEL 
//DEL 	return 1;
//DEL }

//##ModelId=4B149377008B
//DEL int CMyDispatcher::Run(const string &file_path, string &res)
//DEL {
//DEL 	int result = 0;
//DEL 
//DEL 	return result;
//DEL }

void CMyDispatcher::InitMyKey()
{
	//分支语句
		//<my-soft::switch expr="big(count(tag($htmlSource,a,0)),0)" >
		m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "switch", KEY_SWITCH));
		//<my-soft::case value="true">
		m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "case", KEY_CASE));
		//<my-soft::default>
		m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "default", KEY_DEFAULT));
	//循环语句
		//<my-soft::for condition="small($var,count(tag($htmlSource,a,0)))" recycle="inc($var)" >
		m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "for", KEY_FOR));
		//<my-soft::continue>
//		m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "continue", KEY_CONTINUE));
		//<my-soft::break>
//		m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "break", KEY_BREAK));

	//输出语句<my-soft::echo>expr</my-soft::echo>
	m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "echo", KEY_ECHO));
	
	//赋值语句 <my-soft::aasign identify="htmlSource" expr="parse_html(0,$response)"  />
	m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "assign", KEY_ASSIGN));

	//调用外部功能语句
	/*<my-soft::invoke service="httpcall" retvar="response">
		<my-soft::parameter name="" value="" />
		<my-soft::parameter name="" value="" />
		<my-soft::parameter name="" value="" />
		<my-soft::parameter name="" value="" />
	</my-soft::invoke>
	*/

	m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "invoke", KEY_INVOKE));
	m_mKey.insert(map<string,EKEY>::value_type(MYFLOW_TAG_HEADER "parameter", KEY_PARAMETER));

	
}

int CMyDispatcher::Do_KEY_ASSIGN(const CNode *pCurNode)
{
	int result = 0;

	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	m_htmlFlow.AssertValid(pCurNode,m_pText,mpElement,m_pComm);

	//确认节点名
	if( (!mpElement) || ( m_mKey[mpElement->GetTagName()] != KEY_ASSIGN )) 
	{
		result = 1;
		return result;
	}

	//取属性参数 id expr
	string id,expr;
	
	mpElement->GetAttrValue("id",id);
	while((id.size()>1) && (id.at(0) == '$'))
			id =(string &)m_pMyWorker->FetchVarValue(id);

	if(id == "")
		return 1;
		
	
	mpElement->GetAttrValue("expr",expr);

	CMyExpression  myexpr;
	
	myexpr.Identify(expr);

	string a = myexpr.Execute(m_pMyWorker);

	//string b= m_pMyWorker->FetchVarValue(a);
	
	CMyAny tmp=m_pMyWorker->FetchVarValue(a);
	m_mVar.SetVarValue(id,tmp);


	return result;					
}

int CMyDispatcher::Do_KEY_INVOKE(const CNode *pCurNode)
{
	int result = 0;

	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	m_htmlFlow.AssertValid(pCurNode,m_pText,mpElement,m_pComm);

	//确认节点名
	if( (!mpElement) || ( m_mKey[mpElement->GetTagName()] != KEY_INVOKE )) 
	{
		result = 1;
		return result;
	}

	//取属性参数 service retvar
	string service,retvar,type,filepath;
	//服务名
	mpElement->GetAttrValue("service",service);
	//返回值，变量名
	mpElement->GetAttrValue("retvar",retvar);
	//服务类型
	mpElement->GetAttrValue("type",type);
	//文件路径:配置文件
	mpElement->GetAttrValue("filepath",filepath);

	filepath = GetExprResult(filepath);

	//取invoke相应的请求参数
	CStringMap invokeParaMap;

	CElement *mpElementTMP = NULL;

	for(int i = 0;i< mpElement->Child().size(); i++)
	{
		CNode * pNode = mpElement->Child(i);

		m_htmlFlow.AssertValid(pNode,m_pText,mpElementTMP,m_pComm);

		if(mpElementTMP)
		{
			switch(m_mKey[mpElementTMP->GetTagName()])
			{
			case KEY_PARAMETER:
				{
					string name,value,type;
					mpElementTMP->GetAttrValue("name",name);
					mpElementTMP->GetAttrValue("value",value);
					mpElementTMP->GetAttrValue("type",type);

	

					if(type == "var")
					{
						invokeParaMap[name] = (string &)(m_pMyWorker->FetchVarValue(value));
					}
					else if(type == "expr")
					{
						CMyExpression  myexpr;
						
						myexpr.Identify(value);

						string a = myexpr.Execute(m_pMyWorker);

						invokeParaMap[name] =  (string &)m_pMyWorker->FetchVarValue(a);
					}
					else if(type == "const")
					{
						invokeParaMap[name] = value;
					}
					else 
						invokeParaMap[name] = value;

				}
				break;
			}
		}
	}

	//执行invoke，目前只支持httpcall  bpmlcall
	string invokeRes("NULL");

	if(type == "httpcall")
	{
		CHttpClient http;

		http.LoadConfig(filepath,service);

		http.LoadInput(invokeParaMap);

		http.LoadSession();

		http.SendAndRecv();

		http.StoreSession();

		if((( http.m_sRetCode == string("302")  ) ||( http.m_sRetCode == string("200")  )) &&
			(http.m_iStatus == 0))
		{


			invokeRes = http.m_sResBody;
		}
	}
	else if(type== "bpmlcall")
	{
		CMyDispatcher disp;

		string inParas;

		string res;
		
		disp.StartWork(filepath,res,invokeParaMap.Join());		

		invokeRes = res;

	}


	// 返回结果
	CMyAny tmp = invokeRes;
	m_mVar.SetVarValue(retvar,tmp);


	return result;					
}

int CMyDispatcher::Do_KEY_ECHO(const CNode *pCurNode,string &res)
{
	int result = 0;

	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	m_htmlFlow.AssertValid(pCurNode,m_pText,mpElement,m_pComm);

	//确认节点名
	if( (!mpElement) || ( m_mKey[mpElement->GetTagName()] != KEY_ECHO )) 
	{
		result = 1;
		return result;
	}

	//取属性参数 id expr
	string type,value;
	
	mpElement->GetAttrValue("type",type);
	mpElement->GetAttrValue("value",value);


	if(type == "var")
	{
		res += (string &)m_pMyWorker->FetchVarValue(value);
	}
	else if(type == "embvar")
	{
		string tmpres =(string &)m_pMyWorker->FetchVarValue(value);

		while((tmpres.size()>1) && (tmpres.at(0) == '$'))
			tmpres =(string &)m_pMyWorker->FetchVarValue(tmpres);

		res += tmpres;
	}
	else if(type == "const")
	{
		res += value;
	}
	else if(type == "expr")
	{
		CMyExpression  myexpr;
		
		myexpr.Identify(value);

		string a = myexpr.Execute(m_pMyWorker);
		
		res +=  (string &)m_pMyWorker->FetchVarValue(a);
	}
	



	return result;					
}
int CMyDispatcher::Do_KEY_FOR(const CNode *pCurNode,string &res)
{
	int result = 0;

	CText *m_pText = NULL;
	CElement *mpElement = NULL;
	CComment *m_pComm = NULL;

	m_htmlFlow.AssertValid(pCurNode,m_pText,mpElement,m_pComm);

	//确认节点名
	if( (!mpElement) || ( m_mKey[mpElement->GetTagName()] != KEY_FOR )) 
	{
		result = 1;
		return result;
	}

	//取属性参数 id expr
	string condition,recycle;
	
	mpElement->GetAttrValue("condition",condition);
	mpElement->GetAttrValue("recycle",recycle);

	//
	CMyExpression  exprCondition(condition,NULL);
	CMyExpression  exprRecycle(recycle,NULL);
	
	//exprCondition.Identify(condition);
	//exprRecycle.Identify(recycle);

	while(1)
	{
		//执行条件表达式
		string exprCondRes =  exprCondition.Execute(m_pMyWorker);
		if(exprCondRes == "NULL")
		{
			result = 1;
			break;
		}

		string sCondRes = m_pMyWorker->FetchVarValue(exprCondRes);


		if(sCondRes == "true")
		{
			for(int i=0; i < mpElement->Child().size();i++)
			{
				result = Run(mpElement->Child(i),res);
				if(result != 0)
					break;
			}
		}
		else
		{			
			break;
		}

		exprRecycle.Execute(m_pMyWorker);


	}

	return result;
}

void CMyDispatcher::InitSysVar()
{
/*
	string logPath = CModulePath::GetInstance()->m_sLogDir + "/sr.log";

	tracer.Init(logPath.c_str());


	m_mVar.SetVarValue("_DIR_BIN",CMyAny(CModulePath::GetInstance()->m_sBinDir));
	m_mVar.SetVarValue("_DIR_CNF",CMyAny(CModulePath::GetInstance()->m_sCnfDir));
	m_mVar.SetVarValue("_DIR_DAT",CMyAny(CModulePath::GetInstance()->m_sDatDir));
	m_mVar.SetVarValue("_DIR_SES",CMyAny(CModulePath::GetInstance()->m_sSesDir));
	m_mVar.SetVarValue("_DIR_LOG",CMyAny(CModulePath::GetInstance()->m_sLogDir));
	m_mVar.SetVarValue("_DIR_TMP",CMyAny(CModulePath::GetInstance()->m_sTmpDir));
	
	*/
	
	CMyAny bin("./bin/");CMyAny cnf("./cnf/");CMyAny dat("./dat/");
	CMyAny ses("./ses/");CMyAny log("./log/");CMyAny tmp("./tmp/");
	
	m_mVar.SetVarValue("_DIR_BIN",bin);
	m_mVar.SetVarValue("_DIR_CNF",cnf);
	m_mVar.SetVarValue("_DIR_DAT",dat);
	m_mVar.SetVarValue("_DIR_SES",ses);
	m_mVar.SetVarValue("_DIR_LOG",log);
	m_mVar.SetVarValue("_DIR_TMP",tmp);
}
string CMyDispatcher::GetExprResult(const string & expr)
{
	string res;

	CMyExpression  myexpr;
	
	myexpr.Identify(expr);

	string a = myexpr.Execute(m_pMyWorker);

	res = (string &)m_pMyWorker->FetchVarValue(a);

	return res;
}
