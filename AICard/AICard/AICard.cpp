//
//  main.cpp
//  card
//
//  Created by admin on 13-11-19.
//  Copyright (c) 2013年 admin. All rights reserved.
//
//
#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;
#define MAKENODE (A,B,C)  ( A<<16 || B <<8 || C)

/*
#define NODE1 (N)  (0x0000000000001111b & N)
#define NODE2 (N)  (0x0000000011110000b & N)
#define NODE3 (N)  (0x0000111100000000b & N)
*/

#define CARDNUM    21
#define ZUHENUM    4
#define RELMAX     7
#define HOLDCARDNUM      15
#define NODEN (N,deep) (0x000F <<(( deep-1)*4))


//用来表示每一种牌和可以结合的拍的数组
char REL[CARDNUM ][RELMAX]={
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
    {3,12,13,14,17,20},
    {3,13,14,15},       //da 3
    {3,14,15,16},
    {3,15,16,17},       //da 5
    {3,16,17,18},
    {3,17,18,19,20},    //da 7
    {3,18,19,20},
    {2,19,20},
    {1,20}
};


//描述我的牌的情况的多叉树
typedef char CARDTYPE;

typedef struct Node{
   
    CARDTYPE val[ZUHENUM];
    vector<Node *> children;
    Node* parent;
    int score;
    int listScore;
    Node* bestChildren;
    int NodeType;           //1 为叶子节点
}CardTree;


typedef struct  paipai{
    int num;
    CARDTYPE pai[4];
}PAI;


typedef struct  paizu{
    PAI allpai[5];
    char sanpai[16];    //第一个字节记录sanpai数量
}PAIZU;


CardTree my_tree;
int g_TakenCard =   0;
//描述每个人手上的一张牌


int TakeShe(char *);
int TakeKan(char *);
int f0(Node *pNode,char * Card);
void showCardList(Node * pNode);
int SetNode(Node* pNode,int Counter,char* zuhe,char*Card);
int mulitArray2(char *Card,int startPos, Node * pNode );
void showCard(char*zuhe);
int CalScore(char*zuhe);
int SelectBest(Node *pNode);
void showBestCard(Node*pNode,char*my_card);


void showCard(char*zuhe){
    cout<<"Card token = ";
    for(int i = 0 ; zuhe[i] && i < 3 ;i++){
        cout<<(int)(zuhe[i])<<" ";//<=10?zuhe[i]+97:zuhe[i]+65
    }
    cout<<endl;
}

void ShowCardLeft(char*Card){
    cout<<"Card left = ";
    for(int i = 1 ; i < CARDNUM;i++){
        if(Card[i]) for(int k = 0 ;k<Card[i];k++)   cout<< i << " ";
    }
    cout<<endl;
}


int SetNode(Node* pNode,int Counter,char* zuhe,char*Card){
    if(g_TakenCard >= HOLDCARDNUM || g_TakenCard >= HOLDCARDNUM-1)
        return 0 ;
   
   
    Node * ptNode   = new Node;
    for (int i=0 ;i<Counter;i++) {
        ptNode->val[i]=zuhe[i];
    }
    g_TakenCard+=Counter;
    pNode->children.push_back(ptNode);
    pNode->NodeType = 0;            //设置父亲为非父亲节点
    ptNode->parent  = pNode;        //设置父亲节点
    ptNode->score  = CalScore(zuhe);//为该节点计算得分
    ptNode->bestChildren = 0;     //忽略最好子节点ID
    ptNode->NodeType = 1;           //默认为叶子节点
  //  showCard(zuhe);
  //  ShowCardLeft(Card);
  //cout<<"All num="<<g_TakenCard<<endl;
    if(g_TakenCard < 12)
        mulitArray2(Card,1,ptNode);
   
    if( g_TakenCard >= HOLDCARDNUM-1)
        return 0 ;

/*
    for (int k=0; k<Counter; k++) {
        Card[zuhe[k]]++;
    }

    cout<<"card return after";
    ShowCardLeft(Card);
*/    g_TakenCard-=Counter;
    return 1;
}


int mulitArray2(char *Card,int startPos, Node * pNode ){
   
   
    char TokenCardNo[ZUHENUM]   =   {0};
    int Counter                 =   0;
    int NextRelNo               =   0;
    int SecondTaken             =   0;
    int ThirdTaken              =   0;
   
    for(int i = startPos ; i < CARDNUM;i++){

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

 
char my_card[21]={0,2,2,1,0,2,0,0,2,0,1,1,1,0,1,0,0,0,1,0,1};
char my_card2[21]={0,2,2,1,0,2,0,0,2,0,1,1,1,0,1,0,0,0,1,0,1};

int main(int argc, const char * argv[])
{
    Node * Parent   =   new Node;
   
   
    Parent->val[0]  =   0;
    Parent->score  =   -100;
    Parent->parent  =   NULL;
    Parent->NodeType=   0;
    mulitArray2(my_card,1,Parent);
   
   
    vector<PAIZU> m_paizulist;
    int max = SelectBest(Parent);
    showBestCard(Parent,my_card2);

    return 0;
}

int SelectBest(Node *pNode){
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


void showBestCard(Node*pNode,char*my_card){
    if(pNode  ){
        if(pNode->parent)
			printf( "A= %d, B= %d  C= %d \n",(pNode->val[0]), (pNode ->val[1]),(pNode->val[2]));
			my_card[pNode->val[0]]--;
			my_card[pNode->val[1]]--;
			my_card[pNode->val[2]]--;
		showBestCard(pNode->bestChildren,my_card);
    }else
	{
		printf( "  card left ="  );	
		for(int i = 1 ; i <CARDNUM ; i++){

			  if(my_card[i]) for(int k = 0 ;k<my_card[i];k++)   cout<< i << ", ";
		}
	}
}




void showCardList(Node * pNode){   
    printf( "A= %d, B= %d  C= %d \n",(pNode->val[0]), (pNode ->val[1]),(pNode->val[2]));
   
    for (int k = 0; k<pNode->children.size(); k++) {
        showCardList( pNode->children.at(k));
    }
   
    printf( " showing another card list\n" );
}


//计算三个牌的得分
int CalScore(char*zuhe){

    int k1 = zuhe[1] - zuhe[0];
    int k2 = zuhe[2] - zuhe[1];
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
int TakeShe(char * CARD){
    for (int i = 1; i<=CARDNUM; i++) {
        if(CARD [i]>=4){
            CARD[i]=0;
            return i;
        }
    }
}



//去掉坎
int TakeKan(char * CARD){
   
   
    for (int i = 1; i<=CARDNUM; i++) {
        if(CARD [i]==3){
            CARD[i]=0;
            return i;
        }
    }
}