#include "StdAfx.h"
#include "CardPlayer.h"

CardPlayer::CardPlayer(void)
{
		m_CanHoldCardNum	=	NORMAL_CARD_NUM;
		m_bReadytoPlay		=	FALSE;
		memset(m_CardStr,0,sizeof(m_CardStr));
	    memset(m_PlayerName,0,sizeof(m_PlayerName));


}

CardPlayer::~CardPlayer(void)
{
}

void CardPlayer::SetPlayerID(int PlayerId)
{
		m_PlayerID	=	PlayerId;
}

void CardPlayer::SetDesk(DeskBusi*Desk){

	this->m_pDesk	=	Desk;

}

void CardPlayer::SetCard(CARDTYPE*Card,int CardNum){

	memcpy(m_HandCard,Card,sizeof(CARDTYPE)*CardNum);
	
	//for(int i=1;i< CardNum;i++){
	//		m_HandCard[i]=Card[i];
	//} 
}



//���һ����
void CardPlayer::ShowOneCard(CARDTYPE Card){
	if(m_HandCard[Card] > 0 ){

		 ReportStatus(Card);

	}
}

CARDTYPE* CardPlayer::GetCard(){ 
	return this->m_HandCard;	 
}

int CardPlayer::GetCanHoldCard(){ 
	return this->m_CanHoldCardNum;	 
}
		//������ץһ����
int  CardPlayer::GetOneCardFromDesk(CARDTYPE id){


	return 0;
}
		//���ϼ�ȡһ����
int  CardPlayer::GetOneCardFromPre(CARDTYPE id){

	return 0;
}




int  CardPlayer::ReportStatus(CARDTYPE id){		//����״̬

	return 0;

}









//�������name
void  CardPlayer::SetPlayerName(const char* PlayerName){
	
	memcpy(m_PlayerName,PlayerName,strlen(PlayerName));
}