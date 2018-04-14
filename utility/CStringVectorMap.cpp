// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#include "CStringVectorMap.h"

#include "CStringVector.h"

//#include <iostream>

MyUtility::CStringVectorMap& MyUtility::CStringVectorMap::AddElement(const std::string & key,const std::string & val)
{
//std::cout << key << " : " << val << endl;
	
	iterator iterSVM;
	
	iterSVM = find(key);
		
	if(iterSVM == end() )
	{
		CStringVector tmp;
		if(val.size() != 0) 
			tmp.push_back(val);
			
		insert(value_type(key,tmp));
	}
	else
	{
		if(val.size() != 0)
			iterSVM->second.push_back(val);
	}
	

	return *this;
}

//##ModelId=4C05C99A005D
MyUtility::CStringVectorMap& MyUtility::CStringVectorMap::Split(const std::string  &inStr, const std::string &inEleSep, const std::string & inNVSep, bool inFlg,FILTER * filter)
{
  CStringVector vEle,vNv;  
  
  clear();
    
  for(unsigned int i = 0; i< vEle.Split(inStr,inEleSep).size();i++)
  {
    if(vNv.Split(vEle[i],inNVSep).size() < 2)
    {
      if(inFlg)
	  {
		AddElement(vNv[0],"");
	  }
    }
    else
    {
    if(NULL == filter )
    	{
      AddElement(vNv[0],vEle[i].substr(vNv[0].length()+1));
    	}
	else
		{
		AddElement(vNv[0],filter(vEle[i].substr(vNv[0].length()+1)));
		}
    }
  }
  
	
	return *this;
}


//##ModelId=4C05C99A007C
std::string MyUtility::CStringVectorMap::Join(const char *inEleSep, const char *inNVSeq,FILTER * filter) const
{
	string result;
	
	const_iterator itersvm;

	bool first_flag = true;
	
	for(itersvm = begin();itersvm !=end();itersvm++)
	{
		if(!first_flag) result.append(inEleSep);
		
		if(0 == itersvm->second.size() )
		{
			result.append(itersvm->first);			
		}
		else
		{
			for(unsigned int i=0;i < itersvm->second.size();i++)
			{
				if(i != 0) result.append(inEleSep);
				
				result.append(itersvm->first);
				result.append(inNVSeq);
				if(NULL == filter)
					result.append(itersvm->second.at(i));
				else
					result.append(filter(itersvm->second.at(i)));
					
				
			}
		}
		first_flag = false;
		
	}
	
	return result;

}
std::string MyUtility::CStringVectorMap::Join(const std::string &inEleSep, const std::string & inNVSeq,FILTER * filter) const
{
	string result;
	
	const_iterator itersvm;

	bool first_flag = true;
	
	for(itersvm = begin();itersvm !=end();itersvm++)
	{
		if(!first_flag) result.append(inEleSep);
		
		if(0 == itersvm->second.size() )
		{
			result.append(itersvm->first);			
		}
		else
		{
			for(unsigned int i=0;i < itersvm->second.size();i++)
			{
				if(i != 0) result.append(inEleSep);
				
				result.append(itersvm->first);
				result.append(inNVSeq);
				if(NULL == filter)
					result.append(itersvm->second.at(i));
				else
					result.append(filter(itersvm->second.at(i)));
					
				
			}
		}
		first_flag = false;
		
	}
	
	return result;

}

//##ModelId=4C05C99A008C
MyUtility::CStringVectorMap& MyUtility::CStringVectorMap::Split(const char *inStr, const char *inEleSep, const char *inNVSep, bool inFlg,FILTER * filter)
{
  CStringVector vEle,vNv;  
  
  clear();
    
  for(unsigned int i = 0; i< vEle.Split(inStr,inEleSep).size();i++)
  {
    if(vNv.Split(vEle[i],inNVSep).size() < 2)
    {
      if(inFlg)
	  {
		AddElement(vNv[0],"");
	  }
    }
    else
    {
    if(NULL == filter)
      AddElement(vNv[0],vEle[i].substr(vNv[0].length()+1));
	else
      AddElement(vNv[0],filter(vEle[i].substr(vNv[0].length()+1)));
		
    }
  }
  
	
	return *this;
}


//##ModelId=4C05C9BF01B5
MyUtility::CStringVectorMap::CStringVectorMap()
{
}


//##ModelId=4C05C9BF01E4
MyUtility::CStringVectorMap::~CStringVectorMap()
{
}

//##ModelId=4C05C9BF0222
std::string MyUtility::CStringVectorMap::GetFirst(const std::string &inKey)
{
	iterator iterSVM;
	
	iterSVM = find(inKey);
		
	if(iterSVM == end() )
	{
		return "";
	}
	else
	{
		if(iterSVM->second.size() == 0)
			return "";
		else
			return iterSVM->second.at(0) ;
	}

}
std::string MyUtility::CStringVectorMap::GetFirst(const std::string &inKey) const 
{
	const_iterator iterSVM;
	
	iterSVM = find(inKey);
		
	if(iterSVM == end() )
	{
		return "";
	}
	else
	{
		if(iterSVM->second.size() == 0)
			return "";
		else
			return iterSVM->second.at(0) ;
	}

}
//##ModelId=4C05C9BF0222
std::string MyUtility::CStringVectorMap::GetFirst(const char *inKey)
{
	iterator iterSVM;
	
	iterSVM = find(inKey);
		
	if(iterSVM == end() )
	{
		return "";
	}
	else
	{
		if(iterSVM->second.size() == 0)
			return "";
		else
			return iterSVM->second.at(0) ;
	}

}
std::string MyUtility::CStringVectorMap::GetFirst(const char *inKey)const
{
	const_iterator iterSVM;
	
	iterSVM = find(inKey);
		
	if(iterSVM == end() )
	{
		return "";
	}
	else
	{
		if(iterSVM->second.size() == 0)
			return "";
		else
			return iterSVM->second.at(0) ;
	}

}

