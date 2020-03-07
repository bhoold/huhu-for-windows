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
	// TODO: 在此处添加实现代码.
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
	// TODO: 在此处添加实现代码.
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
	// TODO: 在此处添加实现代码.
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = str.GetLength(); // n = 14, len = 18
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
	char* charStr = new char[len + 1]; //以字节为单位
	//宽字节编码转换成多字节编码
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), charStr, len, NULL, NULL);
	charStr[len + 1] = '\0'; //多字节字符以'\0'结束
	return charStr;
}


CString CUtility::CharToCString(LPSTR str)
{
	// TODO: 在此处添加实现代码.
	//计算char *数组大小，以字节为单位，一个汉字占两个字节
	int charLen = strlen(str);
	//计算多字节字符的大小，按字符计算。
	int len = MultiByteToWideChar(CP_ACP, 0, str, charLen, NULL, 0);
	//为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
	TCHAR *buf = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码
	MultiByteToWideChar(CP_ACP, 0, str, charLen, buf, len);
	buf[len] = '\0'; //添加字符串结尾，注意不是len+1
	//将TCHAR数组转换为CString
	CString pWideChar;
	pWideChar.Append(buf);
	//删除缓冲区
	delete[]buf;
	return pWideChar;
}

//另一个版本的转换，消除结尾0
std::string CUtility::ConvertCStringToUTF8(CString strValue)
{
	std::wstring wbuffer;
#ifdef _UNICODE
	wbuffer.assign(strValue.GetString(), strValue.GetLength());
#else
	/*
	* 转换ANSI到UNICODE
	* 获取转换后长度
	*/
	int length = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
	wbuffer.resize(length);
	/* 转换 */
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif

	/* 获取转换后长度 */
	int length = WideCharToMultiByte(CP_UTF8, 0, strValue, -1, NULL, 0, NULL, NULL);
	/* 获取转换后内容 */
	std::string buffer;
	buffer.resize(length);

	length = WideCharToMultiByte(CP_UTF8, 0, strValue, -1,
		(LPSTR)(buffer.data()), length, NULL, NULL);
	buffer.pop_back(); // 结尾'\0'
	return(buffer);
}

//另一个版本的转换，消除结尾0
CString CUtility::ConvertUTF8ToCString(std::string utf8str)
{
	/* 预转换，得到所需空间的大小 */
	int nLen = ::MultiByteToWideChar(CP_UTF8, NULL,
		utf8str.data(), utf8str.size(), NULL, 0);
	/* 转换为Unicode */
	std::wstring wbuffer;
	wbuffer.resize(nLen);
	::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
		(LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
	return(CString(wbuffer.data(), wbuffer.length()));
#else
	/*
	* 转换为ANSI
	* 得到转换后长度
	*/
	nLen = WideCharToMultiByte(CP_ACP, 0,
		wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

	std::string ansistr;
	ansistr.resize(nLen);

	/* 把unicode转成ansi */
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
		(LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
	return(CString(ansistr.data(), ansistr.length()));
#endif
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