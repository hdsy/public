#ifndef _UPGW_CUnixFlock_H_
#define _UPGW_CUnixFlock_H_


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


class CUnixFileLock
{
private:
	int m_iID; // 文件ID

	bool m_bLocked; // 是否锁住

	unsigned int m_iPid; // 锁住的进程号

public:
	CUnixFileLock(const char * szFilename = "./.CUnixFlock")
	{
		m_iID = -1;m_bLocked =false;m_iPid=0;

		m_iID = open( szFilename, O_CREAT|O_RDWR /*| O_TRUNC*/);

		GetLock();
	};

	unsigned int GetWorkingProcessID()
	{
		if (m_iPid != 0 ) return m_iPid;

		if (m_iID != -1 )
		{
			read(m_iID,&m_iPid,sizeof(m_iPid));
		}
		return m_iPid;
	}

	bool GetLock()
	{
		if (m_bLocked)  return m_bLocked; 

		if (m_iID != -1 )
		{
			if( -1 == flock( m_iID, LOCK_NB | LOCK_EX))
			{
				m_bLocked = false;
			}
			else
			{
				m_bLocked = true;

				m_iPid =  getpid();

				write(m_iID,(const void*)&m_iPid,sizeof(m_iPid));

			}
		}

		return m_bLocked;
	};

	virtual ~CUnixFileLock()
	{
		close( m_iID);
	};
};

#endif
