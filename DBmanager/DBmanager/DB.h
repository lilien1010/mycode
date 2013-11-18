
#pragma once

#ifdef WIN32
#include <winsock2.h>
#endif

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if (x) delete x; x = NULL; }
#endif
#include <mysql.h>

#pragma comment(lib,"libmysql.lib")
#define  ERRMSG(fmt,...)	 printf(fmt,__VA_ARGS__);

#define	DB_CONNECT_TOUT 5 //��ʱ


using namespace std;

//API ����http://blog.csdn.net/kunp/article/details/168499
//http://dev.mysql.com/doc/refman/5.1/zh/apis.html#
//http://www.oschina.net/code/snippet_583625_19664

class DB{ 
public:

	DB();

	int dede();		//�Զ����ӵ����ݿ�

	int Connect(const char* szHost, const char* szDB, const char* szUser, const char* szPwd);
 
	void Close();
	


	int Select(const char * szSql);

	int Modity(const char * szSql);

	const char * GetError(int ouput=0);

	int ReConnect();

	char ** FetchRow();

	char* DB::GetField(unsigned int iFieldIndex);


	char* DB::GetField(const char* szFieldName);
	int  GetSelectCount(){return m_seleteCount;}
	bool isConnected();

	void FreeResult(){
		if(NULL !=	m_result){
			mysql_free_result(m_result);
		}

	}
private:
	
	unsigned int m_timeout;	//��ʱʱ��

	bool m_bConnected;		//���ݿ���������?   true--�Ѿ�����;  false--��û������
	
	char m_szErrMsg[1024];	//���������, ������Ϣ���ڴ˴�

	int m_iFields;			//�ֶθ���

	MYSQL * m_conn;

	MYSQL_RES* m_result;		//�����ָ��
		
	MYSQL_ROW m_row;		//һ��,  typedef char **MYSQL_ROW;

	map<string,int>		m_mapField;
	
	string				m_dbhost;

	int					m_seleteCount	;


 

};