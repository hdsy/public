#ifndef CLOG_H
#define CLOG_H

#include <string>
#include <stdarg.h>
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
//#include "log4cxx/fileappender.h"
#include <log4cxx/rollingfileappender.h>
#include "log4cxx/patternlayout.h"
#include "log4cxx/logmanager.h"


extern log4cxx::LoggerPtr g_LoggerPtr;

#define LOG_SET_OPTION(option,value) 	CLog::setOption(g_LoggerPtr,option,value)
#define LOG_INIT(cfg,mod,lev) 		CLog::Init(cfg,mod,lev)

#define LOG_DEBUG(fmt,...) 	CLog::LogDebug(g_LoggerPtr,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define LOG_INFO(fmt,...) 	CLog::LogInfo  (g_LoggerPtr,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define LOG_WARN(fmt,...) 	CLog::LogWarn	 (g_LoggerPtr,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define LOG_ERROR(fmt,...) 	CLog::LogError(g_LoggerPtr,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define LOG_FATAL(fmt,...) 	CLog::LogFatal(g_LoggerPtr,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define LOG_EXIT()		log4cxx::LogManager::shutdown(); 


class CLog
{
public:
    enum ELOG_LEVEL
    {
        EDEBUG  = 0,
        EINFO   = 1,
        EWARN   = 2,
        EERROR  = 3,
        EFATAL  = 4
    };

public:
    CLog();
    virtual ~CLog();
    static void Init(std::string &cfg,std::string &mod,ELOG_LEVEL lev = EINFO);
    static void Init(const char *cfg,const char *mod,ELOG_LEVEL lev = EINFO);

    static void setOption(log4cxx::LoggerPtr &logger,const char *option,const char *value);
    static void setOption(log4cxx::LoggerPtr &logger,std::string &option,std::string &value);

    static void LogDebug(log4cxx::LoggerPtr &logger,const char* pFile,const char *pFunc,int line,const char* pInfo,...);
    static void LogInfo(log4cxx::LoggerPtr &logger,const char* pFile,const char *pFunc,int line,const char* pInfo,...);
    static void LogWarn(log4cxx::LoggerPtr &logger,const char* pFile,const char *pFunc,int line,const char* pInfo,...);
    static void LogError(log4cxx::LoggerPtr &logger,const char* pFile,const char *pFunc,int line,const char* pInfo,...);
    static void LogFatal(log4cxx::LoggerPtr &logger,const char* pFile,const char *pFunc,int line,const char* pInfo,...);

private:
    static int setFileOption(log4cxx::LoggerPtr &logger,int type,std::string &value,int num = 0);
    static void setLevel(log4cxx::LoggerPtr &logger,ELOG_LEVEL lev);
    static void getProcessName(std::string &str);
};

#endif // CLOG_H

