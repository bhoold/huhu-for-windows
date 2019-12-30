
// huhu-for-windowsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "huhu-for-windows.h"
#include "huhu-for-windowsDlg.h"
#include "afxdialogex.h"

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


	CString server;
	CString port;
	CString nickname;

	GetDlgItem(IDC_EDIT_SERVER)->GetWindowTextW(server);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowTextW(port);
	GetDlgItem(IDC_EDIT_NICKNAME)->GetWindowTextW(nickname);




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


	return;







	CSocket socket;
	if (!socket.Create()) {
		CString strError;
		/*
		char szMsg[1024] = { 0 };
		sprintf(szMsg, "create faild: %d", socket.GetLastError());
		strError = szMsg;
		*/
		strError.Format(_T("socket create faild: %d"), socket.GetLastError());
		MessageBox(strError);
		return;
	}

	int nPort = _ttoi(port);
	if (socket.Connect(server, nPort)) {
		TCHAR szRecValue[1024] = { 0 };

		//发送内容给服务器
		CString strText = _T("you我sdfsd");
		CString strRece;

		//char szMsg[1024] = { 0 };
		//sprintf(szMsg, "hello ni %s", 2);
		//socket.Send(szMsg, 1024);
		DWORD l = strText.GetLength();
		DWORD len = strText.GetLength() * sizeof(TCHAR);
		socket.Send(strText, len);

		//接收服务器发送回来的内容(该方法会阻塞, 在此等待有内容接收到才继续向下执行)
		//memset(szRecValue, 0, 1024);
		socket.Receive((void *)szRecValue, 1024);
		strRece.Format(_T("%s"), szRecValue);
		MessageBox(strRece);
	}
	else {
		CString strError;
		strError.Format(_T("socket create faild: %d"), socket.GetLastError());
		MessageBox(strError);
	}
	socket.Close();
}


DWORD ChuhuforwindowsDlg::ThreadProc(LPVOID pParam)
{
	/*
	CDC* pdc;
	//将传入的参数转为RECT*
	RECT* rect = (RECT*)pParam;
	//得到设备句柄
	pdc = AfxGetApp()->m_pMainWnd->GetDC();
	//设置画刷
	CBrush brush(HS_VERTICAL, RGB(0, 255, 0));
	//选入到设备中
	CBrush* oldbrush = pdc->SelectObject(&brush);
	int n = 0;
	while (n++ <= 2000)
	{
		pdc->Rectangle(rect->left, rect->top, rect->right + n, rect->bottom);
		Sleep(1);
	}
	pdc->SelectObject(oldbrush);
	pdc->ReleaseOutputDC();
	*/
	printf("Hello World!\n");





	return 2;
}