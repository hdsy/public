#ifndef STLASTDEVICEDATA_H_HEADER_INCLUDED_AE04F8F8
#define STLASTDEVICEDATA_H_HEADER_INCLUDED_AE04F8F8
#include <sys/types.h>
#include <stdint.h>

#include <string>
#include <ostream>

#pragma pack(1)

//##ModelId=51FA15370236
typedef struct ST_LAST_DEVICE_DATA
{
    // 将数据清空,避免下线设备数据重用时对新设备造成混淆
    //##ModelId=51FA35750286
    void Clear();

    //##ModelId=51FA15B30010
    uint32_t m_uiLatitude;

    //##ModelId=51FA27740326
    uint32_t m_uiLongitue;

    //##ModelId=51FA28900005
    uint16_t m_usLAC;

    //##ModelId=51FA28D80235
    uint64_t m_ullIMEI;

    //##ModelId=51FA29180340
    uint16_t m_usVno;

    //##ModelId=51FA294600F7
    uint16_t m_usDirection;

    //##ModelId=51FA295902D4
    uint8_t m_ubSpeed;

    //##ModelId=51FA29AB0052
    uint8_t m_ubMNC;

    //##ModelId=51FA29BF01B3
    uint16_t m_usCellID;

    // 从右到左：
    // 第一字节 GPS状态
    // 0 GPS 是否定位
    // 1 北纬
    // 2 东经
    // 
    
    // 
    // 第三字节 0到2的四个bit表示档位状态
    // 16+ 0, 档位信息有效则置 1
    // 16+ 1, 
    // 16+ 2, 档位0x0f 0x3
    // 16+ 3, 

	
    //##ModelId=51FA29F80324
    uint32_t m_uiStatus;

    // 最后一次GPS数据上报时间
    //##ModelId=51FA279B017B
    uint32_t m_tmGpsData;

    // 越大，表示电量越高
    // 
    // 0：低电关机；
    // 1：电量不足以打电话发短信等；
    // 2：低电报警；
    // 3：低电，可正常使用；
    // 3~6：均可正常使用，只是依据电量多少不同而排列。
    //##ModelId=51FA2AA50084
    uint8_t m_ubPower;

    // 越大，表示GSM信号越好
    // 0x00：无信号；
    // 0x01：信号极弱
    // 0x02：信号较弱
    // 0x03：信号良好
    // 0x04：信号强
    //##ModelId=51FA2B150099
    uint8_t m_ubGsm;

    // GPS定位的状态
    // 
    // 0 未定位
    // 1 实时
    // 2 差分
    //##ModelId=51FA2B8D01C5
    uint8_t m_ubGpsStatus;

    // GPS定位的卫星数量
    //##ModelId=51FA2C0E03B4
    uint8_t m_ubSNumber;

    // GPS定位的前10颗卫星信噪比
    //##ModelId=51FA2C5F006C
    uint8_t m_ubSSNR[10];

    // 最后一次心跳数据上报时间
    //##ModelId=51FA2CAC01A0
    uint32_t m_tmHBData;

    // 向终端发送地址查询命令的手机号码
    // 
    // 表示22位数字，右对齐。,第一位是表示英文，中文
    //##ModelId=51FA2D750332
    uint8_t m_ubMobile[11];
	

    // 最后一次位置查询时间
    //##ModelId=51FA2E1B0197
    uint32_t m_tmAddrData;

    // 最后一次异常时间
    //##ModelId=51FA2EBD026D
    //设备异常状态
    //   1，10分钟内GPS 无输出重启,。
    //   2，GPS 10分钟内没定到位冷启动。
    //   3，设备连接不上服务器而导致重启。
    //   4，SENSOR寄存器数据复位重新初始化。
    //   5，IMEI丢失导致重写imei至设备。
    //   6，24小时重启设备.
    uint8_t m_ubExp;
    uint32_t m_tmExpData;

    // 设备的唯一标识
    //##ModelId=51FA2FC303DA
    uint32_t m_uiDid;

	
	//
	uint32_t m_tmSvr;
	uint32_t m_tmTerm;

	//设备的通讯信道: 当设备正常工作时，就会保持这个通道 
	int 	m_sockDev;
	//用户的通讯信道: 当用户查看设备，并希望实时收到设备信息时，就会保持这条通道
	int		m_sockUsr;
	
	std::string Hex(const uint8_t *ascii,int len)
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


	template <class T>
	std::string Hex(const T & in)
		{
			return Hex((const uint8_t *)&in,sizeof(in));
		}

	void DumpInfo(std::ostream & os)
	{
		os << "\r\n---" << Hex( m_uiDid ) << " " << Hex( m_ullIMEI ) << "---" << std::endl;
		os << "+lati \t longi \t LAC \t Vno \t Dir \t Speed \t MNC \t CellID \t Status \t GpsDataTimeStamp \r\n"		
			<< Hex( m_uiLatitude ) << " " 
			<< Hex( m_uiLongitue ) << " "
			<< Hex( m_usLAC ) << " "
			<< Hex( m_usVno ) << " "
			<< Hex( m_usDirection ) << " "
			<< Hex( m_ubSpeed ) << " "
			<< Hex( m_ubMNC ) << " "
			<< Hex( m_usCellID ) << " "
			<< Hex( m_uiStatus ) << " "
			<< Hex( m_tmGpsData ) << std::endl;
			
		os << "+power \t gsm \t SNum \t SSNR \t HBDataTimeStamp \r\n"
			<< Hex( m_ubPower ) << " "
			<< Hex( m_ubGsm ) << " "
			<< Hex( m_ubGpsStatus ) << " "
			<< Hex( m_ubSNumber ) << " " 
			<< Hex( m_ubSSNR,10 ) << " "
			<< Hex( m_tmHBData ) << std::endl;
		
		os << "Mobile[11] = " << Hex( m_ubMobile,11 ) << " "  
		 	<< "AddrDataTimeStamp = " << Hex( m_tmAddrData ) << " "
			<< "Exp = " << Hex( m_ubExp ) << " "
			<< "ExpDataTimeStamp = " << Hex( m_tmExpData ) << std::endl;

		os << " ---dev sock " << m_sockDev << " ---- usr sock " << m_sockUsr  << "----\r\n\r\n"; 

		
	}
	

}StLastDeviceData;

#pragma pack()


#endif /* STLASTDEVICEDATA_H_HEADER_INCLUDED_AE04F8F8 */
