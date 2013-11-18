
#include "DB.h"
 
#define DB_TAKEN 1
#define DB_NOTTAKEN 0

typedef map<DB*,int> DBMAP;
//http://www.cnblogs.com/ckaimnet/archive/2012/02/25/2367954.html
//需要添加跨平台 多线程控制

typedef struct  
{
	DB * first;
	int second;
}POOLINFO;

class DBPool
{
public:


	DBPool(){};
	~DBPool();
	int ConnPool(string szHost,string szDB,string szUser,string szPwd,int max_size);
	DB*	GetDB();
	int GetDbNum(){return  m_curSize;}
	int GetTakenNum(){return  m_nTakenNum;}
	static DBPool * GetInstance();
	static DBPool * m_dbpool;
	void ReleaseDB(DB* conn);
	void	DestoryDB(DB* conn);
 	void	DestoryPool();
		DB * CreateDB();
private:
	int m_curSize; //当前已建立的数据库连接数量
	 
	int	m_maxSize; //连接池中定义的最大数据库连接数
	
	int m_nTakenNum;

	DBMAP m_connMap; //连接池的存放，int 标示使用情况
	
	CRITICAL_SECTION m_sect;

	string m_szHost, m_szDB, m_szUser, m_szPwd;
	int DBConnect(DB* p_conn);	//使用上面的信息去连接数据库


	int		InitDBPool( int max_size);
	
	POOLINFO	m_poolInfo[64];

	




};