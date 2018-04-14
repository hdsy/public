// UMSPThread.h: interface for the CUMSPThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPTHREAD_H__A2C7F587_4D2B_45C5_B0C4_7BD0BA94D853__INCLUDED_)
#define AFX_UMSPTHREAD_H__A2C7F587_4D2B_45C5_B0C4_7BD0BA94D853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UnixThread.h"

#define MAX_MUTEX 20

extern	pthread_mutex_t m_hMutexMap[MAX_MUTEX];

enum _THREAD_STATE
{
	THREAD_IDLE,
	THREAD_STOP,
	THREAD_START,
	THREAD_RUN,
};

class CUMSPThread : public CUnixThread  
{
public:
	int UnLock(int i=0);
	int Lock(int i=0);
	void StartWork();
	CUMSPThread();
	virtual ~CUMSPThread();
	
	int m_iState;
	
	virtual bool IsRunning();

protected:
    static bool bInit;
	static void * WorkThread(void * inData);
	virtual void Run()=0;
};

#endif // !defined(AFX_UMSPTHREAD_H__A2C7F587_4D2B_45C5_B0C4_7BD0BA94D853__INCLUDED_)
