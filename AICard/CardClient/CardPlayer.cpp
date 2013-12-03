#include "StdAfx.h"
#include "CardPlayer.h"

CardPlayer::CardPlayer(void)
{
		m_CanHoldCardNum	= NORMAL_CARD_NUM;
}

CardPlayer::~CardPlayer(void)
{
}


void CardPlayer::SetDesk(DeskBusi*Desk){
	
	this->m_pDesk	=	Desk;

}

void CardPlayer::SetCard(CARDTYPE*Card,int CardNum){

	//memcpy(m_HandCard,Card,sizeof(CARDTYPE)*CardNum);
	
	for(int i=1;i<=CardNum;i++){
			m_HandCard[i]=Card[i];
	} 
}



//打出一张牌
void CardPlayer::ShowOneCard(CARDTYPE Card){
	if(m_HandCard[Card] > 0 ){

		m_DeskCard->ReportStatus();

	}


}


		//从桌面抓一张牌
int  CardPlayer::GetOneCardFromDesk(CARDTYPE id){



}
		//从上家取一张牌
int  CardPlayer::GetOneCardFromPre(CARDTYPE id){


}




int  CardPlayer::ReportStatus(CARDTYPE id){		//报告状态
}









//设置玩家name
void  CardPlayer::SetPlayerName(char* PlayerName){
	
	memcpy(m_PlayerName,PlayerName,strlen(PlayerName));
}