#ifndef LSEMAPHORE_H_
#define LSEMAPHORE_H_
#include <windows.h>
//信号量
//二次构造类模板
class CLSemaphore
{
public:
	CLSemaphore(void);
public:
	~CLSemaphore(void);

	BOOL   CreateSemaphore(uint32  uInit = 0, uint32 uMax = 0);

	void    Wait();
	void    Free();

	BOOL    Close();

private:
	HANDLE m_handle;
};

//临界区
class CLCriSection
{
public:
	CLCriSection(void);
public:
	~CLCriSection(void);

	BOOL   CreateCriSection();

	void    Lock();
	void    Unlock();
	BOOL    Close();

private:
	CRITICAL_SECTION*	m_psect;
};

class CLReadWriteLock
{
public:
	CLReadWriteLock(void);
	~CLReadWriteLock(void);
	int ReadLock();
	int ReadUnlock();
	int WriteLock();
	int WriteUnlock();
private:

	CRITICAL_SECTION mEnterLock;
	LONG			 mdwReaders;
};

class CLEvent
{
public:
	CLEvent(void);
public:
	~CLEvent();

	BOOL CreateEvent(bool bManualReset, bool bInitialState);

	void CloseEvent();

	void SetEvent();

	void ResetEvent();

	uint64 Wait(uint64 timeout = INFINITE);
private:
	HANDLE m_handle;
};

#endif //LSEMAPHORE_H_