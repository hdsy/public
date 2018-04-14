#ifndef STPERSISTDEVICEDATA_H_HEADER_INCLUDED_AE00DCAA
#define STPERSISTDEVICEDATA_H_HEADER_INCLUDED_AE00DCAA
#include "StLastDeviceData.h"


#pragma pack(1)
//##ModelId=51FF0DCC031F

#define MAX_DAY_RECORD_NUMBER 8640

typedef struct ST_PERSIST_DEVICE_DATA
{
  public:
    // 使用了多少条空间
    //##ModelId=51FF0FD80141
    uint16_t m_usUsed;

    //##ModelId=51FF2E9E00CB
    uint16_t m_usHourOffset[24];

    // 记录最少一天的数据，最近8640条记录
    //##ModelId=51FF0ECE008A
    StLastDeviceData m_stItem[MAX_DAY_RECORD_NUMBER];

	void DumpInfo(std::ostream & os)
	{
		os << "record number :" << m_usUsed << " || ";

		
		if(m_usUsed>0)
		{
			for(int i=0;i<24;i++)
				os << i << "-" <<m_usHourOffset[i] << " " ;

			os << "\r\n newest reord dump bellow "<< std::endl;

			m_stItem[m_usUsed-1].DumpInfo(os);
		}
	}

}StPersistDeviceData;

#pragma pack()

#endif /* STPERSISTDEVICEDATA_H_HEADER_INCLUDED_AE00DCAA */
