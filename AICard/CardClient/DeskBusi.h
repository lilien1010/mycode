#pragma once
#include "CardBusi.h"
#include "CardPlayer.h"

 
#define MAX_PLAYER_NUM 4 

#define NORMAL_CARD_NUM 14
#define WINNER_CARD_NUM 15
//牌桌的状态
enum DESK_STATUS{
	WAIT_HU=0,		
	WAIT_PAO,
	WAIT_PEN,
	WAIT_CHI,
	WAIT_SHOWCARD,
	WAIT_TAKECARD,
	WAIT_IDLE
};

typedef struct user_status{
	DESK_STATUS		status;
	int				player;
}USER_STATUS;

//牌桌对应每个玩家的状态


class DeskBusi
{	

public:
	DeskBusi(void);
public:
	~DeskBusi(void);

public:
	void DistrubueCard(int playernum);
 
	int InitDesk();

	CardPlayer* JoinDesk(int PlaerID,char* PalerName);
	void LevelDesk(CardPlayer* Plaer);

	int StartGame();
public:
	CARDTYPE m_DeskCard[MAX_CARD_NUM_ID];

	int m_StartPlayerId;		

	int m_DeskID;				//当前桌子ID

	int m_CurrentPlayerNum;

	int m_AllowPlayerNum;

	BOOL		m_bJoinable;			//是否允许加入

	CardPlayer	m_Player[MAX_PLAYER_NUM];
	
	BOOL		m_bSeatStatus[MAX_PLAYER_NUM];	//玩家为之状态，是否可以入座

};
