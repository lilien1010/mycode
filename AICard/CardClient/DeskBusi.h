#pragma once





#ifndef __DESKBUSI_H__ 
#define __DESKBUSI_H__ 

#include	"CardClientDlg.h"

#include "CardBusi.h"
 
#include "CardPlayer.h"

#define LOG_MAX_DESCRIPTION_SIZE 1024

//������״̬
enum DESK_STATUS{
	WAIT_HU		=	0,		
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
class CardPlayer;

class DeskBusi
{	

public:
	DeskBusi(void) ;
public:
	~DeskBusi(void);

public:
	void DistrubueCard(int playernum);

	void SetWinHandle(HWND handle);
	void Showinfo(const char * str,...);
	int InitDesk();

	CardPlayer* JoinDesk(int PlaerID,const char* PalerName);
	
	void LevelDesk(CardPlayer * Player);

	int StartGame();
public:
	CARDTYPE m_DeskCard[MAX_CARD_NUM_ID];

	char m_infoList[LOG_MAX_DESCRIPTION_SIZE];
		
	HWND m_hWnd;

	int m_StartPlayerId;		

	int m_DeskID;				//��ǰ����ID

	int m_AllowedPlayerNum;		//���������������

	int m_EmptySeatNum;		//��λ������

	BOOL		m_bJoinable;			//�Ƿ��������

 	CardPlayer	m_Player[MAX_PLAYER_NUM];
	
	BOOL		m_bSeatStatus[MAX_PLAYER_NUM];	//���Ϊ֮״̬���Ƿ��������

};


#endif