#pragma once

#include "CardBusi.h"
#include "DeskBusi.h"

//������״̬
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
	
	void SetCard(CARDTYPE*Card,int CardNum);			//������ҵ���

	void SetPlayerID(int PlayerId);					//�������ID

	void SetPlayerName(char* name);					//�������name
	
	void SetDesk(DeskBusi*);
	
	void ShowOneCard();							//��һ����

	int GetOneCardFromDesk(CARDTYPE id);		//������ץһ����


	int GetOneCardFromPre(CARDTYPE id);		//���ϼ�ȡһ����
	
	int ReportStatus();		//����״̬
 
	int CardChi(CARDTYPE);					//����
	
	int CardPen(CARDTYPE);					//����

	int CardSao(CARDTYPE);					//ɨ�ƣ�����

	int CardPao(CARDTYPE);					//���ƣ�����
	
	int CardTiLong(CARDTYPE);				//�������ܺ� ����ͬʱ����

	int CanHu(CARDTYPE);					//�ܷ���ƣ�

	int CanChi(CARDTYPE);					//�ܷ����
	

 	char		m_PlayerName[128];			// �������
	int			m_IsWinner;					//�Ƿ�����һ�̵�Ӯ�ң��ǵĻ�15����
	int			m_PlayerID;					//���ID ���ݿ�
	int			m_PlayerNo;					//������ţ�1 - 4
	int			m_CanHoldCardNum;			//��ӵ�е��Ƶ�����,ׯ��15��

	BOOL		m_bReadytoPlay;				//׼����ʼ
	PLAYER_STATUS	m_PlayerStatus;

	DeskBusi	* m_pDesk;						//�������ID
	int			m_DeskID;						//������ӱ��
	CARDTYPE m_HandCard[MAX_CARD_NUM_ID];	//���ϵĸ�����	.[0] ��ʾ����

	CARDTYPE m_DeskCard[MAX_CARD_NUM_ID];	//�������	.[0] ��ʾ����



	CARDTYPE m_Chi[5];
	int		 m_ChiNum;

	CARDTYPE m_Kan[5];
	int		 m_KanNum;

	CARDTYPE m_She[3];		//�ܺ�
	int		 m_SheNum;

	CARDTYPE m_Long[3];		//��
	int		 m_LongNum;
};
