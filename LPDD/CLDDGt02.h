#ifndef CLDDGT02_H_HEADER_INCLUDED_AE04E7A8
#define CLDDGT02_H_HEADER_INCLUDED_AE04E7A8
#include "ILastDeviceData.h"
#include "gt02.h"
#include "StLastDeviceData.h"

#include "CLineSpaceMgr.h"



#include "CPDDGt02.h"


#include <map>

//##ModelId=51FA37690121
class CLDDGt02 : public ILastDeviceData
{
	std::map<uint64_t,uint32_t> m_mIMEI2DID;
	unsigned int m_uiLastLoaded;

	bool m_bInit;
	CLineSpaceMgr objCLineSpaceMgr;
  public:
  	CLDDGt02(){m_bInit=false;}
    // <0 没有足够的空间存放这个设备
    // 
    // 0  获取成功，且为初次注册的设备，可从结构体m_uiDid获取设备内部id
    // 
    // 1  获取成功，是已经注册过的设备
    // 
    //##ModelId=51FB1A5502F7
    virtual int Register(uint64_t imei, StLastDeviceData* &data);

    // *  未注册的设备
    // 
    // 0  获取成功，是已经注册过的设备
    // 
    //##ModelId=51FB1A550307
    virtual int GetByImei(uint64_t imei, StLastDeviceData* &data);

    // *  超出存储空间，此DID不在本存储区块
    // 
    // 0  获取成功
    // 
    //##ModelId=51FB1A55030A
    virtual int GetByDID(uint32_t dir, StLastDeviceData* &data);


	// 0 成功
	// * 失败
	virtual int SetData(const StGt02TermToSvrMsg *pGt02Data,int sock=-1);

	// 初始化存储空间，并建立索引
	// 0 成功
	// * 失败
	int Init(int inDeviceNumber=10000,int inSplitPara_FromNumber = 0,const char * inName="LDD_GT02");

	void DumpInfo(std::ostream & os);

	void LoadChange();
	

};



#endif /* CLDDGT02_H_HEADER_INCLUDED_AE04E7A8 */
