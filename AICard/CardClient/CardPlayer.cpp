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



//���һ����
void CardPlayer::ShowOneCard(CARDTYPE Card){
	if(m_HandCard[Card] > 0 ){

		m_DeskCard->ReportStatus();

	}


}


		//������ץһ����
int  CardPlayer::GetOneCardFromDesk(CARDTYPE id){



}
		//���ϼ�ȡһ����
int  CardPlayer::GetOneCardFromPre(CARDTYPE id){


}




int  CardPlayer::ReportStatus(CARDTYPE id){		//����״̬
}









//�������name
void  CardPlayer::SetPlayerName(char* PlayerName){
	
	memcpy(m_PlayerName,PlayerName,strlen(PlayerName));
}