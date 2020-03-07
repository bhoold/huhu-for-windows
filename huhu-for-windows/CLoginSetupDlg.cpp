// CLoginSetupDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "huhu-for-windows.h"
#include "CLoginSetupDlg.h"
#include "afxdialogex.h"


// CLoginSetupDlg 对话框

IMPLEMENT_DYNAMIC(CLoginSetupDlg, CDialogEx)

CLoginSetupDlg::CLoginSetupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_SETUP_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	m_strServer = theApp.m_oData.m_strServer;
	m_nPort = theApp.m_oData.m_nPort;
}

CLoginSetupDlg::~CLoginSetupDlg()
{
}

void CLoginSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginSetupDlg, CDialogEx)
	ON_STN_CLICKED(IDC_STATIC_RETURN, &CLoginSetupDlg::OnStnClickedStaticReturn)
	ON_BN_CLICKED(IDOK, &CLoginSetupDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginSetupDlg 消息处理程序


void CLoginSetupDlg::OnStnClickedStaticReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CLoginSetupDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strServer;
	CString strPort;
	GetDlgItemText(IDC_EDIT_SERVER, strServer);
	GetDlgItemText(IDC_EDIT_PORT, strPort);

	if (!strServer.IsEmpty()) {
		theApp.m_oData.m_strServer = strServer;
	}
	if (!strPort.IsEmpty()) {
		theApp.m_oData.m_nPort = _ttoi(strPort);
	}

	CDialogEx::OnOK();
}


BOOL CLoginSetupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strPort;
	strPort.Format(_T("%d"), m_nPort);
	SetDlgItemText(IDC_EDIT_SERVER, m_strServer);
	SetDlgItemText(IDC_EDIT_PORT, strPort);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
