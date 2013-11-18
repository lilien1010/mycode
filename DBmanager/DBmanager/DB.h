
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

#define	DB_CONNECT_TOUT 5 //超时


using namespace std;

//API 解释http://blog.csdn.net/kunp/article/details/168499
//http://dev.mysql.com/doc/refman/5.1/zh/apis.html#
//http://www.oschina.net/code/snippet_583625_19664

class DB{ 
public:

	DB();

	int dede();		//自动连接到数据库

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
	
	unsigned int m_timeout;	//超时时间

	bool m_bConnected;		//数据库连接了吗?   true--已经连接;  false--还没有连接
	
	char m_szErrMsg[1024];	//函数出错后, 错误信息放在此处

	int m_iFields;			//字段个数

	MYSQL * m_conn;

	MYSQL_RES* m_result;		//结果集指针
		
	MYSQL_ROW m_row;		//一行,  typedef char **MYSQL_ROW;

	map<string,int>		m_mapField;
	
	string				m_dbhost;

	int					m_seleteCount	;


 

};