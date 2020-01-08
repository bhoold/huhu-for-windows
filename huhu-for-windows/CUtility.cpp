#include "stdafx.h"
#include "CUtility.h"


CUtility::CUtility()
{
}


CUtility::~CUtility()
{
}


// unicode to utf8
LPSTR CUtility::EncodeToUTF8(LPCSTR str)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	wchar_t* wideStr;
	char* utf8Str;
	int charLen;

	charLen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(CP_ACP, 0, str, -1, wideStr, charLen);

	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);

	utf8Str = (char*)malloc(charLen);

	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);

	free(wideStr);
	return utf8Str;
}

// utf8 to unicode
LPSTR CUtility::UTF8ToEncode(LPCSTR str)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	wchar_t* wideStr;
	char* unicodeStr;
	int charLen;

	charLen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(CP_UTF8, 0, str, -1, wideStr, charLen);

	charLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
	unicodeStr = (char*)malloc(charLen);
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, unicodeStr, charLen, NULL, NULL);

	free(wideStr);
	return unicodeStr;
}


LPSTR CUtility::CStringToChar(CString str)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	//ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ����
	int n = str.GetLength(); // n = 14, len = 18
	//��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С
	char* charStr = new char[len + 1]; //���ֽ�Ϊ��λ
	//���ֽڱ���ת���ɶ��ֽڱ���
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), charStr, len, NULL, NULL);
	charStr[len + 1] = '\0'; //���ֽ��ַ���'\0'����
	return charStr;
}


CString CUtility::CharToCString(LPSTR str)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	//����char *�����С�����ֽ�Ϊ��λ��һ������ռ�����ֽ�
	int charLen = strlen(str);
	//������ֽ��ַ��Ĵ�С�����ַ����㡣
	int len = MultiByteToWideChar(CP_ACP, 0, str, charLen, NULL, 0);
	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ķ��ֽ��ַ���С
	TCHAR *buf = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���
	MultiByteToWideChar(CP_ACP, 0, str, charLen, buf, len);
	buf[len] = '\0'; //����ַ�����β��ע�ⲻ��len+1
	//��TCHAR����ת��ΪCString
	CString pWideChar;
	pWideChar.Append(buf);
	//ɾ��������
	delete[]buf;
	return pWideChar;
}


CString CUtility::GetLocalIP()
{
	CString ip;
	/*
	WSADATA wsaData;
	int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (err != 0)
	{
		return _T("");
	}
	getaddrinfo
	char szHostName[MAX_PATH] = { 0 };
	int nRetCode;
	nRetCode = gethostname(szHostName, sizeof(szHostName));

	char* lpLocalIP;
	PHOSTENT hostinfo;

	if (nRetCode != 0)
	{
		WSACleanup();
		return _T("");
	}

	hostinfo = gethostbyname(szHostName);
	lpLocalIP = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);

	WSACleanup();

	ip.Format(_T("%s"), lpLocalIP);*/
	return ip;
}
