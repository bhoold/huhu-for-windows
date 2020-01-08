
// huhu-for-windowsDlg.h: 头文件
//

#pragma once

class CSocketManager;

// ChuhuforwindowsDlg 对话框
class ChuhuforwindowsDlg : public CDialogEx
{
// 构造
public:
	ChuhuforwindowsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUHUFORWINDOWS_DIALOG };
#endif

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
	afx_msg void OnBnClickedButtonConnect();

	bool isLogin = false;
	afx_msg void OnBnClickedButtonSend();
	CSocketManager* m_pCSockMagr;
protected:
	afx_msg LRESULT OnMyAsyncSocket(WPARAM wParam, LPARAM lParam);
public:
	void Login();
	void Send(CString msg);
};
