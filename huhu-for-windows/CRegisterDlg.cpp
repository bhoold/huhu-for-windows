// CRegisterDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "huhu-for-windows.h"
#include "CRegisterDlg.h"
#include "afxdialogex.h"


// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegisterDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC_RETURN, &CRegisterDlg::OnStnClickedStaticReturn)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


void CRegisterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CDialogEx::OnOK();
}


void CRegisterDlg::OnStnClickedStaticReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
