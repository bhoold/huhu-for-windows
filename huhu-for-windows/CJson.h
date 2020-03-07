#pragma once
#include <string>
#include <afx.h>

#include "jsoncpp-release-0.5.0/include/json.h"
#ifdef _DEBUG
#pragma comment(lib, "jsoncpp-release-0.5.0/json_vc71_libmtd.lib")
#else
#pragma comment(lib, "jsoncpp-release-0.5.0/json_vc71_libmt.lib")
#endif

using namespace std;
using namespace Json;

class CJson
{
public:
	CJson();
	~CJson();
	Value Parse(CString str);
	CString Encode(Value jsonValue);
};

