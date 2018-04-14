#include "CCommandLineInfo.h"


#include "CLDDGt02.h"




void InitCommandLine()
{	
	MyUtility::g_objCCommandLineInfo.AddEntry("imei","--imei=","123456789012345",false,false,"device imei which tag device unique");

	MyUtility::g_objCCommandLineInfo.AddEntry("did","--did=","0",false,false,"device id which tag device unique");
	MyUtility::g_objCCommandLineInfo.AddEntry("sock","--sock=","1",false,false,"sock create out body");
	MyUtility::g_objCCommandLineInfo.AddEntry("sockbuf","--sockbuf=","787872176C000000014144445245535326260032003000310030002D00310032002D00330030002000310031003A00340031003A0030003500205E7F4E1C770160E05DDE5E0260E057CE533A4E915C71897F8DEF003653F7262631323532303135303133393831343631003600360023230001ffa80D0A",false,false,"msg content");

	
			
	MyUtility::g_objCCommandLineInfo.AddEntry("cmd","--cmd=","read",false,false,
		"\t\t readbyimei	read device data by imei and dump out  \r\n"
		"\t\t readbydid		read device data by did and dump out  \r\n"
		"\t\t reg	register device for future use  \r\n"
		"\t\t dump	dumpinfo  \r\n"
		"\t\t sockttest	  \r\n"
		);
}

void Dump()
{
	CLDDGt02 objCLDDGt02;

	if (0 != objCLDDGt02.Init())
	{
		std::cout << "open ldd memory faild\r\n";
	}

	objCLDDGt02.DumpInfo(std::cout);
}

void SockTest()
{
	int sock = atoi(MyUtility::g_objCCommandLineInfo.GetArgVal("sock").c_str());

	std::string sockbuf = MyUtility::CBaseEncode::HexStrToCharStr(MyUtility::g_objCCommandLineInfo.GetArgVal("sockbuf"));
	
	std::cout << "send data :" << write(sock,sockbuf.data(),sockbuf.size()) << std::endl;
}

void ReadByDid()
{
	CLDDGt02 objCLDDGt02;

	if (0 != objCLDDGt02.Init())
	{
		std::cout << "open ldd memory faild\r\n";
	}

	for(int i=0;i < MyUtility::g_objCCommandLineInfo.GetArgSize("did") ;i++)
	{		
		uint32_t did  = MyUtility::CBaseEncode::StringToUInt(MyUtility::g_objCCommandLineInfo.GetArgVal("did",i));
		
		StLastDeviceData *pStLastDeviceData =NULL;
		
		if (0 == objCLDDGt02.GetByDID(did,pStLastDeviceData))
		{
			std::cout << "dump memory by did " << did << std::endl;

			pStLastDeviceData->DumpInfo(std::cout);
			
		}
		else
		{
			std::cout << "\r\n#****did not exist***" << did << std::endl;
		}
	}

	
}

void ReadByImei()
{
	CLDDGt02 objCLDDGt02;

	if (0 != objCLDDGt02.Init())
	{
		std::cout << "open ldd memory faild\r\n";
	}

	for(int i=0;i < MyUtility::g_objCCommandLineInfo.GetArgSize("imei") ;i++)
	{
		uint64_t imei=0 ;

		MyUtility::CBaseEncode::Bcd2ToAscii(MyUtility::g_objCCommandLineInfo.GetArgVal("imei",i).c_str(),MyUtility::g_objCCommandLineInfo.GetArgVal("imei").size(),1,(char *)&imei);

		std::cout << "imei in memory : " << MyUtility::CBaseEncode::Hex(imei) << std::endl;

	
		StLastDeviceData *pStLastDeviceData =NULL;
		
	
		if (0 == objCLDDGt02.GetByImei(imei,pStLastDeviceData))
		{
			std::cout << "dump memory by imei " << MyUtility::CBaseEncode::Hex(imei) << std::endl;

			pStLastDeviceData->DumpInfo(std::cout);
		}
		else
		{
			std::cout << "\r\n#****imei not exist***" << MyUtility::CBaseEncode::Hex(imei) << std::endl;
		}
	}

	
}

void Reg()
{
	CLDDGt02 objCLDDGt02;

	if (0 != objCLDDGt02.Init())
	{
		std::cout << "open ldd memory faild\r\n";
	}
	uint64_t imei =0;

	MyUtility::CBaseEncode::Bcd2ToAscii(MyUtility::g_objCCommandLineInfo.GetArgVal("imei").c_str(),MyUtility::g_objCCommandLineInfo.GetArgVal("imei").size(),1,(char *)&imei);

	std::cout << "imei in memory : " << MyUtility::CBaseEncode::Hex(imei) << std::endl;
	
	StLastDeviceData *pStLastDeviceData =NULL;
	
	if (0 == objCLDDGt02.Register(imei,pStLastDeviceData))
	{
		std::cout << "dump memory by imei " << imei << std::endl;

		pStLastDeviceData->DumpInfo(std::cout);
		
	}
	else
	{
		objCLDDGt02.DumpInfo(std::cout);
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
	else if(MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") == "reg")
	{
		Reg();
	}
	else if(MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") == "dump")
	{
		Dump();
	}
	else  if(MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") == "socktest")
	{
		SockTest();
	}
	else 
	{
		std::cout << "Not support cmd : " << MyUtility::g_objCCommandLineInfo.GetArgVal("cmd") << std::endl;
		
	}
	return 0;


  
}


