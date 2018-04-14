#include "CCommandLineInfo.h"
#include "CBaseEncode.h"


#include "CPDDGt02.h"

#include "CTime.h"



void InitCommandLine()
{	
	MyUtility::g_objCCommandLineInfo.AddEntry("imei","--imei=","123456789012345",false,false,"device imei which tag device unique");

	MyUtility::g_objCCommandLineInfo.AddEntry("did","--did=","0",false,false,"device id which tag device unique");
	MyUtility::g_objCCommandLineInfo.AddEntry("bid","--bid=","0",false,false,"block id which tag device unique");


	MyUtility::g_objCCommandLineInfo.AddEntry("bdays","--bdays=","0",false,false,"view $bdays data");

	
			
	MyUtility::g_objCCommandLineInfo.AddEntry("cmd","--cmd=","read",false,false,
		"\t\t readbyimei	read device data by imei and dump out  \r\n"
		"\t\t readbydid		read device data by did and dump out  \r\n"
		"\t\t dump	dumpinfo  \r\n"
		);
}

void Dump()
{
	CPDDGt02 objCPDDGt02;

		int bdays = atoi(MyUtility::g_objCCommandLineInfo.GetArgVal("bdays").c_str());
	
	
	MyUtility::CTime tmNow(time(NULL) - bdays * 86400);

	std::string spddName = "PDD_GT02_" + tmNow.Format("yymmdd");

	if (0 != objCPDDGt02.Init(10000,0,spddName.c_str()))
	{
		std::cout << "open pdd memory faild\r\n";
	}

	objCPDDGt02.DumpInfo(std::cout);
}

void ReadByBid()
{
	
	CPDDGt02 objCPDDGt02;

	int bdays = atoi(MyUtility::g_objCCommandLineInfo.GetArgVal("bdays").c_str());
	
	
	MyUtility::CTime tmNow(time(NULL) - bdays * 86400);

	std::string spddName = "PDD_GT02_" + tmNow.Format("yymmdd");

	if (0 != objCPDDGt02.Init(10000,0,spddName.c_str()))
	{
		std::cout << "open pdd memory faild\r\n";
	}
	

	for(int i=0;i < MyUtility::g_objCCommandLineInfo.GetArgSize("bid") ;i++)
	{		
		uint32_t did  = MyUtility::CBaseEncode::StringToUInt(MyUtility::g_objCCommandLineInfo.GetArgVal("bid",i));
		
		StPersistDeviceData *pStPersistDeviceData =NULL;
		
		if (0 == objCPDDGt02.GetByBid(did,pStPersistDeviceData))
		{
			std::cout << "\r\n dump memory by bid " << did << std::endl;

			pStPersistDeviceData->DumpInfo(std::cout);
			
		}
		else
		{
			std::cout << "\r\n#****did not exist***" << did << std::endl;
		}
	}

	
}

void ReadByDid()
{
	
	CPDDGt02 objCPDDGt02;
	
		int bdays = atoi(MyUtility::g_objCCommandLineInfo.GetArgVal("bdays").c_str());
	
	
	MyUtility::CTime tmNow(time(NULL) - bdays * 86400);

	std::string spddName = "PDD_GT02_" + tmNow.Format("yymmdd");

	if (0 != objCPDDGt02.Init(10000,0,spddName.c_str()))
	{
		std::cout << "open pdd memory faild\r\n";
	}
	

	for(int i=0;i < MyUtility::g_objCCommandLineInfo.GetArgSize("did") ;i++)
	{		
		uint32_t did  = MyUtility::CBaseEncode::StringToUInt(MyUtility::g_objCCommandLineInfo.GetArgVal("did",i));
		
		StPersistDeviceData *pStPersistDeviceData =NULL;
		
		if (0 == objCPDDGt02.GetByDid(did,pStPersistDeviceData))
		{
			std::cout << "\r\ndump memory by did " << did << std::endl;

			pStPersistDeviceData->DumpInfo(std::cout);
			
		}
		else
		{
			std::cout << "\r\n#****did not exist***" << did << std::endl;
		}
	}

	
}

void ReadByImei()
{
	
	CPDDGt02 objCPDDGt02;
	
			int bdays = atoi(MyUtility::g_objCCommandLineInfo.GetArgVal("bdays").c_str());
	
	
	MyUtility::CTime tmNow(time(NULL) - bdays * 86400);
	
		std::string spddName = "PDD_GT02_" + tmNow.Format("yymmdd");
	
		if (0 != objCPDDGt02.Init(10000,0,spddName.c_str()))
		{
			std::cout << "open pdd memory faild\r\n";
		}
	

	for(int i=0;i < MyUtility::g_objCCommandLineInfo.GetArgSize("imei") ;i++)
	{
		uint64_t imei=0 ;

		MyUtility::CBaseEncode::Bcd2ToAscii(MyUtility::g_objCCommandLineInfo.GetArgVal("imei",i).c_str(),MyUtility::g_objCCommandLineInfo.GetArgVal("imei").size(),1,(char *)&imei);

		std::cout << "imei in memory : " << MyUtility::CBaseEncode::Hex(imei) << std::endl;

	
		StPersistDeviceData *pStPersistDeviceData =NULL;
		
	
		if (0 == objCPDDGt02.GetByImei(imei,pStPersistDeviceData))
		{
			std::cout << "\r\ndump memory by imei " << MyUtility::CBaseEncode::Hex(imei) << std::endl;

			pStPersistDeviceData->DumpInfo(std::cout);
		}
		else
		{
			std::cout << "\r\n#****imei not exist***" << MyUtility::CBaseEncode::Hex(imei) << std::endl;
		}
	}

	
}



int main(int argc, const char *argv[])
{
	InitCommandLine();

	if(argc == 1)
	{
		std::cout << MyUtility::g_objCCommandLineInfo.GetPrompt();
		return 0;
	}	
	MyUtility::g_objCCommandLineInfo.Parse( argc, argv);

	if(MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") == "readbyimei")
	{
		ReadByImei();
	}
	else if(MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") == "readbydid")
	{
		ReadByDid();
	}
	else if(MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") == "readbybid")
	{
		ReadByBid();
	}
	else if(MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") == "dump")
	{
		Dump();
	}
	else 
	{
		std::cout << "Not support cmd : " << MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") << std::endl;
		
	}
	return 0;


  
}


