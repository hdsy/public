// UnixThread.h: interface for the CUnixThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIXTHREAD_H__9B7308C4_9666_458A_B387_DDE7E6473170__INCLUDED_)
#define AFX_UNIXTHREAD_H__9B7308C4_9666_458A_B387_DDE7E6473170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <pthread.h>
#include <signal.h>

enum ENUM_THREAD_ATTRIBUTES
{
	CONTENTION_SCOPE	=	0X01,
	DETACH_STATE		=	0X02,
	STACK_ADDR			=	0X04,
	STACK_SIZE			=	0X08,
	SCHED_PARAM			=	0X10,
	SCHED_POLICY		=	0X20,
	INHERITSCHED		=	0X40
};
typedef struct STRU_THREAD_ATTRIBUTES
{
	unsigned char	mask;
	int		contention_scope;
	int		detach_state;
	void	*stack_addr;
	size_t	stack_size;
	struct sched_param	*param;
	int		policy;
	int		inheritsched;
}THREAD_ATTR;

class CUnixThread  
{
public:
	pthread_t m_hThread;
public:
	int DeleteAttr();
	int WaitSig(const sigset_t *set,int *sig);
	int IsInSigSet(sigset_t *set,int signo);
	int DelSigSet(sigset_t *set,int signo);
	int AddSigSet(sigset_t *set,int signo);
	int GenFullSigset(sigset_t *set);
	int EmptySigSet(sigset_t *set);
	int SigMask(int how,const sigset_t *set,sigset_t *oset);
	int SendSignal(int sig);
	int GetAttr(THREAD_ATTR *pThdAttr);
	int SetAttr(THREAD_ATTR *pThdAttr);
	int SetSchedParam(int policy,const struct sched_param *param);
	pthread_attr_t m_hAttr;
	int InitAttr();
	int Detach();
	int Join(void ** status);
	void Exit(void * status);
	
	int Create(void *(*atart_func)(void *),void * arg);
	CUnixThread();
	virtual ~CUnixThread();

};

#endif // !defined(AFX_UNIXTHREAD_H__9B7308C4_9666_458A_B387_DDE7E6473170__INCLUDED_)
