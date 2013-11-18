 #include <stdio.h> 
#include "DB.h"
#include "DBPool.h"
// Windows Header Files:
#include <process.h> 


CRITICAL_SECTION g_cs;
//写者线程输出函数  
void WriterPrintf(char *pszFormat, ...)  
{  
	va_list   pArgList;  
	va_start(pArgList, pszFormat);  
	EnterCriticalSection(&g_cs);   
	 vfprintf(stdout, pszFormat, pArgList); 
	LeaveCriticalSection(&g_cs);  
    va_end(pArgList); 
}  

//#pragma comment(lib,"lwWinLib.lib");


#ifdef WIN32
 unsigned int WINAPI func (void * lparam);
#else
void startThread(LPVOID(*func)(LPVOID *),(LPVOID param));
#endif

#ifdef linux
#include <sys/types.h>
#include <sys/socket.h>
#endif

int main(){
		::InitializeCriticalSection(&g_cs);
	DB *db = new DB;
	if( 0	!=	db->dede()){
		db->GetError(1);
	}
	db->Select("select * from HT_IMDB.HT_USER_ACCOUNT limit 5");
	char** r	=	NULL;

	//printf("%s\t%s\t%s\t%s\t%s\t%s\n",db.GetField(1),db.GetField(1),db.GetField(2),db.GetField(3),db.GetField(4),db.GetField(5));
	while (r = db->FetchRow()){
		printf("%s\t%s\t%s\t%s\t%s\t%s\n", r[0], r[1], r[2], r[3], r[4], r[5], r[6]);
	}
	




	int ret = db->Modity("update HT_USER_ACCOUNT set USERTYPE=2 where USERTYPE=1 limit 40");
	 
	printf(" there are %d rows afftected\n\n",ret);
	
	db->Select("select * from HT_IMDB.HT_USER_ACCOUNT limit 2");
	//printf("%s\t%s\t%s\t%s\t%s\t%s\n",db.GetField(1),db.GetField(1),db.GetField(2),db.GetField(3),db.GetField(4),db.GetField(5));
	while (r = db->FetchRow()){
		printf("%s\t%s\t%s\t%s\t%s\t%s\n", r[0], r[1], r[2], r[3], r[4], r[5], r[6]);
	}

 
	db->Close();

	DBPool * pool	=	DBPool::GetInstance();
	pool->ConnPool("192.168.1.69","hellotalk","root","123456",6);


		for(int i =  0 ;i < 16 ; i++){
				HANDLE hHandle = (HANDLE)_beginthreadex(NULL, 0, func, NULL, 0, NULL);
				if(hHandle == INVALID_HANDLE_VALUE){
					printf(" create Thread INVALID_HANDLE_VALUE");
				}
		}

	Sleep(90000);
	return 0;
 

	system("pause");
}


 unsigned int   WINAPI func (void * lparam){
	 

	for(int i =  0 ;i < 300 ; i++){

		DBPool *pool	=	DBPool::GetInstance();
		DB * p_conn		=	pool->GetDB();
		
		if (p_conn == NULL)
		{
				Sleep(100);
				WriterPrintf("Get a NULL  DB waitting 100ms\n"); 
				continue;
		}
		char** r	=	NULL;

		int ret =	p_conn->Select("SELECT SQL_NO_CACHE * FROM hellotalk.userinfo LEFT JOIN hellotalk.userstatus USING(username) WHERE nickname LIKE '%po%' AND username IN (SELECT username FROM hellotalk.deletehideuser)");
 
		WriterPrintf("select return is %d \n running in %d， 连接池数量 is %d,and 取走的数量=%d,连接query次数=%d \n\n",
			ret,GetCurrentThreadId(),pool->GetDbNum(),pool->GetTakenNum(),p_conn->GetSelectCount());

		
/*
		if(p_conn->GetSelectCount()>80){
			pool->DestoryDB(p_conn);
		}else*/{
			pool->ReleaseDB(p_conn);
		}
		
		 Sleep(700);
	
	 }

	WriterPrintf("____________________ this thread is closing ____________________\n");


	return NULL;

}




//跨平台的线程开启函数 

void startThread( unsigned int (WINAPI*func)(void *) ,void * param)
{

	HANDLE hHandle = (HANDLE)_beginthreadex(NULL, 0, func, (void *)param, 0, NULL);
	if(hHandle == INVALID_HANDLE_VALUE){
		printf(" create Thread INVALID_HANDLE_VALUE");
	}

}
 