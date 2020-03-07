
// huhu-for-windowsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "huhu-for-windows.h"
#include "huhu-for-windowsDlg.h"
#include "afxdialogex.h"

#include "CMyAsyncSocket.h"
#include "CSocketManager.h"
#include "CUtility.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ChuhuforwindowsDlg 对话框


ChuhuforwindowsDlg::ChuhuforwindowsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HUHUFORWINDOWS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChuhuforwindowsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ChuhuforwindowsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &ChuhuforwindowsDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &ChuhuforwindowsDlg::OnBnClickedButtonSend)
	ON_MESSAGE(WM_MYASYNCSOCKET, &ChuhuforwindowsDlg::OnMyAsyncSocket)
END_MESSAGE_MAP()


// ChuhuforwindowsDlg 消息处理程序

BOOL ChuhuforwindowsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT_SERVER)->SetWindowTextW(_T("172.18.18.220"));
	GetDlgItem(IDC_EDIT_PORT)->SetWindowTextW(_T("9501"));
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);

	m_pCSockMagr = new CSocketManager;
	m_pCSockMagr->Init(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ChuhuforwindowsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ChuhuforwindowsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR ChuhuforwindowsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void ChuhuforwindowsDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strServer;
	CString strPort;
	DWORD nPort;

	GetDlgItem(IDC_EDIT_SERVER)->GetWindowText(strServer);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(strPort);
	nPort = _ttoi(strPort);

	m_pCSockMagr->Connect(strServer, nPort);

}



void ChuhuforwindowsDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_MESSAGE)->GetWindowText(str);

	if (str.IsEmpty()) {
		return;
	}
	GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowText(_T(""));

	CString msg;
	msg.Format(_T("{\"type\":\"message\",\"message\":{\"to\":\"all\",\"content\":\"%s\"},\"token\":\"asdf\"}"),
		str);
	Send(msg);
}


void ChuhuforwindowsDlg::Login()
{
	// TODO: 在此处添加实现代码.
		/*
		{
			"id":"001",
				"type" : "login",
				"user" : {
				"account":"haha",
					"password" : "123456"
			},
				"platform" : {
					"os":"windows10"
						"ip" : "192.168.1.1"
				},
					"version" : "0.0.1"
		}
		*/
	CString strName;
	CString strPwd;
	GetDlgItem(IDC_EDIT_NICKNAME)->GetWindowText(strName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(strPwd);

	if (strName.IsEmpty() || strPwd.IsEmpty()) {
		MessageBox(_T("请输入账号和密码"));
		return;
	}

	CString msg;
	msg.Format(_T("{\"type\":\"login\",\"user\":{\"account\":\"%s\",\"password\":\"%s\"},\"client\":{\"os\":\"windows10\",\"version\":\"0.0.1\"}}"),
		strName, strPwd);
	Send(msg);
}


void ChuhuforwindowsDlg::Send(CString msg)
{
	// TODO: 在此处添加实现代码.

	char* strBuffer = CUtility::EncodeToUTF8(CUtility::CStringToChar(msg));
	int nBytesBufferSize = strlen(strBuffer) - 1;
	int nBytesSent = 0;

	while (nBytesSent < nBytesBufferSize)
	{
		int dwBytes;

		if ((dwBytes = m_pCSockMagr->m_pSocket->Send((LPCTSTR)strBuffer + nBytesSent, nBytesBufferSize - nBytesSent)) == SOCKET_ERROR)
		{
			if (m_pCSockMagr->m_pSocket->GetLastError() == WSAEWOULDBLOCK)
			{
				break;
			}
			else
			{
				TCHAR szError[256];
				_stprintf_s(szError, _T("发送失败: %d"),
					GetLastError());
				m_pCSockMagr->m_pSocket->Close();
				AfxMessageBox(szError);
			}
		}
		else
		{
			nBytesSent += dwBytes;
		}
	}

	if (nBytesSent == nBytesBufferSize)
	{
		nBytesSent = nBytesBufferSize = 0;
	}
}


afx_msg LRESULT ChuhuforwindowsDlg::OnMyAsyncSocket(WPARAM wParam, LPARAM lParam)
{
	CSocketManager* pCSockMagr = (CSocketManager*)wParam;
	DWORD event = *((DWORD*)(lParam));
	int recvLen;
	const int BUF_SIZE = 1024;
	char buf[BUF_SIZE];
	switch (event)
	{
	case EVENT_CONNECT://connect
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(_T("EVENT_CONNECT\r\n")));

		break;
	case EVENT_SEND://send
	{
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(_T("EVENT_SEND\r\n")));

		Login();
	}
		break;
	case EVENT_RECEIVE://receive
	{
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(_T("EVENT_RECEIVE\r\n")));

		
		TCHAR szRecValue[1024] = { 0 };
		CString strRecev;

		char buff[1024] = {0};
		m_pCSockMagr->m_pSocket->Receive((void *)buff, 1024);
		char* newBuff = CUtility::UTF8ToEncode(buff);

		CString str = CUtility::CharToCString(newBuff);

		CTime tm; tm = CTime::GetCurrentTime();
		strRecev = tm.Format("%Y年%m月%d日 %X\r\n");
		strRecev.AppendFormat(_T("%s\r\n"), str);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(strRecev.GetBuffer()));

		if (strRecev.CompareNoCase(_T("bye")) == 0)
		{
			m_pCSockMagr->m_pSocket->ShutDown();
		}

		m_bLogin = true;

		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow();
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		
	}
		break;
	case EVENT_CLOSE://close
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(_T("EVENT_CLOSE\r\n")));

		m_bLogin = false;

		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow();

		m_pCSockMagr->Close();

		break;
	default:
		break;
	}
	TCHAR szError[256];
	_stprintf_s(szError, _T(": %d"), event);
	TRACE(szError);
	return 0;
}

