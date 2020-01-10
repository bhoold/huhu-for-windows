#pragma once
#include <string>
#include <afx.h>

// 该类在项目是UNICODE字符集使用
class CUtility
{
public:
	CUtility();
	~CUtility();

	static LPSTR EncodeToUTF8(LPCSTR str);
	static LPSTR UTF8ToEncode(LPCSTR str);
	static LPSTR CStringToChar(CString str);
	static CString CharToCString(LPSTR str);

	static std::string ConvertCStringToUTF8(CString strValue);
	static CString ConvertUTF8ToCString(std::string utf8str);

	static CString GetLocalIP();
};

