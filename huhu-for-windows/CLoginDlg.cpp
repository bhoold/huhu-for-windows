// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "huhu-for-windows.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "CRegisterDlg.h"
#include "CLoginSetupDlg.h"
// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC_SETUP, &CLoginDlg::OnStnClickedStaticSetup)
	ON_STN_CLICKED(IDC_STATIC_REG, &CLoginDlg::OnStnClickedStaticReg)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	/*
	CRegisterDlg dlg;
	dlg.DoModal();

	CRegisterDlg *pDlg = new CRegisterDlg;
	pDlg->Create(IDD_REGISTER_DIALOG, this);
	pDlg->ShowWindow(SW_SHOW);
	*/
}


void CLoginDlg::OnStnClickedStaticSetup()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);

	CLoginSetupDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		ShowWindow(SW_SHOW);
	}
	else
	{
		// TODO: 在此放置处理何时用
		//PostQuitMessage(0);
		ShowWindow(SW_SHOW);
	}
}


void CLoginDlg::OnStnClickedStaticReg()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);

	CRegisterDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		ShowWindow(SW_SHOW);
	}
	else
	{
		// TODO: 在此放置处理何时用
		//PostQuitMessage(0);
		ShowWindow(SW_SHOW);
	}
}


void CLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnSysCommand(nID, lParam);
}
