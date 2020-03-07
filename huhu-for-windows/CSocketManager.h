#pragma once

class ChuhuApp;
class CMyAsyncSocket;

class CSocketManager
{
public:
	CSocketManager();
	~CSocketManager();
	CWnd* m_pWnd;
	ChuhuApp* m_pApp;
	CMyAsyncSocket* m_pSocket;
	CArray<MsgTask> m_arrTaskList;
	bool m_bInit;
	bool m_bCreated;
	bool m_bConnected;
	void Init(CWnd* pWnd);
	void Connect(CString strServer, DWORD nPort);
	void Message(DWORD event);
	void Close();
	void Send(CWnd* pWnd, CString msg);
	void Emit(CWnd* pWnd, CString msg);
	UINT m_nMsgId;
};

