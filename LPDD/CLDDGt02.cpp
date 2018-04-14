#include "CLDDGt02.h"

#include "CCommandLineInfo.h"


//##ModelId=51FB1A5502F7
int CLDDGt02::Register(uint64_t imei, StLastDeviceData* &data)
{	
	LoadChange();
	//
	if(m_mIMEI2DID.find(imei) != m_mIMEI2DID.end())
	{
		//
		data = (StLastDeviceData*) objCLineSpaceMgr.AsVoid(CPointer(1,m_mIMEI2DID[imei]));

		if (NULL==data)
			return SPACE_MANAGER_FILO_NOT_INIT;
		
		return 1;
	}
	else
	{
		CPointer pt = objCLineSpaceMgr.Alloc();

		data = (StLastDeviceData*) objCLineSpaceMgr.AsVoid(pt);

		if (NULL==data)
			return SPACE_MANAGER_FILO_NOT_INIT;

		memset(data,0,sizeof(StLastDeviceData));

		data->m_ullIMEI = imei;
		data->m_uiDid = pt.m_uiOffset + m_uiFromDid;

		m_mIMEI2DID[data->m_ullIMEI] = data->m_uiDid;
		
		//
		return 0;
	}
}

//##ModelId=51FB1A550307
int CLDDGt02::GetByImei(uint64_t imei, StLastDeviceData* &data)
{
	LoadChange();
	
	if(m_mIMEI2DID.find(imei) != m_mIMEI2DID.end())
	{
		//
		data = (StLastDeviceData*) objCLineSpaceMgr.AsVoid(CPointer(1,m_mIMEI2DID[imei]));

		if (NULL==data)
			return SPACE_MANAGER_FILO_NOT_INIT;
		
		return 0;
	}

	return -1;
}

//##ModelId=51FB1A55030A
int CLDDGt02::GetByDID(uint32_t did, StLastDeviceData* &data)
{
	data = (StLastDeviceData*) objCLineSpaceMgr.AsVoid(CPointer(1,did-m_uiFromDid));

	if (NULL==data)
		return SPACE_MANAGER_FILO_NOT_INIT;

	if (did != data->m_uiDid)
		return SPACE_MANAGER_FILO_NOT_INIT;
	
	return 0;
}

int CLDDGt02::SetData(const StGt02TermToSvrMsg *pGt02Data,int sock)
{
	StLastDeviceData * data = NULL;

	if (0 != GetByImei(pGt02Data->m_stHeader.m_ullImei,data))
		return -1;// 设备未注册

	uint32_t tmTerm = 0;

	data->m_sockDev = sock;

	switch(pGt02Data->m_stHeader.m_ubCmd)
	{
	case 0x10:
		{
			CGt02Time gt02time((const char *)pGt02Data->m_unContent.m_st0x10.m_szDateTime);

			tmTerm = gt02time.m_iTime;
			
			if(gt02time.m_iTime >= data->m_tmGpsData)
			{
				data->m_usLAC = pGt02Data->m_stHeader.m_usLAC;
				data->m_usVno= pGt02Data->m_stHeader.m_usVno;

				data->m_tmGpsData = gt02time.m_iTime;

				data->m_uiLatitude = pGt02Data->m_unContent.m_st0x10.m_uiLatitude;
				data->m_uiLongitue = pGt02Data->m_unContent.m_st0x10.m_uiLongitude;
				data->m_ubMNC = pGt02Data->m_unContent.m_st0x10.m_ubMNC;
				data->m_ubSpeed = pGt02Data->m_unContent.m_st0x10.m_ubSpeed;
				data->m_uiStatus = pGt02Data->m_unContent.m_st0x10.m_uiStatus;
				data->m_usCellID = pGt02Data->m_unContent.m_st0x10.m_usCellID;
				data->m_usDirection = pGt02Data->m_unContent.m_st0x10.m_usDitection;

				data->m_tmTerm = data->m_tmGpsData;

				data->m_tmSvr = time(NULL);
			}
		}break;
	case 0x1a:
		{
			const uint16_t &tmp = pGt02Data->m_stHeader.m_usLAC;
			data->m_ubPower= *((uint8_t *)&tmp);
			data->m_ubGsm = *(((uint8_t *)&tmp)+1);
			
			data->m_usVno= pGt02Data->m_stHeader.m_usVno;

			data->m_tmHBData= time(NULL);

			data->m_ubGpsStatus = pGt02Data->m_unContent.m_st0x1a.m_ubGpsStatus;
			data->m_ubSNumber = pGt02Data->m_unContent.m_st0x1a.m_ubSNumber;
			
			memcpy(data->m_ubSSNR,pGt02Data->m_unContent.m_st0x1a.m_szSStatus,data->m_ubSNumber<=10?data->m_ubSNumber:10);

			data->m_tmTerm = data->m_tmSvr = time(NULL);
			
		}break;
	case 0x1d:
		{			
			CGt02Time gt02time((const char *)pGt02Data->m_unContent.m_st0x1d.m_szDateTime);

			tmTerm = gt02time.m_iTime;
			
			if(gt02time.m_iTime >= data->m_tmExpData)
			{
				data->m_tmExpData = gt02time.m_iTime;

				data->m_ubExp = pGt02Data->m_unContent.m_st0x1d.m_ubStatus;

				data->m_tmTerm = data->m_tmExpData;

				data->m_tmSvr = time(NULL);
			}
		}break;
	case 0x1b:
		{
			
			CGt02Time gt02time((const char *)pGt02Data->m_unContent.m_st0x1b.m_szDateTime);

			tmTerm = gt02time.m_iTime;

			if(gt02time.m_iTime >= data->m_tmAddrData)
			{
				data->m_usLAC = pGt02Data->m_stHeader.m_usLAC;
				data->m_usVno= pGt02Data->m_stHeader.m_usVno;
				data->m_tmAddrData= gt02time.m_iTime;

				data->m_uiLatitude = pGt02Data->m_unContent.m_st0x1b.m_uiLatitude;
				data->m_uiLongitue = pGt02Data->m_unContent.m_st0x1b.m_uiLongitude;
				data->m_ubMNC = pGt02Data->m_unContent.m_st0x1b.m_ubMNC;
				data->m_ubSpeed = pGt02Data->m_unContent.m_st0x1b.m_ubSpeed;
				data->m_uiStatus = pGt02Data->m_unContent.m_st0x1b.m_uiStatus;
				data->m_usCellID = pGt02Data->m_unContent.m_st0x1b.m_usCellID;
				data->m_usDirection = pGt02Data->m_unContent.m_st0x1b.m_usDitection;

				MyUtility::CBaseEncode::Bcd2ToAscii((const char *)pGt02Data->m_unContent.m_st0x1b.m_szTele,21,1,(char *)data->m_ubMobile);

				if(pGt02Data->m_unContent.m_st0x1b.m_ubLang == 0x02)
					data->m_ubMobile[0] |= 0x80;//英文置1

				data->m_tmTerm = data->m_tmAddrData;

				data->m_tmSvr = time(NULL);
			}
			
		}break;
	default:
		return -2;// not support cmd
		break;
	}

	// 写入PDD
	CPDDGt02 *pobjCPDDGt02 = CPDDGt02Mgr::GetInstance()->GetPDD(tmTerm);

	if(pobjCPDDGt02 == NULL) 
		return -3; //  获取失败
	
	if(0 != pobjCPDDGt02->AppendData(data))
		return -4; // 写入失败
	
	
	return 0;
}

void CLDDGt02::LoadChange()
{
	// 遍历 ,建立IMEI到did的映射 : 此空间永远不会释放，因为是当作hash使用的
	for(int i=m_uiLastLoaded;i<objCLineSpaceMgr.GetSize();i++)
	{
		StLastDeviceData *pStLastDeviceData = (StLastDeviceData*) objCLineSpaceMgr.AsVoid(CPointer(1,i));

		if(pStLastDeviceData == NULL)
			return ;

		m_mIMEI2DID[pStLastDeviceData->m_ullIMEI] = pStLastDeviceData->m_uiDid;
	}

}
void CLDDGt02::DumpInfo(std::ostream & os)
{
	objCLineSpaceMgr.DumpInfo(os);

	LoadChange();

	os << "reged device number is :" << m_mIMEI2DID.size() << std::endl;

	std::map<uint64_t,uint32_t>::const_iterator iter;

	for(iter=m_mIMEI2DID.begin();iter!=m_mIMEI2DID.end();iter++)
	{
		static int i =0;

		os << i++ << " : imei  " << iter->first << " ,did " << iter->second << std::endl;

		if (i>= 10) break;
	}
}

int CLDDGt02::Init(int inDeviceNumber/*=10000*/,int inSplitPara_FromNumber /*= 0*/,const char * inName/*="LDD_GT02"*/)
{
	if(m_bInit) return 0;

	int iRet = objCLineSpaceMgr.Init(sizeof(StLastDeviceData),inDeviceNumber,inName,true);	

	if(iRet != OK)
	{
		return iRet;
	}

	m_uiFromDid = inSplitPara_FromNumber;

	m_mIMEI2DID.clear();

	m_uiLastLoaded = 0;
	
	// 遍历 ,建立IMEI到did的映射 : 此空间永远不会释放，因为是当作hash使用的
	for(int i=m_uiLastLoaded;i<objCLineSpaceMgr.GetSize();i++)
	{
		StLastDeviceData *pStLastDeviceData = (StLastDeviceData*) objCLineSpaceMgr.AsVoid(CPointer(1,i));

		if(pStLastDeviceData == NULL)
			return SPACE_MANAGER_FILO_NOT_INIT;

		m_mIMEI2DID[pStLastDeviceData->m_ullIMEI] = pStLastDeviceData->m_uiDid;

		m_uiLastLoaded = i;
	}

	// 初始化PDD
	CPDDGt02Mgr::GetInstance()->GetPDD();


	m_bInit = true;

	return 0;
}



