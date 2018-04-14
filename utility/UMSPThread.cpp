// UMSPThread.cpp: implementation of the CUMSPThread class.
//
//////////////////////////////////////////////////////////////////////

#include "UMSPThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
pthread_mutex_t m_hMutexMap[20];


bool CUMSPThread:: bInit = false;


bool CUMSPThread::IsRunning()
{
	return false;
}

CUMSPThread::CUMSPThread()
{
    	if(bInit)
        	return;
        
        for(int i = 0 ;i < MAX_MUTEX ; i++)
        {
		pthread_mutex_init(&m_hMutexMap[i], NULL);
	}
	
	bInit = true;
}

CUMSPThread::~CUMSPThread()
{
	//pthread_mutex_destroy(&m_hMutexMap);
}


void * CUMSPThread::WorkThread(void *inData)
{
	CUMSPThread * pUmspThread = (CUMSPThread *) inData;
	pUmspThread->Run();
}

void CUMSPThread::StartWork()
{
	THREAD_ATTR attr;
	attr.mask = CONTENTION_SCOPE|DETACH_STATE;
	attr.contention_scope = PTHREAD_SCOPE_SYSTEM;
	attr.detach_state = PTHREAD_CREATE_DETACHED;
	
	SetAttr(&attr);

	Create(CUMSPThread::WorkThread ,(void *) this);

}

int CUMSPThread::Lock(int i)
{
	return  pthread_mutex_lock(&m_hMutexMap[i]);
//    switch (i)
//    {
//    case 0:
//    	return pthread_mutex_lock(&m_hMutexMap);break;
//    case 1:
//    	return pthread_mutex_lock(&m_hMutexMap1);break;
//    case 2:
//    	return pthread_mutex_lock(&m_hMutexMap2);break;
//    case 3:
//        return pthread_mutex_lock(&m_hMutexMap3);break;
//    }
}

int CUMSPThread::UnLock(int i)
{
	return  pthread_mutex_unlock(&m_hMutexMap[i]);
//    switch (i)
//    {
//    case 0:
//    	return pthread_mutex_unlock(&m_hMutexMap);break;
//    case 1:
//    	return pthread_mutex_unlock(&m_hMutexMap1);break;
//    case 2:
//    	return pthread_mutex_unlock(&m_hMutexMap2);break;
//    case 3:
//        return pthread_mutex_unlock(&m_hMutexMap3);break;
//    }	
}
