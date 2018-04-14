// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#include "CBaseEncode.h"

#include <iostream>
char MyUtility::CMemString::ReadChar(const std::string & inMemstr,int inOffset,int &oSize)
{
	char c='\0';

	oSize = 0;


	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		c = inMemstr.at(inOffset);
	}


	return c;
}
unsigned char MyUtility::CMemString::ReadUChar(const std::string & inMemstr,int inOffset,int &oSize)
{
	unsigned char c='\0';

	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		c = (unsigned char)inMemstr.at(inOffset);
	}


	return c;
}
short MyUtility::CMemString::ReadShort(const std::string & inMemstr,int inOffset,int &oSize)
{
	short c=0;

	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		memcpy((void *) &c ,inMemstr.data() + inOffset, oSize);
	}
	
	return c;
}
unsigned short MyUtility::CMemString::ReadUShort(const std::string & inMemstr,int inOffset,int &oSize)
{
	unsigned short c=0;

	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		memcpy((void *) &c ,inMemstr.data() + inOffset, oSize);
	}
	
	return c;
}
int MyUtility::CMemString::ReadInt(const std::string & inMemstr,int inOffset,int &oSize)
{
	int c=0;

	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		memcpy((void *) &c ,inMemstr.data() + inOffset, oSize);
	}
	
	return c;
}
unsigned int MyUtility::CMemString::ReadUInt(const std::string & inMemstr,int inOffset,int &oSize)
{
	unsigned int c=0;

	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		memcpy((void *) &c ,inMemstr.data() + inOffset, oSize);
	}
	
	return c;
}
long MyUtility::CMemString::ReadLong(const std::string & inMemstr,int inOffset,int &oSize)
{
	long c=0;

	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		memcpy((void *) &c ,inMemstr.data() + inOffset, oSize);
	}
	
	return c;
}
unsigned long MyUtility::CMemString::ReadULong(const std::string & inMemstr,int inOffset,int &oSize)
{
	unsigned long c=0;
	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		memcpy((void *) &c ,inMemstr.data() + inOffset, oSize);
	}
	
	return c;
}
float MyUtility::CMemString::ReadFloat(const std::string & inMemstr,int inOffset,int &oSize)
{
	float c=0;

	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		memcpy((void *) &c ,inMemstr.data() + inOffset, oSize);
	}
	
	return c;
}
double MyUtility::CMemString::ReadDouble(const std::string & inMemstr,int inOffset,int &oSize)
{
	double c = 0;

	oSize = 0;

	if(inMemstr.size() >= inOffset + sizeof(c))
	{
		oSize = sizeof(c);
		memcpy((void *) &c ,inMemstr.data() + inOffset, oSize);
	}
	
	return c;
}

std::string MyUtility::CMemString::ReadCString(const std::string & inMemstr,int inOffset,int &ioSize)
{
	std::string c("");

	int i=0,size_real;
	
	if((int)inMemstr.size() <= inOffset)
	{
		size_real= 0;
	}
	else
	{
		size_real = inMemstr.size()  - inOffset;
	}
	if(ioSize < size_real)
		size_real = ioSize;

	if(size_real > 0)
	{
		for(i=0; i < size_real; i++)
		{
			if(inMemstr.at(inOffset+i) != '\0')
				c.append(1,inMemstr.at(inOffset+i));
		}
	}

	ioSize = i;

	return c;
}
std::string MyUtility::CMemString::ReadBString(const std::string & inMemstr,int inOffset,int &ioSize)
{
	std::string c("");
	
	if((int)inMemstr.size() >= inOffset + ioSize)
	{
		c=inMemstr.substr(inOffset,ioSize);
	}
	else if((int)inMemstr.size() <= inOffset)
	{
		ioSize = 0;
	}
	else
	{
		ioSize = inMemstr.size()  - inOffset;
		c=inMemstr.substr(inOffset,ioSize);
	}


	
	return c;
}

//##ModelId=4C032991022D
std::string &MyUtility::CBaseEncode::UrlEncode(std::string &ioStr)
{
	std::string result;
  std::string::const_iterator iter;
  
  for(iter = ioStr.begin(); iter != ioStr.end(); ++iter) {
    switch(*iter) {
        /* */
    case ' ':
      result.append(1, '+');
      break;
     
      // alnum
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
    case 'V': case 'W': case 'X': case 'Y': case 'Z':
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
    case 'v': case 'w': case 'x': case 'y': case 'z':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6':
    case '7': case '8': case '9':
      // mark
    case '-': case '_': case '.': case '!': case '~': case '*': case '\'': 
    case '(': case ')':
      result.append(1, *iter);
      break;
      // escape
    default:
        if((unsigned char)(*iter) > 127)
        {
                result.append(1, *iter);
        }
        else
        {
	      result.append(1, '%');
	      result.append(CharToHex(*iter));
        }
      break;
    }
  }
  
  ioStr = result;
  
  return ioStr;
}

std::string &MyUtility::CBaseEncode::UrlEncode2(std::string &ioStr)
{
	std::string result;
  std::string::const_iterator iter;
  
  for(iter = ioStr.begin(); iter != ioStr.end(); ++iter) {
    switch(*iter) {
        /**/
    case ' ':
      result.append(1, '+');
      break;
      
      // alnum
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
    case 'V': case 'W': case 'X': case 'Y': case 'Z':
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
    case 'v': case 'w': case 'x': case 'y': case 'z':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6':
    case '7': case '8': case '9':
      // mark
   // case '-': case '_': case '.': case '!': case '~': case '*': case '\'': 
   // case '(': case ')':
      result.append(1, *iter);
      break;
      // escape
    default:
        //if((unsigned char)(*iter) > 127)
        //{
        //        result.append(1, *iter);
        //}
       // else
        {
      result.append(1, '%');
      result.append(CharToHex(*iter));
        }
      break;
    }
  }
  
  ioStr = result;
  
  return ioStr;
}
//##ModelId=4C0329C60134
std::string MyUtility::CBaseEncode::UrlEncode(const std::string &inStr)
{
  std::string result;
  std::string::const_iterator iter;
  
  for(iter = inStr.begin(); iter != inStr.end(); ++iter) {
    switch(*iter) {
        /**/
    case ' ':
      result.append(1, '+');
      break;
      
      // alnum
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
    case 'V': case 'W': case 'X': case 'Y': case 'Z':
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
    case 'v': case 'w': case 'x': case 'y': case 'z':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6':
    case '7': case '8': case '9':
      // mark
    case '-': case '_': case '.': case '!': case '~': case '*': case '\'': 
    case '(': case ')':
      result.append(1, *iter);
      break;
      // escape
    default:
        if((unsigned char)(*iter) > 127)
        {
                result.append(1, *iter);
        }
        else
        {
      result.append(1, '%');
      result.append(CharToHex(*iter));
        }
      break;
    }
  }
  
  return result;
}

//##ModelId=4C0329C60134
std::string MyUtility::CBaseEncode::UrlEncode2(const std::string &inStr)
{
  std::string result;
  std::string::const_iterator iter;
  
  for(iter = inStr.begin(); iter != inStr.end(); ++iter) {
    switch(*iter) {
        /**/
    case ' ':
      result.append(1, '+');
      break;
      
      // alnum
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
    case 'V': case 'W': case 'X': case 'Y': case 'Z':
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
    case 'v': case 'w': case 'x': case 'y': case 'z':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6':
    case '7': case '8': case '9':
      // mark
   // case '-': case '_': case '.': case '!': case '~': case '*': case '\'': 
   // case '(': case ')':
      result.append(1, *iter);
      break;
      // escape
    default:
        //if((unsigned char)(*iter) > 127)
        //{
        //        result.append(1, *iter);
        //}
        //else
        {
      result.append(1, '%');
      result.append(CharToHex(*iter));
        }
      break;
    }
  }
  
  return result;
}


//##ModelId=4C0329F60200
std::string &MyUtility::CBaseEncode::UrlDecode(std::string &ioStr)
{
  std::string result;
  std::string::const_iterator iter,iter_end;
  
  
  iter_end = ioStr.end();
  
  
  char c;

  for(iter = ioStr.begin(); iter != ioStr.end(); ++iter) 
  {
    switch(*iter) {
    /**/
    case '+':
      result.append(1, ' ');
      break;
    
    case '%':
        // Don't assume well-formed input
        if(std::distance(iter, iter_end) >= 2
           && std::isxdigit(*(iter + 1)) && std::isxdigit(*(iter + 2))) 
		{
            c = *++iter;
            result.append(1, HexToChar(c, *++iter));
        }
        // Just pass the % through untouched
        else {
            result.append(1, '%');
        }
        break;
    
    default:
      result.append(1, *iter);
      break;
    }
  }
  
  ioStr = result;
  
  return ioStr;
}

//##ModelId=4C0329F6020F
std::string MyUtility::CBaseEncode::UrlDecode(const std::string &inStr)
{
  std::string result;
  std::string::const_iterator iter;
  char c;

  for(iter = inStr.begin(); iter != inStr.end(); ++iter) {
    switch(*iter) {
    /**/
    case '+':
      result.append(1, ' ');
      break;
    
    case '%':
        // Don't assume well-formed input
        if(std::distance(iter, inStr.end()) >= 2
           && std::isxdigit(*(iter + 1)) && std::isxdigit(*(iter + 2))) {
            c = *++iter;
            result.append(1, HexToChar(c, *++iter));
        }
        // Just pass the % through untouched
        else {
            result.append(1, '%');
        }
        break;
    
    default:
      result.append(1, *iter);
      break;
    }
  }
  
  return result;
}


//##ModelId=4C032B7F031F
std::string MyUtility::CBaseEncode::CharToHex(char inChar)
{
  std::string result;
  char first, second;

  first = (inChar & 0xF0) / 16;
  first += first > 9 ? 'A' - 10 : '0';
  second = inChar & 0x0F;
  second += second > 9 ? 'A' - 10 : '0';

  result.append(1, first);
  result.append(1, second);
  
  return result;
}


//##ModelId=4C032BBF0245
char MyUtility::CBaseEncode::HexToChar(char inFirstChar, char inSecondChar)
{
  int digit;
  
  digit = (inFirstChar >= 'A' ? ((inFirstChar & 0xDF) - 'A') + 10 : (inFirstChar - '0'));
  digit *= 16;
  digit += (inSecondChar >= 'A' ? ((inSecondChar & 0xDF) - 'A') + 10 : (inSecondChar - '0'));
  return static_cast<char>(digit);
}


//##ModelId=4C03339402E4
std::string &MyUtility::CBaseEncode::XmlEncode(std::string &ioStr)
{
string result;
		string::const_iterator iter;
		
		for(iter = ioStr.begin(); iter != ioStr.end(); ++iter) 
		{
			switch(*iter) 
			{
			case '<':
				result.append("&lt;");
				break;		
			case '>':
				result.append("&gt;");
				break;	
			case '&':
				result.append("&amp;");
				break;	
				break;	
			case '\'':
				result.append("&apos;");
				break;	
			case '"':
				result.append("&quot;");
				break;	
			default:
				result.append(1, *iter);
				break;
			}
		}
		ioStr = result;
		return ioStr;
}

//##ModelId=4C03339402F4
std::string MyUtility::CBaseEncode::XmlEncode(const std::string &inStr)
{
		string result;
		string::const_iterator iter;
		
		for(iter = inStr.begin(); iter != inStr.end(); ++iter) 
		{
			switch(*iter) 
			{
			case '<':
				result.append("&lt;");
				break;		
			case '>':
				result.append("&gt;");
				break;	
			case '&':
				result.append("&amp;");
				break;	
				break;	
			case '\'':
				result.append("&apos;");
				break;	
			case '"':
				result.append("&quot;");
				break;	
			default:
				result.append(1, *iter);
				break;
			}
		}
		
		return result;
	}


//##ModelId=4C0333DE0150
std::string &MyUtility::CBaseEncode::XmlDecode(std::string &ioStr)
{
string result;
		string::const_iterator iter;
		
		for(iter = ioStr.begin(); iter != ioStr.end(); ++iter) 
		{
			switch(*iter) 
			{
			case '&':
				{
					string entity;
					do
					{
						if(*iter == ';')
						{
							entity.append(1,*iter);
							break;
						}
						else
						{
							entity.append(1,*iter++);
						}
					}while(iter != ioStr.end());
					
					if(entity == "&lt;")
						result.append(1, '<');
					else if(entity == "&gt;")
						result.append(1, '>');
					else if(entity == "&amp;")
						result.append(1, '&');
					else if(entity == "&apos;")
						result.append(1, '\'');
					else if(entity == "&quot;")
						result.append(1, '"');
					else
					{
						result.append(1, '&');
						iter -= entity.size()-1;
					}
				}
				break;				
			default:
				result.append(1, *iter);
				break;
			}
		}
		ioStr = result;
		return ioStr;
}

//##ModelId=4C0333DE0170
std::string MyUtility::CBaseEncode::XmlDecode(const std::string &inStr)
{
		string result;
		string::const_iterator iter;
		
		for(iter = inStr.begin(); iter != inStr.end(); ++iter) 
		{
			switch(*iter) 
			{
			case '&':
				{
					string entity;
					do
					{
						if(*iter == ';')
						{
							entity.append(1,*iter);
							break;
						}
						else
							entity.append(1,*iter++);
					}while(iter != inStr.end());

					if(entity == "&lt;")
						result.append(1, '<');
					else if(entity == "&gt;")
						result.append(1, '>');
					else if(entity == "&amp;")
						result.append(1, '&');
					else if(entity == "&apos;")
						result.append(1, '\'');
					else if(entity == "&quot;")
						result.append(1, '"');
				}
				break;				
			default:
				result.append(1, *iter);
				break;
			}
		}
		
		return result;
	}


//##ModelId=4C0476B50108
int MyUtility::CBaseEncode::HexToInt(char inHexChar)
{
char &c = inHexChar;
		if(c>='0' && c <= '9')
			return c-'0';
		else if(c>='A' && c<= 'F')
			return c-'A' + 10;
		else if(c>='a' && c<= 'f')
			return c-'a' + 10;
		else
			return -1;
	}


//##ModelId=4C0477550001
int MyUtility::CBaseEncode::HexToInt(const std::string &inHexStr)
{
		int tmp, res = 0;
		string::const_iterator iter;
		
		for(iter = inHexStr.begin(); iter != inHexStr.end(); ++iter) 
		{
			tmp = HexToInt(*iter);
			if(tmp != -1)
			{
				res = res * 16 + tmp;
			}
			else

				return -1;
		}

		return res;
	}

unsigned int MyUtility::CBaseEncode::HexToUInt(char inHexChar)
{
	char &c = inHexChar;
	if(c>='0' && c <= '9')
		return c-'0';
	else if(c>='A' && c<= 'F')
		return c-'A' + 10;
	else if(c>='a' && c<= 'f')
		return c-'a' + 10;
	else
		return -1;
}


//##ModelId=4C0477550001
unsigned int MyUtility::CBaseEncode::HexToUInt(const std::string &inHexStr)
{
	unsigned int tmp, res = 0;
	string::const_iterator iter;
	
	for(iter = inHexStr.begin(); iter != inHexStr.end(); ++iter) 
	{
		tmp = HexToUInt(*iter);
		if(tmp != (unsigned int )-1)
		{
			res = res * 16 + tmp;
		}
		else

			return -1;
	}

	return res;
}
std::string  MyUtility::CBaseEncode::UIntToHex(unsigned int inData)
{
	unsigned char *pc  = (unsigned char *)&inData;
	
	std::string res;
	
	for(int i=0;i<(int)sizeof(inData);i++)
	{
		res+= CharToHex(*(pc+i));
	}
	return res;
}

//##ModelId=4C04777702D0
long MyUtility::CBaseEncode::HexToLong(const std::string &inHexStr)
{
long tmp, res = 0;
		string::const_iterator iter;
		
		for(iter = inHexStr.begin(); iter != inHexStr.end(); ++iter) 
		{
			tmp = HexToInt(*iter);
			if(tmp != -1)
			{
				res = res * 16 + tmp;
			}
			else

				return -1;
		}

		return res;
}

//##ModelId=4C0478FA020E
long MyUtility::CBaseEncode::StringToLong(const std::string &inStr)
{
	long i = 0;

		sscanf(inStr.c_str(),"%ld",&i);

		return i;
}

//##ModelId=4C0479250117
int MyUtility::CBaseEncode::StringToInt(const std::string &inStr)
{
int i = 0;

		sscanf(inStr.c_str(),"%d",&i);

		return i;
}


unsigned int MyUtility::CBaseEncode::StringToUInt(const std::string &inStr)
{
	unsigned int i = 0;

		sscanf(inStr.c_str(),"%u",&i);

		return i;
}

//##ModelId=4C0479360127
unsigned long MyUtility::CBaseEncode::HexToULong(const std::string &inHexStr)
{
	unsigned long tmp, res = 0;
		string::const_iterator iter;
		
		for(iter = inHexStr.begin(); iter != inHexStr.end(); ++iter) 
		{
			tmp = HexToInt(*iter);
			if(tmp != (unsigned int )-1)
			{
				res = res * 16 + tmp;
			}
			else

				return 0;
		}

		return res;
}

//##ModelId=4C04794602FD
unsigned long MyUtility::CBaseEncode::StringToULong(const std::string &inStr)
{
unsigned long i = 0;

		sscanf(inStr.c_str(),"%lu",&i);

		return i;
}

//##ModelId=4C04798C016B
std::string MyUtility::CBaseEncode::ULongToString(unsigned long inULong)
{
char szBuf[100] = {0};

		snprintf(szBuf,sizeof(szBuf),"%lu",inULong);

		return string(szBuf);
}
std::string MyUtility::CBaseEncode::IntToString(int inInt)
{
char szBuf[100] = {0};

		snprintf(szBuf,sizeof(szBuf),"%d",inInt);

		return string(szBuf);
}
std::string MyUtility::CBaseEncode::UIntToString(unsigned int inInt)
{
	char szBuf[100] = {0};

		snprintf(szBuf,sizeof(szBuf),"%u",inInt);

		return string(szBuf);
}

//##ModelId=4C0481990278
string &MyUtility::CBaseEncode::TrimLeft(std::string &ioStr, const string &inTrim)
{
string::const_iterator iter;
		iter = ioStr.begin();

		if(inTrim.size() == 0)
			return ioStr;
		while( iter != ioStr.end()) 
		{
			if(string::npos != inTrim.find(*iter) )
			//if((*iter)  == ' ')
			{
				ioStr.erase(0,1);
				iter = ioStr.begin();
			}
			else
				break;

		}
		return ioStr;
}

//##ModelId=4C04821803B7
string &MyUtility::CBaseEncode::TrimRight(std::string &src, const string &trim)
{
string::iterator iter,iterLast,iterTmp;
		iter = src.begin();
		iterLast = iter + (src.size() - 1);
		iterTmp = iter + (src.size() - 1);


		if(trim.size() == 0)
			return src;

		while( iterTmp != src.end()) 
		{
			if(string::npos != trim.find(*iterTmp) )
			//if((*iter)  == ' ')
			{
				iterTmp--;
			}
			else
				break;

		}
		if(iterLast != iterTmp++)
			src.erase(iterTmp,src.end());

		return src;
}

//##ModelId=4C04827402B0
std::string MyUtility::CBaseEncode::CharStrToHexStr(const std::string &inCharStr)
{
  std::string result;
  
  string::const_iterator iter;

  for(iter = inCharStr.begin(); iter != inCharStr.end(); ++iter) 
  {
    result.append(CharToHex(*iter));
  }
  
  return result;
}


//##ModelId=4C04827402DF
std::string MyUtility::CBaseEncode::HexStrToCharStr(const std::string &inHexStr, int inFlag)
{
  std::string result,tmp(inHexStr);
  
  if(inHexStr.size() % 2  !=  0 )
  {
	switch (inFlag)
	{
	case 0:
		return result;
	case 1:
		tmp="0" + tmp;
		break;
	case 2:
		tmp=tmp + "0";
		break;
	}
  }
  
  
  string::const_iterator iter;

  for(iter = tmp.begin(); iter != tmp.end(); ++iter) 
  {
  	char left = *iter++;
	char right = *iter;
    result.append(1,HexToChar(left,right));
  }

  
  return result;
  
}


//##ModelId=4C0483CD0113
std::string &MyUtility::CBaseEncode::StrReplace(std::string &str, const std::string &old_value, const std::string &new_value, int inFlag)
{
	if(inFlag == 1)
	{
		while(true)   
		{   
			string::size_type   pos(0);   
			if(   (pos=str.find(old_value))!=string::npos   )   
				str.replace(pos,old_value.length(),new_value);   
			else   
				break;   
		}   
	}
	else
	{
		for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   
		{   
			if(   (pos=str.find(old_value,pos))!=string::npos   )   
				str.replace(pos,old_value.length(),new_value);   
			else   break;   
		}   
	}
	
	
		return   str;   

}

