#pragma once
#define WM_MYASYNCSOCKET WM_USER+1001

#define EVENT_CONNECT 1
#define EVENT_SEND 2
#define EVENT_RECEIVE 3
#define EVENT_CLOSE 4



// CMyAsyncSocket 命令目标

class CMyAsyncSocket : public CAsyncSocket
{
public:
	CMyAsyncSocket();
	virtual ~CMyAsyncSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CWnd* m_pWnd;
};


