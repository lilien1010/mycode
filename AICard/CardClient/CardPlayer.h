#pragma once

#include "CardBusi.h"
#include "DeskBusi.h"

//牌桌的状态
enum PLAYER_STATUS{
	CAN_HU	=0,		
	CAN_PAO,
	CAN_PEN,
	CAN_CHI,
	SHOWINGCARD,
	TAKINGCARD,
	WAIT_PLAYERCARD,
	WAIT_DESKCARD,
	IDLE
};


typedef struct  paipai{
	int num;
	int type;
	CARDTYPE pai[4];
}PAI;




class CardPlayer
{
	friend class DeskBusi;
	friend class CardBusi;
public:
	CardPlayer(void);
public:
	~CardPlayer(void);
	
	void SetCard(CARDTYPE*Card,int CardNum);			//设置玩家的牌

	void SetPlayerID(int PlayerId);					//设置玩家ID

	void SetPlayerName(char* name);					//设置玩家name
	
	void SetDesk(DeskBusi*);
	
	void ShowOneCard();							//打一张牌

	int GetOneCardFromDesk(CARDTYPE id);		//从桌面抓一张牌


	int GetOneCardFromPre(CARDTYPE id);		//从上家取一张牌
	
	int ReportStatus();		//报告状态
 
	int CardChi(CARDTYPE);					//吃牌
	
	int CardPen(CARDTYPE);					//碰牌

	int CardSao(CARDTYPE);					//扫牌，暗碰

	int CardPao(CARDTYPE);					//跑牌，四张
	
	int CardTiLong(CARDTYPE);				//提龙，跑和 自摸同时成立

	int CanHu(CARDTYPE);					//能否胡牌，

	int CanChi(CARDTYPE);					//能否吃牌
	

 	char		m_PlayerName[128];			// 玩家姓名
	int			m_IsWinner;					//是否是上一盘的赢家，是的话15张牌
	int			m_PlayerID;					//玩家ID 数据库
	int			m_PlayerNo;					//桌子序号，1 - 4
	int			m_CanHoldCardNum;			//能拥有的牌的数量,庄家15长

	BOOL		m_bReadytoPlay;				//准备开始
	PLAYER_STATUS	m_PlayerStatus;

	DeskBusi	* m_pDesk;						//玩家桌子ID
	int			m_DeskID;						//玩家桌子编号
	CARDTYPE m_HandCard[MAX_CARD_NUM_ID];	//手上的个数牌	.[0] 表示个数

	CARDTYPE m_DeskCard[MAX_CARD_NUM_ID];	//桌面的牌	.[0] 表示个数



	CARDTYPE m_Chi[5];
	int		 m_ChiNum;

	CARDTYPE m_Kan[5];
	int		 m_KanNum;

	CARDTYPE m_She[3];		//跑和
	int		 m_SheNum;

	CARDTYPE m_Long[3];		//龙
	int		 m_LongNum;
};
