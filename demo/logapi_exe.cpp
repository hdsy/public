#include "CMyLogApi.h"


//using namespace log4cxx;

//log4cxx::LoggerPtr logger = log4cxx::Logger::getRootLogger();

int main(int argc, char **argv)
{

	LOG_INIT(argv[1],argv[2],argv[3]);

	LOG_DEBUG("%s,%d","debug test err",11);

	LOG_INFO("%s,%d","info test inf",11);

	LOG_WARN("%s,%d","warn test err",11);

	LOG_ERROR("%s,%d","error test err",11);

	LOG_FATAL("%s,%d","fatal test err",11);


	LOGER_DEBUG << "loger debug"<<LOG4CXX_ENDMSG;
	LOGER_INFO << "loger info"<<LOG4CXX_ENDMSG;
	LOGER_WARN<< "loger warn"<<LOG4CXX_ENDMSG;

	LOGER_ERROR<< "loger error"<<LOG4CXX_ENDMSG;

	LOGER_FATAL<< "loger fatal"<<LOG4CXX_ENDMSG;



	LOG_EXIT();	


	return 0;
}

