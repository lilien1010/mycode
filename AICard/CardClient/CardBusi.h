#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)  {if(x){delete x;x=NULL;}}
#endif

#define  MAX_CARD_NUM		20
#define  MAX_CARD_NUM_ID	21
#define  MAX_HAND_CARD_NUM   14
#define ZUHENUM    4
#define RELMAX     7
#define HOLDCARDNUM      15 
#define MAX_CARD_NUM     4
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
//�����ҵ��Ƶ�����Ķ����
typedef char CARDTYPE;

typedef struct Node{

	CARDTYPE val[ZUHENUM];
	vector<Node *> children;
	Node* parent;
	int score;
	int listScore;
	Node* bestChildren;
	int NodeType;           //1 ΪҶ�ӽڵ�
}CardTree;




class CardBusi
{
public:
	CardBusi(void);
	

	int start();
	void GetAllCard(string&);
	void RandCard();
	int GetOrderedCard(CARDTYPE *out,CARDTYPE*sanpai,int deep=0,Node*pNode=NULL);
	void TakeShe(CARDTYPE *Card);
	void TakeKan(CARDTYPE *Card);
	int SetNode(Node* pNode,int Counter,CARDTYPE* zuhe,CARDTYPE*Card);
	int mulitArray(CARDTYPE *Card,int startPos, Node * pNode );
	void showCard(CARDTYPE*zuhe);
	int CalScore(CARDTYPE*zuhe);
	int  SelectBest(Node *pNode);
	void showBestCard(Node*pNode,CARDTYPE*my_card);
public:
	~CardBusi(void);
private:
	void DeleteTree(Node*pNode);
public:
	CARDTYPE m_MyCard[CARDNUM];
	int m_TakenCard;
	CARDTYPE	m_She[3];	//
	CARDTYPE	m_Kan[5];
	 Node * m_CardParent;
	int m_Shenum;
	int m_Kannum;

};
