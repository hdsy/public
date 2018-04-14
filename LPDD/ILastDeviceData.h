#ifndef ILASTDEVICEDATA_H_HEADER_INCLUDED_AE04E1FB
#define ILASTDEVICEDATA_H_HEADER_INCLUDED_AE04E1FB
#include "StLastDeviceData.h"

//##ModelId=51FA22C40133
class ILastDeviceData
{
  public:
  	
  	//
  	uint32_t m_uiFromDid;
    // <0 没有足够的空间存放这个设备
    // 
    // 0  获取成功，且为初次注册的设备，可从结构体m_uiDid获取设备内部id
    // 
    // 1  获取成功，是已经注册过的设备
    // 
    //##ModelId=51FA268B0244
    virtual int Register(uint64_t imei, StLastDeviceData* &data) = 0;

    // *  未注册的设备
    // 
    // 0  获取成功，是已经注册过的设备
    // 
    //##ModelId=51FA36B202C4
    virtual int GetByImei(uint64_t imei, StLastDeviceData* &data) = 0;

    // *  超出存储空间，此DID不在本存储区块
    // 
    // 0  获取成功
    // 
    //##ModelId=51FA36FE0168
    virtual int GetByDID(uint32_t did, StLastDeviceData* &data) = 0;

};



#endif /* ILASTDEVICEDATA_H_HEADER_INCLUDED_AE04E1FB */
