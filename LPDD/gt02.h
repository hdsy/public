#ifndef DEVICE_GT02_H
#define DEVICE_GT02_H

#include <stdint.h>

#include <sys/types.h>


#include "CBaseEncode.h"
#include "CTime.h"


#define PREFIX 	(0x6868)
#define POSTFIX	(0x0a0d)

#pragma pack(1)
// GT02 协议报文
	typedef struct ST_GT02_TERM_TO_SVR_HEADER
	{

		uint16_t 	m_usPrefix;
		uint8_t		m_ubLength;
		uint16_t	m_usLAC;		// heartbeat:1电压登记、2GSM信号强度
		uint64_t	m_ullImei;
		uint16_t	m_usVno;
		uint8_t		m_ubCmd;
		
	}StGt02TermToSvrHeader;
	
	//  无回报
	typedef struct ST_GT02_TERM_TO_SVR_0x10_Content
	{
		uint8_t 	m_szDateTime[6];//
		uint32_t	m_uiLatitude;	//
		uint32_t	m_uiLongitude;	//
		uint8_t		m_ubSpeed;		//
		uint16_t	m_usDitection;	//
		uint8_t		m_ubMNC;		//
		uint16_t	m_usCellID;		//
		uint32_t	m_uiStatus;		// 0 卫星定位与否 1 北纬与否 2 东经与否
		uint16_t	m_uiPostfix;	//	结束符号
	}StGt02TermToSvr0x10Content;
	
	typedef struct ST_GT02_TERM_TO_SVR_0x1a_Content
	{
		uint8_t 	m_ubGpsStatus;	//	值范围00H~02H 定位状态： 0—没有定位 1—实时GPS 2—差分GPS 
		uint8_t		m_ubSNumber;	//	卫星的个数
		uint8_t		m_szSStatus[0];	//	卫星的状态，一个一个列表		
	}StGt02TermToSvr0x1aContent;
	
	typedef struct ST_GT02_SVT_TO_TERM_RESPONSE
	{
		uint16_t 	m_usPrefix;		//	开始符号
		uint8_t		m_ubCmd;		//	协议号
		uint16_t	m_uiPostfix;	//	结束符号
		
		ST_GT02_SVT_TO_TERM_RESPONSE(uint8_t cmd,uint16_t pre=PREFIX,uint16_t post=POSTFIX)
		{
			m_usPrefix = pre;m_ubCmd=cmd;m_uiPostfix=post;
		}
	}StGt02SvrToTermResponse;
	
	//
	typedef struct ST_GT02_TERM_TO_SVR_0x1b_Content
	{
		uint8_t 	m_szDateTime[6];//
		uint32_t	m_uiLatitude;	//
		uint32_t	m_uiLongitude;	//
		uint8_t		m_ubSpeed;		//
		uint16_t	m_usDitection;	//
		uint8_t		m_ubMNC;		//
		uint16_t	m_usCellID;		//
		uint32_t	m_uiStatus;		// 0 卫星定位与否 1 北纬与否 2 东经与否
		uint8_t		m_szTele[21];	//
		uint8_t		m_ubLang;		// 0x01 中文 0x02 英文
		uint16_t	m_uiPostfix;	//	结束符号
	}StGt02TermToSvr0x1bContent;

	

	typedef struct ST_GT02_TERM_TO_SVR_0x1d_Content
	{
		uint8_t	m_ubStatus;		// 0 卫星定位与否 1 北纬与否 2 东经与否
		uint8_t 	m_szDateTime[6];
		uint16_t	m_uiPostfix;	//	结束符号
	}StGt02TermToSvr0x1dContent;

typedef union UN_GT02_TERM_TO_SVR_CONTENT
{
	uint8_t		m_szContent[0];
	StGt02TermToSvr0x1bContent	m_st0x1b;
	StGt02TermToSvr0x1aContent	m_st0x1a;
	StGt02TermToSvr0x10Content	m_st0x10;
	StGt02TermToSvr0x1dContent	m_st0x1d;
}UnGt02TermToSvrContent;

typedef struct ST_GT02_TERM_TO_SVR_MSG
{
	StGt02TermToSvrHeader 	m_stHeader;
	UnGt02TermToSvrContent	m_unContent;

	/*	
		^([a-z_.]+)
		os << "m_st0x10.\1=" <<m_unContent.m_st0x10.\1 << std::endl
	 */

	template<class T>
	std::string Hex(const T & in)
	{
		return BaseHex((const uint8_t *)&in,sizeof(in));
	}
	std::string BaseHex(const uint8_t *ascii,int len)
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

	
	void DumpInfo(std::ostream &os )
	{
		//输出头
		os << "m_stHeader.m_usPrefix=" << Hex(m_stHeader.m_usPrefix) << std::endl;
		os << "m_stHeader.m_ubLength=" << Hex(m_stHeader.m_ubLength) << std::endl;
		os << "m_stHeader.m_usLAC=" << 	  Hex(m_stHeader.m_usLAC) << std::endl;		// heartbeat:1电压登记、2GSM信号强度
		os << "m_stHeader.m_ullImei=" <<  Hex(m_stHeader.m_ullImei) << std::endl;
		os << "m_stHeader.m_usVno=" <<    Hex(m_stHeader.m_usVno) << std::endl;
		os << "m_stHeader.m_ubCmd=" <<    Hex(m_stHeader.m_ubCmd) << std::endl;

		switch(m_stHeader.m_ubCmd)
		{
		case 0x10: 
			{
				os << "m_st0x10.m_szDateTime=" <<BaseHex(m_unContent.m_st0x10.m_szDateTime,6) << std::endl;//
				os << "m_st0x10.m_uiLatitude=" <<Hex(m_unContent.m_st0x10.m_uiLatitude) << std::endl;	//
				os << "m_st0x10.m_uiLongitude=" <<Hex(m_unContent.m_st0x10.m_uiLongitude) << std::endl;	//
				os << "m_st0x10.m_ubSpeed=" <<Hex(m_unContent.m_st0x10.m_ubSpeed) << std::endl;		//
				os << "m_st0x10.m_usDitection=" <<Hex(m_unContent.m_st0x10.m_usDitection) << std::endl;	//
				os << "m_st0x10.m_ubMNC=" <<Hex(m_unContent.m_st0x10.m_ubMNC) << std::endl;		//
				os << "m_st0x10.m_usCellID=" <<Hex(m_unContent.m_st0x10.m_usCellID) << std::endl;		//
				os << "m_st0x10.m_uiStatus=" <<Hex(m_unContent.m_st0x10.m_uiStatus) << std::endl;		// 0 卫星定位与否 1 北纬与否 2 东经与否
				os << "m_st0x10.m_uiPostfix=" <<Hex(m_unContent.m_st0x10.m_uiPostfix) << std::endl;	//	结束符号
				break;
			}
		default:
			break;
		}
		
	}

}StGt02TermToSvrMsg;	


typedef struct ST_GT02_SVR_TO_TERM_0x17_Header
{
	uint16_t m_uiPrefix;
	uint8_t	 m_ubLength;
	uint8_t	 m_ubCmd;
	uint8_t	 m_ubCmdLen;
	
	uint32_t m_uiSvrTag;		// 未完

	uint8_t	 m_ubContent[250];

	uint16_t m_usVno;
	uint16_t m_usChkcd;
	uint16_t m_usPostfix;
	
}StGt02SvrToTerm0x17Header;




#pragma pack()

static const uint16_t crctab16[] =
{
    0X0000, 0X1189, 0X2312, 0X329B, 0X4624, 0X57AD, 0X6536, 0X74BF,
    0X8C48, 0X9DC1, 0XAF5A, 0XBED3, 0XCA6C, 0XDBE5, 0XE97E, 0XF8F7,
    0X1081, 0X0108, 0X3393, 0X221A, 0X56A5, 0X472C, 0X75B7, 0X643E,
    0X9CC9, 0X8D40, 0XBFDB, 0XAE52, 0XDAED, 0XCB64, 0XF9FF, 0XE876,
    0X2102, 0X308B, 0X0210, 0X1399, 0X6726, 0X76AF, 0X4434, 0X55BD,
    0XAD4A, 0XBCC3, 0X8E58, 0X9FD1, 0XEB6E, 0XFAE7, 0XC87C, 0XD9F5,
    0X3183, 0X200A, 0X1291, 0X0318, 0X77A7, 0X662E, 0X54B5, 0X453C,
    0XBDCB, 0XAC42, 0X9ED9, 0X8F50, 0XFBEF, 0XEA66, 0XD8FD, 0XC974,
    0X4204, 0X538D, 0X6116, 0X709F, 0X0420, 0X15A9, 0X2732, 0X36BB,
    0XCE4C, 0XDFC5, 0XED5E, 0XFCD7, 0X8868, 0X99E1, 0XAB7A, 0XBAF3,
    0X5285, 0X430C, 0X7197, 0X601E, 0X14A1, 0X0528, 0X37B3, 0X263A,
    0XDECD, 0XCF44, 0XFDDF, 0XEC56, 0X98E9, 0X8960, 0XBBFB, 0XAA72,
    0X6306, 0X728F, 0X4014, 0X519D, 0X2522, 0X34AB, 0X0630, 0X17B9,
    0XEF4E, 0XFEC7, 0XCC5C, 0XDDD5, 0XA96A, 0XB8E3, 0X8A78, 0X9BF1,
    0X7387, 0X620E, 0X5095, 0X411C, 0X35A3, 0X242A, 0X16B1, 0X0738,
    0XFFCF, 0XEE46, 0XDCDD, 0XCD54, 0XB9EB, 0XA862, 0X9AF9, 0X8B70,
    0X8408, 0X9581, 0XA71A, 0XB693, 0XC22C, 0XD3A5, 0XE13E, 0XF0B7,
    0X0840, 0X19C9, 0X2B52, 0X3ADB, 0X4E64, 0X5FED, 0X6D76, 0X7CFF,
    0X9489, 0X8500, 0XB79B, 0XA612, 0XD2AD, 0XC324, 0XF1BF, 0XE036,
    0X18C1, 0X0948, 0X3BD3, 0X2A5A, 0X5EE5, 0X4F6C, 0X7DF7, 0X6C7E,
    0XA50A, 0XB483, 0X8618, 0X9791, 0XE32E, 0XF2A7, 0XC03C, 0XD1B5,
    0X2942, 0X38CB, 0X0A50, 0X1BD9, 0X6F66, 0X7EEF, 0X4C74, 0X5DFD,
    0XB58B, 0XA402, 0X9699, 0X8710, 0XF3AF, 0XE226, 0XD0BD, 0XC134,
    0X39C3, 0X284A, 0X1AD1, 0X0B58, 0X7FE7, 0X6E6E, 0X5CF5, 0X4D7C,
    0XC60C, 0XD785, 0XE51E, 0XF497, 0X8028, 0X91A1, 0XA33A, 0XB2B3,
    0X4A44, 0X5BCD, 0X6956, 0X78DF, 0X0C60, 0X1DE9, 0X2F72, 0X3EFB,
    0XD68D, 0XC704, 0XF59F, 0XE416, 0X90A9, 0X8120, 0XB3BB, 0XA232,
    0X5AC5, 0X4B4C, 0X79D7, 0X685E, 0X1CE1, 0X0D68, 0X3FF3, 0X2E7A,
    0XE70E, 0XF687, 0XC41C, 0XD595, 0XA12A, 0XB0A3, 0X8238, 0X93B1,
    0X6B46, 0X7ACF, 0X4854, 0X59DD, 0X2D62, 0X3CEB, 0X0E70, 0X1FF9,
    0XF78F, 0XE606, 0XD49D, 0XC514, 0XB1AB, 0XA022, 0X92B9, 0X8330,
    0X7BC7, 0X6A4E, 0X58D5, 0X495C, 0X3DE3, 0X2C6A, 0X1EF1, 0X0F78,
};

//  计算给定长度数据的 16 位 CRC。
class CGt02Method
{
public:
	static uint16_t Gt02_GetCrc16(const uint8_t* pData, int nLength)
	{
	    uint16_t  fcs  =  0xffff;         
		
		//  初始化
	    while(nLength>0)
		{
	        fcs = (fcs >> 8) ^ crctab16[(fcs ^ *pData) & 0xff];
	        nLength--;
	        pData++;
	    }
		
		//  取反
	    return  ~fcs;         
	}
};


class CGt02Time : public MyUtility::CTime
{
public:
	CGt02Time(const string & inYMDhms)
	{
		sscanf(MyUtility::CBaseEncode::CharStrToHexStr(inYMDhms).c_str(), 
			"%02d%02d%02d%02d%02d%02d" ,
			&(m_strutm.tm_year), &(m_strutm.tm_mon), &(m_strutm.tm_mday),
			&(m_strutm.tm_hour), &(m_strutm.tm_min), &(m_strutm.tm_sec));
		
		m_strutm.tm_year += 100;
		m_strutm.tm_mon--;
		m_strutm.tm_isdst = -1;
		m_iTime = mktime(&m_strutm);

	}

	CGt02Time():CTime()
	{
		//CTime::CTime();
	}
	
	~CGt02Time()
	{
	}

	string Format(const char * pFormat="0xyymmddhhmmss" ) const
	{
		if(strcasecmp(pFormat,"0xyymmddhhmmss") == 0 )
		{
	        char t_szBuf[256];

	        memset(t_szBuf,0,sizeof(t_szBuf));	        

            snprintf(t_szBuf,sizeof(t_szBuf),"%02d%02d%02d%02d%02d%02d",
				(m_strutm.tm_year+1900)%100,
				m_strutm.tm_mon+1,
	            m_strutm.tm_mday,
	            m_strutm.tm_hour,
	            m_strutm.tm_min,
	            m_strutm.tm_sec);


	        return MyUtility::CBaseEncode::HexStrToCharStr(t_szBuf);
		}
		else
			return CTime::Format(pFormat);
	};
		
};

class CGt02Position
{
public:
	uint32_t m_uiLatitude,m_uiLongitude;

	double m_dblLatitude,m_dblLongitude;

	CGt02Position(double dblLati,double dblLongi):m_dblLatitude(dblLati),m_dblLongitude(dblLongi)
	{
		m_uiLatitude = dblLati * 60 * 30000;
		m_uiLongitude = dblLongi * 60 * 30000;
	}

	CGt02Position(uint32_t uiLati,uint32_t uiLongi)
	{
		m_dblLatitude = m_uiLatitude = uiLati ;

		m_dblLatitude /= 30000 * 60 ;
		
		m_dblLongitude = m_uiLongitude = uiLongi ;

		m_dblLongitude /= 30000 * 60;
	}

	~CGt02Position(){}

	void DumpInfo(std::ostream &os )
	{
		os << "gt02 : " << m_uiLatitude << "," << m_uiLongitude << std::endl;
		os << "comn : " << m_dblLatitude << "," << m_dblLongitude << std::endl;
	}

	
};

	
#endif //DEVICE_GT02_H

