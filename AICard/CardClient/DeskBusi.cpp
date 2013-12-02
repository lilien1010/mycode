#include "StdAfx.h"
#include "DeskBusi.h"

DeskBusi::DeskBusi(void)
{
		InitDesk();
		m_StartPlayerId = 0;
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
	m_StartPlayerId = 0;

}

//为num个玩家，分发牌
void DeskBusi::DistrubueCard(CARDTYPE **Card,int playernum){
	
	int pai = 0 ,;
	int NumInfo[MAX_PLAYER_NUM]={0};
	for (int k = 0 ; k < playernum ; k++)
	{
		srand((unsigned)time(0));

		for (  ; NumInfo[k] <= MAX_HAND_CARD_NUM ;)
		{ 
			pai	= rand()%MAX_CARD_NUM_ID;
		 
			if( m_DeskCard[pai]>0){
					Card[k][pai]++;
					NumInfo[k]++;
					m_DeskCard[pai]--;
			} 
			
		}
	}

}