// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#include "CStringMap.h"
#include "CStringVector.h"

#include "CBaseEncode.h"

//##ModelId=4C032D85028A
MyUtility::CStringMap& MyUtility::CStringMap::Split(const std::string  &inStr, const std::string &inEleSep, const std::string & inNVSep, bool inFlg,FILTER* filter)
{
  CStringVector vEle,vNv;  
  
  clear();
    
  for(unsigned int i = 0; i< vEle.Split(inStr,inEleSep).size();i++)
  {
    if(vNv.Split(vEle[i],inNVSep, inFlg).size() < 2)
    {
      if(inFlg)
	  {
		insert(value_type(vNv[0],""));
	  }
    }
    else
    {
    if(NULL == filter)
      insert(value_type(vNv[0],vEle[i].substr(vNv[0].length()+1)));
	else
      insert(value_type(vNv[0],filter(vEle[i].substr(vNv[0].length()+1))));
		
    }
  }
  
	
	return *this;
}


//##ModelId=4C032D8502C8
std::string MyUtility::CStringMap::Join(const char *inEleSep, const char *inNVSeq,FILTER* filter) const
{
	string result;
	
	const_iterator itersvm;

	bool first_flag = true;
	
	for(itersvm = begin();itersvm !=end();itersvm++)
	{
		if(!first_flag) result.append(inEleSep);
		
		result.append(itersvm->first);		
		result.append(inNVSeq);
		if(NULL == filter )
		{
			result.append(itersvm->second);	
		}
		else
		{
			result.append(filter(itersvm->second));				
		}
		
		first_flag = false;
	}
	
	return result;
}
std::string MyUtility::CStringMap::Join(const std::string & inEleSep, const  std::string &  inNVSeq,FILTER* filter) const
{
	string result;
	
	const_iterator itersvm;

	bool first_flag = true;
	
	for(itersvm = begin();itersvm !=end();itersvm++)
	{
		if(!first_flag) result.append(inEleSep);
		
		result.append(itersvm->first);		
		result.append(inNVSeq);
		if(NULL == filter )
		{
			result.append(itersvm->second);	
		}
		else
		{
			result.append(filter(itersvm->second));				
		}
		
		first_flag = false;
	}
	
	return result;
}

//##ModelId=4C0332AC01D3
MyUtility::CStringMap::CStringMap()
{
}


//##ModelId=4C0332AC0202
MyUtility::CStringMap::~CStringMap()
{
}

//##ModelId=4C05C91F00F8
MyUtility::CStringMap& MyUtility::CStringMap::Split(const char *inStr, const char *inEleSep, const char *inNVSep, bool inFlg,FILTER* filter)
{
  CStringVector vEle,vNv;  
  
  clear();
    
  for(unsigned int i = 0; i< vEle.Split(inStr,inEleSep).size();i++)
  {
    if(vNv.Split(vEle[i],inNVSep, inFlg).size() < 2)
    {
      if(inFlg)
	  {
		insert(value_type(vNv[0],""));
	  }
    }
    else
    {
    	if(NULL == filter )
	{
		insert(value_type(vNv[0],vEle[i].substr(vNv[0].length()+1)));
	}
	else
	{
     		 insert(value_type(vNv[0],filter(vEle[i].substr(vNv[0].length()+1))));
	}
    }
  }
  
	
	return *this;
}


