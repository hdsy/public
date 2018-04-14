#include "HttpClient.h"


#include <iostream>

using namespace std;

const char *pszFile = "./test.xml";
const char *pszSerid = "LOGIN";
const char *pszInParas = "a=b&c=d";

int main(int argc,char ** argv)
{

	const char *filepath,* service;

	if(argc == 3)
	{
		filepath = argv[1];
		service = argv[2];
	}
	else
	{
		filepath=pszFile;
		service = pszSerid;
	}
	
	
	
	CStringMap sm;
	sm.Split(pszInParas);
	
	{
		CHttpClient http;

		http.LoadConfig(filepath,service);

		http.LoadInput(sm);

		http.LoadSession();

		http.SendAndRecv();

		http.StoreSession();	
		
		string invokeRes;

		if((( http.m_sRetCode == string("302")  ) ||( http.m_sRetCode == string("200")  )) &&
			(http.m_iStatus == 0))
		{
			invokeRes = http.m_sResBody;
			cout << invokeRes << endl;
		}
		else
		{
			cout << "error" << endl;
		}
	
	}
	return 1;
}
