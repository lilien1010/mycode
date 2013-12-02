#pragma once
#include "CardBusi.h"

#define PLAYERNUM 4
#define MAX_PLAYER_NUM 4

class DeskBusi
{	

public:
	DeskBusi(void);
public:
	~DeskBusi(void);

public:
	void DistrubueCard(CARDTYPE **Card,int playernum);
 
	int InitDesk();

public:
	CARDTYPE m_DeskCard[MAX_CARD_NUM_ID];

	int m_StartPlayerId;

	int m_Player[PLAYERNUM];
};
