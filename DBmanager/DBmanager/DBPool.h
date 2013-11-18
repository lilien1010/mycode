
#include "DB.h"
 
#define DB_TAKEN 1
#define DB_NOTTAKEN 0

typedef map<DB*,int> DBMAP;
//http://www.cnblogs.com/ckaimnet/archive/2012/02/25/2367954.html
//��Ҫ��ӿ�ƽ̨ ���߳̿���

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
	int m_curSize; //��ǰ�ѽ��������ݿ���������
	 
	int	m_maxSize; //���ӳ��ж����������ݿ�������
	
	int m_nTakenNum;

	DBMAP m_connMap; //���ӳصĴ�ţ�int ��ʾʹ�����
	
	CRITICAL_SECTION m_sect;

	string m_szHost, m_szDB, m_szUser, m_szPwd;
	int DBConnect(DB* p_conn);	//ʹ���������Ϣȥ�������ݿ�


	int		InitDBPool( int max_size);
	
	POOLINFO	m_poolInfo[64];

	




};