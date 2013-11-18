// lwWinLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "lwInc.h"
#include "LNetTrans.h"
#include "LSemaphore.h"
#include "LTimer.h"
#include "LThread.h"

///////////////mobile semaphore sync object cpp/////////////
CLWSemaphore::CLWSemaphore()
{
	m_pLSemap = new CLSemaphore();
}

BOOL   CLWSemaphore::CreateSemaphore(uint32  uInit /*0*/, uint32 uMax /*0*/)
{
	return m_pLSemap->CreateSemaphore(uInit, uMax);
}

void   CLWSemaphore::Wait()
{
	m_pLSemap->Wait();
}

void   CLWSemaphore::Release()
{
	m_pLSemap->Free();
}

BOOL   CLWSemaphore::Close()
{
	return m_pLSemap->Close();
}

CLWSemaphore::~CLWSemaphore(void)
{
	if(m_pLSemap)
		delete m_pLSemap;
}

///////////////critical section interface implement cpp /////////////

CLWCriSection::CLWCriSection()
{
	m_pLCriSection = new CLCriSection();
}

BOOL   CLWCriSection::CreateCriSection()
{
	return m_pLCriSection->CreateCriSection();
}

void   CLWCriSection::Lock()
{
	m_pLCriSection->Lock();
}

int    CLWCriSection::TryLock()
{
	return 0;
}

void   CLWCriSection::TimeLock(int nSecond)
{
	m_pLCriSection->Lock();
}

void   CLWCriSection::Unlock()
{
	m_pLCriSection->Unlock();
}

BOOL   CLWCriSection::Close()
{
	return m_pLCriSection->Close();
}

CLWCriSection::~CLWCriSection(void)
{
	if(m_pLCriSection)
		delete m_pLCriSection;
}

////////////////LRWLock interface implement cpp/////////////

CLWReadWriteLock::CLWReadWriteLock()
{
	m_pReadWriteLock = new CLReadWriteLock();
}
CLWReadWriteLock::~CLWReadWriteLock()
{
	if(m_pReadWriteLock)
		delete m_pReadWriteLock;
}

int CLWReadWriteLock::ReadLock()
{
	return m_pReadWriteLock->ReadLock();
}

int CLWReadWriteLock::WriteLock()
{
	return m_pReadWriteLock->WriteLock();
}

int CLWReadWriteLock::Unlock()
{
	return m_pReadWriteLock->ReadUnlock();
}

void CLWReadWriteLock::TimeLock(int nSecond)
{
	m_pReadWriteLock->ReadLock();
}

////////////////Event interface implement cpp/////////////
CLWEvent::CLWEvent()
{
	m_pLEvent = new CLEvent();
}

CLWEvent::~CLWEvent()
{
	if(m_pLEvent)
	{
		m_pLEvent->CloseEvent();
		delete m_pLEvent;
	}
	m_pLEvent = NULL;
}

BOOL CLWEvent::CreateEvent(bool bManualReset, bool bInitialState)
{
	return m_pLEvent->CreateEvent(bManualReset, bInitialState);
}

void CLWEvent::SetEvent()
{
	m_pLEvent->SetEvent();
}

void CLWEvent::ResetEvent()
{
	m_pLEvent->ResetEvent();
}

uint64 CLWEvent::Wait(uint64 timeout)
{
	return m_pLEvent->Wait(timeout);
}

BOOL CLWEvent::CloseEvent()
{
	m_pLEvent->CloseEvent();
	return TRUE;
}

///////////////thread interface implement cpp/////////////
CLWThread::CLWThread()
{
	m_pLThread = new CLThread();
}

CLWThread::~CLWThread()
{
	if(m_pLThread)
		delete m_pLThread;
}

BOOL CLWThread::SetActive(ILWHandThread *pi)
{
	return m_pLThread->SetActive(pi);
}

void CLWThread::KillThread()
{
	m_pLThread->KillThread();
}

///////////////timer interface implement cpp/////////////
CLWTimer::CLWTimer()
{
	m_pLTimer = new CLTimer();
}

CLWTimer::~CLWTimer()
{
	if(m_pLTimer)
		delete m_pLTimer;
}

BOOL CLWTimer::SetTimer(UINT32 nIDEvent,UINT32 uElapse, ILWHandleTimer * pi)
{
	return m_pLTimer->SetTimer(nIDEvent,uElapse,pi);
}
BOOL CLWTimer::Cancel()
{
	return m_pLTimer->Cancel();
}

//////////////////////////////CLWNetTrans cpp /////////////////////////////
CLWNetTrans::CLWNetTrans()
{
	m_pl = new CLNetTrans();
}

CLWNetTrans::~CLWNetTrans()
{
	if(m_pl)
		delete m_pl; m_pl = NULL;
}
//连接函数
BOOL CLWNetTrans::Connect(const char * remoteIP, UINT16 remotePort,ILWHandleNetTrans * pi,UINT32 nRecvTimeout)
{
	return m_pl->Connect(remoteIP,remotePort,pi,nRecvTimeout);
}

//异步连接
void CLWNetTrans::ConnectAsyn(const char * remoteIP, UINT16 remotePort,ILWHandleNetTrans * pi,UINT32 nRecvTimeout)
{
	return m_pl->ConnectAsyn(remoteIP, remotePort,pi,nRecvTimeout);
}

//加载保持的的连接
BOOL CLWNetTrans::LoadSocket(UINT32 orgSocket)
{
	return m_pl->LoadKeepConnect(orgSocket);
}

UINT32 CLWNetTrans::GetSocket(void)
{
	return m_pl->GetSocket();
}

//断开连接
BOOL CLWNetTrans::DisConnect(void)
{
	return m_pl->DisConnect();
}

//判断是否连接
BOOL CLWNetTrans::IsConnect(void)
{
	return m_pl->IsConnect();
}

//发送函数
BOOL CLWNetTrans::Send(const char *pszData, uint32 ulen)
{
	return m_pl->Send(pszData, ulen);
}

char * CLWNetTrans::GetRemoteIP()
{
	return m_pl->GetRemoteIP();
}
UINT16 CLWNetTrans::GetRemotePort()
{
	return m_pl->GetRemotePort();
}