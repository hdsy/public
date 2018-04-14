#ifndef _UPGW_CTIME_H_
#define _UPGW_CTIME_H_

#include <time.h>
#include <string>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include <iostream>
using namespace std;


/*
	CTime tm = CTime::GetCurrentTime();
	tm.Format();
*/
namespace MyUtility {
class CTime
{
private:
public:
        time_t m_iTime;
		struct tm m_strutm ;

public:
        int GetInterval()
		{
		        int res;

		        time_t cur;
		        time(&cur);

		        res = cur - m_iTime;

		        return res;
		};
        int Touch()
		{
			time(&m_iTime);
	        localtime_r(&m_iTime,&m_strutm);
			
			return 0;
		};
		unsigned int GetTimeStamp()
		{
			return m_iTime;
		}
		int operator>(const CTime& right)
		{
			
			int res = 0;

				res = (this->m_iTime > right.m_iTime);				

			return res;
		}
		int operator<(const CTime& right)
		{
			
			int res = 0;

				res = (this->m_iTime < right.m_iTime);				

			return res;
		}
		int operator>=(const CTime& right)
		{
			
			int res = 0;

				res = (this->m_iTime >= right.m_iTime);				

			return res;
		}
		int operator==(const CTime& right)
		{
			
			int res = 0;

				res = (this->m_iTime == right.m_iTime);				

			return res;
		}
		int GetHour()
		{
			return  m_strutm.tm_hour;
		}
		
		void SetHour(int nHour)
		{
			m_strutm.tm_hour= nHour;
			m_iTime = mktime(&m_strutm);
		}
		int GetMinute()
		{
			return  m_strutm.tm_min;
		}
		void SetMinute(int nMin)
		{
			m_strutm.tm_min= nMin;
			m_iTime = mktime(&m_strutm);
		}
		int GetSecond()
		{
			return  m_strutm.tm_sec;
		}
		void SetSecond(int nSec)
		{
			m_strutm.tm_sec= nSec;
			m_iTime = mktime(&m_strutm);
		}
	
        string Format(const char * pFormat="yyyy-mm-dd HH:MM:SS" ) const
		{
	        char t_szBuf[256];

	        memset(t_szBuf,0,sizeof(t_szBuf));

	        

	        if (strcasecmp(pFormat,"yyyymmdd") == 0 )
	                snprintf(t_szBuf,sizeof(t_szBuf),"%04d%02d%02d",m_strutm.tm_year+1900,m_strutm.tm_mon+1,
	                        m_strutm.tm_mday);
			else if(strcasecmp(pFormat,"yymmdd") == 0 )
	                snprintf(t_szBuf,sizeof(t_szBuf),"%02d%02d%02d",(m_strutm.tm_year+1900)%100,m_strutm.tm_mon+1,
	                        m_strutm.tm_mday);
	        else if (strcasecmp(pFormat,"yyyy-mm-dd") == 0 )
	                snprintf(t_szBuf,sizeof(t_szBuf),"%04d-%02d-%02d",m_strutm.tm_year+1900,m_strutm.tm_mon+1,
	                        m_strutm.tm_mday);
	        else
	                snprintf(t_szBuf,sizeof(t_szBuf),"%04d-%02d-%02d %02d:%02d:%02d",m_strutm.tm_year+1900,m_strutm.tm_mon+1,
	                        m_strutm.tm_mday,m_strutm.tm_hour,m_strutm.tm_min,m_strutm.tm_sec);


	        return string(t_szBuf);
		};



        static CTime GetCurrentTime()
		{
			time_t tm;
			return CTime(time(&tm));
		};
        CTime()
		{
				time(&m_iTime);
	       			 localtime_r(&m_iTime,&m_strutm);
		};
        CTime(time_t tm)
		{
			m_iTime = tm;
			localtime_r(&m_iTime,&m_strutm);
		};
        CTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec = 0, int nDST = -1)
		{
			//struct tm m_strutm;

		        m_strutm.tm_sec = nSec;
		        m_strutm.tm_min = nMin;
		        m_strutm.tm_hour= nHour;
		        m_strutm.tm_mday= nDay;
		        m_strutm.tm_mon = nMonth-1;
		        m_strutm.tm_year= nYear-1900;
		        m_strutm.tm_isdst= nDST;

		        m_iTime = mktime(&m_strutm);
			
			//localtime_r(&m_iTime,&m_strutm);
		};
	CTime(const string & inYMDhms)
	{
		sscanf(inYMDhms.c_str(), "%d-%d-%d %d:%d:%d" ,
			&(m_strutm.tm_year), &(m_strutm.tm_mon), &(m_strutm.tm_mday),
			&(m_strutm.tm_hour), &(m_strutm.tm_min), &(m_strutm.tm_sec));
		
		m_strutm.tm_year -= 1900;
		m_strutm.tm_mon--;
		m_strutm.tm_isdst = -1;
		m_iTime = mktime(&m_strutm);

	}
        ~CTime(){};

};
}
#endif

