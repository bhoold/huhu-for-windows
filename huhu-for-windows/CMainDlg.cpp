// CMainDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "huhu-for-windows.h"
#include "CMainDlg.h"
#include "afxdialogex.h"

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序


BOOL CMainDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CDialogEx::PreCreateWindow(cs);
}
