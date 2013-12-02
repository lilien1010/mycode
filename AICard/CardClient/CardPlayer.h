#pragma once

#include "CardBusi.h"
#include "DeskBusi.h"



typedef struct  pai{
	int num;
	int type;
	CARDTYPE pai[4];
}PAI;




class CardPlayer
{
public:
	CardPlayer(void);
public:
	~CardPlayer(void);

	SetCard(CARDTYPE*Card,int CardNum);			//������ҵ���

	SetPlayerID(int PlayerId);					//�������ID

	SetPlayerName(char* name);					//�������name
	
	int GetOneCardFromDesk(CARDTYPE id);		//������ץһ����


	int GetOneCardFromPre(CARDTYPE id);		//���ϼ�ȡһ����
	


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

	DeskBusi * m_DeskID;					//�������ID

	CARDTYPE m_HandCard[MAX_CARD_NUM_ID];	//���ϵĸ�����	.[0] ��ʾ����

	CARDTYPE m_DeskCard[MAX_CARD_NUM_ID];	//�������	.[0] ��ʾ����



	CARDTYPE m_Chi[5];
	int		 m_ChiNum;

	CARDTYPE m_Kan[5];
	int		 m_KanNum;

	CARDTYPE m_She[3];		//�ܺ�
	int		 m_SheNum;

	CARDTYPE m_Long[3];		//��
	int		 m_SheNum;
};
