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
	IDLE
};

typedef struct user_status{
	DESK_STATUS		status;
	int				player;
};

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

public:
	CARDTYPE m_DeskCard[TOTAL_CARD_NUM];

	int m_StartPlayerId;

	int m_DeskID;

	int m_CurrentPlayerNum;

	int m_AllowPlayerNum;

	CardPlayer m_Player[MAX_PLAYER_NUM];
};
