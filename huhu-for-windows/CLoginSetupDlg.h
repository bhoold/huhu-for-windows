#pragma once


// CLoginSetupDlg 对话框

class CLoginSetupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginSetupDlg)

public:
	CLoginSetupDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginSetupDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_SETUP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticReturn();
	afx_msg void OnBnClickedOk();
	CString m_strServer;
	UINT m_nPort;
	virtual BOOL OnInitDialog();
};
