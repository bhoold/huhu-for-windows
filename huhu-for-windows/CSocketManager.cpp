#include "stdafx.h"
#include "CSocketManager.h"
#include "CMyAsyncSocket.h"
#include "huhu-for-windows.h"
#include "CUtility.h"


CSocketManager::CSocketManager()
{
	m_nMsgId = 0;
}


CSocketManager::~CSocketManager()
{
}


void CSocketManager::Init(CWnd* pWnd)
{
	// TODO: 在此处添加实现代码.
	m_pWnd = pWnd;
	if (true != m_bInit) {
		m_pSocket = new CMyAsyncSocket();
		m_pSocket->m_pCSockMagr = this;

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
		//m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}
		break;
	case EVENT_SEND:
	{
		m_bConnected = true;
		
		for (int i = 0; i < m_arrTaskList.GetSize(); i++)
		{
			MsgTask task = m_arrTaskList.GetAt(i);
			Emit(task.pWnd, task.msg);
		}
		
		DWORD param = EVENT_SEND;
		//m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}
		break;
	case EVENT_RECEIVE:
	{
		
		for (int i = 0; i < m_arrTaskList.GetSize(); i++)
		{
			MsgTask task = m_arrTaskList.GetAt(i);
			//task.msg
			m_arrTaskList.RemoveAt(i);
			break;
		}

		DWORD param = EVENT_RECEIVE;
		//m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}
		break;
	case EVENT_CLOSE: 
	{
		DWORD param = EVENT_CLOSE;
		//m_pWnd->SendMessage(WM_MYASYNCSOCKET, (WPARAM)this, (LPARAM)&param);
	}

		break;
	default:
		break;
	}
}


void CSocketManager::Close()
{
	// TODO: 在此处添加实现代码.
	m_bConnected = false;
}


void CSocketManager::Send(CWnd* pWnd, CString msg)
{
	// TODO: 在此处添加实现代码.
	Init(pWnd);
	Connect(m_pApp->m_oData.m_strServer, m_pApp->m_oData.m_nPort);

	msg.AppendFormat(_T("id:%d"), m_nMsgId);
	Emit(pWnd, msg);
}


void CSocketManager::Emit(CWnd* pWnd, CString msg)
{
	// TODO: 在此处添加实现代码.
	if (true != m_bConnected) {
		MsgTask task = {
			pWnd,
			msg
		};
		m_arrTaskList.Add(task);
		return;
	}

	char* strBuffer = CUtility::EncodeToUTF8(CUtility::CStringToChar(msg));
	int nBytesBufferSize = strlen(strBuffer) - 1;
	int nBytesSent = 0;

	while (nBytesSent < nBytesBufferSize)
	{
		int dwBytes;

		if ((dwBytes = m_pSocket->Send((LPCTSTR)strBuffer + nBytesSent, nBytesBufferSize - nBytesSent)) == SOCKET_ERROR)
		{
			if (m_pSocket->GetLastError() == WSAEWOULDBLOCK)
			{
				break;
			}
			else
			{
				TCHAR szError[256];
				_stprintf_s(szError, _T("发送失败: %d"),
					GetLastError());
				m_pSocket->Close();
				//AfxMessageBox(szError);
				break;
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
