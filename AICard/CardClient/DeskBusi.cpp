#include "StdAfx.h"
#include "DeskBusi.h"

DeskBusi::DeskBusi(void)
{
		InitDesk(); 
		m_CurrentPlayerNum	=	4;
		m_bJoinable			=	TRUE;
		m_AllowPlayerNum	=	0;
		m_Player[0].m_CanHoldCardNum	=	WINNER_CARD_NUM;	//设置第一个入场的玩家为庄家
		
		for(int i = 0 ; i< m_CurrentPlayerNum ; i++){
			m_Player[i].m_PlayerNo= i;
			m_Player[i].m_DeskID=m_DeskID;
			m_bSeatStatus[i]	=	TRUE;
		}
}

DeskBusi::~DeskBusi(void)
{

}

//初始化牌桌
int DeskBusi::InitDesk(){
	m_DeskCard[0]=0;
	for (int i =1 ; i <= MAX_CARD_NUM ; i++)
	{
			m_DeskCard[i] =  4;
	}
	return 0;
}

//为num个玩家，分发牌
void DeskBusi::DistrubueCard(int playernum){
	
	int pai = 0;
	int TakeCardNum=0;		//记录玩家牌的数量
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


int DeskBusi::StartGame(){

	for(int i = 0 ; i< m_CurrentPlayerNum ; i++){

			if(m_Player[i].m_bReadytoPlay==FALSE)
					return FALSE;
	}
	return TRUE;

}


CardPlayer* DeskBusi::JoinDesk(int PlaerID,char*PalerName){
	if(m_bJoinable == FALSE)	return NULL;
	for(int i = 0 ; i< m_CurrentPlayerNum ; i++){ 
		if(m_bSeatStatus[i]	==	TRUE){
 
			m_Player[m_CurrentPlayerNum].SetPlayerID(PlaerID);

			m_Player[m_CurrentPlayerNum].SetPlayerName(PalerName);
			if(m_CurrentPlayerNum + 1 >= m_AllowPlayerNum)
				m_bJoinable	=	FALSE;
			return &m_Player[m_CurrentPlayerNum++];

		}
	}

	return NULL;
	
}

void DeskBusi::LevelDesk(CardPlayer* Plaer){
	
	m_bSeatStatus[Plaer->m_PlayerNo]	=	TRUE;
	m_CurrentPlayerNum--;
	m_bJoinable	=	TRUE;

}
