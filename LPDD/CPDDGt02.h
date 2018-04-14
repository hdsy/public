#ifndef CPDDGT02_H_HEADER_INCLUDED_AE00B072
#define CPDDGT02_H_HEADER_INCLUDED_AE00B072
#include "IPersistDeviceData.h"
#include <map>
#include "StLastDeviceData.h"

#include "StPersistDeviceData.h"

#include "CTime.h"

#include "CLineSpaceMgr.h"

#include <string>


//class StLastDeviceData;

//##ModelId=51FF28220088
class CPDDGt02 : public IPersistDeviceData
{
	uint32_t m_uiFromDid;
	std::map<uint64_t,uint32_t> m_mIMEI2BID;
	std::map<uint32_t,uint32_t> m_mDID2BID;
	unsigned int m_uiLastLoaded;
	CLineSpaceMgr objCLineSpaceMgr;
  public:
    // 0 成功，可根据输出的
    // * 失败
    //##ModelId=51FF2CB60240
    virtual int GetByImei(uint64_t inImei, StPersistDeviceData* &data);

    //##ModelId=51FF2CB60260
    virtual int AppendData(const StLastDeviceData *stData);

    //##ModelId=51FF2CB6026F
    virtual int GetByDid(uint32_t inDid, StPersistDeviceData* &data);

	virtual int GetByBid(uint32_t inBid, StPersistDeviceData* &data);

    //##ModelId=51FF2EFB0224
    int Init(int inDevNum = 10000, uint32_t inSplitPara_FromNum = 0, const char *inName = "PDD_GT02");

	void LoadChange();

	void DumpInfo(std::ostream & os);

};

typedef std::map<std::string,CPDDGt02 *> CString2PDDGt02Map;

class CPDDGt02Mgr : public CString2PDDGt02Map
{
	int m_iMaxDays;
	std::string m_sPrefix;
	uint32_t m_iDevNum;
	uint32_t m_uiFromDid;
	
	CPDDGt02Mgr(int inMaxDays = 60,const char * inPrefix="PDD_GT02_",int32_t inDevNum = 10000, uint32_t inSplitPara_FromNum = 0)
	{
		m_iMaxDays = (inMaxDays);
		m_sPrefix = (inPrefix);
		m_iDevNum = (inDevNum);
		m_uiFromDid = (inSplitPara_FromNum);
	}
public:
	static CPDDGt02Mgr * GetInstance()
	{
		static CPDDGt02Mgr * m_pCPDDGt02Mgr = NULL;

		if (m_pCPDDGt02Mgr == NULL)
		{
			m_pCPDDGt02Mgr = new CPDDGt02Mgr();

		}

		return m_pCPDDGt02Mgr;
	};
	void Init(int inMaxDays = 60,const char * inPrefix="PDD_GT02_",int32_t inDevNum = 10000, uint32_t inSplitPara_FromNum = 0)
	{
		m_iMaxDays = (inMaxDays);
		m_sPrefix = (inPrefix);
		m_iDevNum = (inDevNum);
		m_uiFromDid = (inSplitPara_FromNum);
	};

	void Purge()
	{
		//
		MyUtility::CTime tmNow(time(NULL) - m_iMaxDays*86400);

		std::string spddName = m_sPrefix + tmNow.Format("yymmdd");
		
		iterator iter ;

		iter = begin();

		while( iter != end())
		{
			if(iter->first < spddName)
			{
				delete iter->second;
				erase(iter);

				iter = begin();
			}
			else
				break;
		}
	}

	CPDDGt02 * GetPDD(uint32_t tmStamp = 0)
	{		
		if (tmStamp == 0)  tmStamp = time(NULL);

		CPDDGt02 * pobjCPDDGt02 = NULL;

		if(time(NULL) - m_iMaxDays*86400 > tmStamp)
			return pobjCPDDGt02;

		Purge();
		
		MyUtility::CTime tmNow(tmStamp);

		std::string spddName = m_sPrefix + tmNow.Format("yymmdd");

		iterator iter =  find(spddName);
		if (iter == end())
		{
			pobjCPDDGt02 =  new CPDDGt02;

			if (pobjCPDDGt02 != NULL   &&  0 == pobjCPDDGt02->Init(m_iDevNum,m_uiFromDid,spddName.c_str()))
			{
				insert(value_type(spddName,pobjCPDDGt02));
			}
		}
		else
		{
			pobjCPDDGt02 = iter->second;
		}
		
		return pobjCPDDGt02;

	 
	};
	
};



#endif /* CPDDGT02_H_HEADER_INCLUDED_AE00B072 */
