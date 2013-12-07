// CardClientDlg.h : 头文件
//

#pragma once

#include "DeskBusi.h"
#include "CardPlayer.h"
#include "Resource.h"
#define WM_INFOLIST	(WM_USER+23)

// CCardClientDlg 对话框
class CCardClientDlg : public CDialog
{
// 构造
public:
	CCardClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CARDCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CString GetCardStr(CARDTYPE *card,int Num);
// 实现
protected:
	HICON m_hIcon;
	
	DeskBusi * m_MyDesk;
	CardPlayer * m_PlayerA;
	CardPlayer * m_PlayerB;
	CardPlayer * m_PlayerC;
	CardPlayer * m_PlayerD;

	afx_msg LRESULT	OnInfoList(WPARAM wParam,LPARAM lParam);




	CRITICAL_SECTION  m_Sec;


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();
public:
	afx_msg void OnBnClickedButtonLogout();
public:
	afx_msg void OnBnClickedButtonCardfromdesk();
public:
	afx_msg void OnBnClickedButtonCardfromhand();
 
public:
	afx_msg void OnLbnSelchangeListHandcard();
public:
	CListBox m_HandCardList;
public:
	afx_msg void OnBnClickedButtonStartGame();
public:
	afx_msg void OnBnClickedButtonUseraJoin();
public:
	afx_msg void OnBnClickedButtonUserbJoin();
public:
	afx_msg void OnBnClickedButtonUsercJoin();
public:
	afx_msg void OnBnClickedButtonUserdJoin();
};
