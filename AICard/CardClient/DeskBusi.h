#pragma once
#include "CardBusi.h"
#include "CardPlayer.h"

 
#define MAX_PLAYER_NUM 4 

#define NORMAL_CARD_NUM 14
#define WINNER_CARD_NUM 15
//������״̬
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

//������Ӧÿ����ҵ�״̬


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

	int m_DeskID;				//��ǰ����ID

	int m_CurrentPlayerNum;

	int m_AllowPlayerNum;

	BOOL		m_bJoinable;			//�Ƿ��������

	CardPlayer	m_Player[MAX_PLAYER_NUM];
	
	BOOL		m_bSeatStatus[MAX_PLAYER_NUM];	//���Ϊ֮״̬���Ƿ��������

};
