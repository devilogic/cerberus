#pragma once

#pragma warning (disable : 4996)

class TiXmlDocument;
class CTinyXmlNode;

#include "tinyxml.h"
#include "LString.h"

typedef CTinyXmlNode XMLNode;
typedef std::vector< CTinyXmlNode* > XMLNodes;

class CTinyXml
{
	TiXmlDocument	*m_pXMLDocument;	
public:
	CTinyXml(void);
	~CTinyXml(void);
	bool		Load( const char * pszFilename, bool bErrorMsgBox = true );	
	bool		LoadBuffer( const char *pBuffer, bool bErrorMsgBox = true );
	XMLNodes	GetChilds( const char * pszChildName );
	XMLNode*	GetChild( const char * pszChildName );
	XMLNode *	GetRootChild( const char * pszChildName );
	void		Close() { };

	XMLNode *	CreateRootNode(const char *pSzRootName);
	XMLNode *	CreateRootCommentNode(const char *pSzRootName);
	bool		Save(const char* pSzFileName);
};

class CTinyXmlNode : public TiXmlNode
{	
public:	
	XMLNode*	GetChild( const char * pszChildName );
	XMLNode*	GetChild( const wchar_t * pwszChildName );
	XMLNode*	GetChildFormat( const char *pSzFormat, ... );
	XMLNodes	GetChilds( const char * pszChildName );
	XMLNodes	GetChilds();	
	String		GetAttr( const char * pszAttrName );
	String		Value();

	void		RemoveAttr( const char * pszAttrName );
	void		SetAttrFloat( const char * pSzAttrName, float &fValue );
	void		SetAttrDWORD( const char *pSzAttrName, DWORD &dwValue );

	int			GetAttrInt( const char *pSzAttrName );
	UINT		GetAttrUINT( const char *pSzAttrName );
	UCHAR		GetAttrUCHAR( const char *pSzAttrName );
	DWORD		GetAttrDWORD( const char *pSzAttrName );
	DWORD64		GetAttrDWORD64( const char *pSzAttrName );
	DWORD		GetAttrHexDWORD( const char *pSzAttrName );
	float		GetAttrFloat( const char *pSzAttrName );
	bool		GetAttrBool( const char *pSzAttrName );

	bool		GetAttr( const char *pSzAttrName, String &strValue );
	bool		GetAttr( const char *pSzAttrName, string & strValue );
	bool		GetAttr( const char *pSzAttrName, wstring & wstrValue );
	bool		GetAttrInt( const char *pSzAttrName, int &iValue );
	bool		GetAttrUINT( const char *pSzAttrName, UINT & unValue );
	bool		GetAttrUCHAR( const char *pSzAttrName, UCHAR  & ucValue );
	bool		GetAttrDWORD( const char *pSzAttrName, DWORD &dwValue );
	bool		GetAttrDWORD64( const char *pSzAttrName, DWORD64 &ddwValue );
	bool		GetAttrHexDWORD( const char *pSzAttrName, DWORD &dwValue );
	bool		GetAttrFloat( const char *pSzAttrName, float &fValue );
	bool		GetAttrDouble( const char *pSzAttrName, double &dValue );
	bool		GetAttrBool( const char *pSzAttrName, bool &bValue );
	void		GetAttrFloat4( void * pData );

	String		GetChildAttr( const char * pszChildName, const char * pszAttrName );
	int			GetChildAttrInt( const char * pszChildName, const char * pszAttrName );	
	UINT		GetChildAttrUINT( const char * pszChildName, const char * pszAttrName );
	UCHAR		GetChildAttrUCHAR( const char * pszChildName, const char * pszAttrName );
	DWORD		GetChildAttrDWORD( const char * pszChildName, const char * pszAttrName );
	DWORD64		GetChildAttrDWORD64( const char * pszChildName, const char * pszAttrName );
	DWORD		GetChildAttrHexDWORD( const char * pszChildName, const char * pszAttrName );
	float		GetChildAttrFloat( const char * pszChildName, const char * pszAttrName );
	bool		GetChildAttrBool( const char * pszChildName, const char * pszAttrName );
	String		GetChildText( const char * pszChildName );
	bool		GetChildBinary( const char *pszChildName, void *pData, int iSize );

	bool		GetChildAttrString( const char * pszChildName, const char * pszAttrName, String & strValue );
	bool		GetChildAttrString( const char * pszChildName, const char * pszAttrName, string & strValue );
	bool		GetChildAttrWstring( const char * pszChildName, const char * pszAttrName, wstring & wstrValue );
	bool		GetChildAttrInt( const char * pszChildName, const char * pszAttrName, int &iValue );
	bool		GetChildAttrUINT( const char * pszChildName, const char * pszAttrName, UINT & unValue );
	bool		GetChildAttrUCHAR( const char * pszChildName, const char * pszAttrName, UCHAR & ucValue );
	bool		GetChildAttrDWORD( const char * pszChildName, const char * pszAttrName, DWORD &dwValue );
	bool		GetChildAttrDWORD64( const char * pszChildName, const char * pszAttrName, DWORD64 &ddwValue );
	bool		GetChildAttrHexDWORD( const char * pszChildName, const char * pszAttrName, DWORD &dwValue );
	bool		GetChildAttrFloat( const char * pszChildName, const char * pszAttrName, float &fValue );
	bool		GetChildAttrDouble( const char * pszChildName, const char * pszAttrName, double &dValue );
	bool		GetChildAttrBool( const char * pszChildName, const char * pszAttrName, bool &bValue );	

	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, String & strValue )			{ return GetChildAttrString( pszChildName, pszAttrName, strValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, string & strValue )			{ return GetChildAttrString( pszChildName, pszAttrName, strValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, wstring & wstrValue )		{ return GetChildAttrWstring( pszChildName, pszAttrName, wstrValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, int & iValue )				{ return GetChildAttrInt( pszChildName, pszAttrName, iValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, DWORD & dwValue )			{ return GetChildAttrDWORD( pszChildName, pszAttrName, dwValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, DWORD64 & ddwValue )		{ return GetChildAttrDWORD64( pszChildName, pszAttrName, ddwValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, float & fValue )			{ return GetChildAttrFloat( pszChildName, pszAttrName, fValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, double & dValue )			{ return GetChildAttrDouble( pszChildName, pszAttrName, dValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, bool & bValue )				{ return GetChildAttrBool( pszChildName, pszAttrName, bValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, UINT & unValue)				{ return GetChildAttrUINT( pszChildName, pszAttrName, unValue ); }

	void		GetChildAttrFloat2( const char * pszChildName, void * pData, int iCount );
	void		GetChildAttrFloat3( const char * pszChildName, void * pData );
	void		GetChildAttrFloat4( const char * pszChildName, void * pData );


	// 노드 추가
	XMLNode *	AddNode( const char * pSzNodeName );
	XMLNode *	AddNode( const wchar_t * pwszNodeName );
	XMLNode *	AddNodeFormat( const char * pSzFormat, ... );

	/////////////////////////////////////////////
	// 속성 추가
	void AddAttribute(const char *pSzAttrName, const char *pSzValue)				{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, pSzValue ); }
	void AddAttribute(const char *pSzAttrName, const wchar_t *pwszValue)			{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, UniToAnsi2( pwszValue ) ); }
	void AddAttribute(const char *pSzAttrName, const string & strValue)				{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, strValue.c_str() ); }
	void AddAttribute(const char *pSzAttrName, const wstring & wstrValue)			{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, UniToAnsi2( wstrValue.c_str() ) ); }
	void AddAttribute(const char *pSzAttrName, int iValue)							{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, iValue ); }
	void AddAttribute(const char *pSzAttrName, DWORD dwValue)						{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, (int)dwValue ); }	
	void AddAttribute(const char *pSzAttrName, DWORD64 dwValue);
	void AddAttribute(const char *pSzAttrName, float fValue)						{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%.6f", fValue ); }
	void AddAttribute(const char *pSzAttrName, double dDouble)						{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%.9f", dDouble ); }
	void AddAttribute(const char *pSzAttrName, unsigned int uiValue)				{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%u", uiValue ); }
	void AddAttribute(const char *pSzAttrName, bool bValue)							{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, bValue ? "TRUE" : "FALSE" ); }
	void AddAttributeBool(const char *pSzAttrName, int iValue)						{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, iValue ? "TRUE" : "FALSE" ); }	
	void AddAttributeFormat(const char * pSzAttrName, const char *pSzFormat, ...);
	void AddAttributeFloat2(const void * pData , int iCount);
	void AddAttributeFloat3(const void * pData);
	void AddAttributeFloat4(const void * pData);
	void AddAttributeText(const char *pSzFormat, ...);
	void AddAttributeHexDword( const char *pSzAttrName, DWORD dwValue);

	/////////////////////////////////////////////
	// 노드 속성 추가
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const char *pSzValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const string & strValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const wchar_t * pwszValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const wstring & wstrValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const int iValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const DWORD dwValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const DWORD64 dwValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const float fValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const double dValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const UINT uiValue);
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const bool bValue);
	XMLNode* AddNodeAttributeFloat2(const char *pSzNodeName, const void *pData , int iCount);
	XMLNode* AddNodeAttributeFloat3(const char *pSzNodeName, const void *pData);
	XMLNode* AddNodeAttributeFloat4(const char *pSzNodeName, const void *pData);
	XMLNode* AddNodeText(const char *pSzNodeName, const char *pSzFormat, ...);
	XMLNode* AddNodeAttributeHexDword(const char *pSzNodeName, const char *pSzAttrName, DWORD dwValue);
	XMLNode* AddNodeBinary(const char *pSzNodeName, void *buff, int size);	 ///< Based64형 텍스트 추가
};

//--------------------------------------------------------------------------------------------------
inline int CTinyXmlNode::GetAttrInt( const char *pSzAttrName )
{
	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
		return (int)atoi(strTemp.GetString());

	return 0;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int		CTinyXmlNode::GetAttrUINT( const char *pSzAttrName )
{
	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
		return (unsigned int)atoi(strTemp.GetString());

	return 0;
}

//--------------------------------------------------------------------------------------------------
inline UCHAR	CTinyXmlNode::GetAttrUCHAR( const char *pSzAttrName )
{
	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
		return (UCHAR)atoi(strTemp.GetString());

	return 0;
}

//--------------------------------------------------------------------------------------------------
inline DWORD CTinyXmlNode::GetAttrDWORD( const char *pSzAttrName )
{
	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
		return (DWORD)atoi(strTemp.GetString());

	return 0xFFFFFFFF;
}

//------------------------------------------------------------------------------------------------------
inline DWORD CTinyXmlNode::GetAttrHexDWORD( const char *pSzAttrName )
{
	/*
	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
	{
		DWORD dwValue = 0;
		sscanf( strTemp.GetString(), "%x", &dwValue );
		return dwValue;
	}
	*/

	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
	{
		if( strTemp.GetToken( 0 ) != "decimal" )
		{
			DWORD dwValue = 0;
			sscanf( strTemp.GetString(), "%x", &dwValue );
			return dwValue;
		}
		else
		{
			DWORD dwValue = 0;
			int nAlpha = 255;
			int nRed = strTemp.GetToken( 1 ).A2I();
			int nGreen = strTemp.GetToken( 2 ).A2I();
			int nBlue = strTemp.GetToken( 3 ).A2I();

			dwValue = (((nAlpha&0xff)<<24)|((nRed&0xff)<<16)|((nGreen&0xff)<<8)|(nBlue&0xff));
			return dwValue;
		}
	}

	return 0xFFFFFFFF;
}

//------------------------------------------------------------------------------------------------------
inline DWORD64 CTinyXmlNode::GetAttrDWORD64( const char *pSzAttrName )
{
	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
		return (DWORD64)_atoi64(strTemp.GetString());

	return 0xFFFFFFFF;
}
//------------------------------------------------------------------------------------------------------
inline float CTinyXmlNode::GetAttrFloat( const char *pSzAttrName )
{
	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
		return (float)atof(strTemp.GetString());

	return 0.0f;
}

//------------------------------------------------------------------------------------------------------
inline bool CTinyXmlNode::GetAttrBool( const char *pSzAttrName )
{
	String strTemp = GetAttr(pSzAttrName);
	if (strTemp.GetLens() > 0)
	{
		//strTemp.MakeLower();
		return (strTemp == "true") ? true : false;
	}

	return false;
}
//------------------------------------------------------------------------------------------------------
inline bool CTinyXmlNode::GetAttrInt( const char *pSzAttrName, int &iValue )
{
	String strTemp;
	if (GetAttr(pSzAttrName, strTemp))
	{
		if (strTemp.GetLens() > 0)
		{
			iValue = (int)atoi(strTemp.GetString());
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------------------------------
inline bool	CTinyXmlNode::GetAttrUINT( const char *pSzAttrName, UINT & unValue )
{
	String strTemp;
	if (GetAttr(pSzAttrName, strTemp))
	{
		if (strTemp.GetLens() > 0)
		{
			unValue = (UINT)atoi(strTemp.GetString());
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------------------------------
inline bool	CTinyXmlNode::GetAttrUCHAR( const char *pSzAttrName, UCHAR  & ucValue )
{
	String strTemp;
	if ( GetAttr(pSzAttrName, strTemp) )
	{
		if (strTemp.GetLens() > 0)
		{
			ucValue = (UCHAR)atoi(strTemp.GetString());
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------------------------------
inline bool CTinyXmlNode::GetAttrDWORD( const char *pSzAttrName, DWORD &dwValue )
{
	String strTemp;
	if (GetAttr(pSzAttrName, strTemp))
	{
		if (strTemp.GetLens() > 0)
		{
			dwValue = (DWORD)atoi(strTemp.GetString());
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------------------------------
inline bool CTinyXmlNode::GetAttrHexDWORD( const char *pSzAttrName, DWORD &dwValue )
{
	String strTemp;
	if (GetAttr(pSzAttrName, strTemp))
	{
		if (strTemp.GetLens() > 0)
		{
			if( strTemp.GetToken( 0 ) != "decimal" )
			{
				sscanf( strTemp.GetString(), "%x", &dwValue );
			}
			else
			{
				int nAlpha = 255;//strTemp.GetToken( 1 ).A2I();
				int nRed = strTemp.GetToken( 1 ).A2I();
				int nGreen = strTemp.GetToken( 2 ).A2I();
				int nBlue = strTemp.GetToken( 3 ).A2I();

				dwValue = (((nAlpha&0xff)<<24)|((nRed&0xff)<<16)|((nGreen&0xff)<<8)|(nBlue&0xff));
			}
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------------------------------
inline bool CTinyXmlNode::GetAttrDWORD64( const char *pSzAttrName, DWORD64 &ddwValue )
{
	String strTemp;
	if (GetAttr(pSzAttrName, strTemp))
	{
		if (strTemp.GetLens() > 0)
		{
			ddwValue = (DWORD64)_atoi64(strTemp.GetString());
			return true;
		}
	}

	return false;
}
//------------------------------------------------------------------------------------------------------
inline bool CTinyXmlNode::GetAttrFloat( const char *pSzAttrName, float &fValue )
{
	String strTemp;
	if (GetAttr(pSzAttrName, strTemp))
	{
		if (strTemp.GetLens() > 0)
		{
			fValue = (float)atof(strTemp.GetString());
			return true;
		}
	}

	return false;
}

inline bool CTinyXmlNode::GetAttrDouble( const char *pSzAttrName, double &dValue )
{
	String strTemp;
	if ( GetAttr( pSzAttrName, strTemp ) )
	{
		if (strTemp.GetLens() > 0)
		{
			dValue = atof( strTemp.GetString() );
			return true;
		}
	}

	return false;
}

inline bool CTinyXmlNode::GetAttrBool( const char *pSzAttrName, bool &bValue )
{
	String strTemp;
	if (GetAttr(pSzAttrName, strTemp))
	{
		if (strTemp.GetLens() > 0)
		{
			//strTemp.MakeLower();
			bValue = ( strTemp == "true" ) ? true : false;
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------------------------------
inline void	CTinyXmlNode::GetAttrFloat4( void * pData )
{
	assert(pData);

	float * fData = (float *)pData;
	GetAttrFloat( "r", fData[ 0 ] );
	GetAttrFloat( "g", fData[ 1 ] );
	GetAttrFloat( "b", fData[ 2 ] );
	GetAttrFloat( "a", fData[ 3 ] );
}

// 저장 관련
//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const char *pSzValue)
{
	XMLNode* pNode = AddNode(pSzNodeName);
	pNode->AddAttribute(pSzAttrName, pSzValue);
	return pNode;
}

//--------------------------------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const string & strValue)
{
	XMLNode* pNode = AddNode(pSzNodeName);
	pNode->AddAttribute( pSzAttrName, strValue.c_str() );
	return pNode;
}

//--------------------------------------------------------------------------------------------------
inline XMLNode * XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const wchar_t * pwszValue)
{
	XMLNode* pNode = AddNode( pSzNodeName );
	pNode->AddAttribute( pSzAttrName, UniToAnsi2( pwszValue ) );
	return pNode;
}

//--------------------------------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const wstring & wstrValue)
{
	XMLNode* pNode = AddNode( pSzNodeName );
	pNode->AddAttribute( pSzAttrName, UniToAnsi2( wstrValue.c_str() ) );
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const int iValue)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttribute(pSzAttrName, iValue);
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const DWORD dwValue)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttribute(pSzAttrName, (int)dwValue);
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const DWORD64 dwValue)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttribute(pSzAttrName, dwValue);
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const float fValue)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttribute(pSzAttrName, fValue);
	return pNode;
}

inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const double dValue)
{
	XMLNode *pNode = AddNode( pSzNodeName );
	pNode->AddAttribute( pSzAttrName, dValue );
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const UINT uiValue)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttribute(pSzAttrName, uiValue);
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const bool bValue)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttribute(pSzAttrName, bValue);
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttributeFloat2(const char *pSzNodeName, const void *pData , int iCount)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttributeFloat2(pData, iCount);
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttributeFloat3(const char *pSzNodeName, const void * pData)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttributeFloat3(pData);
	return pNode;
}

//-----------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttributeFloat4(const char *pSzNodeName, const void *pData)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttributeFloat4(pData);
	return pNode;
}

//--------------------------------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeText(const char *pSzNodeName, const char *pSzFormat, ...)
{
	XMLNode *pNode = AddNode(pSzNodeName);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);
	pNode->AddAttributeText(pSzBuf);
	return pNode;
}

//--------------------------------------------------------------------------------------------------
inline XMLNode* XMLNode::AddNodeAttributeHexDword(const char *pSzNodeName, const char *pSzAttrName, DWORD dwValue)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	String strHex;
	strHex.Format("%x", dwValue);
	pNode->AddAttribute(pSzAttrName, strHex);
	return pNode;
}

//--------------------------------------------------------------------------------------------------
#pragma warning (default : 4996)