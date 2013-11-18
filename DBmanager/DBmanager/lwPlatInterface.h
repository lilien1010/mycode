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
//_LIB--�ڹ�����̬�⹤����������Ĭ���У� LW_USELIB--��ʹ�þ�̬��Ĺ���������
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

//���߳�>>��Ϣ������
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

//���߳�>>����������
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

//���߳�>>�¼�����
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

//���߳�>>�߳̽ӿ�
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


//>>>>>>>>>>>>>>>>>timer interface Ϊÿһ��ʱ�Ӵ���ʵ������,���һ��Ӧ��ֻ֧��3��timer
//ʱ�ӽӿ�
class ILWHandleTimer
{
public:
	virtual BOOL Run(uint32 uIDEvent) = 0; //nIDEvent �û������¼���ʶ
};
class CLTimer;
class LWINTERFACE_C CLWTimer
{
public:
	LWINTERFACE_CM CLWTimer();
	LWINTERFACE_CM virtual ~CLWTimer(void);
	// TODO: add your methods here.
	LWINTERFACE_CM BOOL SetTimer(uint32 uIDEvent, uint32 uElapse, ILWHandleTimer * pi);//��λ��ms
	LWINTERFACE_CM BOOL Cancel();
private:
	CLTimer * m_pLTimer;
};


//>>>>>>>>>>>>>>>>>>>>����ӿ� ����ͻ���(ֱ����������)����Ӧ��һ���ͻ���socket����
//CMNet����ӿ�
//data tcp�����ݰ���ҵ��������и���Э�����
//enent ʼ��ΪNE_IORECV

#define MAX_NETBUF 20 * 1024 //����ҵ������棨���Ժ�С����Ϊ�Ѿ������Զ��ڴ������ƣ�

enum ELW_NET_ERROR {ERR_SUCCESS = 0x00, ERR_INVALID_VALUE=0x01,
ERR_INVALID_ADDR = 0x02, ERR_CONNECT = 0x03,
ERR_READ = 0x04, ERR_WRITE = 0x05, ERR_BUSY = 0x06, ERR_FILENOTFIND = 0x07};

//other ������� ģ���������usb���ӡ����wi-fi��
enum ELW_NET_EVENT {NE_IORECV = 0x01,NE_IOWRITE = 0x02,NE_IOACCEPT = 0x03,
NE_IOFAILED = 0x04,NE_IORECVED=0x05,NE_IORECVSTART = 0x06,
NE_BUSIERR = 0x07,NE_CONNECT = 0x08,NE_IOTIMEOUT = 0x09};
//��Ϊ NE_IORECV NE_IORECVEDʱ��code��ʾ��ǰ���ݳ��ȣ��ڶ̵�����ģʽ��dataΪNULL��
//��ΪNE_IORECVSTARTʱ��code��ʾ�����ܳ��ȣ�����ͷ���壩��
//��ΪNE_BUSIERRʱ����ʾ��׼ҵ�񷵻ش���data����������code�Զ��������루-1��δ֪���� 1���ڴ治�� 2�����̿ռ䲻�� 3���ļ���ʧ�� ������HTTP ERROR CODE��
//NE_CONNECT, code 0���ӳɹ������� ʧ��
//>>>>>>>>>>>>>����ײ�ӿ�
class ILWHandleNetTrans
{
public:
	virtual BOOL Run(uint8 cEvent, const char * pszData, uint32 uCode)  = 0;
};

#define LW_RECVTIMEOUT_DEFAULT		30*1000 //Ĭ��30�볬ʱ
#ifdef WIN32
class CLNetTrans;
class LWINTERFACE_C CLWNetTrans
{
public:
	LWINTERFACE_CM CLWNetTrans();
	LWINTERFACE_CM virtual ~CLWNetTrans();
	//ͬ������
	LWINTERFACE_CM BOOL Connect(const char * pszRemoteIP, uint16 usRemotePort, ILWHandleNetTrans * pi, uint32 uRecvTimeout = LW_RECVTIMEOUT_DEFAULT);
	//�첽����
	LWINTERFACE_CM void ConnectAsyn(const char * pszRemoteIP, uint16 usRemotePort, ILWHandleNetTrans * pi, uint32 uRecvTimeout = LW_RECVTIMEOUT_DEFAULT);
	//�Ͽ�����
	LWINTERFACE_CM BOOL DisConnect(void);
	//�ж��Ƿ�����
	LWINTERFACE_CM BOOL IsConnect(void);

	//���ر��ֵĵ�����
	LWINTERFACE_CM BOOL LoadSocket(uint32 uOrgSck);

	//��ȡͨ���׽���
	LWINTERFACE_CM	uint32 GetSocket(void);
	//���ͺ���
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
