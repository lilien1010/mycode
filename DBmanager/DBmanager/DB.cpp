#include "DB.h"

DB::DB()
{
	m_conn			=	NULL;
	m_timeout		=	DB_CONNECT_TOUT;
	m_bConnected	=	false;
	m_result		=	NULL;
	m_seleteCount	=	0;
}

int DB::dede()
{

	const char* szHost="192.168.1.69";
	const char* szDB="HT_IMDB";
	const char* szUser="root";
	const char* szPwd="123456";
	int ret	=	Connect( szHost,  szDB,  szUser,  szPwd);
	ERRMSG(" connect return is %d \n",ret);
	return ret;
}

int DB::Connect(const char* szHost, const char* szDB, const char* szUser, const char* szPwd){

	// Reset connection
	Close();

	m_conn = new MYSQL;
	if(NULL == m_conn || !mysql_init(m_conn))
		return -1;

	mysql_options(m_conn, MYSQL_OPT_CONNECT_TIMEOUT, (const char*)&m_timeout);

	// read write timeout
	unsigned int nTimeout =10; //seconds
	mysql_options(m_conn, MYSQL_OPT_READ_TIMEOUT, (const char*)&nTimeout);
	mysql_options(m_conn, MYSQL_OPT_WRITE_TIMEOUT, (const char*)&nTimeout);

	if (mysql_real_connect(m_conn, szHost, szUser, szPwd, szDB, 0, NULL, CLIENT_MULTI_STATEMENTS)) 
	{
		// this option must be set after connect - bug in mysql client library
		my_bool reconn = 0;
		mysql_options(m_conn, MYSQL_OPT_RECONNECT, (const char*)&reconn);
		return 0;
	}

	return mysql_errno(m_conn);


}

void DB::Close()
{
	if (m_conn)
	{ 
		mysql_close(m_conn);

		Sleep(10); //PIPPOOO 
		delete m_conn;
		m_conn = NULL;
	}
}



char ** DB::FetchRow()
{
		if (m_result == NULL)
			return NULL;
 
		m_row = mysql_fetch_row(m_result);

		return m_row;
}


char* DB::GetField(unsigned int iFieldIndex) {

		if (iFieldIndex >= m_iFields)
			return NULL;

		return m_row[iFieldIndex];

}


char* DB::GetField(const char* szFieldName) {
		return GetField(m_mapField[szFieldName]);
}


int DB::Select(const char * szSql){
 
 
	 if (szSql == NULL) {
	     ERRMSG("%s\n", "szSQL==NULL");
	     return -1;
	 }
	
	 if (!isConnected()) {
	     ERRMSG("%s", "��û�н�������\n");
		 int nRet = ReConnect(); 
		 if (nRet != 0 || m_conn==NULL)
			  return -2;
	 }
		//��Щ����������йأ����쳣ʱ������
	 try{

		 if(m_conn==NULL){
			 return -2;
			 ERRMSG("some thing wrong with MYSQL*\n");
		 }
		 m_seleteCount++;
		 ERRMSG("Current Thread ID is %d\n",GetCurrentThreadId());
		 if( 0!= mysql_real_query(m_conn, szSql, strlen(szSql) ) ) {
	 
	         ERRMSG("ReConnect()  is called, select111  !!!***\r\n");
	
	         int nRet = ReConnect();
	
	         if (nRet != 0)
				 return -3;
	
			 if (mysql_real_query(m_conn, szSql, strlen(szSql))){
				GetError(TRUE);
	             return -4;
			 }
	
	     }

	
	     //�ͷ���һ�εĽ����
	     FreeResult();

	     //ȡ�����
	     m_result = mysql_store_result(m_conn);
	
	     if (m_result == NULL) {
	         GetError(TRUE);
	         return -5;
	     }
	
	 } catch (...) {
	
	     ERRMSG("ReConnect()  is called, select  wrong\r\n");
	
	     ReConnect();
	     return -5;
	
	 }
	
	 //ȡ�ֶεĸ���
	
	 m_iFields = mysql_num_fields(m_result);
	
	 m_mapField.clear();
	
	 //ȡ�����ֶε�������Ϣ
	
	 MYSQL_FIELD *fields;
	
	 fields = mysql_fetch_fields(m_result);
	
	 for (unsigned int i = 0; i < m_iFields; i++) {
	
	     m_mapField[fields[i].name] = i;
	
	 }
	
    return 0;
}

const char *DB::GetError(int ouput){

	if(m_conn){
		const char * info	=	mysql_error(m_conn);
		if(ouput)	ERRMSG("%s",info);
		return  info;
	}

}

int DB::ReConnect() {

		return dede();

}


int DB::Modity(const char * szSql)
{
	if (szSql == NULL) {
		ERRMSG("%s", "szSQL==NULL");
		return -1;
	}

	if (!isConnected()) {
		ERRMSG("%s", "��û�н�������");
		return -2;
	}

	try
	{
		 m_seleteCount++;
		if(mysql_real_query(m_conn,szSql,strlen(szSql))){
			ERRMSG("Query Error %s",mysql_error(m_conn));
			return -3;

		}

	} 
	catch (...)
	{
			ERRMSG("Reconnecting``````` in Modify");
			this->ReConnect();

			return -5;
	}
	int Afftected	=	mysql_affected_rows(m_conn);
    return Afftected;  


}

bool DB::isConnected(){
 
 
	if (!m_conn || 0 != mysql_ping(m_conn))
	{
		 
		Close(); // close connection immediately 
		return false;
	}

	return true;

}