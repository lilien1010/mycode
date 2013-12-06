#include "StdAfx.h"
#include "DeskBusi.h"

DeskBusi::DeskBusi(void)
{
		memset(m_infoList,0,LOG_MAX_DESCRIPTION_SIZE);
		m_CurrentPlayerNum	=	4;	
		//m_hWnd->unused		=	0;
		m_bJoinable			=	TRUE;
		m_AllowPlayerNum	=	0;
		m_Player[0].m_CanHoldCardNum	=	WINNER_CARD_NUM;	//���õ�һ���볡�����Ϊׯ��
		
		InitDesk(); 
		DistrubueCard(m_CurrentPlayerNum);


		for(int i = 0 ; i< m_CurrentPlayerNum ; i++){
			m_Player[i].m_PlayerNo= i;
			m_Player[i].m_DeskID=m_DeskID;
			m_bSeatStatus[i]	=	TRUE;
		}
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
	return 0;
}

//Ϊnum����ң��ַ���
void DeskBusi::DistrubueCard(int playernum){
	
	int pai = 0;
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


int DeskBusi::StartGame(){
	 Showinfo("��Ϸ��ʼ");
	for(int i = 0 ; i< m_CurrentPlayerNum ; i++){ 
			if(m_Player[i].m_bReadytoPlay==FALSE)
					return FALSE;
	}
	InitDesk();
	DistrubueCard(m_CurrentPlayerNum);
	return TRUE;

}


CardPlayer* DeskBusi::JoinDesk(int PlaerID,const char *PalerName){

	if(m_bJoinable == FALSE)
		return NULL;
	Showinfo("���:%s ID=%d ,��������Ϸ",PalerName,PlaerID);
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

	Showinfo("���:%s ID=%d ,λ�ñ��Ϊ �뿪����Ϸ��",Plaer->m_PlayerName,Plaer->m_PlayerID,Plaer->m_PlayerNo);
}


void DeskBusi::SetWinHandle(HWND handle){
	m_hWnd	=	handle;
}

void DeskBusi::Showinfo(const char * str,...){
	//memcpy(m_infoList,str,strlen(str));
 
 
	va_list argList;
	va_start(argList, str);
	vsnprintf(m_infoList,LOG_MAX_DESCRIPTION_SIZE, str, argList);
	va_end(argList); 

	::PostMessage(m_hWnd,WM_INFOLIST,NULL,(LPARAM)m_infoList);
}




