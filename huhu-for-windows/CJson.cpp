#include "stdafx.h"
#include "CJson.h"


CJson::CJson()
{
}


CJson::~CJson()
{
}


Value CJson::Parse(CString str)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	USES_CONVERSION;
	string s(W2A(str));
	string strValue = s.c_str();

	Reader reader;
	Value value;
	reader.parse(strValue, value);
	return value;
}


CString CJson::Encode(Value jsonValue)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	CString str;
	return str;
}
