#include "CMyExpression.h"
#include "CMyHtml2XmlWorker.h"
#include "CMyDispatcher.h"


#include "CStringVector.h"
#include "CStringVectorMap.h"
#include "CStringMap.h"

#include <iostream>

using namespace std;

const char * m_strSource_def = "a=b&c=d";
const char * m_strFilePath_def = "./test.bpml";

int main(int argc,char ** argv)
{
	CMyDispatcher disp;

	string res;
	
	int i = 0;

	const char * m_strSource, *m_strFilePath;
	
	if(argc == 3 )
	{
		m_strSource = argv[2];
		m_strFilePath = argv[1];
	}
	else if(argc == 2)
	{
		m_strFilePath = argv[1];
		m_strSource = m_strSource_def;
		
	}
	else if(argc == 1)
	{
		m_strSource = m_strSource_def;
		m_strFilePath = m_strFilePath_def;
	}
	else
	{
		cout << argv[0] << " bpml_file  input_paras " << endl;
		return 1;
	}

	string inParas(m_strSource);
	i = disp.StartWork(m_strFilePath,res,inParas);


	cout << i << ":"  << res << endl; 
	return 0;
}
