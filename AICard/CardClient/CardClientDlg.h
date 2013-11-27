// CardClientDlg.h : 头文件
//

#pragma once


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


// 实现
protected:
	HICON m_hIcon;

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
};
