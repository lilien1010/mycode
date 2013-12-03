#include "StdAfx.h"
#include "DeskBusi.h"

DeskBusi::DeskBusi(void)
{
		InitDesk(); 
		m_CurrentPlayerNum	=	4;

		m_AllowPlayerNum	=	0;
		m_Player[0].m_CanHoldCardNum	=	WINNER_CARD_NUM;	//���õ�һ���볡�����Ϊׯ��
}

DeskBusi::~DeskBusi(void)
{

}

//��ʼ������
int DeskBusi::InitDesk(){
	m_DeskCard[0]=0;
	for (int i =1 ; i <= MAX_CARD_NUM ; i++)
	{
			m_DeskCard[i] =  4;
	}
}

//Ϊnum����ң��ַ���
void DeskBusi::DistrubueCard(int playernum){
	
	int pai = 0 ,;
	int TakeCardNum=0;		//��¼����Ƶ�����
	CARDTYPE tem_Card[MAX_CARD_NUM_ID]={0};
	for (int k = 0 ; k < playernum ; k++)
	{
		srand((unsigned)time(0));
		TakeCardNum=0;
		for (  ; TakeCardNum <  m_Player[k].m_CanHoldCardNum ;)
		{ 
			pai	= rand()%MAX_CARD_NUM_ID;
		 
			if( m_DeskCard[pai]>0){
					tem_Card[pai]++;
					TakeCardNum++;
					m_DeskCard[pai]--;
			} 
			
		}
		m_Player[k].SetCard(tem_Card, m_Player[k].m_CanHoldCardNum);
		m_Player[k].SetDesk(this);
	}

}