// CMyAsyncSocket.cpp: 实现文件
//

#include "stdafx.h"
#include "huhu-for-windows.h"
#include "CMyAsyncSocket.h"


// CMyAsyncSocket

CMyAsyncSocket::CMyAsyncSocket()
{
}

CMyAsyncSocket::~CMyAsyncSocket()
{
}


// CMyAsyncSocket 成员函数


void CMyAsyncSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	printf("CMyAsyncSocket::OnReceive");
	DWORD param = EVENT_RECEIVE;
	if (m_pWnd != NULL)
		m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);

	CAsyncSocket::OnReceive(nErrorCode);
}


void CMyAsyncSocket::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	//该事件表示可以send了，不是send之后触发
	printf("CMyAsyncSocket::OnSend");
	DWORD param = EVENT_SEND;
	if (m_pWnd != NULL)
		m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);

	CAsyncSocket::OnSend(nErrorCode);
}


void CMyAsyncSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	printf("CMyAsyncSocket::OnConnect");
	if (0 != nErrorCode) {
		switch (nErrorCode)
		{
		case WSAEADDRINUSE:
			AfxMessageBox(_T("The specified address is already in use.\n"));
			break;
		case WSAEADDRNOTAVAIL:
			AfxMessageBox(_T("The specified address is not available from ")
				_T("the local machine.\n"));
			break;
		case WSAEAFNOSUPPORT:
			AfxMessageBox(_T("Addresses in the specified family cannot be ")
				_T("used with this socket.\n"));
			break;
		case WSAECONNREFUSED:
			AfxMessageBox(_T("服务器连接被拒绝.\n"));
			break;
		case WSAEDESTADDRREQ:
			AfxMessageBox(_T("A destination address is required.\n"));
			break;
		case WSAEFAULT:
			AfxMessageBox(_T("The lpSockAddrLen argument is incorrect.\n"));
			break;
		case WSAEINVAL:
			AfxMessageBox(_T("The socket is already bound to an address.\n"));
			break;
		case WSAEISCONN:
			AfxMessageBox(_T("The socket is already connected.\n"));
			break;
		case WSAEMFILE:
			AfxMessageBox(_T("No more file descriptors are available.\n"));
			break;
		case WSAENETUNREACH:
			AfxMessageBox(_T("The network cannot be reached from this host ")
				_T("at this time.\n"));
			break;
		case WSAENOBUFS:
			AfxMessageBox(_T("No buffer space is available. The socket ")
				_T("cannot be connected.\n"));
			break;
		case WSAENOTCONN:
			AfxMessageBox(_T("The socket is not connected.\n"));
			break;
		case WSAENOTSOCK:
			AfxMessageBox(_T("The descriptor is a file, not a socket.\n"));
			break;
		case WSAETIMEDOUT:
			AfxMessageBox(_T("The attempt to connect timed out without ")
				_T("establishing a connection. \n"));
			break;
		default:
			TCHAR szError[256];
			_stprintf_s(szError, _T("服务器连接错误: %d"), nErrorCode);
			AfxMessageBox(szError);
			break;
		}
	}
	else {
		DWORD param = EVENT_CONNECT;
		if (m_pWnd != NULL)
			m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}

	CAsyncSocket::OnConnect(nErrorCode);
}


void CMyAsyncSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	DWORD param = EVENT_CLOSE;
	if (m_pWnd != NULL)
		m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);

	CAsyncSocket::OnClose(nErrorCode);
}
