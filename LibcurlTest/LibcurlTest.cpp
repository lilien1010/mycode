#include "stdafx.h"
 #include<stdio.h>
#include <iostream> 
#include "curl/curl.h" 
 #include <string>

typedef struct downfile {
	int  len;
	char * buffer;
	FILE *fp;
}DownFile;

#pragma comment( lib,"libcurl_imp.lib" ) 
#define MAXHTML_SIZE 20480
using namespace std;
FILE *fp,*fp_jpg ;

typedef   size_t  (* DownLoadWriteCallBack)(void *, size_t , size_t , void *)  ;

BOOL PostData (CURL * curl,const char* url,const char * postdata ,  DownLoadWriteCallBack ,void*databack );

string get_token(string * webhtml,string firststr,string endstr){
	int id1 = 0,id2=0;
 
	id1 = webhtml->find(firststr);
	if(id1< 0 ) return 0;
	int firststr_len = firststr.length();

	id2 = webhtml->find(endstr,id1+firststr_len+1);
	if(id2< 0 ) return 0;

	return webhtml->substr(id1+firststr_len,id2-id1-firststr_len);
}

string g_webhtml = "";
string g_session = "";
string g_otn = "";
string g_outcookie = "";
int	 g_openhead = 0,g_openzip=0,g_savecookie=0;

int HTML_SIZE = 0;

size_t handle_html (void * ptr, size_t size, size_t nmemb , void * stream) 
{
       g_webhtml.append((char*)ptr);

        return size*nmemb;
}

size_t handle_login (void * ptr, size_t size, size_t nmemb , void * stream) 
{
	g_webhtml.append((char*)ptr);
	fwrite(ptr,size,nmemb ,(FILE*)stream);
	return size*nmemb;
}

int time_s = 0;
int filesize_jpg=0,write_size =0;
size_t save_yanzhengma (void * ptr, size_t size, size_t nmemb , void * stream) 
{
    DownFile   *df = (DownFile*)stream;
	//write_size+=fwrite(ptr ,size,nmemb,df->fp);
	memcpy(&(df->buffer[df->len]),ptr,size*nmemb);
	df->len+=size *nmemb;

	return size *nmemb;
}




int CheckRandCode(CURL *curl,const char * postdata);

int _tmain (int argc, _TCHAR * argv[])
{
         CURL *curl ;
         CURLcode res ;
        
		 DownFile   df;
		 df.buffer = new char[MAXHTML_SIZE];
		 df.len = 0;
		 
         int start =  GetTickCount();
         cout<<" 开始初始化 curl"<<endl ;
         curl = curl_easy_init ();
         if( !curl ) {
                 cout<<"curl 初始化失败 "<<endl ;

        }


		 
         g_openhead = 0;
         cout<<"curl 初始化成功 "<<endl ;
		 char File_url[256]="https://kyfw.12306.cn/otn/passcodeNew/getPassCodeNew?module=passenger&amp;rand=randp";
		 while(1){

			 g_webhtml.clear();
			 filesize_jpg=0,write_size =0;
			 memset(df.buffer,0,MAXHTML_SIZE);
			 df.len = 0;
			 if((fp =fopen( "baidu.txt","w" ))==NULL)
			 {
				 curl_easy_cleanup(curl );
				 exit(1);
			 }
			 if(( df.fp =fopen( "验证码.jpg","wb" ))==NULL)
			 {
				 curl_easy_cleanup(curl );
				 exit(1);

			 }
			 g_savecookie = 1;
			 g_openhead = 1;
			 g_openzip = 1;
			 //登陆页面获取session，还有验证码
			 PostData(curl
					, "https://kyfw.12306.cn/otn/login/init"
					, NULL
					,handle_html ,NULL);

			 fwrite(g_webhtml.c_str(),1,g_webhtml.length(),fp);
			g_openhead = 0;
			g_openzip = 0;
			 g_savecookie = 0;
 
			randcode:
			 cout<<" ======================下载验证码======================" <<endl;
			
			 //下载验证码
			 PostData(curl
				 ,"https://kyfw.12306.cn/otn/passcodeNew/getPassCodeNew?module=login&rand=sjrand"
				 ,NULL
				 ,save_yanzhengma ,(char*)&df);
		 
			 int ret = fwrite(df.buffer,1,df.len,df.fp);

				fclose(fp);
				
				fclose(df.fp);
	         
			g_webhtml.clear();

			cout<<"输入验证码:"<<endl;

			string username,passwd,code;
			username="lilien1010";
			passwd="qq331838389";
			cin>>code;
		
			
			string rand_code = ""; 
			rand_code.append("randCode=");
			rand_code.append(code);
			rand_code.append("&rand=sjrand");
			if(FALSE == CheckRandCode(curl,rand_code.c_str())){ 
					goto  randcode;
			}
 

			cout<<" =====================登录检查======================" <<endl;
			g_webhtml.clear();
			cout<<"你的输入是 username= "<<username<<" passwd= "<<passwd<<" code= "<<code<<endl;
			string post_data="";
			post_data.append("loginUserDTO.user_name=");
			post_data.append(username);
			post_data.append("&userDTO.password=");
			post_data.append(passwd);
			post_data.append("&randCode=");
			post_data.append(code); 
			FILE * logfp = fopen("登录返回.txt","w");
			//登录
			PostData(curl
					,"https://kyfw.12306.cn/otn/login/loginAysnSuggest"
					,post_data.c_str()
					,handle_login ,logfp);  
			cout<<" 登录检查------------ "<<endl;
			if(g_webhtml.find("\"loginCheck\":\"Y\"")>0)
			{
				cout<<"------------登录成功------------"<<endl;
			}else{
				cout<<"------------登录成功失败------------"<<g_webhtml<<endl;
				goto  randcode;
			}

			fclose(logfp);
			g_webhtml.clear();

			cout<<" =====================获取个人信息======================" <<endl;

			FILE * userfp = fopen("获取个人信息.txt","w");

			//获取个人信息
			PostData(curl
					,"https://kyfw.12306.cn/otn/confirmPassenger/getPassengerDTOs"
					,NULL
					,handle_login ,userfp);  
			cout<<" 获取个人信息------------ "<<endl;

			if(g_webhtml.find("\"isExist\":true")>0)
			{
				cout<<"------------获取成功------------"<<endl;
			}else{
				cout<<"------------获取成功失败------------"<<g_webhtml<<endl; 
			}
			fclose(userfp);
   
			g_webhtml.clear();



		
			cout<<" =====================查询列车======================" <<endl;

			FILE * chaxunfp = fopen("查询列车.txt","w");
			curl_easy_setopt(curl, CURLOPT_HTTPGET, "?test=string");
			//查询列车
			PostData(curl
				,"https://kyfw.12306.cn/otn/leftTicket/query?leftTicketDTO.train_date=2014-01-08&leftTicketDTO.from_station=SZQ&leftTicketDTO.to_station=HYQ&purpose_codes=ADULT"
				,NULL
				,handle_login ,chaxunfp);  
			cout<<" 查询列车------------ "<<endl;

			if(g_webhtml.find("\"httpstatus\":200")>0)
			{
				cout<<"------------查询列车成功------------"<<endl;
			}else{
				cout<<"-----------查询列车失败------------"<<g_webhtml<<endl; 
			}
			fclose(chaxunfp); 
			g_webhtml.clear();


			cout<<" ====================订单提交主页====================" <<endl;
			
			g_openzip = 1;
			FILE * get_order_page = fopen("下订单页面.txt","w"); 
			//查询列车
			PostData(curl
				,"https://kyfw.12306.cn/otn/confirmPassenger/initDc"
				,"_json_att=", handle_login ,get_order_page);  
			cout<<" 查询列车------------ "<<endl;

			if(g_webhtml.find("globalRepeatSubmitToken")>0)
			{
				cout<<"------------下订单页成功------------"<<endl;
			}else{
				cout<<"-----------下订单页失败------------"<<g_webhtml<<endl; 
			}
			string REPEAT_SUBMIT_TOKEN = get_token(&g_webhtml,"globalRepeatSubmitToken = '","';");
		 
			fclose(get_order_page); 
			g_openzip = 0;

			g_webhtml.clear();


			
			cout<<" ====================下载提交订单验证码====================" <<endl;

			df.fp = fopen("提交订单验证码.jpg","wb");
			memset(df.buffer,0,MAXHTML_SIZE);
			df.len = 0;
			
			curl_easy_setopt(curl, CURLOPT_HTTPGET, "?module=passenger&rand=randp");
			//查询列车
			PostData(curl
				,"https://kyfw.12306.cn/otn/passcodeNew/getPassCodeNew?module=passenger&rand=randp"
				,NULL
				, save_yanzhengma ,&df);  
			cout<<" 提交订单 ------------ "<<g_webhtml<<endl;

			fwrite(df.buffer,1,df.len,df.fp);		
			fclose(df.fp); 
			cout<<" 请输入验证码 "<<endl;	
			
  
			cin>>code;
 
			rand_code = ""; 
			rand_code.append("randCode=");
			rand_code.append(code);
			rand_code.append("&rand=randp");
			rand_code.append("&REPEAT_SUBMIT_TOKEN");
			rand_code.append(REPEAT_SUBMIT_TOKEN);
			if(FALSE == CheckRandCode(curl,rand_code.c_str())){ 
				goto  randcode;
			}



			 string in="";
				cin>>in;
		 }
		 curl_easy_cleanup(curl );
         return 0;
}


BOOL PostData (CURL * curl,const char* url,const char * postdata , DownLoadWriteCallBack  handle_html_p ,void*databack  ){

         CURLcode res ;
			g_webhtml	="";
         curl_easy_setopt( curl , CURLOPT_URL, url);

         curl_easy_setopt(curl , CURLOPT_SSL_VERIFYPEER, 0L);     
        
         curl_slist *http_headers = NULL;

 
         http_headers = curl_slist_append (http_headers, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
         http_headers = curl_slist_append (http_headers, "Accept-Encoding: gzip,deflate,sdch" );
         http_headers = curl_slist_append (http_headers, "Accept-Language: zh-CN,zh;q=0.8" );
         http_headers = curl_slist_append (http_headers, "Accept-Charset: GBK,utf-8;q=0.7,*;q=0.3");
         http_headers = curl_slist_append (http_headers, "Host: kyfw.12306.cn" );
         http_headers = curl_slist_append (http_headers, "Connection: keep-alive" );
         http_headers = curl_slist_append (http_headers, "Referer: https://kyfw.12306.cn/otn/login/init");

		 if(g_savecookie)
				curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "C:\\cookie.txt");
		 else
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "C:\\cookie.txt");

	     curl_easy_setopt(curl , CURLOPT_VERBOSE, 1L);

         curl_easy_setopt(curl , CURLOPT_HTTPHEADER, http_headers);
         curl_easy_setopt(curl , CURLOPT_HEADER, g_openhead);                                       // 显示返回的Header区域内容
         curl_easy_setopt(curl , CURLOPT_SSL_VERIFYPEER, 0L);
         curl_easy_setopt(curl , CURLOPT_SSL_VERIFYHOST, 0L);
         curl_easy_setopt(curl , CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.89 Safari/537.1");
		if(g_openzip)	curl_easy_setopt(curl , CURLOPT_ENCODING, "gzip");

         if(postdata ){
                 curl_easy_setopt(curl , CURLOPT_POSTFIELDS, postdata);
        }

 
        
		 if(databack){
				 curl_easy_setopt(curl , CURLOPT_WRITEDATA, databack); 
		 }
		 if(handle_html_p){
				 curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION, handle_html_p); 
		}
         res = curl_easy_perform ( curl );
         long code ; 
 
         curl_easy_getinfo(curl ,CURLINFO_RESPONSE_CODE, & code); 
         curl_slist_free_all(http_headers );

         //fwrite(szbuffer ,1,strlen( szbuffer),fp );
         if(CURLE_OK !=res)
                 return FALSE ;
 
         return TRUE ;    
}


 



int CheckRandCode(CURL *curl,const char * postdata){

	cout<<" ======================检查验证码======================" <<endl;
	g_webhtml.clear();
	g_openzip = 0;
	//检查验证码 
	PostData(curl
		,"https://kyfw.12306.cn/otn/passcodeNew/checkRandCodeAnsyn"
		,postdata
		, handle_html ,NULL); 

	cout<<"验证码检查------------ "<<g_webhtml<<endl;

	if(g_webhtml.find("data: \"Y\"")>0)
	{
		cout<<"------------验证码成功------------"<<endl;
	}else{
		cout<<"------------验证码检查失败------------"<<endl;
		return FALSE;
	}

	return TRUE;

}
