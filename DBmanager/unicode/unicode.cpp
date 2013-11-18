// unicode.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"


#include <math.h> 
#include <iostream>  
#include <string>
#include "windows.h" 

using namespace std;


long hex2dec(char * s){
	int L=strlen(s);
	char c;
	long re=0;
	while(c=s++[0]){
		if(c >='0' && c <='9'){
			c-=48;
		}else{
			c=c>'Z'? c-32:c; 
			c-='A'-10;	
		}
		re+= c*pow( (long double)16 ,(int)--L) ;
	}
	return re;
} 

string unescape(char * str){
	char* re =(char *)calloc( strlen(str) +1,1);
	char *_str;
	char * _re=re;
	char code[5]={0};
	WCHAR wc;
	int n;
	while(str){
		_str= strchr(str,'\\') ;
		if(!_str) break;
		if( n=_str-str ){
			memcpy(_re,str, n   );
			_re+=n;
		}
		strset(code,0);
		if(_str[1]=='u'){
			memcpy(code,_str+2,4);	
			str=_str+6;	
			wc=hex2dec(code);
			memset(code,0,5);	
			WideCharToMultiByte(CP_OEMCP,NULL, &wc,-1,(char*)code,2,NULL,FALSE);
			memcpy(_re,code,2);
			_re+=2;
		}else{
			memcpy(code,_str+1,2);
			str=_str+3;	
			_re[0]=hex2dec(code);
			_re++;	
		}
	}
	strcpy(_re,str);
	return re;
}

int main(int argc, char* argv[])
{
	char* str="\\u660e\\u5e74\\u5f00\\u59cb\\u5728\\u4e1c\\u4eac\\u5de5\\u4f5c\\u3088\\u308d\\u3057\\u304f\\u304a\\u9858\\u3044\\u3057\\u307e\\u3059";
	cout<<  unescape(str)  << endl;
	return 0;
}