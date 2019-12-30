#pragma once
#define WM_MYASYNCSOCKET WM_USER+1001

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


