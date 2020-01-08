#include "stdafx.h"
#include "CSocketManager.h"
#include "CMyAsyncSocket.h"

CSocketManager::CSocketManager()
{
}


CSocketManager::~CSocketManager()
{
}


void CSocketManager::Init(CWnd* pWnd)
{
	// TODO: 在此处添加实现代码.
	if (true != m_bInit) {
		m_pSocket = new CMyAsyncSocket();
		m_pSocket->m_pCSockMagr = this;
		m_pWnd = pWnd;

		m_bInit = true;
	}
	
}


void CSocketManager::Connect(CString strServer, DWORD nPort)
{
	// TODO: 在此处添加实现代码.
	if (true == m_bInit) {
		if (true != m_bCreated) {
			if (FALSE == m_pSocket->Create()) {
				CString strError;
				strError.Format(_T("Socket创建失败，错误号: %d"), GetLastError());
				TRACE(strError);
				return;
			}
			else {
				m_bCreated = true;
			}
		}

		if (true != m_bConnected) {
			m_pSocket->Connect(strServer, nPort);

			m_bConnected = true;
		}
	}
}


void CSocketManager::Message(DWORD event)
{
	// TODO: 在此处添加实现代码.
	switch (event)
	{
	case EVENT_CONNECT:
	{
		DWORD param = EVENT_CONNECT;
		m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}
		break;
	case EVENT_SEND:
	{
		DWORD param = EVENT_SEND;
		m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}
		break;
	case EVENT_RECEIVE:
	{
		DWORD param = EVENT_RECEIVE;
		m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}
		break;
	case EVENT_CLOSE: 
	{
		DWORD param = EVENT_CLOSE;
		m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}

		break;
	default:
		break;
	}
}
