// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#include "CConfigEntry.h"


#include "CHtml.h"

/*概要配置文件*/
static const std::string g_sTagName_Instruction_include("include");
	static const std::string g_sTagName_Instruction_include_namespace("namespace");
	static const std::string g_sTagName_Instruction_include_filepath("filepath");
	static const std::string g_sTagName_Instruction_include_type("type");
		static const std::string g_sTagName_Instruction_include_type_element("element");
		static const std::string g_sTagName_Instruction_include_type_service("service");
		static const std::string g_sTagName_Instruction_include_type_include("include");
		static const std::string g_sTagName_Instruction_include_type_complex("complex");
	static const std::string g_sTagName_Instruction_include_desc("desc");

/*Error information */
static const std::string g_sConfigElementError("Err in MyConfig::CConfigEntry::GetElement ");
static const std::string g_sConfigServiceError("Err in MyConfig::CConfigEntry::GetService ");
static const unsigned long g_iErrcode = 1;
/*
<element name="QQ" format="[1-9][0-9]{4,9}" check="0" convert="0" desc="">5-10位数字</element>
*/
static const std::string g_sTagName_element("element");
	static const std::string g_sAttrName_element_name("name");
	static const std::string g_sAttrName_element_format("format");
	static const std::string g_sAttrName_element_checker("checker");
	static const std::string g_sAttrName_element_translator("translator");
	static const std::string g_sAttrName_element_desc("desc");

/*
<transaction name="login" type="" desc="">
	<variables>
		<variable name="ip" value="172.25.38.10" desc="">ip address</variable>
		<variable name="port" value="3306" desc="">port</variable>
		<variable name="timeout" value="5" desc="">timeout</variable>
		<variable name="dbname" value="db_system" desc="">database name</variable>
		<variable name="user" value="root" desc="">user name</variable>
		<variable name="passwd" value="root1234" desc="">user passwd</variable>
		<variable name="language" value="latin1" desc="">language</variable>
	<variables>
	<parameters> 	    
		<parameter name="QQ" 	request="M" 	response="M"	default="" desc="财付通帐户"/>   
	</parameters>
</transaction>
*/
static const std::string g_sTagName_service("service");	
	static const std::string g_sAttrName_service_name("name");
	static const std::string g_sAttrName_service_type("type");
	static const std::string g_sAttrName_service_desc("desc");
	
	static const std::string g_sTagName_variable("variable");	
		static const std::string g_sAttrName_variable_name("name");
		static const std::string g_sAttrName_variable_value("value");
		static const std::string g_sAttrName_variable_desc("desc");
	
	static const std::string g_sTagName_parameter("parameter");	
		static const std::string g_sAttrName_parameter_name("name");
		static const std::string g_sAttrName_parameter_request("request");
		static const std::string g_sAttrName_parameter_response("response");
		static const std::string g_sAttrName_parameter_default("default");
		static const std::string g_sAttrName_parameter_desc("desc");
	
//##ModelId=4C0C685B02F7
MyConfig::CConfigEntry::CConfigEntry()
{
	service.clear();
	element.clear();
	m_vNamespace.clear();
}


//##ModelId=4C0C685B0335
MyConfig::CConfigEntry::~CConfigEntry()
{
	service.clear();
	element.clear();
	m_vNamespace.clear();
}
int MyConfig::CConfigEntry::LoadInclude(const std::string & inFileName)
{
	int res = 0;

	CHtml doc;
	
	res = doc.ParseFile(inFileName);

	//include all other files	

	std::string s_namespace,filepath,type,desc;
	
	int ele_num = doc.GetElementByTagName(g_sTagName_Instruction_include);
	for(int i = 0;i < ele_num; i++)
	{
		CElement *pEle = (CElement *)doc.GetResult(i);
		
		pEle->GetAttrValue(g_sTagName_Instruction_include_namespace,s_namespace);
		pEle->GetAttrValue(g_sTagName_Instruction_include_type,type);
		pEle->GetAttrValue(g_sTagName_Instruction_include_filepath,filepath);
		pEle->GetAttrValue(g_sTagName_Instruction_include_desc,desc);


		if( g_sTagName_Instruction_include_type_element == type )
		{
			m_vNamespace.push_back(s_namespace);

			LoadElement(filepath);

			m_vNamespace.pop_back();
		}
		else if(g_sTagName_Instruction_include_type_service == type )
		{
			m_vNamespace.push_back(s_namespace);

			LoadService(filepath);

			m_vNamespace.pop_back();
		}
		else if(g_sTagName_Instruction_include_type_include == type )
		{
			m_vNamespace.push_back(s_namespace);

			LoadInclude(filepath);

			m_vNamespace.pop_back();
		}
		else if(g_sTagName_Instruction_include_type_complex == type )
		{
			m_vNamespace.push_back(s_namespace);

			LoadInclude(filepath);
			LoadService(filepath);
			LoadElement(filepath);

			m_vNamespace.pop_back();
		}
		
	}
	
	return res;
}
int MyConfig::CConfigEntry::LoadConfig(const std::string & inFileName)
{
	int res = 0;
	
	LoadService(inFileName);
	LoadElement(inFileName);
	LoadInclude(inFileName);

	return res;
}
void MyConfig::CConfigEntry::Clear()
{
	service.clear();
	element.clear();
	m_vNamespace.clear();
}
//##ModelId=4C0C6AB702A4
MyConfig::CConfigElementMap& MyConfig::CConfigEntry::LoadElement(const std::string &inFileName)
{
	CHtml doc;
	
	int res = doc.ParseFile(inFileName);
	
	if(res == 0)
	{
	
		std::string name,format,checker,translator,desc;
		
		int ele_num = doc.GetElementByTagName(g_sTagName_element);
		for(int i = 0;i < ele_num; i++)
		{
			CElement *pEle = (CElement *)doc.GetResult(i);
			
			pEle->GetAttrValue(g_sAttrName_element_name,name);
			pEle->GetAttrValue(g_sAttrName_element_format,format);
			pEle->GetAttrValue(g_sAttrName_element_checker,checker);
			pEle->GetAttrValue(g_sAttrName_element_translator,translator);
			pEle->GetAttrValue(g_sAttrName_element_desc,desc);
			
			element.insert(MyConfig::CConfigElementMap::value_type(m_vNamespace.Join("")+name,MyConfig::CConfigElement(name,format,checker,translator,desc)));
		}
	}
	return element;
}

//##ModelId=4C0C6B3102F5
MyConfig::CServiceMap& MyConfig::CConfigEntry::LoadService(const std::string & inFileName)
{
	
	CHtml doc;
	
	int res = doc.ParseFile(inFileName);
	
	if(res == 0)
	{
		std::string name,type,desc;
		
		int service_num = doc.GetElementByTagName(g_sTagName_service);
		for(int i = 0;i < service_num; i++)
		{
			CElement *pEle = (CElement *)doc.GetResult(i);
			
			//获取属性
			pEle->GetAttrValue(g_sAttrName_service_name,name);
			pEle->GetAttrValue(g_sAttrName_service_type,type);
			pEle->GetAttrValue(g_sAttrName_service_desc,desc);
			
			MyConfig::CService svr(name,type,desc);
			
			
			//MyConfig::CParameterMap &mapPara = svr.GetParameterMap();
			//MyConfig::CVariableMap &mapVar = svr.GetVariableMap();

			MyConfig::CParameterVectorMap &mapvPara = svr.GetParameterVectorMap();
			MyConfig::CVariableVectorMap &mapvVar= svr.GetVariableVectorMap();
			
			//获取变量
			std::string var_name,var_value,var_desc;
			int var_num = pEle->GetElementByTagName(g_sTagName_variable);
			for(int j=0;j < var_num; j++)
			{
				CElement *pEle_var = (CElement *)pEle->GetResult(j);
			
				//获取属性
				pEle_var->GetAttrValue(g_sAttrName_variable_name,var_name);
				pEle_var->GetAttrValue(g_sAttrName_variable_value,var_value);
				pEle_var->GetAttrValue(g_sAttrName_variable_desc,var_desc);
				
				//mapVar.insert(MyConfig::CVariableMap::value_type(var_name,CVariable(var_name,var_value,var_desc)));

				mapvVar[var_name].push_back(CVariable(var_name,var_value,var_desc));
			}
			//获取参数
			std::string para_name,para_in,para_out,para_default,para_desc;
			int para_num = pEle->GetElementByTagName(g_sTagName_parameter);
			for(int k=0;k < para_num; k++)
			{
				CElement *pEle_para = (CElement *)pEle->GetResult(k);
			
				//获取属性
				pEle_para->GetAttrValue(g_sAttrName_parameter_name,para_name);
				pEle_para->GetAttrValue(g_sAttrName_parameter_request,para_in);
				pEle_para->GetAttrValue(g_sAttrName_parameter_response,para_out);
				pEle_para->GetAttrValue(g_sAttrName_parameter_default,para_default);
				pEle_para->GetAttrValue(g_sAttrName_parameter_desc,para_desc);
				
				//mapPara.insert(MyConfig::CParameterMap::value_type(para_name,CParameter(para_name,para_in,para_out,para_default,para_desc)));

				mapvPara[para_name].push_back(CParameter(para_name,para_in,para_out,para_default,para_desc));
			}
			
			
			service.insert(MyConfig::CServiceMap::value_type(m_vNamespace.Join("")+name,svr));
		}
	}
	
	return service;
}

//##ModelId=4C0C6BB300C5
MyConfig::CConfigElementMap const& MyConfig::CConfigEntry::GetElementMap() const
{
    return element;
}


//##ModelId=4C0C6BB30161
MyConfig::CServiceMap const& MyConfig::CConfigEntry::GetServiceMap() const
{
    return service;
}


//##ModelId=4C0F3C1A01BE
bool MyConfig::CConfigEntry::IsExistService(const std::string &inServiceName)
{
	CServiceMap::const_iterator iter;
	
	iter = service.find(inServiceName);
	
	return (iter != service.end());
}

//##ModelId=4C0F3C440123
bool MyConfig::CConfigEntry::IsExistElement(const std::string &inElementName)
{
	CConfigElementMap::const_iterator iter;
	
	iter = element.find(inElementName);
	
	return (iter != element.end());
}
//##ModelId=4C0F3C7603B5
MyConfig::CService const & MyConfig::CConfigEntry::GetService(const std::string &inServiceName) throw(MyUtility::CMyException)
{
	CServiceMap::const_iterator iter;
	
	iter = service.find(inServiceName);
	
	if (iter != service.end())
		return iter->second;
	else
		throw MyUtility::CMyException(g_sConfigServiceError+inServiceName,g_iErrcode);
}

//##ModelId=4C0F3C7603E4
MyConfig::CConfigElement const & MyConfig::CConfigEntry::GetElement(const std::string &inElementName) throw(MyUtility::CMyException)
{
	CConfigElementMap::const_iterator iter;
	
	iter = element.find(inElementName);
	
	if (iter != element.end()) 
		return iter->second;
	else
		throw MyUtility::CMyException(g_sConfigElementError+inElementName,g_iErrcode);
}

