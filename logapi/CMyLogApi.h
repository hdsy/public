#ifndef CMYLOGAPI_H_20130811
#define CMYLOGAPI_H_20130811

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>



#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <apr_general.h>
#include <apr_time.h>
#include <iostream>
#include <log4cxx/stream.h>
#include <exception>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>


using namespace log4cxx;
using namespace log4cxx::helpers;

// max size per time write to loger
#define LOGER_PER_MAX_SIZE 10240


enum ELOG_LEVEL
{
	EDEBUG	= 0,
	EINFO	= 1,
	EWARN	= 2,
	EERROR	= 3,
	EFATAL	= 4,
	ECONS	= 5,
};


// base on log4cpp on appache org
class CMyLogApi
{

private:

	
	
	static CMyLogApi * m_pCMyLogApi;
	
	void Init(const std::string & inConfigFilePath="../cnf/log.ini",const std::string & inModuleName="",const std::string & inInterfaceName="")
	{
		if(inConfigFilePath.length() > 4 && inConfigFilePath.substr(inConfigFilePath.length() - 4) == ".xml")
		{
#if APR_HAS_THREADS               
			xml::DOMConfigurator::configureAndWatch(inConfigFilePath, 3000);
#else               
			xml::DOMConfigurator::configure(inConfigFilePath);
#endif                
		}				 
		else				
		{
#if APR_HAS_THREADS                        
			PropertyConfigurator::configureAndWatch(inConfigFilePath, 3000);
#else                        
			PropertyConfigurator::configure(inConfigFilePath);
#endif                
		}

		m_sModuleName = inModuleName;

		m_sInterfaceName = inInterfaceName;

		m_pidProcessID = getpid();

		m_LoggerPtrROOT = Logger::getRootLogger();
		m_plogstreamROOT = new logstream(m_LoggerPtrROOT,Level::getDebug());
			
		m_LoggerPtrDEBUG = Logger::getLogger("DEBUG");
		m_plogstreamDEBUG = new logstream(m_LoggerPtrDEBUG,Level::getDebug());
		
		m_LoggerPtrINFO = Logger::getLogger("INFO");
		m_plogstreamINFO = new logstream(m_LoggerPtrINFO,Level::getDebug());
		
		m_LoggerPtrWARN = Logger::getLogger("WARN");
		m_plogstreamWARN = new logstream(m_LoggerPtrWARN,Level::getDebug());
		
		m_LoggerPtrERROR = Logger::getLogger("ERROR");
		m_plogstreamERROR = new logstream(m_LoggerPtrERROR,Level::getDebug());
		
		m_LoggerPtrFATAL = Logger::getLogger("FATAL");
		m_plogstreamFATAL = new logstream(m_LoggerPtrFATAL,Level::getDebug());


		
		
	};

	
	CMyLogApi(){};

	


	char m_szBuffer[LOGER_PER_MAX_SIZE];
	
	LoggerPtr m_LoggerPtrROOT;	logstream *m_plogstreamROOT;
	LoggerPtr m_LoggerPtrDEBUG; logstream *m_plogstreamDEBUG;
	LoggerPtr m_LoggerPtrINFO;	logstream *m_plogstreamINFO;
	LoggerPtr m_LoggerPtrWARN;	logstream *m_plogstreamWARN;
	LoggerPtr m_LoggerPtrERROR; logstream *m_plogstreamERROR;
	LoggerPtr m_LoggerPtrFATAL; logstream *m_plogstreamFATAL;

public:
	
	
	std::string m_sModuleName;
	std::string m_sInterfaceName;
	pid_t m_pidProcessID;

	logstream & GetLoger(int inLevel)
	{
		switch(inLevel)
		{
		case EDEBUG: return *m_plogstreamDEBUG; break;
		case EINFO: return *m_plogstreamINFO; break;
		case EWARN: return *m_plogstreamWARN; break;
		case EERROR: return *m_plogstreamERROR; break;
		case EFATAL: return *m_plogstreamFATAL; break;
		}
	}

	// level datetime modulename interfacename filename line functionname  pid tid msg \r\n 
	void Log(int inLevel,const char * inFilename,int inLine,const char * inFunctionname,const char * inMsgFmt,...)
	{		
		pid_t tid = syscall(SYS_gettid);

		int iTmp=0;
		
		iTmp = snprintf(m_szBuffer,sizeof(m_szBuffer),"%s %s %s:%d %s [%d:%d] ",
			m_sModuleName.c_str(),
			m_sInterfaceName.c_str(),
			inFilename,inLine,
			inFunctionname,
			m_pidProcessID,tid,
			inMsgFmt);

		va_list va;
			va_start(va, inMsgFmt);
			iTmp += vsnprintf(m_szBuffer+iTmp, sizeof(m_szBuffer)-iTmp, inMsgFmt, va);
		va_end(va);

		m_szBuffer[iTmp] =0;

		switch(inLevel)
		{
		case EDEBUG:
			LOG4CXX_DEBUG(m_LoggerPtrDEBUG,m_szBuffer); break;
		
		case EINFO:
			LOG4CXX_INFO(m_LoggerPtrINFO,m_szBuffer); break;
		
		case EERROR:
			LOG4CXX_ERROR(m_LoggerPtrERROR,m_szBuffer); break;
		
		case EWARN:
			LOG4CXX_WARN(m_LoggerPtrWARN,m_szBuffer); break;
		
		case EFATAL:
			LOG4CXX_FATAL(m_LoggerPtrFATAL,m_szBuffer); break;

		case ECONS:
			fprintf(stdout,"\r\n%d %s\r\n",time(NULL),m_szBuffer);
			break;
		}
	}

	static CMyLogApi *GetInstance(const  std::string & inConfigFilePath="../cnf/log.ini",
		const std::string & inModuleName="",const std::string & inInterfaceName="")
	{
		if(NULL == m_pCMyLogApi)
		{
			m_pCMyLogApi = new CMyLogApi;

			if(NULL != m_pCMyLogApi)
			{
				apr_initialize();

				m_pCMyLogApi->Init(inConfigFilePath,inModuleName,inInterfaceName);
			}
			else
			{
				std::cout << __FILE__ << " " << __LINE__ << "Error in initting logger ... " << std::endl;
				exit(-1);
			}
		}
		
		return m_pCMyLogApi;
	}

	static void ExitInstance()
	{
		if(NULL != m_pCMyLogApi)
		{
			

			if(m_pCMyLogApi->m_plogstreamDEBUG != NULL) delete m_pCMyLogApi->m_plogstreamDEBUG;
			if(m_pCMyLogApi->m_plogstreamERROR != NULL) delete m_pCMyLogApi->m_plogstreamERROR;
			if(m_pCMyLogApi->m_plogstreamFATAL != NULL) delete m_pCMyLogApi->m_plogstreamFATAL;
			if(m_pCMyLogApi->m_plogstreamINFO  != NULL) delete m_pCMyLogApi->m_plogstreamINFO;
			if(m_pCMyLogApi->m_plogstreamROOT  != NULL) delete m_pCMyLogApi->m_plogstreamROOT;
			if(m_pCMyLogApi->m_plogstreamWARN  != NULL) delete m_pCMyLogApi->m_plogstreamWARN;

			
			delete m_pCMyLogApi;
		
			apr_terminate();
		}
	};
	

};


//the macro defined here 
// before used logger, you should call CMyLogApi::GetInstacne(argc,argv,config,module,interface) first
#define LOG_INIT(config_file_path,module_name,interface_name) CMyLogApi::GetInstance(config_file_path,module_name,interface_name);
#define LOG_SET_INTFACE(interface_name) {CMyLogApi::GetInstance()->m_sInterfaceName=interface_name;}
#define LOG_SET_MODULE(module_name) {CMyLogApi::GetInstance()->m_sModuleName=interface_name;}


// c function call
#define LOG_STD(fmt,...)	CMyLogApi::GetInstance()->Log(ECONS,__FILE__,__LINE__,__FUNCTION__,fmt,##__VA_ARGS__);
#define LOG_DEBUG(fmt,...) 	CMyLogApi::GetInstance()->Log(EDEBUG,__FILE__,__LINE__,__FUNCTION__,fmt,##__VA_ARGS__);
#define LOG_INFO(fmt,...) 	CMyLogApi::GetInstance()->Log(EINFO,__FILE__,__LINE__,__FUNCTION__,fmt,##__VA_ARGS__);
#define LOG_WARN(fmt,...) 	CMyLogApi::GetInstance()->Log(EWARN,__FILE__,__LINE__,__FUNCTION__,fmt,##__VA_ARGS__);
#define LOG_ERROR(fmt,...) 	CMyLogApi::GetInstance()->Log(EERROR,__FILE__,__LINE__,__FUNCTION__,fmt,##__VA_ARGS__);
#define LOG_FATAL(fmt,...) 	CMyLogApi::GetInstance()->Log(EFATAL,__FILE__,__LINE__,__FUNCTION__,fmt,##__VA_ARGS__);

// c++ stream call
// level datetime modulename interfacename filename line functionname  pid tid msg \r\n 

#define LOGER_STD   std::cout<<CMyLogApi::GetInstance()->m_sModuleName<<" "\
	<<CMyLogApi::GetInstance()->m_sInterfaceName<<" "<<__FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<CMyLogApi::GetInstance()->m_pidProcessID\
	<<syscall(SYS_gettid)<<" " 

#define LOGER_DEBUG CMyLogApi::GetInstance()->GetLoger(EDEBUG)<<Level::getDebug()<<CMyLogApi::GetInstance()->m_sModuleName<<" "\
	<<CMyLogApi::GetInstance()->m_sInterfaceName<<" "<<__FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<CMyLogApi::GetInstance()->m_pidProcessID\
	<<syscall(SYS_gettid)<<" " 
	
#define LOGER_INFO  CMyLogApi::GetInstance()->GetLoger(EINFO)<<Level::getInfo()<<CMyLogApi::GetInstance()->m_sModuleName<<" "\
	<<CMyLogApi::GetInstance()->m_sInterfaceName<<" "<<__FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<CMyLogApi::GetInstance()->m_pidProcessID\
	<<syscall(SYS_gettid)<<" " 
	
#define LOGER_WARN  CMyLogApi::GetInstance()->GetLoger(EWARN)<<Level::getWarn()<<CMyLogApi::GetInstance()->m_sModuleName<<" "\
	<<CMyLogApi::GetInstance()->m_sInterfaceName<<" "<<__FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<CMyLogApi::GetInstance()->m_pidProcessID\
	<<syscall(SYS_gettid)<<" " 
	
#define LOGER_ERROR CMyLogApi::GetInstance()->GetLoger(EERROR)<<Level::getError()<<CMyLogApi::GetInstance()->m_sModuleName<<" "\
	<<CMyLogApi::GetInstance()->m_sInterfaceName<<" "<<__FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<CMyLogApi::GetInstance()->m_pidProcessID\
	<<syscall(SYS_gettid)<<" " 
	
#define LOGER_FATAL CMyLogApi::GetInstance()->GetLoger(EFATAL)<<Level::getFatal()<<CMyLogApi::GetInstance()->m_sModuleName<<" "\
	<<CMyLogApi::GetInstance()->m_sInterfaceName<<" "<<__FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<CMyLogApi::GetInstance()->m_pidProcessID\
	<<syscall(SYS_gettid)<<" " 


#define LOG_EXIT()		CMyLogApi::ExitInstance(); 


#define LOGER_ETAG LOG4CXX_ENDMSG

#define DEBUG_LOGER LOGER_DEBUG
#define ERROR_LOGER LOGER_ERROR
#define INFO_LOGER LOGER_INFO


#endif

