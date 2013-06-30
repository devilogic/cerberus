#include "stdafx.h"
#include "LString.h"

String::String(const char* str)
: std::string(str)
{
}

String::String(const std::string& str)
: std::string(str)
{

}

int String::A2I(void)
{
	return atoi(c_str());
}

float String::A2F(void)
{
	return (float)atof(c_str());
}

// 参数:strSep如果为空则默认为 " ,\t\n/" 
String String::GetToken(int nToken, char* strSep) const
{	
	if (strSep == NULL)
	{
		strSep = " ,\t\n/";
	}

	char* pStrTemp = (char*)(_alloca((length() + 1) * sizeof(char)));
	strcpy(pStrTemp, c_str());

	char* pTemp = (char*)(_alloca((length() + 1) * sizeof(char)));
	char* pToken;	

	strcpy(pTemp, c_str());

	char*  pNextToken = NULL;
	pToken = strtok_s(pTemp, strSep, &pNextToken);

	for(int cToken=0; cToken < nToken; cToken++)
	{
		pToken = strtok_s(NULL, strSep, &pNextToken);
		if(pToken == NULL)
		{			
			return "";
		}
	}
	if(pToken == NULL)
		return "";

	return pToken;
}

void String::Format(const char* pString, ...)
{
	char pStrTemp[2048];
	va_list args;
	va_start(args, pString);
	vsprintf(pStrTemp, pString, args);	
	operator=(pStrTemp);
}

String String::GetFilename(void) const
{	
	int nSize = (int)(length()+ 1);
	char* pStrTemp = (char*)(_alloca(nSize * sizeof(char)));
	strcpy(pStrTemp, c_str());

	char* p = strrchr(pStrTemp, '/');
	if(p == NULL)
	{
		p = strrchr(pStrTemp, '\\');
		if(p == NULL)
		{
			String strRes = pStrTemp;
			return strRes;		 
		}
	}
	p++;

	return p;
}

int String::Search(const char* pStrSearch) const
{
	if(strstr(c_str(), pStrSearch))
		return 1;

	return 0;
}

void String::Replace(char cTarget, char cReplace)
{
	char* pStrTemp = (char*)(_alloca((length() + 1) * sizeof(char)));
	strcpy(pStrTemp, c_str());

	const size_type nLens = length();

	for(size_type cChar=0; cChar < nLens; cChar++)
	{
		if(pStrTemp[ cChar ] == cTarget)
		{
			pStrTemp[ cChar ] = cReplace;
		}
	}

	operator=(pStrTemp);
}

void String::Replace(const char* strTarget, const char* strReplace)
{
	size_type index;

	index = find(strTarget);
	if (index != string::npos)
		replace(index, strlen(strTarget), strReplace);
}

void String::ExtractExt(void)
{
	char* pStrTemp = (char*)(_alloca((length() + 1) * sizeof(char)));
	strcpy(pStrTemp, c_str());

	char* p = strrchr(pStrTemp, '.');	 
	if(p == NULL)
		return;
	*p = 0;

	operator=(pStrTemp);
}

void String::ReplaceExt(char* pExt)
{
	char strTemp[MAX_PATH];
	strcpy(strTemp, c_str());

	char* p = strrchr(strTemp, '.');	 
	if(p == NULL)
		return;
	p++;
	strcpy(p, pExt);

	operator=(strTemp);
}

void String::GetPath(void)
{	
	char* pStrTemp = (char*)(_alloca((length() + 1) * sizeof(char)));
	strcpy(pStrTemp, c_str());

	char* p = strrchr(pStrTemp, '/');
	if(p == NULL)
	{
		p = strrchr(pStrTemp, '\\');
		if(p == NULL)
			return;		 
	}
	p[ 0 ] = 0;	
	operator=(pStrTemp);
}

int String::GetCharCount(char cChar) const
{
	int nCount = 0;
	for(size_type c=0; c < length(); c++)
	{
		if(operator[](c) == cChar)
			nCount++;
	}

	return nCount;	
}

// djb2 hash function
unsigned int ComputeHashCode(const char* pSzString)
{
	unsigned int i,len;
	unsigned int ch;
	unsigned int result;

	len = (unsigned int)strlen(pSzString);
	if(len <= 0)
		return 0;

	result = 5381;
	for(i = 0; i < len; i++)
	{
		ch = (unsigned int)pSzString[i];
		result = ((result << 5) + result) + ch;
	}	  

	return result;
}

bool GetStrParam(const char* pStrString, int iIndex, char* pStrParam)
{
	const char* pFinder = pStrString;
	int iCount = 0;
	bool bOpen = false;
	int iParam = 0;
	int i = 0;
	while (pFinder[i] != '\0' && iCount <= iIndex)
	{
		if (pFinder[i] == '"')
		{
			bOpen = (bOpen == false) ? true : false;
		}
		else
		{
			if (bOpen == false && (pFinder[i] == ' ' || pFinder[i] == '\t'))
			{
				iCount++;
			}
			else
			{
				if (iCount == iIndex)
					pStrParam[iParam++] = pFinder[i];
			}
		}
		i++;
	}
	pStrParam[iParam] = '\0';

	if (iParam == 0)
		return false;

	return true;
}

bool GetStrParam(const wchar_t *pStrString, int iIndex, wchar_t *pStrParam)
{
	const wchar_t *pFinder = pStrString;
	int iCount = 0;
	bool bOpen = false;
	int iParam = 0;
	int i = 0;
	while (pFinder[i] != L'\0' && iCount <= iIndex)
	{
		if (pFinder[i] == L'"')
		{
			bOpen = (bOpen == false) ? true : false;
		}
		else
		{
			if (bOpen == false && (pFinder[i] == L' ' || pFinder[i] == L'\t'))
			{
				iCount++;
			}
			else
			{
				if (iCount == iIndex)
					pStrParam[iParam++] = pFinder[i];
			}
		}
		i++;
	}
	pStrParam[iParam] = L'\0';

	if (iParam == 0)
		return false;

	return true;
}


//////////////////////////////////////////////////////////////////////////

CAnsiToUni2::CAnsiToUni2( const char *pStrAnsi )
{
	int iLen = (int)strlen(pStrAnsi) + 1; 
	m_pString = new wchar_t[iLen];
	MultiByteToWideChar(CP_ACP, 0, pStrAnsi, -1, m_pString, iLen);
}

CAnsiToUni2::~CAnsiToUni2()
{
	if (m_pString)
	{
		delete(m_pString);
		m_pString = NULL;
	}
}

CAnsiToUni2::operator wchar_t*()
{
	return( m_pString );
}

CUniToAnsi2::CUniToAnsi2( const wchar_t *pStrUni )
{
	int iLen = (int)wcslen(pStrUni) * 2 + 1; 
	m_pString = new char[iLen];
	WideCharToMultiByte(CP_ACP, 0, pStrUni, -1, m_pString, iLen, NULL, NULL);
}

CUniToAnsi2::~CUniToAnsi2()
{
	if (m_pString)
	{
		delete(m_pString);
		m_pString = NULL;
	}
}

CUniToAnsi2::operator char*()
{
	return( m_pString );
}