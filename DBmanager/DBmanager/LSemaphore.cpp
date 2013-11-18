#include "LSemaphore.h"
#include <assert.h>

CLSemaphore::CLSemaphore(void)
{
	m_handle = NULL;
}

CLSemaphore::~CLSemaphore(void)
{
	Close();
}


BOOL CLSemaphore::CreateSemaphore(uint32  uInit , uint32 uMax)
{
	m_handle = ::CreateSemaphore( NULL, uInit, uMax, NULL );
	return m_handle!= NULL;
}

void CLSemaphore::Wait()
{
	assert(m_handle);

	::WaitForSingleObject(m_handle,INFINITE);
}

void CLSemaphore::Free()
{
	assert(m_handle);

	::ReleaseSemaphore( m_handle, 1, NULL ) ;
}

BOOL    CLSemaphore::Close()
{
	if( m_handle != NULL )
	{
		::CloseHandle( m_handle );
		m_handle = NULL;
	}
	return TRUE;
}

///////////////////////CLCriSection cpp///////////////////////
CLCriSection::CLCriSection(void)
{
	m_psect = new CRITICAL_SECTION;
}
CLCriSection::~CLCriSection(void)
{
	Close();
}

BOOL   CLCriSection::CreateCriSection()
{
	::InitializeCriticalSection(m_psect);
	return TRUE;
}

void    CLCriSection::Lock()
{
	::EnterCriticalSection(m_psect);
}
void    CLCriSection::Unlock()
{
	::LeaveCriticalSection(m_psect);
}

BOOL CLCriSection::Close()
{
	if(m_psect )
	{
		::DeleteCriticalSection(m_psect);
		delete m_psect;
		m_psect = NULL;
	}
	
	return TRUE;
}


CLReadWriteLock::CLReadWriteLock(void)
{
    InitializeCriticalSection(&mEnterLock);
    mdwReaders = 0;
    #ifdef _FAN_DEBUG__
        std::cout<<"Create ReadWriteLock"<<endl;
    #endif //_FAN_DEBUG__
}
 
CLReadWriteLock::~CLReadWriteLock(void)
{
    DeleteCriticalSection(&mEnterLock);
    #ifdef _FAN_DEBUG__
        std::cout<<"Delete ReadWriteLock"<<endl;
    #endif //_FAN_DEBUG__
}


int CLReadWriteLock::ReadLock()
{
    EnterCriticalSection(&mEnterLock);
    InterlockedIncrement(&mdwReaders);
    LeaveCriticalSection(&mEnterLock);
    #ifdef _FAN_DEBUG__
        std::cout<<"Reader lock success."<<endl;
    #endif //_FAN_DEBUG__
    return 0;
}

int CLReadWriteLock::ReadUnlock()
{
    InterlockedDecrement(&mdwReaders);
    #ifdef _FAN_DEBUG__
        std::cout<<"Reader unlock success."<<endl;
    #endif //_FAN_DEBUG__
    return 0;
}


int CLReadWriteLock::WriteLock()
{
    //HANDLE mhThread = GetCurrentThread();
    //BOOL mbSetPrioritySuccess = FALSE;
    EnterCriticalSection(&mEnterLock);
    //直到读的用户全部退出
    //if (mdwReaders>0)
    //{
    //        mbSetPrioritySuccess =
    //        SetThreadPriority(mhThread,THREAD_PRIORITY_LOWEST);
    //}
    while(mdwReaders>0)
    {
    #ifdef _FAN_DEBUG__
        std::cout<<"Writer lock test Reader number."<<endl;
        std::cout<<"Current Reader number is "<<mdwReaders<<endl;
    #endif //_FAN_DEBUG__
        Sleep(0);
    }
    //if (mbSetPrioritySuccess)
    //{
    //  SetThreadPriority(mhThread,THREAD_PRIORITY_NORMAL);
    //}
    #ifdef _FAN_DEBUG__
        std::cout<<"Writer lock success."<<endl;
    #endif //_FAN_DEBUG__
    return 0;
}




int CLReadWriteLock::WriteUnlock()
{
    LeaveCriticalSection(&mEnterLock);
    #ifdef _FAN_DEBUG__
        std::cout<<"Writer unlock success."<<endl;
    #endif //_FAN_DEBUG__
    return 0;
}


CLEvent::CLEvent( void )
{
	m_handle = NULL;
}

CLEvent::~CLEvent()
{	
	CloseEvent();	
}

BOOL CLEvent::CreateEvent(bool bManualReset, bool bInitialState)
{
	m_handle = ::CreateEvent(NULL, bManualReset, bInitialState, NULL);
	return m_handle != NULL;
}

void CLEvent::CloseEvent()
{
	if( m_handle )
	{
		::CloseHandle(m_handle);
	}
	m_handle = NULL;
}

void CLEvent::SetEvent()
{
	::SetEvent(m_handle);
}

void CLEvent::ResetEvent()
{
	::ResetEvent(m_handle);
}

uint64 CLEvent::Wait( uint64 timeout /*= INFINITE*/ )
{
	return  ::WaitForSingleObject(m_handle, (DWORD)timeout);
}