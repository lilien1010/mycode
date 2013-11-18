/*
 * commondefine.h
 * 
 *
 * 文件描述：通用定义文件
 * 
 * 创建人：Pippo
 * 时间：	2013-04-26
 * 修改记录：
 */

#pragma once

typedef unsigned    long        DWORD;
typedef unsigned	char		byte;
typedef signed      char        int8; 
typedef unsigned    char        uint8;
typedef signed      short       int16;
typedef unsigned    short       uint16;
typedef signed      int         int32;
typedef unsigned    int         uint32;
typedef wchar_t					wchar;
#ifdef WIN32
typedef signed      __int64     int64;
typedef unsigned    __int64     uint64;
#else
typedef signed long long         int64;
typedef unsigned long long       uint64;
#endif

#if defined __x86_64__
typedef uint64		ptr_size;
#else
typedef uint32		ptr_size;
#endif

#ifdef linux
#define sprintf_s snprintf

typedef unsigned char            UINT8;
typedef signed   char            INT8;
typedef bool                     BOOL;
typedef unsigned char            BYTE;
typedef void*                    LPVOID;
typedef void*                    PVOID;
typedef PVOID                    HANDLE;
typedef unsigned long            DWORD;
typedef int                      SOCKET;
typedef unsigned short           USHORT;
typedef unsigned int             UINT;
typedef void*                    DWORD_PTR;

typedef wchar_t WCHAR;
typedef struct
{
  int wSecond;			/* Seconds.	[0-60] (1 leap second) */
  int wMinute;			/* Minutes.	[0-59] */
  int wHour;			/* Hours.	[0-23] */
  int wDay;			    /* Day.		[1-31] */
  int wMonth;			/* Month.	[0-11] */
  int wYear;			/* Year	- 1900.  */
  int wDayOfWeek;		/* Day of week.	[0-6] */
  int tm_yday;			/* Days in year.[0-365]	*/
  int tm_isdst;			/* DST.		[-1/0/1]*/
#ifdef	__USE_BSD
  long int tm_gmtoff;		/* Seconds east of UTC.  */
  __const char *tm_zone;	/* Timezone abbreviation.  */
#else
  long int __tm_gmtoff;		/* Seconds east of UTC.  */
  __const char *__tm_zone;	/* Timezone abbreviation.  */
#endif
}SYSTEMTIME;
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define WSAEWOULDBLOCK  EWOULDBLOCK
#define WSAGetLastError() errno
#define GetLastError() errno
#define MAX_PATH 260
#define SD_BOTH SHUT_RDWR
#define INFINITE 0xFFFFFFFF
#define WAIT_TIMEOUT 0x00000102L
#define WAIT_OBJECT_0 0

#define TRUE true
#define FALSE false
#define Sleep(x) sleep(x)
#define __stdcall
#define _tmain main
#define _TCHAR char
#define SSIZE_T ssize_t
//#define lwSprintf snprintf
#include <pthread.h>
typedef struct
{
    pthread_mutex_t mtx;
    pthread_cond_t cond;
    bool manual_reset;
    bool signaled;
}THANDLE,*PHANDLE;

typedef void(*PFN)(void*);
enum{TIME_ONESHOT = true,TIME_PERIODIC = false};

typedef struct
{
    int timerID;
    pthread_t tid;
    PFN pfn;
    void *lpParam;
    bool bOneShot;
}MMRESULT,*PMMRESULT;

#endif

/*
#ifdef WIN32
#define I64 I64u
#else
#define I64 llu
#endif
*/

#pragma pack(push,1) // 网络数据包，一字节对奇

//自定义网络上传输的时间格式
struct NTTime
{
	uint16 	wYear;
	uint8 	wMonth;
	uint8	wDay;
	uint8 	wHour;
	uint8	wMinute;
	uint8	wSecond;
};

#define MD5_LEN		32
#define TOKEN_STRING_LEN	64

#pragma pack(pop)



