// CardClientDlg.h : ͷ�ļ�
//

#pragma once


// CCardClientDlg �Ի���
class CCardClientDlg : public CDialog
{
// ����
public:
	CCardClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CARDCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
