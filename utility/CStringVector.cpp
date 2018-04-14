// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#include "CStringVector.h"

//##ModelId=4BFF2CAC000F
MyUtility::CStringVector& MyUtility::CStringVector::Split(const std::string  &inStr, const std::string &inSep, bool inFlg,FILTER *filter)
{
	erase(begin(), end());
	
	string::const_iterator iterCur,iterLast,iterBegin;
	
	iterCur = iterBegin = inStr.begin();
	iterLast = inStr.end();
	
	
	for(;iterCur != iterLast;iterCur++)
	{				
		if(inSep.find(*iterCur) != string::npos)
		{
			if(iterCur == iterBegin)
			{
				if(inFlg) push_back("");
				
				iterBegin++;
			}
			else
			{
				string tmp(iterBegin, iterCur);
				if(NULL == filter)
		               	push_back(tmp);
				else
					push_back(filter(tmp));
				iterBegin = iterCur + 1;
			}
		}
	}
	
	if((iterCur != iterBegin) /*&& (iterCur == string::npos) */)
	{
		push_back(std::string(iterBegin,iterLast));
	}
	
	
	return *this;
}


//##ModelId=4BFF2EA60338
MyUtility::CStringVector& MyUtility::CStringVector::Split(const char *inStr, const char *inSep, bool inFlg,FILTER * filter)
{
        erase(begin(), end());

        const char* p;
        const char* s = inStr;
        do
        {
                p = strpbrk(s, inSep);
                if (p)
                {
                        if (p == s)
                        {
								if(inFlg)
								{
									string tmp = "";
									push_back(tmp);
								}
                                p++;
                                s++;
                        }
                        else
                        {
                                string tmp(s, p - s);
				if(NULL == filter)
		               	push_back(tmp);
				else
					push_back(filter(tmp));

                                p++;
                                s = p;
                        }
                }
                else
                {
                        if(strlen(s))
                        {
                                string tmp(s);
				if(NULL == filter)
		               	push_back(tmp);
				else
					push_back(filter(tmp));
                        }
                }
        } while (p);
		
        return *this;
}


//##ModelId=4C032750028D
MyUtility::CStringVector::CStringVector()
{
}


//##ModelId=4C03275002BC
MyUtility::CStringVector::~CStringVector()
{
}

//##ModelId=4C03275A009A
std::string MyUtility::CStringVector::Join(const char *inSep,FILTER * filter) const
{
	string result;
	
	MyUtility::CStringVector::const_iterator iter;
	
	for(iter = begin(); iter != end(); iter++)
	{
		if(iter != begin())
			result.append(inSep);
		
				if(NULL == filter)
		               	result.append(*iter);
				else
					result.append(filter(*iter));
		
	}
	
	return result;
}

std::string MyUtility::CStringVector::Join(const std::string & inSep,FILTER * filter) const
{
	string result;
	
	MyUtility::CStringVector::const_iterator iter;
	
	for(iter = begin(); iter != end(); iter++)
	{
		if(iter != begin())
			result.append(inSep);
		if(NULL == filter)
		               	result.append(*iter);
				else
					result.append(filter(*iter));
	}
	
	return result;
}

