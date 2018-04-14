#include "CPDDGt02.h"
#include "StLastDeviceData.h"

#include "StPersistDeviceData.h"

#include "CTime.h"

#include "CLineSpaceMgr.h"





//##ModelId=51FF2CB60240
int CPDDGt02::GetByImei(uint64_t inImei, StPersistDeviceData* &data)
{
	
	LoadChange();
	
	if(m_mIMEI2BID.find(inImei) != m_mIMEI2BID.end())
	{
		
		data = (StPersistDeviceData*) objCLineSpaceMgr.AsVoid(CPointer(1,m_mIMEI2BID[inImei]));

		if (NULL==data)
			return SPACE_MANAGER_FILO_NOT_INIT;

		
		
		return 0;
	}

	return -1;
}

void CPDDGt02::DumpInfo(std::ostream & os)
{
	objCLineSpaceMgr.DumpInfo(os);

	LoadChange();

	os << "recorded device number is :" << m_mIMEI2BID.size() << std::endl;

	std::map<uint64_t,uint32_t>::const_iterator iter;

	StPersistDeviceData* data = NULL;

	for(iter=m_mIMEI2BID.begin();iter!=m_mIMEI2BID.end();iter++)
	{
		static int i =0;
		

		os << i++ << " : imei  " << iter->first << " ,bid " << iter->second ;

		if(0 == GetByImei(iter->first,data))
		{
			data->DumpInfo(os);
		}

		if (i>= 10) break;
	}
}


//##ModelId=51FF2CB60260
int CPDDGt02::AppendData(const StLastDeviceData *stData)
{
	StPersistDeviceData *data;

	if( 0 != GetByImei(stData->m_ullIMEI,data))
	{
		CPointer pt = objCLineSpaceMgr.Alloc();

		data = (StPersistDeviceData*) objCLineSpaceMgr.AsVoid(pt);

		if (NULL==data)
			return SPACE_MANAGER_FILO_NOT_INIT;

		memset(data,0,sizeof(StPersistDeviceData));

		m_mIMEI2BID[stData->m_ullIMEI] = pt.m_uiOffset;
		m_mDID2BID[stData->m_uiDid] = pt.m_uiOffset;
	}

	data->m_stItem[data->m_usUsed++] = *stData;

	
	MyUtility::CTime tmTerm(stData->m_tmTerm);

	if(data->m_usHourOffset[tmTerm.GetHour()] == 0)
		data->m_usHourOffset[tmTerm.GetHour()] = data->m_usUsed; // 0 表示空,-1表示真正的序号
		
	//

	return 0;

}

//##ModelId=51FF2CB6026F
int CPDDGt02::GetByDid(uint32_t inDid, StPersistDeviceData* &data)
{
	

	LoadChange();
	
	if(m_mDID2BID.find(inDid) != m_mDID2BID.end())
	{
		
		data = (StPersistDeviceData*) objCLineSpaceMgr.AsVoid(CPointer(1,m_mDID2BID[inDid]));

		if (NULL==data)
			return SPACE_MANAGER_FILO_NOT_INIT;

		
		
		return 0;
	}
}
int CPDDGt02::GetByBid(uint32_t inBid, StPersistDeviceData* &data)
{
	
		
		data = (StPersistDeviceData*) objCLineSpaceMgr.AsVoid(CPointer(1,inBid));

		if (NULL==data)
			return SPACE_MANAGER_FILO_NOT_INIT;

		
		
		return 0;
}

//##ModelId=51FF2EFB0224
int CPDDGt02::Init(int inDevNum, uint32_t inSplitPara_FromNum, const char *inName)
{
	int iRet = objCLineSpaceMgr.Init(sizeof(StPersistDeviceData),inDevNum,inName,true);	

	if(iRet != OK)
	{
		return iRet;
	}

	m_uiFromDid = inSplitPara_FromNum;

	m_mIMEI2BID.clear();
	m_mDID2BID.clear();

	m_uiLastLoaded = 0;
	
	// 遍历 ,建立IMEI,DID到bid的映射 : 此空间确保能快速检索当日的(最近8640条)数据
	
	for(int i=m_uiLastLoaded;i<objCLineSpaceMgr.GetSize();i++)
	{
		CPointer tmpPoint(1,i);
		StPersistDeviceData *pStPersistDeviceData = (StPersistDeviceData*) objCLineSpaceMgr.AsVoid(tmpPoint);

		if(pStPersistDeviceData == NULL)
			return SPACE_MANAGER_FILO_NOT_INIT;

		if(pStPersistDeviceData->m_usUsed == 0 )
		{
			objCLineSpaceMgr.Free(tmpPoint);
		}


		m_mIMEI2BID[pStPersistDeviceData->m_stItem[0].m_ullIMEI] = i;
		m_mDID2BID[pStPersistDeviceData->m_stItem[0].m_uiDid] = i;
		m_uiLastLoaded = i;
	}

	return 0;
}

void CPDDGt02::LoadChange()
{
	for(int i=m_uiLastLoaded;i<objCLineSpaceMgr.GetSize();i++)
	{
		CPointer tmpPoint(1,i);
		StPersistDeviceData *pStPersistDeviceData = (StPersistDeviceData*) objCLineSpaceMgr.AsVoid(tmpPoint);

		if(pStPersistDeviceData == NULL)
			return ;

		if(pStPersistDeviceData->m_usUsed == 0 )
		{
			objCLineSpaceMgr.Free(tmpPoint);
		}

		m_mIMEI2BID[pStPersistDeviceData->m_stItem[0].m_ullIMEI] = i;
		m_mDID2BID[pStPersistDeviceData->m_stItem[0].m_uiDid] = i;

		m_uiLastLoaded = i;
	}

}


