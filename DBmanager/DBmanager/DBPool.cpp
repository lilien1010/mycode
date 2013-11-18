#include "DBPool.h"


using namespace std; 

DBPool* DBPool::m_dbpool		=	NULL;

DBPool::~DBPool()  
{  
	this->DestoryPool();
}  
 
DBPool * DBPool::GetInstance(){

	if(m_dbpool == NULL){
		
		m_dbpool	=	new DBPool();

		return m_dbpool;
	}

	return m_dbpool;

}


int DBPool::ConnPool(string szHost,string szDB,string szUser,string szPwd,int max_size){

	m_szHost	=	szHost;
	m_szDB		=	szDB;
	m_szUser	=	szUser;
	m_szPwd		=	szPwd;
	m_maxSize	=	max_size; 
	m_nTakenNum	=	m_curSize	=	0; 
	
	::InitializeCriticalSection(&m_sect);
	return InitDBPool(m_maxSize/2);
}




int DBPool::InitDBPool(int conn_num){
	DB	* p_conn=NULL;
	
	//加锁
	 ::EnterCriticalSection(&m_sect);
	for(int i =0 ; i <conn_num; i++){
		p_conn		=	new DB();
		if( 0 == DBConnect(p_conn)){
			m_connMap.insert(pair<DB*,int>(p_conn,DB_NOTTAKEN)); 
			m_curSize++;
		}
	}
	
	::LeaveCriticalSection(&m_sect);
	return m_curSize;
	//释放枷锁
}
 

DB*	DBPool::GetDB(){

	::EnterCriticalSection(&m_sect);
	DBMAP::iterator it	=	m_connMap.begin();
	DB*		p_conn =NULL;
	//加锁

	for(;it != m_connMap.end()	;it++){

			if(it->second == DB_NOTTAKEN){
				p_conn	=	it->first;
				
				if(p_conn && !p_conn->isConnected()){
					/* m_connMap.erase(it++);
					 m_curSize--;
					 continue;*/
					DBConnect(p_conn);
				}

				it->second	=	DB_TAKEN;
				//开锁	
				m_nTakenNum++;
				::LeaveCriticalSection(&m_sect);
				return it->first;
			}
			
	}

	if (m_curSize < m_maxSize){

		DB	*	p_conn	=	 new DB();
		if(p_conn == NULL)	return NULL;

		if( 0 == DBConnect(p_conn)){
			m_connMap.insert(make_pair(p_conn,DB_NOTTAKEN)); 
			m_curSize++;
			//开锁	
			::LeaveCriticalSection(&m_sect);
			return p_conn;
		}else{
			SAFE_DELETE(p_conn);
		}
 
	}
	//开锁	
	::LeaveCriticalSection(&m_sect);
	return NULL;
}

void	DBPool::DestoryPool(){
	if(m_dbpool == NULL)	return;
	DB	* p_conn		=	NULL;
	DBMAP::iterator it=m_connMap.begin();
	//加锁
	::EnterCriticalSection(&m_sect);

	for(;it != m_connMap.end()	;	it++){
		it->first->Close();
		delete (it->first);
	}

	m_connMap.clear();
	m_curSize	=	0;
	//去掉锁
	::LeaveCriticalSection(&m_sect);


	::DeleteCriticalSection(&m_sect);

	 DBPool::m_dbpool	=	NULL;
}

void	DBPool::DestoryDB(DB* p_conn){
	
	if(p_conn){

		::EnterCriticalSection(&m_sect);
		p_conn->Close();
		m_curSize--;
		DBMAP::iterator it	= m_connMap.find(p_conn);
		if(it->second == DB_TAKEN){
				m_nTakenNum--;
		}
		m_connMap.erase(it);
		SAFE_DELETE(p_conn);
		::LeaveCriticalSection(&m_sect);
	}
}
 

DB * DBPool::CreateDB(){

	return NULL;
}

void DBPool::ReleaseDB(DB* conn){
	
	if(conn){
		//加锁
		::EnterCriticalSection(&m_sect);
		m_connMap[conn]	=	DB_NOTTAKEN;	
		m_nTakenNum--;
		//开锁	
		::LeaveCriticalSection(&m_sect);

	}
}
int DBPool::DBConnect(DB* p_conn){

	if(p_conn){
		return p_conn->Connect(m_szHost.c_str(),m_szDB.c_str(),m_szUser.c_str(),m_szPwd.c_str());
	}
	return 0;
	
}