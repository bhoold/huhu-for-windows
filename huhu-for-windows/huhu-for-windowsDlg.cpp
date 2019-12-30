﻿
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


	//CString nickname;

	//GetDlgItem(IDC_EDIT_SERVER)->GetWindowTextW(server);
	//GetDlgItem(IDC_EDIT_PORT)->GetWindowTextW(port);
	//GetDlgItem(IDC_EDIT_NICKNAME)->GetWindowTextW(nickname);




	CString strServer;
	CString strPort;
	DWORD nPort;

	GetDlgItem(IDC_EDIT_SERVER)->GetWindowTextW(strServer);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowTextW(strPort);

	nPort = _ttoi(strPort);

	pSocketClient->m_pWnd = this;
	if (FALSE == pSocketClient->Create()) {
		CString strError;
		strError.Format(_T("创建链接失败，错误号: %d"), pSocketClient->GetLastError());
		GetDlgItem(IDC_RICHEDIT2_CHAT)->SetWindowText(strError);
		return;
	}
	
	pSocketClient->Connect(strServer, nPort);


	/*
	if (FALSE == ) {
		CString strError;
		strError.Format(_T("连接服务器失败，错误号: %d"), pSocketClient->GetLastError());
		GetDlgItem(IDC_RICHEDIT2_CHAT)->SetWindowText(strError);

		//::EnableWindow(::GetDlgItem(pDlg->m_hWnd, IDC_BUTTON_CONNECT), TRUE);
		return;
	}*/


	/*
	RECT rect1;
	rect1.left = 20;  //左上角x坐标
	rect1.top = 100;    //左上角y坐标
	rect1.right = 20;       //右下角x坐标
	rect1.bottom = rect1.top + 100;   //右下角y坐标
	//创建第一个线程ThreadProc,相对优先级THREAD_PRIORITY_IDLE面对任何等级调整为1    
	AfxBeginThread((AFX_THREADPROC)ThreadProc, &rect1, THREAD_PRIORITY_IDLE);

	RECT rect2;
	rect2.left = rect1.left;
	rect2.top = rect1.bottom + 20;
	rect2.right = rect1.right;
	rect2.bottom = rect2.top + 100;
	//创建第二个线程ThreadProc,相对优先级THREAD_PRIORITY_TIME_CRITICAL
	//面对任何等级调整为15,面对REALTIME等级调整为32
	AfxBeginThread((AFX_THREADPROC)ThreadProc, &rect2, THREAD_PRIORITY_TIME_CRITICAL);
	*/
	//AfxBeginThread((AFX_THREADPROC)ThreadProc, this, THREAD_PRIORITY_IDLE);

}


DWORD ChuhuforwindowsDlg::ThreadProc(LPVOID pParam)
{

	ChuhuforwindowsDlg *pDlg = (ChuhuforwindowsDlg *)pParam;

	CString server;
	CString port;

	server = pDlg->server;
	port = pDlg->port;

	if (!pDlg->isConnect) {
		AfxSocketInit();
		if (!pDlg->socket.Create()) {
			CString strError;
			strError.Format(_T("socket create faild: %d"), pDlg->socket.GetLastError());
			//::MessageBox(pDlg->m_hWnd, strError, _T("标题"), 0);
			::SetWindowText(::GetDlgItem(pDlg->m_hWnd, IDC_RICHEDIT2_CHAT), strError);
			return 0;
		}

		::EnableWindow(::GetDlgItem(pDlg->m_hWnd, IDC_BUTTON_CONNECT), FALSE);

		int nPort = _ttoi(port);
		if (pDlg->socket.Connect(server, nPort)) {
			pDlg->isConnect = true;
		}
		else {
			CString strError;
			strError.Format(_T("socket connect faild: %d"), pDlg->socket.GetLastError());
			::SetWindowText(::GetDlgItem(pDlg->m_hWnd, IDC_RICHEDIT2_CHAT), strError);
			::EnableWindow(::GetDlgItem(pDlg->m_hWnd, IDC_BUTTON_CONNECT), TRUE);
		}
		//pDlg->socket.Close();
	}



	while (true)
	{
		if (pDlg->isConnect) {
			if (pDlg->isLogin) {
				if (pDlg->isSend) {
					CString strText;
					CString strMsg;

					pDlg->GetDlgItem(IDC_EDIT_MESSAGE)->GetWindowText(strMsg);
					strText.Format(_T("{message:%s}"), strMsg);
					DWORD len = strText.GetLength() * sizeof(TCHAR);
					pDlg->socket.Send(strText, len);

					pDlg->GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowText(_T(""));



					TCHAR szRecValue[1024] = { 0 };
					CString strRece;

					pDlg->socket.Receive((void *)szRecValue, 1024);

					CTime tm; tm = CTime::GetCurrentTime();
					strRece = tm.Format("%Y年%m月%d日 %X");
					strRece.AppendFormat(_T("%s"), szRecValue);
					::SetWindowText(::GetDlgItem(pDlg->m_hWnd, IDC_RICHEDIT2_CHAT), strRece);


					pDlg->isSend = false;
				}
			}
			else {
				CString strText;
				CString strName;

				pDlg->GetDlgItem(IDC_EDIT_NICKNAME)->GetWindowText(strName);
				strText.Format(_T("{login:%s}"), strName);
				DWORD len = strText.GetLength() * sizeof(TCHAR);
				pDlg->socket.Send(strText, len);



				TCHAR szRecValue[1024] = { 0 };
				CString strRece;

				pDlg->socket.Receive((void *)szRecValue, 1024);

				CTime tm; tm = CTime::GetCurrentTime();
				strRece = tm.Format("%Y年%m月%d日 %X");
				strRece.AppendFormat(_T("%s"), szRecValue);
				::SetWindowText(::GetDlgItem(pDlg->m_hWnd, IDC_RICHEDIT2_CHAT), strRece);

				/*
				SETTEXTEX stex = { ST_NEWCHARS, 1200 };
				::SendMessage(::GetDlgItem(pDlg->m_hWnd, IDC_RICHEDIT2_CHAT), EM_SETTEXTEX, (WPARAM)&stex, (LPARAM)_T("sdf"));
				*/

				::EnableWindow(::GetDlgItem(pDlg->m_hWnd, IDC_BUTTON_SEND), TRUE);

				pDlg->isLogin = true;
			}

		}
		Sleep(0);
	}

	/*
	::SetWindowText(::GetDlgItem(pDlg->m_hWnd, IDC_EDIT_SERVER), _T("Hello World"));
	Sleep(1000);
	::SetWindowText(::GetDlgItem(pDlg->m_hWnd, IDC_EDIT_PORT), _T("Hello Android"));
	Sleep(1000);
	*/
	return 0;
}







CString ChuhuforwindowsDlg::UTF8AndUnicode_Convert(CString &strSource, UINT nSourceCodePage, UINT nTargetCodePage)
{
	CString        strTarget;
	/*
	wchar_t        *pWideBuf;
	int            nWideBufLen;

	char           *pMultiBuf;
	int            nMiltiBufLen;

	int            nSourceLen;

	nSourceLen = strSource.GetLength();
	nWideBufLen = MultiByteToWideChar(nSourceCodePage, 0, strSource, -1, NULL, 0);

	pWideBuf = new wchar_t[nWideBufLen + 1];
	memset(pWideBuf, 0, (nWideBufLen + 1) * sizeof(wchar_t));

	MultiByteToWideChar(nSourceCodePage, 0, strSource, -1, (LPWSTR)pWideBuf, nWideBufLen);

	pMultiBuf = NULL;
	nMiltiBufLen = WideCharToMultiByte(nTargetCodePage, 0, (LPWSTR)pWideBuf, -1, (char *)pMultiBuf, 0, NULL, NULL);

	pMultiBuf = new char[nMiltiBufLen + 1];
	memset(pMultiBuf, 0, nMiltiBufLen + 1);

	WideCharToMultiByte(nTargetCodePage, 0, (LPWSTR)pWideBuf, -1, (char *)pMultiBuf, nMiltiBufLen, NULL, NULL);

	strTarget.Format(_T("%s"), pMultiBuf);

	delete pWideBuf;
	delete pMultiBuf;
	*/
	return strTarget;
}

void ChuhuforwindowsDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码

	if (isLogin) {
		isSend = true;
	}
	else {
		MessageBox(_T("未连接"), _T("提示"));
	}
}



afx_msg LRESULT ChuhuforwindowsDlg::OnMyAsyncSocket(WPARAM wParam, LPARAM lParam)
{
	CMyAsyncSocket* pSock = (CMyAsyncSocket*)wParam;
	DWORD param = *((DWORD*)(lParam));
	int recvLen;
	const int BUF_SIZE = 1024;
	char buf[BUF_SIZE];
	switch (param)
	{
	case 1://connect
		//pSock->Send(buf, BUF_SIZE-1);
		break;
	case 2://send
	{
		CString  m_sendBuffer = _T("它帝业");   //for async send
		int      m_nBytesSent = 0;
		int      m_nBytesBufferSize = m_sendBuffer.GetLength()*2;
		while (m_nBytesSent < m_nBytesBufferSize)
		{
			int dwBytes;

			if ((dwBytes = pSock->Send((LPCTSTR)m_sendBuffer + m_nBytesSent, m_nBytesBufferSize - m_nBytesSent)) == SOCKET_ERROR)
			{
				if (GetLastError() == WSAEWOULDBLOCK)
				{
					break;
				}
				else
				{
					TCHAR szError[256];
					_stprintf_s(szError, _T("Server Socket failed to send: %d"),
						GetLastError());
					pSock->Close();
					AfxMessageBox(szError);
				}
			}
			else
			{
				m_nBytesSent += dwBytes;
			}
		}

		if (m_nBytesSent == m_nBytesBufferSize)
		{
			m_nBytesSent = m_nBytesBufferSize = 0;
			m_sendBuffer = _T("");
		}
	}
		break;
	case 3://receive
	{
		TCHAR szRecValue[1024] = { 0 };
		CString strRece;

		pSock->Receive((void *)szRecValue, 1024);

		CTime tm; tm = CTime::GetCurrentTime();
		strRece = tm.Format("%Y年%m月%d日 %X");
		strRece.AppendFormat(_T("%s"), szRecValue);
		GetDlgItem(IDC_RICHEDIT2_CHAT)->SetWindowText(strRece);


		/*
		CString  m_strRecv;

		static int i = 0;

		i++;

		TCHAR buff[4096];
		int nRead;
		nRead = pSock->Receive(buff, 4096);

		switch (nRead)
		{
		case 0:
			pSock->Close();
			break;
		case SOCKET_ERROR:
			if (GetLastError() != WSAEWOULDBLOCK)
			{
				AfxMessageBox(_T("Error occurred"));
				pSock->Close();
			}
			break;
		default:
			buff[nRead] = _T('\0'); //terminate the string
			CString szTemp(buff);
			m_strRecv += szTemp; // m_strRecv is a CString declared
								 // in CMyAsyncSocket
			if (szTemp.CompareNoCase(_T("bye")) == 0)
			{
				pSock->ShutDown();
			}
			MessageBox(szTemp);
		}*/
	}
		break;
	case 4://close
		break;
		default:
			break;
	}
	TCHAR szError[256];
	_stprintf_s(szError, _T(": %d"), param);
	MessageBox(szError);
	return 0;
}
