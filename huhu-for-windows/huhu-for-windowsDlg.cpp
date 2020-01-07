
// huhu-for-windowsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "huhu-for-windows.h"
#include "huhu-for-windowsDlg.h"
#include "afxdialogex.h"

#include "CMyAsyncSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


char* EncodeToUTF8(const char* mbcsStr)
{
	wchar_t* wideStr;
	char* utf8Str;
	int charLen;

	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen);

	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);

	utf8Str = (char*)malloc(charLen);

	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);

	free(wideStr);
	return utf8Str;

}
char* UTF8ToEncode(const char* mbcsStr)
{
	wchar_t* wideStr;
	char* unicodeStr;
	int charLen;

	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, wideStr, charLen);

	charLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
	unicodeStr = (char*)malloc(charLen);
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, unicodeStr, charLen, NULL, NULL);

	free(wideStr);
	return unicodeStr;
}

char* CStringToChar(CString str)
{
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = str.GetLength(); // n = 14, len = 18
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
	char * pFileName = new char[len + 1]; //以字节为单位
	//宽字节编码转换成多字节编码
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), pFileName, len, NULL, NULL);
	pFileName[len + 1] = '\0'; //多字节字符以'\0'结束
	return pFileName;
}

CString CharToCString(char* chars)
{
	//计算char *数组大小，以字节为单位，一个汉字占两个字节
	int charLen = strlen(chars);
	//计算多字节字符的大小，按字符计算。
	int len = MultiByteToWideChar(CP_ACP, 0, chars, charLen, NULL, 0);
	//为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
	TCHAR *buf = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码
	MultiByteToWideChar(CP_ACP, 0, chars, charLen, buf, len);
	buf[len] = '\0'; //添加字符串结尾，注意不是len+1
	//将TCHAR数组转换为CString
	CString pWideChar;
	pWideChar.Append(buf);
	//删除缓冲区
	delete[]buf;

	return pWideChar;
}






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
	GetDlgItem(IDC_EDIT_SERVER)->SetWindowTextW(_T("172.18.18.210"));
	GetDlgItem(IDC_EDIT_PORT)->SetWindowTextW(_T("9501"));
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);

	pSocketClient = new CMyAsyncSocket;

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

	GetDlgItem(IDC_EDIT_SERVER)->GetWindowTextW(strServer);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowTextW(strPort);
	nPort = _ttoi(strPort);

	if (!isCreated) {
		pSocketClient->m_pWnd = this;
		if (FALSE == pSocketClient->Create()) {
			CString strError;
			strError.Format(_T("创建链接失败，错误号: %d"), pSocketClient->GetLastError());
			GetDlgItem(IDC_RICHEDIT2_CHAT)->SetWindowText(strError);
			return;
		}
		else {
			isCreated = true;
		}
	}

	
	pSocketClient->Connect(strServer, nPort);

}



void ChuhuforwindowsDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CMyAsyncSocket* pSocket = pSocketClient;

	
	CString  str;
	GetDlgItemText(IDC_EDIT_MESSAGE, str);

	CString m_sendBuffer;
	m_sendBuffer.Format(_T("{login:\"%s\"}"), str);

	char* strBuffer = EncodeToUTF8(CStringToChar(m_sendBuffer));
	int nBytesBufferSize = strlen(strBuffer) - 1;
	int nBytesSent = 0;

	while (nBytesSent < nBytesBufferSize)
	{
		int dwBytes;

		if ((dwBytes = pSocket->Send((LPCTSTR)strBuffer + nBytesSent, nBytesBufferSize - nBytesSent)) == SOCKET_ERROR)
		{
			if (GetLastError() == WSAEWOULDBLOCK)
			{
				break;
			}
			else
			{
				TCHAR szError[256];
				_stprintf_s(szError, _T("发送失败: %d"),
					GetLastError());
				pSocket->Close();
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
	CMyAsyncSocket* pSocket = (CMyAsyncSocket*)wParam;
	DWORD param = *((DWORD*)(lParam));
	int recvLen;
	const int BUF_SIZE = 1024;
	char buf[BUF_SIZE];
	switch (param)
	{
	case EVENT_CONNECT://connect
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(_T("EVENT_CONNECT\r\n")));

		break;
	case EVENT_SEND://send
	{
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(_T("EVENT_SEND\r\n")));


		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow();

		CString m_sendBuffer = _T("{login:\"hello\"}");
		char* strBuffer = EncodeToUTF8(CStringToChar(m_sendBuffer));
		int nBytesBufferSize = strlen(strBuffer)-1;
		int nBytesSent = 0;

		while (nBytesSent < nBytesBufferSize)
		{
			int dwBytes;

			if ((dwBytes = pSocket->Send((LPCTSTR)strBuffer + nBytesSent, nBytesBufferSize - nBytesSent)) == SOCKET_ERROR)
			{
				if (GetLastError() == WSAEWOULDBLOCK)
				{
					break;
				}
				else
				{
					TCHAR szError[256];
					_stprintf_s(szError, _T("发送失败: %d"),
						GetLastError());
					pSocket->Close();
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
		break;
	case EVENT_RECEIVE://receive
	{
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(_T("EVENT_RECEIVE\r\n")));


		TCHAR szRecValue[1024] = { 0 };
		CString strRecev;

		char buff[1024] = {0};
		pSocket->Receive((void *)buff, 1024);
		char* newBuff = UTF8ToEncode(buff);

		CString str = CharToCString(newBuff);

		CTime tm; tm = CTime::GetCurrentTime();
		strRecev = tm.Format("%Y年%m月%d日 %X\r\n");
		strRecev.AppendFormat(_T("%s\r\n"), str);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(strRecev.GetBuffer()));



		if (strRecev.CompareNoCase(_T("bye")) == 0)
		{
			pSocket->ShutDown();
		}

	}
		break;
	case EVENT_CLOSE://close
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_SETSEL, -1, -1);
		::SendMessage((*GetDlgItem(IDC_RICHEDIT2_CHAT)), EM_REPLACESEL, 0, (LPARAM)(_T("EVENT_CLOSE\r\n")));
		break;
	default:
		break;
	}
	TCHAR szError[256];
	_stprintf_s(szError, _T(": %d"), param);
	TRACE(szError);
	return 0;
}
