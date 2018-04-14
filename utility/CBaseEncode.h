// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#ifndef CBASEENCODE_H_HEADER_INCLUDED_B3FA7E34
#define CBASEENCODE_H_HEADER_INCLUDED_B3FA7E34

#include "mysoft_utility.h"

#include <openssl/evp.h>
#include <openssl/sha.h>
#include "openssl/md5.h"

namespace MyUtility {

class CMemString
{
public:
	static char ReadChar(const std::string & inMemstr,int inOffset,int &oSize);
	static unsigned char ReadUChar(const std::string & inMemstr,int inOffset,int &oSize);
	static short ReadShort(const std::string & inMemstr,int inOffset,int &oSize);
	static unsigned short ReadUShort(const std::string & inMemstr,int inOffset,int &oSize);
	static int ReadInt(const std::string & inMemstr,int inOffset,int &oSize);
	static unsigned int ReadUInt(const std::string & inMemstr,int inOffset,int &oSize);
	static long ReadLong(const std::string & inMemstr,int inOffset,int &oSize);
	static unsigned long ReadULong(const std::string & inMemstr,int inOffset,int &oSize);
	static float ReadFloat(const std::string & inMemstr,int inOffset,int &oSize);
	static double ReadDouble(const std::string & inMemstr,int inOffset,int &oSize);

	static std::string ReadCString(const std::string & inMemstr,int inOffset,int &ioSize);
	static std::string ReadBString(const std::string & inMemstr,int inOffset,int &ioSize);
};

// int long string char char *
//##ModelId=4C03287D0237
class CBaseEncode
{
  public:
    // URL编码，如" " -> "%25"
    //##ModelId=4C032991022D
    static std::string &UrlEncode(std::string &ioStr);
    static std::string &UrlEncode2(std::string &ioStr);

    // URL编码
    //##ModelId=4C0329C60134
    static std::string UrlEncode(const std::string &inStr);
    static std::string UrlEncode2(const std::string &ioStr);

    // URL解码
    //##ModelId=4C0329F60200
    static std::string &UrlDecode(std::string &ioStr);

    // URL解码
    //##ModelId=4C0329F6020F
    static std::string UrlDecode(const std::string &inStr);

    // charToHex:  "1" ->  "31"
    //##ModelId=4C032B7F031F
    static std::string CharToHex(char inChar);

    // charToHex: "31" -> "1"
    //##ModelId=4C032BBF0245
    static char HexToChar(char inFirstChar, char inSecondChar);

    // XML编码
    //##ModelId=4C03339402E4
    static std::string &XmlEncode(std::string &ioStr);

    // XML编码
    //##ModelId=4C03339402F4
    static std::string XmlEncode(const std::string &inStr);

    // XML编码
    //##ModelId=4C0333DE0150
    static std::string &XmlDecode(std::string &ioStr);

    // XML编码
    //##ModelId=4C0333DE0170
    static std::string XmlDecode(const std::string &inStr);

    //##ModelId=4C0476B50108
    static int HexToInt(char inHexChar);

    //##ModelId=4C0477550001
    static int HexToInt(const std::string &inHexStr);
    //##ModelId=4C0476B50108
    static unsigned int HexToUInt(char inHexChar);

    //##ModelId=4C0477550001
    static unsigned int HexToUInt(const std::string &inHexStr);
    static std::string UIntToHex(unsigned int inData);

    //##ModelId=4C04777702D0
    static long HexToLong(const std::string &inHexStr);

    //##ModelId=4C0478FA020E
    static long StringToLong(const std::string &inHexStr);

    //##ModelId=4C0479250117
    static int StringToInt(const std::string &inHexStr);
	static unsigned int StringToUInt(const std::string &inHexStr);

    //##ModelId=4C0479360127
    static unsigned long HexToULong(const std::string &inHexStr);

    //##ModelId=4C04794602FD
    static unsigned long StringToULong(const std::string &inStr);

    //##ModelId=4C04798C016B
    static std::string ULongToString(unsigned long inULong);
    static std::string IntToString(int inULong);
    static std::string UIntToString(unsigned  int inULong);

    // string & Trim(string & src,const string &trim = " ")
    //##ModelId=4C0481990278
    static string &TrimLeft(std::string &ioStr, const string &inTrim = " ");

    // string & Trim(string & src,const string &trim = " ")
    //##ModelId=4C04821803B7
    static string &TrimRight(std::string &ioStr, const string &inTrim = " ");

    // charToHex:  "1" ->  "31"
    //##ModelId=4C04827402B0
    static std::string CharStrToHexStr(const std::string &inCharStr);

    // charToHex: "31" -> "1"
    //##ModelId=4C04827402DF
    static std::string HexStrToCharStr(const std::string &inHexStr, 
        // 0 不进行补位操作
        // 1 如果不是偶数位，左补零操作
        // 2 如果不是偶数位，右补零操作
        int inFlag = 0);

    // 替换字符串中指定的值
    //##ModelId=4C0483CD0113
    static std::string &StrReplace(
        // 将被处理的字符串
        std::string &ioStr, 
        // 将被替换的字符串
        const std::string &inReplace, 
        // 将用来替换的字符串
        const std::string &inUse, 
        // 0 从头到尾扫描一遍，并替换
        // 1 始终从头扫描替换，直至没有
        int inFlag = 0);

		//////////////////////////////////////////
		static int get_first_http_text(const string &src,string::const_iterator &iter)
	{
		//无正文
		int res = 1;

		//0 1 2
		int state = 0;
		
		for( ; iter != src.end(); ++iter) 
		{
			switch(*iter) 
			{
			case '\n':
				state++;
				if(state == 2)
				{
					iter++;
					return 0;
				}
				break;	
			case '\r':
				break;
			default:
				if(state == 1) state=0;
				break;
			}
		}
		return res;

	}

	static string &get_first_line(string::const_iterator &iterBegin,const string::const_iterator &iterEnd,string & val)
	{
		val = "";
		for( ; iterBegin != iterEnd; ++iterBegin) 
		{
			switch(*iterBegin) 
			{
			case '\n':
				iterBegin++;
				return val;
				break;
			case '\r':						
				break;				
			default:
				val.append(1, *iterBegin);
				break;
			}
		}
		return val;
	}


	static string &get_first_line(const string & src,string::const_iterator &iter,string & val)
	{
		val = "";
		for( ; iter != src.end(); ++iter) 
		{
			switch(*iter) 
			{
			case '\n':
				iter++;
				return val;
				break;
			case '\r':						
				break;				
			default:
				val.append(1, *iter);
				break;
			}
		}
		return val;
	}

	static string& get_first_line(const string & src,string & val)
	{
		val = "";
		string::const_iterator iter;
		
		for(iter = src.begin(); iter != src.end(); ++iter) 
		{
			switch(*iter) 
			{
			case '\n':
				return val;
				break;
			case '\r':				
				break;				
			default:
				val.append(1, *iter);
				break;
			}
		}
		return val;
	}
static int AsciiToBcd2(const char *ascii,int len,char *bcd)
{
	const char *tbl="0123456789ABCDEF";
	unsigned char t;
	for(int i=0;i<len;i++)
	{
		t=(ascii[i]&(0xf0));
		t=t>>4;
		bcd[2*i]=*(tbl+t);
		t=(ascii[i]&(0x0f));
		bcd[2*i+1]=*(tbl+t);		
	}	
	return (2*len);
};
static int Bcd2ToAscii(const char *bcd,int len,int align,char *ascii)
{
	const char *tbl="0123456789ABCDEF";
	const char *tbl_low="0123456789abcdef";
	int i,j;
	char *tmpbuf;
	tmpbuf=(char *) malloc((len+1)*sizeof(char));
	memset(tmpbuf,'0',len+1);
	if((align!=0)&&(len%2)!=0)//右对齐
	{
		memcpy(tmpbuf+1,bcd,len);
	}
	else	//左对齐
	{
		memcpy(tmpbuf,bcd,len);
	}
	for(i=0;i<((len+1)/2);i++)
	{
		for(j=0;j<16;j++)
			if((*(tbl+j)==tmpbuf[2*i]) ||
				(*(tbl_low+j)==tmpbuf[2*i]))
				break;
		if(j==16)
		{
			free(tmpbuf);
			return -1;
		}
		ascii[i]=j;
		ascii[i] = ascii[i] << 4;
		for(j=0;j<16;j++)
			if((*(tbl+j)==tmpbuf[2*i+1])||
				(*(tbl_low+j)==tmpbuf[2*i+1]))
				break;
		if(j==16)
		{
			free(tmpbuf);
			return -1;
		}
		ascii[i] += j;
	}	
	free(tmpbuf);
	return (len+1)/2;
};

static string GetSiteFromUrl(const string &url)
	{
		string result;
		
		string::size_type   pos(0);   

		if(url.substr(0,7) == string("http://"))
			result = url.substr(7);
		else if(url.substr(0,8) == string("https://"))
			result = url.substr(8);


		if(((pos = result.find("/")) != string::npos))
		{
			result = result.substr(0,pos);
		}

		return result;

	}
	
	
	static double StringToDouble(string & str)
	{
		double i = 0;

		sscanf(str.c_str(),"%lf",&i);

		return i;
	}

	static string DoubleToString(double i)
	{
		char szBuf[100] = {0};

		snprintf(szBuf,sizeof(szBuf),"%lf",i);

		return string(szBuf);
	}

	template <class T>
	static std::string Hex(const T & in)
	{
		return Hex((const uint8_t *)&in,sizeof(in));
	}
	static std::string Hex(const uint8_t *ascii,int len)
	{
		std::string res("");
		
		const char *tbl="0123456789ABCDEF";
		unsigned char t;
		for(int i=0;i<len;i++)
		{
			t=(ascii[i]&(0xf0));
			t=t>>4;
			res +=*(tbl+t);
			
			t=(ascii[i]&(0x0f));

			res+=*(tbl+t);		
		}	
		return res;
	};
	
	static std::string &md5(const std::string &in, std::string &out)
	{
		char szSign[1024] = {0};

		unsigned char md[MD5_DIGEST_LENGTH];

		char *pszResult = szSign;

		EVP_Digest((void *)in.data(),in.size(),md,NULL,EVP_md5(), NULL);

		for (int i=0; i<MD5_DIGEST_LENGTH; i++)
			sprintf(pszResult+2*i,"%02X",md[i]);

		out =  szSign;

		return out;
	}
	
		//////////////////////////////////////////
};

} // namespace MyUtility



#endif /* CBASEENCODE_H_HEADER_INCLUDED_B3FA7E34 */
