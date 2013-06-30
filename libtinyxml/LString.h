#pragma once

#pragma warning (disable : 4996)

#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

class String : public std::string
{

public:
	String() {}
	String(const char* str);
	String(const std::string& str);

public:
	int GetLens() const { return static_cast<int>(length()); }
	const char* GetString() const { return c_str(); }
	bool IsEmpty() const { return empty(); }

public:
	int A2I(void);
	float A2F(void);

	String GetToken(int nToken, char* strSep = NULL) const;

	void Format(const char *pString, ...);
	String GetFilename(void) const;
	int Search(const char *pStrSearch) const;
	void Replace(char cTarget, char cReplace);
	void Replace(const char* strTarget, const char* strReplace);
	void ExtractExt(void);
	void ReplaceExt(char *pExt);
	void GetPath(void);
	int GetCharCount(char cChar) const;
};

unsigned int ComputeHashCode(const char *pSzString);
bool GetStrParam(const char *pStrString, int iIndex, char *pStrParam);
bool GetStrParam(const wchar_t *pStrString, int iIndex, wchar_t *pStrParam);

//---------------------------------------------------------------------
class CUniToAnsi2
{
public :
	CUniToAnsi2(const wchar_t *pStrUni);;
	~CUniToAnsi2();
	operator char*();

	char *m_pString;
};

#define UniToAnsi2(str) string(CUniToAnsi2(str)).c_str()

class CAnsiToUni2
{
public :
	CAnsiToUni2(const char *pStrAnsi);
	~CAnsiToUni2();
	operator wchar_t*();

	wchar_t *m_pString;
};

#define AnsiToUni2(str) wstring(CAnsiToUni2(str)).c_str()
//-------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////

#define GetStrFormat(buf, fmt)	\
	va_list args;\
	va_start(args, fmt);\
	int len = _vscprintf(fmt, args) + 1;\
	buf = static_cast<char *>(_alloca(len * sizeof(char)));\
	vsprintf_s(buf, len, fmt, args);

#define GetStrFormatW(buf, fmt)	\
	va_list args;\
	va_start(args, fmt);\
	int len = _vscwprintf(fmt, args) + 1;\
	buf = static_cast<wchar_t *>(_alloca(len * sizeof(wchar_t)));\
	vswprintf_s(buf, len, fmt, args);

#pragma warning (default : 4996)
