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
         cout<<" ��ʼ��ʼ�� curl"<<endl ;
         curl = curl_easy_init ();
         if( !curl ) {
                 cout<<"curl ��ʼ��ʧ�� "<<endl ;

        }


		 
         g_openhead = 0;
         cout<<"curl ��ʼ���ɹ� "<<endl ;
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
			 if(( df.fp =fopen( "��֤��.jpg","wb" ))==NULL)
			 {
				 curl_easy_cleanup(curl );
				 exit(1);

			 }
			 g_savecookie = 1;
			 g_openhead = 1;
			 g_openzip = 1;
			 //��½ҳ���ȡsession��������֤��
			 PostData(curl
					, "https://kyfw.12306.cn/otn/login/init"
					, NULL
					,handle_html ,NULL);

			 fwrite(g_webhtml.c_str(),1,g_webhtml.length(),fp);
			g_openhead = 0;
			g_openzip = 0;
			 g_savecookie = 0;
 
			randcode:
			 cout<<" ======================������֤��======================" <<endl;
			
			 //������֤��
			 PostData(curl
				 ,"https://kyfw.12306.cn/otn/passcodeNew/getPassCodeNew?module=login&rand=sjrand"
				 ,NULL
				 ,save_yanzhengma ,(char*)&df);
		 
			 int ret = fwrite(df.buffer,1,df.len,df.fp);

				fclose(fp);
				
				fclose(df.fp);
	         
			g_webhtml.clear();

			cout<<"������֤��:"<<endl;

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
 

			cout<<" =====================��¼���======================" <<endl;
			g_webhtml.clear();
			cout<<"��������� username= "<<username<<" passwd= "<<passwd<<" code= "<<code<<endl;
			string post_data="";
			post_data.append("loginUserDTO.user_name=");
			post_data.append(username);
			post_data.append("&userDTO.password=");
			post_data.append(passwd);
			post_data.append("&randCode=");
			post_data.append(code); 
			FILE * logfp = fopen("��¼����.txt","w");
			//��¼
			PostData(curl
					,"https://kyfw.12306.cn/otn/login/loginAysnSuggest"
					,post_data.c_str()
					,handle_login ,logfp);  
			cout<<" ��¼���------------ "<<endl;
			if(g_webhtml.find("\"loginCheck\":\"Y\"")>0)
			{
				cout<<"------------��¼�ɹ�------------"<<endl;
			}else{
				cout<<"------------��¼�ɹ�ʧ��------------"<<g_webhtml<<endl;
				goto  randcode;
			}

			fclose(logfp);
			g_webhtml.clear();

			cout<<" =====================��ȡ������Ϣ======================" <<endl;

			FILE * userfp = fopen("��ȡ������Ϣ.txt","w");

			//��ȡ������Ϣ
			PostData(curl
					,"https://kyfw.12306.cn/otn/confirmPassenger/getPassengerDTOs"
					,NULL
					,handle_login ,userfp);  
			cout<<" ��ȡ������Ϣ------------ "<<endl;

			if(g_webhtml.find("\"isExist\":true")>0)
			{
				cout<<"------------��ȡ�ɹ�------------"<<endl;
			}else{
				cout<<"------------��ȡ�ɹ�ʧ��------------"<<g_webhtml<<endl; 
			}
			fclose(userfp);
   
			g_webhtml.clear();



		
			cout<<" =====================��ѯ�г�======================" <<endl;

			FILE * chaxunfp = fopen("��ѯ�г�.txt","w");
			curl_easy_setopt(curl, CURLOPT_HTTPGET, "?test=string");
			//��ѯ�г�
			PostData(curl
				,"https://kyfw.12306.cn/otn/leftTicket/query?leftTicketDTO.train_date=2014-01-08&leftTicketDTO.from_station=SZQ&leftTicketDTO.to_station=HYQ&purpose_codes=ADULT"
				,NULL
				,handle_login ,chaxunfp);  
			cout<<" ��ѯ�г�------------ "<<endl;

			if(g_webhtml.find("\"httpstatus\":200")>0)
			{
				cout<<"------------��ѯ�г��ɹ�------------"<<endl;
			}else{
				cout<<"-----------��ѯ�г�ʧ��------------"<<g_webhtml<<endl; 
			}
			fclose(chaxunfp); 
			g_webhtml.clear();


			cout<<" ====================�����ύ��ҳ====================" <<endl;
			
			g_openzip = 1;
			FILE * get_order_page = fopen("�¶���ҳ��.txt","w"); 
			//��ѯ�г�
			PostData(curl
				,"https://kyfw.12306.cn/otn/confirmPassenger/initDc"
				,"_json_att=", handle_login ,get_order_page);  
			cout<<" ��ѯ�г�------------ "<<endl;

			if(g_webhtml.find("globalRepeatSubmitToken")>0)
			{
				cout<<"------------�¶���ҳ�ɹ�------------"<<endl;
			}else{
				cout<<"-----------�¶���ҳʧ��------------"<<g_webhtml<<endl; 
			}
			string REPEAT_SUBMIT_TOKEN = get_token(&g_webhtml,"globalRepeatSubmitToken = '","';");
		 
			fclose(get_order_page); 
			g_openzip = 0;

			g_webhtml.clear();


			
			cout<<" ====================�����ύ������֤��====================" <<endl;

			df.fp = fopen("�ύ������֤��.jpg","wb");
			memset(df.buffer,0,MAXHTML_SIZE);
			df.len = 0;
			
			curl_easy_setopt(curl, CURLOPT_HTTPGET, "?module=passenger&rand=randp");
			//��ѯ�г�
			PostData(curl
				,"https://kyfw.12306.cn/otn/passcodeNew/getPassCodeNew?module=passenger&rand=randp"
				,NULL
				, save_yanzhengma ,&df);  
			cout<<" �ύ���� ------------ "<<g_webhtml<<endl;

			fwrite(df.buffer,1,df.len,df.fp);		
			fclose(df.fp); 
			cout<<" ��������֤�� "<<endl;	
			
  
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
         curl_easy_setopt(curl , CURLOPT_HEADER, g_openhead);                                       // ��ʾ���ص�Header��������
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

	cout<<" ======================�����֤��======================" <<endl;
	g_webhtml.clear();
	g_openzip = 0;
	//�����֤�� 
	PostData(curl
		,"https://kyfw.12306.cn/otn/passcodeNew/checkRandCodeAnsyn"
		,postdata
		, handle_html ,NULL); 

	cout<<"��֤����------------ "<<g_webhtml<<endl;

	if(g_webhtml.find("data: \"Y\"")>0)
	{
		cout<<"------------��֤��ɹ�------------"<<endl;
	}else{
		cout<<"------------��֤����ʧ��------------"<<endl;
		return FALSE;
	}

	return TRUE;

}
