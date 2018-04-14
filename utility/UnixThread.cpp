// UnixThread.cpp: implementation of the CUnixThread class.
//
//////////////////////////////////////////////////////////////////////

#include "UnixThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUnixThread::CUnixThread()
{
	m_hThread = 0;
	InitAttr();
}

CUnixThread::~CUnixThread()
{
	DeleteAttr();
}

int CUnixThread::Create(void *(*atart_func)(void *),void *arg)
{
	return pthread_create(&m_hThread,&m_hAttr,atart_func,arg);
}

void CUnixThread::Exit(void *status)
{
	pthread_exit(status);
}

int CUnixThread::Join(void **status)
{
	return pthread_join(m_hThread,status);
}
/*
return:		EINVAL(22)	thread already detached
			ESRCH(3)	thread not exist
*/
int CUnixThread::Detach()
{
	return pthread_detach(m_hThread);
}

int CUnixThread::InitAttr()
{
	return pthread_attr_init(&m_hAttr);
}

int CUnixThread::SetSchedParam(int policy, const struct sched_param *param)
{
	return pthread_setschedparam(m_hThread,policy,param);
}

int CUnixThread::SetAttr(THREAD_ATTR *pThdAttr)
{
	int ret=0;
	unsigned char mask;
	mask &= 0x00;

	if(pThdAttr->mask & CONTENTION_SCOPE)
		ret = pthread_attr_setscope(&m_hAttr,pThdAttr->contention_scope);
	if (ret == 0)
		mask |= CONTENTION_SCOPE;
	if(pThdAttr->mask & DETACH_STATE)
		ret = pthread_attr_setdetachstate(&m_hAttr,pThdAttr->detach_state);
	if (ret == 0)
		mask |= DETACH_STATE;
//	if(pThdAttr->mask & STACK_ADDR)
//		ret = pthread_attr_setstackaddr(&m_hAttr,pThdAttr->stack_addr);
//	if (ret == 0)
//		mask |= STACK_ADDR;

	if(pThdAttr->mask & STACK_SIZE)
		ret = pthread_attr_setstacksize(&m_hAttr,pThdAttr->stack_size);
	if (ret == 0)
		mask |= STACK_SIZE;

	if(pThdAttr->mask & SCHED_PARAM)
		ret = pthread_attr_setschedparam(&m_hAttr,pThdAttr->param);
	if (ret == 0)
		mask |= SCHED_PARAM;

	if(pThdAttr->mask & SCHED_POLICY)
		ret = pthread_attr_setschedpolicy(&m_hAttr,pThdAttr->policy);
	if (ret == 0)
		mask |= SCHED_POLICY;

	if(pThdAttr->mask & INHERITSCHED)
	ret = pthread_attr_setinheritsched(&m_hAttr,pThdAttr->inheritsched);
	if (ret == 0)
		mask |= INHERITSCHED;

	pThdAttr->mask = mask;
end:
	return ret;

}

int CUnixThread::GetAttr(THREAD_ATTR *pThdAttr)
{
	int ret =0;
	unsigned char mask;
	mask &= 0x00;

	if(pThdAttr->mask & CONTENTION_SCOPE)
		ret = pthread_attr_getscope(&m_hAttr,&pThdAttr->contention_scope);
	if (ret == 0)
		mask |= CONTENTION_SCOPE;
	if(pThdAttr->mask & DETACH_STATE)
		ret = pthread_attr_getdetachstate(&m_hAttr,&pThdAttr->detach_state);
	if (ret == 0)
		mask |= DETACH_STATE;
//	if(pThdAttr->mask & STACK_ADDR)
//		ret = pthread_attr_getstackaddr(&m_hAttr,&pThdAttr->stack_addr);
//	if (ret == 0)
//		mask |= STACK_ADDR;
	if(pThdAttr->mask & STACK_SIZE)
		ret = pthread_attr_getstacksize(&m_hAttr,&pThdAttr->stack_size);
	if (ret == 0)
		mask |= STACK_SIZE;
	if(pThdAttr->mask & SCHED_PARAM)
		ret = pthread_attr_getschedparam(&m_hAttr,pThdAttr->param);
	if (ret == 0)
		mask |= SCHED_PARAM;
	if(pThdAttr->mask & SCHED_POLICY)
		ret = pthread_attr_getschedpolicy(&m_hAttr,&pThdAttr->policy);
	if (ret == 0)
		mask |= SCHED_POLICY;
	if(pThdAttr->mask & INHERITSCHED)
		ret = pthread_attr_getinheritsched(&m_hAttr,&pThdAttr->inheritsched);
	if (ret == 0)
		mask |= INHERITSCHED;

	pThdAttr->mask = mask;
end:
	return ret;
}

int CUnixThread::SendSignal(int sig)
{
	return pthread_kill(m_hThread,sig);
}

int CUnixThread::SigMask(int how, const sigset_t *set, sigset_t *oset)
{
	return pthread_sigmask(how,set,oset);
}

int CUnixThread::EmptySigSet(sigset_t *set)
{
	return sigemptyset(set);
}

int CUnixThread::GenFullSigset(sigset_t *set)
{
	return sigfillset(set);
}

int CUnixThread::AddSigSet(sigset_t *set, int signo)
{
	return sigaddset(set,signo);
}

int CUnixThread::DelSigSet(sigset_t *set, int signo)
{
	return sigdelset(set,signo);
}

int CUnixThread::IsInSigSet(sigset_t *set, int signo)
{
	return sigismember(set,signo);
}

int CUnixThread::WaitSig(const sigset_t *set, int *sig)
{
	return sigwait(set,sig);
}

int CUnixThread::DeleteAttr()
{
	return pthread_attr_destroy(&m_hAttr);
}
