#include "CLineSpaceMgr.h"

#include "CCommandLineInfo.h"
#include "CBaseEncode.h"

#include <string>
#include <iostream>

CLineSpaceMgr g_objCLineSpaceMgr;

MyUtility::CCommandLineInfo & ci = MyUtility::g_objCCommandLineInfo;


void InitCmdLine()
{	
	
	ci.AddEntry("type","--type=","mmap",false,false,"mmap|shmget  pointed diffrence way ");
	
	ci.AddEntry("object_size","--objsize=","1023",false,false,"Bytes per Object ");

	ci.AddEntry("max_object_count","--maxcount=","1024000",false,false,"max object count");
	
	ci.AddEntry("shmname","--shmname=","12345678",false,false,"Line Space Name ,should be unique per exec ");
	
	ci.AddEntry("value","--value=","abcd1234",false,false,"Content for write into memory ");

	ci.AddEntry("offset","--offset=","0",false,false,"offset used to gen CPointer ");
	
	ci.AddEntry("times","--times=","2",false,false,"alloc test times");

	//ci.AddEntry("data","--data=","this is only a test",false,false,"data, add to uin buffer");
	
	ci.AddEntry("cmd","--cmd=","open",false,false,
		"\r\n\t\t open: open an exist or create a new  memory and dump meminfo\r\n"
		"\t\t alloc: alloc single block and write value to buffer \r\n"
		"\t\t alloc2: alloc times block and write value to buffer with address printed \r\n"
		"\t\t free: free single block  \r\n"
		"\t\t read: read single block and print it's value  \r\n"
		"\t\t alloc_test: alloc until failed,then sleep 1 sec, retest  \r\n"
		"\t\t free_test: free until failed,then exit  \r\n"
		);
}

void Usage()
{
	std::cout << ci.GetPrompt() << std::endl;

	exit(0);
}
size_t szObjSize;
size_t szObjMaxCount;
const char * pszName;
bool ismmap = true;

void Dump()
{
	g_objCLineSpaceMgr.DumpInfo(std::cout);
}

void Open()
{
	int iRet = g_objCLineSpaceMgr.Init(szObjSize,szObjMaxCount,pszName,ismmap);

	

	if(iRet == OK)
	{
		std::cout << "Open Ok. " << std::endl;
		
	}
	else
	{
		std::cout << "Trace .... \r\n" << iRet << ":" << g_objCLineSpaceMgr.GetTraceLog();
		exit(0);
	}
}

int main(int argc,const char ** argv)
{
	 InitCmdLine();
	 	
	if(argc == 1)
	{
		Usage();
	}
	
	ci.Parse(argc,argv);

	szObjSize = MyUtility::CBaseEncode::StringToUInt(ci.GetArgVal("object_size"));
	szObjMaxCount = MyUtility::CBaseEncode::StringToUInt(ci.GetArgVal("max_object_count"));
	pszName = ci.GetArgVal("shmname").c_str();



	if (ci.GetArgVal("type") == "shmget") ismmap=false;
	
	if(ci.GetArgVal("cmd")  ==  "open")
	{
		Open();
		Dump();
	}
	else if(ci.GetArgVal("cmd")  ==  "alloc")
	{
		Open();
		
		CPointer objCPointer = g_objCLineSpaceMgr.Alloc();

		if(objCPointer.IsNull())
		{
			std::cout << "Not Enough Space " << std::endl;
		}
		else
		{
			char * pBuffer= (char *)g_objCLineSpaceMgr.AsVoid(objCPointer);

			if(pBuffer == NULL)
				std::cout << "Failed in AsVoid CPointer:" << objCPointer.m_uiBlock << "," << objCPointer.m_uiOffset << std::endl;
			else
			{
				std::cout << "Alloc CPointer:" << objCPointer.m_uiBlock << "," << objCPointer.m_uiOffset << " and set value ..." << std::endl;
				strncpy(pBuffer,ci.GetArgVal("value").c_str(),szObjSize);

				printf("poinrter is : %p",pBuffer);
			}
		}
	}
	else if(ci.GetArgVal("cmd")  ==  "alloc2")
	{
		Open();

		for(int i=0;i<atoi(ci.GetArgVal("times").c_str());i++)
		{
			
			CPointer objCPointer = g_objCLineSpaceMgr.Alloc();

			if(objCPointer.IsNull())
			{
				std::cout << "Not Enough Space " << std::endl;
			}
			else
			{
				char * pBuffer= (char *)g_objCLineSpaceMgr.AsVoid(objCPointer);

				if(pBuffer == NULL)
					std::cout << "Failed in AsVoid CPointer:" << objCPointer.m_uiBlock << "," << objCPointer.m_uiOffset << std::endl;
				else
				{
					std::cout << "Alloc CPointer:" << objCPointer.m_uiBlock << "," << objCPointer.m_uiOffset << " and set value ..." << std::endl;
					strncpy(pBuffer,ci.GetArgVal("value").c_str(),szObjSize);

					printf("poinrter is : %p\r\n",pBuffer);
				}
			}
		}
	}
	else if(ci.GetArgVal("cmd")  ==  "free")
	{
		Open();
		
		CPointer objCPointer (1,MyUtility::CBaseEncode::StringToUInt(ci.GetArgVal("offset")));


		int retcd = 0;

		retcd = g_objCLineSpaceMgr.Free(objCPointer);

		if(retcd == 0 )
		{
			std::cout << "Free CPointer(1," << ci.GetArgVal("offset") << ") OK" << std::endl;
		}
		else
		{
			std::cout << "Free CPointer(1," << ci.GetArgVal("offset") << ") ERR"  << retcd << std::endl;
		}
	}	
	else if(ci.GetArgVal("cmd")  ==  "read")
	{
		Open();
		
		CPointer objCPointer (1,MyUtility::CBaseEncode::StringToUInt(ci.GetArgVal("offset")));


		char * pBuffer= (char *)g_objCLineSpaceMgr.AsVoid(objCPointer);

		if(pBuffer == NULL)
				std::cout << "Failed in AsVoid CPointer(" << objCPointer.m_uiBlock << "," << objCPointer.m_uiOffset<< ")" << std::endl;
			else
				std::cout << "Value in  CPointer(" << objCPointer.m_uiBlock << "," << objCPointer.m_uiOffset<< ") is : "  <<  pBuffer << std::endl;
	}
	else if(ci.GetArgVal("cmd")  ==  "alloc_test")
	{
		Open();
		
		
		int i=0,j=0;

		while(1)			
		{

			CPointer objCPointer = g_objCLineSpaceMgr.Alloc();
		
			if(objCPointer.IsNull())
			{
				std::cout << "Not Enough Space " << std::endl;
				sleep(1);
				j++;
			}
			else
			{
				char * pBuffer= (char *)g_objCLineSpaceMgr.AsVoid(objCPointer);

				if(pBuffer == NULL)
					std::cout << "Failed in AsVoid CPointer:" << objCPointer.m_uiBlock << "," << objCPointer.m_uiOffset << std::endl;
				else
					snprintf(pBuffer,szObjSize,"%s:%d:%d",ci.GetArgVal("value").c_str(),i++,j);
			}
		}
	}	
	else if(ci.GetArgVal("cmd")  ==  "free_test")
	{
		Open();
		
			int i=0,j=0;	
		while(1)			
		{		
		
			CPointer objCPointer (1,i++);


			int retcd = 0;

			retcd = g_objCLineSpaceMgr.Free(objCPointer);

			if(retcd == 0 )
			{
				std::cout << "Free CPointer(1," << i << ") OK" << std::endl;
			}
			else
			{
				std::cout << "Free CPointer(1," << i << ") ERR"  << retcd << std::endl;

				sleep(1);
				//j++; i=0;
				
			}
		}
	}
	else
	{
		std::cout << "Not support cmd : "  << ci.GetArgVal("cmd") << std::endl;
	}
	
	return 0;
}

