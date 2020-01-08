#pragma once

class CMyAsyncSocket;

class CSocketManager
{
public:
	CSocketManager();
	~CSocketManager();
	CWnd* m_pWnd;
	CMyAsyncSocket* m_pSocket;
	bool m_bInit;
	bool m_bCreated;
	bool m_bConnected;
	void Init(CWnd* pWnd);
	void Connect(CString strServer, DWORD nPort);
	void Message(DWORD event);
};

