
// huhu-for-windowsDlg.h: 头文件
//

#pragma once


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
	static DWORD WINAPI ThreadProc(LPVOID pParam);

	bool isConnect = false;
	bool isLogin = false;
	bool isSend = false;
	CSocket socket;
	CString server;
	CString port;
	CString UTF8AndUnicode_Convert(CString &strSource, UINT nSourceCodePage, UINT nTargetCodePage);
	afx_msg void OnBnClickedButtonSend();
};
