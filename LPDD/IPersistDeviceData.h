#ifndef IPERSISTDEVICEDATA_H_HEADER_INCLUDED_AE00E5FD
#define IPERSISTDEVICEDATA_H_HEADER_INCLUDED_AE00E5FD
//class StLastDeviceData;
#include "StLastDeviceData.h"
#include "StPersistDeviceData.h"

//##ModelId=51FF11110278
class IPersistDeviceData
{
  public:
    // 0 成功，可根据输出的
    // * 失败
    //##ModelId=51FF112600D0
    virtual int GetByImei(uint64_t inImei, StPersistDeviceData * &outstData) = 0;

    //##ModelId=51FF11600238
    virtual int AppendData(const StLastDeviceData *stData) = 0;

    //##ModelId=51FF1CD2004D
    virtual int GetByDid(uint32_t inDid, StPersistDeviceData* & outstData) = 0;

};



#endif /* IPERSISTDEVICEDATA_H_HEADER_INCLUDED_AE00E5FD */
