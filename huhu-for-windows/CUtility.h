#pragma once

// ��������Ŀ��UNICODE�ַ���ʹ��
class CUtility
{
public:
	CUtility();
	~CUtility();

	static LPSTR EncodeToUTF8(LPCSTR str);
	static LPSTR UTF8ToEncode(LPCSTR str);
	static LPSTR CStringToChar(CString str);
	static CString CharToCString(LPSTR str);
};

