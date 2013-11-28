#include "StdAfx.h"
#include "CardBusi.h"
#include <sstream>

//用来表示每一种牌和可以结合的拍的数组
char REL[MAX_CARD_NUM_ID][RELMAX]={
	{0},
	{4,1,2,3,11},       //xiao 1
	{6,2,3,4,7,10,12},  //xiao 2
	{4,3,4,5,13},       //xiao 3
	{4,4,5,6,14},       //xiao 4
	{4,5,6,7,15},       //xiao 5
	{4,6,7,8,16},       //xiao 6
	{5,7,8,9,10,17},    //xiao 7
	{4,8,9,10,18},      //xiao 8
	{3,9,10,19},        //xiao 9
	{2,10,20},
	{3,11,12,13},       //da 1
	{5,12,13,14,17,20},
	{3,13,14,15},       //da 3
	{3,14,15,16},
	{3,15,16,17},       //da 5
	{3,16,17,18},
	{4,17,18,19,20},    //da 7
	{3,18,19,20},
	{2,19,20},
	{1,20}
};
CardBusi::CardBusi(void)
{
		m_TakenCard	=0;
		m_Kannum	=0;
		m_Shenum	=0;
		m_CardParent   =   NULL;	
}

CardBusi::~CardBusi(void)
{
	DeleteTree(m_CardParent);
}	

int CardBusi::start()
{ 
	RandCard();
	DeleteTree(m_CardParent);
	TakeShe(m_MyCard);
	TakeKan(m_MyCard);
	m_CardParent   =   new Node;
	m_CardParent->bestChildren = 0;
	m_CardParent->parent = NULL;
	mulitArray(m_MyCard,1,m_CardParent);
	SelectBest(m_CardParent); 
	//memcpy(card2,m_MyCard,CARDNUM*sizeof(CARDTYPE));
	//showBestCard(m_CardParent,m_MyCard);
	return 1;
}

void CardBusi::GetAllCard(string&str){
	
	ostringstream ostr; 
	 for(int i = 1 ; i <=MAX_CARD_NUM ; i++){
		if(m_MyCard[i])
			ostr<<i<<","<<endl; 
	 }

	str = ostr.str(); 
}

int CardBusi::GetOrderedCard(CARDTYPE *out,CARDTYPE*leftcard,int deep,Node*pNode)
{
 
	if(pNode==NULL && deep==0){ 
		pNode	=	m_CardParent;
		memset(out,0,sizeof(CARDTYPE)*(MAX_CARD_NUM));
		memset(leftcard,0,sizeof(CARDTYPE)*(MAX_CARD_NUM));
	}
	if(pNode ){
		if(pNode->parent){
			 
			m_MyCard[pNode->val[0]]--;
			m_MyCard[pNode->val[1]]--;
			m_MyCard[pNode->val[2]]--; 
			out[deep++]	=	pNode->val[0];
			out[deep++]	=	pNode->val[1];
			out[deep++]	=	pNode->val[2];
		}
		GetOrderedCard(out,leftcard,deep,pNode->bestChildren);
	}else{ 
		for(int i = 1 ; i <= MAX_CARD_NUM ; i++){

			if(m_MyCard[i]){
				for(int k = 0,start=leftcard[0] ;k<m_MyCard[i];k++) 
				{
					 leftcard[start+k+1]=i;
				}
				leftcard[0] += m_MyCard[i];
			}
		}
	}
	return deep;

}

void CardBusi::RandCard()
{	
	memset(m_MyCard,0,sizeof(CARDTYPE)*(MAX_CARD_NUM+1));
	srand((unsigned)time(0));
	for(int i = 1 ; i < 15 ; i++){
		
		int pai	= rand()%(MAX_CARD_NUM_ID);
		if(pai==0) pai++;
		if(m_MyCard[pai]<=MAX_CARD_NUM)  m_MyCard[pai]++;
		else srand((unsigned)time(0));
	}
	
}

int CardBusi::SetNode(Node* pNode,int Counter,char* zuhe,char*Card){
    if(m_TakenCard >= HOLDCARDNUM & m_TakenCard >= HOLDCARDNUM-1)
        return 0 ;
   
   
    Node * ptNode   = new Node;
    for (int i=0 ;i<Counter;i++) {
        ptNode->val[i]=zuhe[i];
    }
    m_TakenCard+=Counter;
    pNode->children.push_back(ptNode);
    pNode->NodeType = 0;             //设置父亲为非父亲节点
    ptNode->parent  = pNode;         //设置父亲节点
    ptNode->score  = CalScore(zuhe); //为该节点计算得分
    ptNode->bestChildren = 0;        //忽略最好子节点ID
    ptNode->NodeType = 1;            //默认为叶子节点
 
    if(m_TakenCard < 12)
        mulitArray(Card,1,ptNode);
   
    if( m_TakenCard >= HOLDCARDNUM )
        return 0 ;
     m_TakenCard-=Counter;
    return 1;
}


int CardBusi::mulitArray(CARDTYPE *Card,int startPos, Node * pNode ){
   
   
    char TokenCardNo[ZUHENUM]   =   {0};
    int Counter                 =   0;
    int NextRelNo               =   0;
    int SecondTaken             =   0;
    int ThirdTaken              =   0;
   
    for(int i = startPos ; i <= MAX_CARD_NUM;i++){

        if(0 == Card[i]) continue;
        Counter            =   0;
        ThirdTaken=SecondTaken = 0;
        memset(TokenCardNo, 0, sizeof(TokenCardNo));
        for (int k1  =   1; k1 <= REL[i][0]  ;k1++) {
            if(0 == Card[REL[i][k1]]) continue;
            SecondTaken = TokenCardNo[Counter]=REL[i][k1];
            Counter ++;
            Card[REL[i][k1]]--;
           
            // SetNode(pNode,Counter,TokenCardNo,Card);
            for (int k2  =   1; k2 <= REL[SecondTaken][0] ;k2++) {
               
                if(0 == Card[REL[SecondTaken][k2]]) continue;
               
                ThirdTaken=TokenCardNo[Counter]=REL[SecondTaken][k2];
                Counter ++;
                Card[REL[SecondTaken][k2]]--;
                //SetNode(pNode,Counter,TokenCardNo,Card);
               
               
                for (int k3  =   1; k3 <= REL[ThirdTaken][0] ;k3++) {
                    if( 0 == Card[REL[ThirdTaken][k3]]) continue;
                    TokenCardNo[Counter]=REL[ThirdTaken][k3];
                    Counter ++;
                    Card[REL[ThirdTaken][k3]]--;
                    SetNode(pNode,Counter,TokenCardNo,Card);
                    //recoverCard(Counter,TokenCardNo,Card);
                    Card[REL[ThirdTaken][k3]]++;
                    Counter--;
                   
                }
                 Card[REL[SecondTaken][k2]]++;
               // recoverCard(Counter,TokenCardNo,Card);
                Counter--;
               
               
            }
            Card[REL[i][k1]]++;
            // recoverCard(Counter,TokenCardNo,Card);
            Counter--;
        }
       
    }
   
    return 0;
   
}

void CardBusi::DeleteTree(Node*pNode){
	if(pNode){
		size_t size = pNode->children.size();
		for (int k = 0; k < size; k++) {

			DeleteTree(pNode->children.at(k));
			
		}
		SAFE_DELETE(pNode);
	}

}


int CardBusi::SelectBest(Node *pNode){

	if(!pNode)	return 0;
	unsigned long size =  pNode->children.size();
	int max  =  0 ;
	int max_id = 0;

	for (int k = 0; k < size; k++) {

		if(pNode->children.at(k)->NodeType == 1){
			//
			if(pNode->children.at(k)->score > max){
				max = pNode->children.at(k)->score ;
				max_id = k;
			}
		}else{
			int next= SelectBest( pNode->children.at(k));
			if(max<   next){
				max = next;
				max_id = k;
			}
		}
	} 
	pNode->bestChildren = pNode->children.at(max_id);
	return  max+pNode->score;
}


void CardBusi::showBestCard(Node*pNode,CARDTYPE *my_card){
	string str1="";
	char str[256]={0};
	if(pNode  ){
		if(pNode->parent){
			//sprintf( str,"A= %d, B= %d  C= %d \n",(pNode->val[0]), (pNode ->val[1]),(pNode->val[2]));
			str1	=	str;
			my_card[pNode->val[0]]--;
			my_card[pNode->val[1]]--;
			my_card[pNode->val[2]]--;
			
			
		}
		showBestCard(pNode->bestChildren,my_card);
	}else
	{
		//sprintf( str,"  card left ="  );	
		str1	=	str;
		for(int i = 1 ; i <= MAX_CARD_NUM ; i++){

			if(my_card[i]){
				for(int k = 0 ;k<my_card[i];k++) 
					itoa(i+1,str,10);

					str1 += str;
			}
		}
	}
	AfxMessageBox(str1.c_str(),MB_OK,0);
}




//计算三个牌的得分
// A= 5, B= 6  C= 7 
// A= 14, B= 15  C= 16 
// A= 14, B= 15  C= 16 
// A= 17, B= 19  C= 19 
// left card is:   12 ,  20 ,
// 20 ,
int CardBusi::CalScore(CARDTYPE*zuhe){

	int k1 = abs(zuhe[1] - zuhe[0]);
	int k2 = abs(zuhe[2] - zuhe[1]);
	//顺子
	if (k1 == k2) {

		if(k1 ==1)          //1 2 3
			return  20;
		else if(k1 == 2)    //2 4 6
			return 10;
	}


	if(k1 == 5 && k2 == 3)    //2 7 10
		return 20;

	// 6 6 ^6 , 6 ^6  ^6
	if ( (k1 == 0 && k2 == 10) || (k1 == 0 && k2 == 10)) {
		return 20;
	}

	if(k1 == 0 || k2 == 0 )
		return 15;


	return 0;

}

//去掉蛇
void CardBusi::TakeShe(CARDTYPE * CARD){
	for (int i = 1,k=0; i< MAX_CARD_NUM; i++) {
		if(CARD [i]>=MAX_CARD_NUM){
			CARD[i]=0;
			m_Shenum++;
			m_TakenCard+=MAX_CARD_NUM;
			m_She[k++]=i;
		}
	}
}



//去掉坎
void CardBusi::TakeKan(CARDTYPE * CARD){


	for (int i=1,k=0; i<= MAX_CARD_NUM; i++) {
		if(CARD [i]==3){
			CARD[i]=0;
			CARD[i]=0;
			m_TakenCard+=3;
			m_Kannum++;
			m_Kan[k++]=i;
		}
	}
}