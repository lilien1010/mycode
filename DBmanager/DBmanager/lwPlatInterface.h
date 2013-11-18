#ifndef PLATINTERFACE_H_
#define PLATINTERFACE_H_
#include "CommDefine.h"
#ifdef linux
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <deque>
using namespace std;
#endif

#ifdef WIN32
#define LW_USELIB

#if defined(_LIB) || defined(LW_USELIB)
//_LIB--在公共静态库工程中声明（默认有） LW_USELIB--在使用静态库的工程中声明
#define LWINTERFACE_C
#define LWINTERFACE_CM
#define LWINTERFACE_API

#else
//DLL

#ifdef LWINTERFACEDLL_EXPORTS
#define LWINTERFACEDLL_API __declspec(dllexport)
#else
#define LWINTERFACEDLL_API __declspec(dllimport)
#endif

#define LWINTERFACE_C		LWINTERFACEDLL_API
#define LWINTERFACE_CM
#define LWINTERFACE_API		LWINTERFACEDLL_API


#endif//end of output type
#else

#define LWINTERFACE_C
#define LWINTERFACE_CM
#endif

//多线程>>信息量申明
class CLSemaphore;
class LWINTERFACE_C CLWSemaphore
{
public:
	LWINTERFACE_CM CLWSemaphore();
	LWINTERFACE_CM virtual ~CLWSemaphore(void);
	// TODO: add your methods here.
	 LWINTERFACE_CM BOOL CreateSemaphore(uint32  uInit = 0, uint32 uMax = 0);
	 LWINTERFACE_CM void Wait();
	 LWINTERFACE_CM void Release();
	 LWINTERFACE_CM BOOL Close();

private:
	CLSemaphore * m_pLSemap;
};

//多线程>>互斥体申明
class CLCriSection;
class LWINTERFACE_C CLWCriSection
{
public:
	LWINTERFACE_CM CLWCriSection();
	LWINTERFACE_CM virtual ~CLWCriSection(void);
	// TODO: add your methods here.
	LWINTERFACE_CM BOOL CreateCriSection();
	LWINTERFACE_CM void Lock();

	LWINTERFACE_CM int TryLock();

	LWINTERFACE_CM void Unlock();
	LWINTERFACE_CM BOOL Close();

	LWINTERFACE_CM void TimeLock(int nSecond = 20);

private:
	CLCriSection * m_pLCriSection;
};

class CLReadWriteLock;
class LWINTERFACE_C CLWReadWriteLock
{
public:
	LWINTERFACE_CM	CLWReadWriteLock();
	LWINTERFACE_CM virtual ~CLWReadWriteLock();
	LWINTERFACE_CM int ReadLock();
	LWINTERFACE_CM int WriteLock();
	LWINTERFACE_CM int Unlock();
	LWINTERFACE_CM void TimeLock(int nSecond = 20);
private:
	CLReadWriteLock	* m_pReadWriteLock;
};

//多线程>>事件申明
class CLEvent;
class LWINTERFACE_C CLWEvent
{
public:
	LWINTERFACE_CM CLWEvent();
	LWINTERFACE_CM virtual~CLWEvent(void);
	// TODO: add your methods here.
	LWINTERFACE_CM BOOL CreateEvent(bool bManualReset, bool bInitialState);
	LWINTERFACE_CM void SetEvent();
	LWINTERFACE_CM void ResetEvent();
	LWINTERFACE_CM uint64 Wait(uint64 timeout = INFINITE);
	LWINTERFACE_CM BOOL CloseEvent();
private:
	CLEvent	*m_pLEvent;
};

//多线程>>线程接口
class ILWHandThread
{
public:
	virtual BOOL Run() = 0;
};
class CLThread;
class LWINTERFACE_C CLWThread
{
public:
	LWINTERFACE_CM CLWThread();
	LWINTERFACE_CM virtual ~CLWThread(void);
	// TODO: add your methods here.
	LWINTERFACE_CM BOOL SetActive(ILWHandThread * pi);
protected:
 	LWINTERFACE_CM void KillThread();

private:
	CLThread * m_pLThread;
};


//>>>>>>>>>>>>>>>>>timer interface 为每一个时钟创建实例对象,最多一个应用只支持3个timer
//时钟接口
class ILWHandleTimer
{
public:
	virtual BOOL Run(uint32 uIDEvent) = 0; //nIDEvent 用户传入事件标识
};
class CLTimer;
class LWINTERFACE_C CLWTimer
{
public:
	LWINTERFACE_CM CLWTimer();
	LWINTERFACE_CM virtual ~CLWTimer(void);
	// TODO: add your methods here.
	LWINTERFACE_CM BOOL SetTimer(uint32 uIDEvent, uint32 uElapse, ILWHandleTimer * pi);//单位：ms
	LWINTERFACE_CM BOOL Cancel();
private:
	CLTimer * m_pLTimer;
};


//>>>>>>>>>>>>>>>>>>>>网络接口 网络客户端(直接连互联网)，对应着一个客户端socket连接
//CMNet网络接口
//data tcp流数据包，业务层需自行根据协议组包
//enent 始终为NE_IORECV

#define MAX_NETBUF 20 * 1024 //接收业务包缓存（可以很小，因为已经有了自动内存分配机制）

enum ELW_NET_ERROR {ERR_SUCCESS = 0x00, ERR_INVALID_VALUE=0x01,
ERR_INVALID_ADDR = 0x02, ERR_CONNECT = 0x03,
ERR_READ = 0x04, ERR_WRITE = 0x05, ERR_BUSY = 0x06, ERR_FILENOTFIND = 0x07};

//other 可能情况 模拟器、真机usb连接、真机wi-fi等
enum ELW_NET_EVENT {NE_IORECV = 0x01,NE_IOWRITE = 0x02,NE_IOACCEPT = 0x03,
NE_IOFAILED = 0x04,NE_IORECVED=0x05,NE_IORECVSTART = 0x06,
NE_BUSIERR = 0x07,NE_CONNECT = 0x08,NE_IOTIMEOUT = 0x09};
//当为 NE_IORECV NE_IORECVED时，code表示当前数据长度；在短点续传模式下data为NULL。
//当为NE_IORECVSTART时，code表示数据总长度（包括头及体）。
//当为NE_BUSIERR时，表示标准业务返回错误，data错误描述，code自定义错误代码（-1：未知错误 1：内存不足 2：磁盘空间不足 3：文件打开失败 其它：HTTP ERROR CODE）
//NE_CONNECT, code 0连接成功，其他 失败
//>>>>>>>>>>>>>网络底层接口
class ILWHandleNetTrans
{
public:
	virtual BOOL Run(uint8 cEvent, const char * pszData, uint32 uCode)  = 0;
};

#define LW_RECVTIMEOUT_DEFAULT		30*1000 //默认30秒超时
#ifdef WIN32
class CLNetTrans;
class LWINTERFACE_C CLWNetTrans
{
public:
	LWINTERFACE_CM CLWNetTrans();
	LWINTERFACE_CM virtual ~CLWNetTrans();
	//同步连接
	LWINTERFACE_CM BOOL Connect(const char * pszRemoteIP, uint16 usRemotePort, ILWHandleNetTrans * pi, uint32 uRecvTimeout = LW_RECVTIMEOUT_DEFAULT);
	//异步连接
	LWINTERFACE_CM void ConnectAsyn(const char * pszRemoteIP, uint16 usRemotePort, ILWHandleNetTrans * pi, uint32 uRecvTimeout = LW_RECVTIMEOUT_DEFAULT);
	//断开连接
	LWINTERFACE_CM BOOL DisConnect(void);
	//判断是否连接
	LWINTERFACE_CM BOOL IsConnect(void);

	//加载保持的的连接
	LWINTERFACE_CM BOOL LoadSocket(uint32 uOrgSck);

	//获取通信套接字
	LWINTERFACE_CM	uint32 GetSocket(void);
	//发送函数
	LWINTERFACE_CM BOOL Send(const char *pszData, uint32 ulen);

	LWINTERFACE_CM char * GetRemoteIP();
	LWINTERFACE_CM uint16 GetRemotePort();
private:
	CLNetTrans * m_pl;
};
uint32 lwGetPrivateProfileString(const char *pcsSection, const char* pcsKey, const char *pDefaultValue, char *pReturnValue, uint32 uReturnSize, char* pcsFileName);
uint32 lwGetPrivateProfileInt(const char *pcsSection, const char* pcsKey, const int32 &uDefaultValue, char* pcsFileName);
#endif
uint32 lwGetModuleFileName(char *pcsFileName, uint32 uNameSize);

uint32 lwGetCurrentDir(char *csDirName, uint32 uDirSize);

uint32 lwCreateDirectory(char *csDirName);

#ifdef linux

PHANDLE CreateEvent(void *pSec,bool bManualReset,bool bInitialState,char *pStr);
void SetEvent(PHANDLE &handle);
void ResetEvent(PHANDLE &handle);
void CloseHandle(PHANDLE &handle);
void TerminateThread(pthread_t pthread,int nExitCode);
int  WaitForSingleObject(PHANDLE &hdl,unsigned int timeout);
void SetConsoleTitle(char *pStr);

DWORD timeGetTime();
int closesocket(SOCKET s);
void InterlockedIncrement(volatile long *v);
void InterlockedDecrement(volatile long *v);
void sleep(int ms);
PMMRESULT timeSetEvent(unsigned int uDelay,unsigned int uResolution,PFN pfn,void *lpParam,bool OneShot);
void timeKillEvent(PMMRESULT timer);
char* strrev(char*pstr);
//int lwSprintf(char *buffer,size_t count,const char *format, ...);
void GetMemInfo(unsigned long *pFreeMB,unsigned long *pTotalMB);
void GetDiskInfo(unsigned long *pFreeGB,unsigned long *pTotalGB);
void GetCPUInfo(unsigned long *pTotal,unsigned long *pIdle);
void GetEth0Info(unsigned long long*pRecvd,unsigned long long*pSent);



#endif


#endif	//define PLATINTERFACE_H_
