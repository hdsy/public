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
	int m_iID;

	bool m_bLocked;

public:
	CUnixFileLock(const char * szFilename = "./.CUnixFlock")
	{
		m_iID = -1;m_bLocked =false;

		m_iID = open( szFilename, O_CREAT|O_RDWR /*| O_TRUNC*/);

		GetLock();
	};

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

				unsigned int pid =  getpid();

				write(m_iID,(const void*)&pid,sizeof(pid));

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
