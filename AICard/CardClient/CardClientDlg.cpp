// CardClientDlg.cpp : ʵ���ļ�
//



#include "stdafx.h"
#include "CardClient.h"
#include "CardClientDlg.h"
#include "CardBusi.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCardClientDlg �Ի���




CCardClientDlg::CCardClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_MyDesk	=	new DeskBusi();

	 m_PlayerA	=	NULL;
	 m_PlayerB	=	NULL;
	 m_PlayerC	=	NULL;
	 m_PlayerD	=	NULL;

	 InitializeCriticalSection(&m_Sec);

}

void CCardClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_LIST_HANDCARD, m_HandCardList);
}

BEGIN_MESSAGE_MAP(CCardClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
 
	ON_MESSAGE(WM_INFOLIST, &CCardClientDlg::OnInfoList)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CCardClientDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CCardClientDlg::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_CARDFROMDESK, &CCardClientDlg::OnBnClickedButtonCardfromdesk)
	ON_BN_CLICKED(IDC_BUTTON_CARDFROMHAND, &CCardClientDlg::OnBnClickedButtonCardfromhand)
	ON_LBN_SELCHANGE(IDC_LIST_HANDCARD, &CCardClientDlg::OnLbnSelchangeListHandcard)
	ON_BN_CLICKED(IDC_BUTTON_START_GAME, &CCardClientDlg::OnBnClickedButtonStartGame)
	ON_BN_CLICKED(IDC_BUTTON_USERA_JOIN, &CCardClientDlg::OnBnClickedButtonUseraJoin)
	ON_BN_CLICKED(IDC_BUTTON_USERB_JOIN, &CCardClientDlg::OnBnClickedButtonUserbJoin)
	ON_BN_CLICKED(IDC_BUTTON_USERC_JOIN, &CCardClientDlg::OnBnClickedButtonUsercJoin)
	ON_BN_CLICKED(IDC_BUTTON_USERD_JOIN, &CCardClientDlg::OnBnClickedButtonUserdJoin)
END_MESSAGE_MAP()


// CCardClientDlg ��Ϣ�������

BOOL CCardClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetDlgItemText(IDC_EDIT_IP, "192.168.0.109");
	SetDlgItemText(IDC_EDIT_PORT, "8088");
	SetDlgItemText(IDC_EDIT_USERNAME, "totti@sina.com");
	SetDlgItemText(IDC_EDIT_PASSWORD, "123456");

 
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCardClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCardClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	m_MyDesk->SetWinHandle(this->m_hWnd);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CCardClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCardClientDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CCardClientDlg::OnBnClickedButtonLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CCardClientDlg::OnBnClickedButtonCardfromdesk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_HandCardList.AddString(_T("asdf"));
}

LRESULT	CCardClientDlg::OnInfoList(WPARAM wParam,LPARAM lParam){


	EnterCriticalSection(&m_Sec);
	
	CString show2	=  "";
	GetDlgItemText(IDC_EDIT_INFOLIST,show2);
	show2	+=CString("\r\n")+(LPCTSTR)lParam;
	SetDlgItemText(IDC_EDIT_INFOLIST,show2); 

	LeaveCriticalSection(&m_Sec);
		
	return NULL;
}


void CCardClientDlg::OnBnClickedButtonCardfromhand()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CardBusi  * pCard = new CardBusi;

	pCard->start();
		string show_str =""; 
	pCard->GetAllCard(show_str );

	CARDTYPE greatcard[MAX_CARD_NUM_ID]={0};
	CARDTYPE leftcard[MAX_CARD_NUM_ID]={0};
 
	int num = pCard->GetOrderedCard(greatcard,leftcard);
	
 
	CString show = "",show2 = "";

	SetDlgItemText(IDC_EDIT_INFOLIST, show_str.c_str() );
	for (int i =0 ; greatcard[i];i+=3)
	{
		 show.Format(" A= %d, B= %d  C= %d \r\n",greatcard[i],greatcard[i+1],greatcard[i+2]);
		 show2 += show;
	}
	show2 +="left card is: ";
	for (int i =0 ; i< leftcard[0];i++)
	{	if(leftcard[1+i]==0) continue;
		show.Format("  %d ,",leftcard[1+i]);
		show2 += show;
	} 
	show2 += "\r\n";	
	for (int i = 0 ; i < pCard->m_Shenum ;i++)
	{
		show.Format(" she= %d \r\n",pCard->m_She[i]);
		show2 += show;	
	}

	for (int i = 0 ; i < pCard->m_Kannum ;i++)
	{
		show.Format("kan=  %d \r\n",pCard->m_Kan[i]);
		show2 += show;
	}

	SetDlgItemText(IDC_EDIT_INFOLIST,show2);


	SAFE_DELETE(pCard);
}

CString CCardClientDlg::GetCardStr(CARDTYPE *card,int Num){
	CString show = "";
	CString show2 = "";
	int addnum	=	0;
	for (int i =1 ; i<  Num;i++)
	{	
		if(card[i]==0) continue; 

		for(int k = 0 ;k<card[i];k++) 
		{ 
			addnum++;	
			show.Format("%d,",i); 
			if(addnum%3==0)	show2 += "\r\n";
			show2 += show;
		} 
	} 
	return show2;
}

void CCardClientDlg::OnLbnSelchangeListHandcard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
 
	 
}

void CCardClientDlg::OnBnClickedButtonStartGame()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(TRUE == m_MyDesk->StartGame() ){
		char* str = "��Ϸ��ʼ�ɹ���������";
		SendMessage(WM_INFOLIST,NULL,(LPARAM)str);
	}else{
		char* str2 = "��Ϸ��ʼʧ�ܣ�������";
		SendMessage(WM_INFOLIST,NULL,(LPARAM)str2);  

	}


	//����ҵ�����ʾ����
	SetDlgItemText(IDC_EDIT_USERA,this->GetCardStr(m_PlayerA->GetCard(),MAX_CARD_NUM_ID));
	
	SetDlgItemText(IDC_EDIT_USERB,this->GetCardStr(m_PlayerB->GetCard(),MAX_CARD_NUM_ID));

	SetDlgItemText(IDC_EDIT_USERC,this->GetCardStr(m_PlayerC->GetCard(),MAX_CARD_NUM_ID));


	SetDlgItemText(IDC_EDIT_ME,this->GetCardStr(m_PlayerD->GetCard(),MAX_CARD_NUM_ID));
}



void CCardClientDlg::OnBnClickedButtonUseraJoin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	string name = "���A";
	int		id  = 10000;

	m_PlayerA	=	m_MyDesk->JoinDesk(id,name.c_str());
}

void CCardClientDlg::OnBnClickedButtonUserbJoin()
{
	string name = "���b";
	int		id  = 10001;
	m_PlayerB	=	m_MyDesk->JoinDesk(id,name.c_str());
}

void CCardClientDlg::OnBnClickedButtonUsercJoin()
{
	string name = "���C";
	int		id  = 10002;
	m_PlayerC	=	m_MyDesk->JoinDesk(id,name.c_str());
}

void CCardClientDlg::OnBnClickedButtonUserdJoin()
{
	string name = "���D";
	int		id  = 10003;

	m_PlayerD	=	m_MyDesk->JoinDesk(id,name.c_str());
}
