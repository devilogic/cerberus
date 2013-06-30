#include "stdafx.h"
#include "CTinyXml.h"

//----------------------------------------------------------------------------------------------
struct SXmlFloat2
{
	float x;
	float y;
};
struct SXmlFloat3
{
	float x;
	float y;
	float z;
};
struct SXmlFloat4
{
	float r;
	float g;
	float b;
	float a;
};
	
#define	 BOOLVALUE_TO_STRING(b) (b) ? "TRUE" : "FALSE"
#define	 BOOLSTRING_TO_VALUE(b) (strcmp(b, "TRUE")) ? 0 : 1

//----------------------------------------------------------------------------------------------
CTinyXml::CTinyXml(void)
{
	m_pXMLDocument = new TiXmlDocument;
}

CTinyXml::~CTinyXml(void)
{
	Close();
	if (m_pXMLDocument)
	{
		delete m_pXMLDocument;
		m_pXMLDocument = NULL;
	}
}

bool CTinyXml::Load( const char * pszFilename, bool bErrorMsgBox )
{
	//TiXmlDocument XMLFile( strFilename.GetString() );	

	if( m_pXMLDocument->LoadFile( pszFilename ) == false )
	{
		//g_pError->SetErrorFormat(1, "XML Load Error = %s : %s \n Line = %d", pszFilename, m_pXMLDocument->ErrorDesc(), m_pXMLDocument->ErrorRow() );
		//if (bErrorMsgBox)
		//	MessageBox( NULL, g_pError->GetErrorString(), "Load XML Error", 0 );
		return false;
	}	
	return true;
}

//-----------------------------------------------------------------------------
bool CTinyXml::Save(const char* pSzFileName)	
{	
	assert(pSzFileName);

	return m_pXMLDocument->SaveFile(pSzFileName);	
}

//-----------------------------------------------------------------------------
XMLNode * CTinyXml::CreateRootNode(const char *pSzRootName)
{
	assert(pSzRootName);

	TiXmlNode *pChildNode;
	pChildNode = m_pXMLDocument->InsertEndChild(TiXmlElement(pSzRootName));

	return (XMLNode*)pChildNode;
}

XMLNode * CTinyXml::CreateRootCommentNode(const char *pSzRootName)
{
	assert(pSzRootName);

	TiXmlNode *pChildNode;
	pChildNode = m_pXMLDocument->InsertEndChild(TiXmlComment(pSzRootName));

	return (XMLNode*)pChildNode;
}


//---------------------------------------------------------------------------------
bool CTinyXml::LoadBuffer( const char *pBuffer, bool bErrorMsgBox )
{	
	m_pXMLDocument->Parse( pBuffer );

	if( m_pXMLDocument->Error() )
	{		
		m_pXMLDocument->Parse( pBuffer );
		if( m_pXMLDocument->Error() )
		{
			//g_pError->SetErrorFormat(1, "XML Load Error = %s \n Line = %d", m_pXMLDocument->ErrorDesc(), m_pXMLDocument->ErrorRow() );
			//if (bErrorMsgBox)
			//	MessageBox( NULL, g_pError->GetErrorString(), "Load XML Error", 0 );
			return false;
		}
	}	
	return true;
}

XMLNodes CTinyXml::GetChilds( const char * pszChildName )
{
	XMLNodes lstChildNode;

	TiXmlNode *pChildNode;
	
	pChildNode = m_pXMLDocument->FirstChild()->FirstChild( pszChildName );	
	
	for( ; pChildNode; pChildNode = pChildNode->NextSibling( pszChildName ) )
	{
		lstChildNode.push_back( ( XMLNode*) pChildNode );
	}

	return lstChildNode;
}

XMLNode* CTinyXml::GetChild( const char * pszChildName )
{
	TiXmlNode *pChildNode;
	pChildNode = m_pXMLDocument->FirstChild()->FirstChild( pszChildName );		

	return (XMLNode*)pChildNode;
}

XMLNode *CTinyXml::GetRootChild( const char * pszChildName )
{
	TiXmlNode *pChildNode;
	pChildNode = m_pXMLDocument->FirstChild( pszChildName );		

	return (XMLNode*)pChildNode;
}



///////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------------
XMLNodes CTinyXmlNode::GetChilds( const char * pszChildName )
{
	XMLNodes lstChildNode;

	TiXmlNode *pChildNode;
	
	pChildNode = FirstChild( pszChildName );	
	
	for( ; pChildNode; pChildNode = pChildNode->NextSibling( pszChildName ) )
		lstChildNode.push_back( (XMLNode*)pChildNode );

	return lstChildNode;
}

XMLNodes CTinyXmlNode::GetChilds()
{
	XMLNodes lstChildNode;

	TiXmlNode *pChildNode;
	
	pChildNode = FirstChild();	
	
	for( ; pChildNode; pChildNode = pChildNode->NextSibling() )
	{
		lstChildNode.push_back( (XMLNode*)pChildNode );
	}

	return lstChildNode;
}


XMLNode* CTinyXmlNode::GetChild( const char * pszChildName )
{
	return (XMLNode*)FirstChild( pszChildName );
}

XMLNode*	CTinyXmlNode::GetChild( const wchar_t * pwszChildName )
{
	return (XMLNode*)FirstChild( UniToAnsi2( pwszChildName ) );
}

//-----------------------------------------------------------------------------
XMLNode* CTinyXmlNode::GetChildFormat(const char *pSzFormat, ...)
{
	assert(pSzFormat);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);

	return GetChild( pSzBuf );
}

String CTinyXmlNode::GetAttr( const char * pszAttrName )
{
	TiXmlElement* pElement = ToElement();

	const char* pAttr = pElement->Attribute( pszAttrName );

	if( pAttr )
		return pAttr;
	else
		return "";
}

//--------------------------------------------------------------------------------------------------
bool CTinyXmlNode::GetAttr( const char * pSzAttrName, String &strValue )
{
	TiXmlElement* pElement = NULL;
	pElement = ToElement();
	//pElement = FirstChild()->ToElement();
	const char * pAttr = pElement->Attribute( pSzAttrName );
	if( pAttr )
	{
		strValue = pAttr;
		return true;
	}

	return false;
}

//--------------------------------------------------------------------------------------------------
bool	CTinyXmlNode::GetAttr( const char *pSzAttrName, string & strValue )
{
	TiXmlElement* pElement = NULL;
	pElement = ToElement();
	//pElement = FirstChild()->ToElement();
	const char *pAttr = pElement->Attribute( pSzAttrName );
	if( pAttr )
	{
		strValue = pAttr;
		return true;
	}

	return false;
}

//--------------------------------------------------------------------------------------------------
bool	CTinyXmlNode::GetAttr( const char *pSzAttrName, wstring & wstrValue )
{
	String strTemp;
	if( !GetAttr( pSzAttrName, strTemp ) )
		return false;

	wstrValue = AnsiToUni2( strTemp.GetString() );
	return true;
}

//--------------------------------------------------------------------------------------------------
String CTinyXmlNode::Value()
{
	TiXmlNode *pChildNode;
	pChildNode = FirstChild();
	if (pChildNode)
		return pChildNode->Value();
	return "";
}

String CTinyXmlNode::GetChildAttr( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttr(pszAttrName);
	return "";
}

int	CTinyXmlNode::GetChildAttrInt( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrInt(pszAttrName);
	return 0;
}

UINT	CTinyXmlNode::GetChildAttrUINT( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrUINT( pszAttrName );
	return 0;
}

UCHAR	CTinyXmlNode::GetChildAttrUCHAR( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrUCHAR( pszAttrName );
	return 0;
}

DWORD CTinyXmlNode::GetChildAttrDWORD( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrDWORD(pszAttrName);
	return 0;
}

DWORD CTinyXmlNode::GetChildAttrHexDWORD( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrHexDWORD(pszAttrName);
	return 0;
}

DWORD64 CTinyXmlNode::GetChildAttrDWORD64( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrDWORD64(pszAttrName);
	return 0;
}


float CTinyXmlNode::GetChildAttrFloat( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrFloat(pszAttrName);
	return 0.0f;
}

bool CTinyXmlNode::GetChildAttrBool( const char * pszChildName, const char * pszAttrName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
	{
		return pNode->GetAttrBool(pszAttrName);
	}
	return false;
}

//--------------------------------------------------------------------------------------------------
bool	CTinyXmlNode::GetChildAttrString( const char * pszChildName, const char * pszAttrName, String & strValue )
{
	XMLNode *pNode = GetChild( pszChildName );
	if ( pNode )
		return pNode->GetAttr( pszAttrName, strValue );

	return false;
}

bool	CTinyXmlNode::GetChildAttrString( const char * pszChildName, const char * pszAttrName, string & strValue )
{
	XMLNode *pNode = GetChild( pszChildName );
	if ( pNode )
		return pNode->GetAttr( pszAttrName, strValue );

	return false;
}

bool CTinyXmlNode::GetChildAttrWstring( const char * pszChildName, const char * pszAttrName, wstring & wstrValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
	{
		String strTemp;
		bool bSucceeded = pNode->GetAttr( pszAttrName, strTemp );
		wstrValue = AnsiToUni2( strTemp.c_str() );		
		return bSucceeded;
	}

	return false;
}

bool CTinyXmlNode::GetChildAttrInt( const char * pszChildName, const char * pszAttrName, int &iValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrInt(pszAttrName, iValue);
	return false;
}

bool	CTinyXmlNode::GetChildAttrUINT( const char * pszChildName, const char * pszAttrName, UINT & unValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrUINT(pszAttrName, unValue);
	return false;
}

bool	CTinyXmlNode::GetChildAttrUCHAR( const char * pszChildName, const char * pszAttrName, UCHAR & ucValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrUCHAR(pszAttrName, ucValue);
	return false;
}

bool CTinyXmlNode::GetChildAttrDWORD( const char * pszChildName, const char * pszAttrName, DWORD &dwValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrDWORD(pszAttrName, dwValue);
	return false;
}

bool CTinyXmlNode::GetChildAttrHexDWORD( const char * pszChildName, const char * pszAttrName, DWORD &dwValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrHexDWORD(pszAttrName, dwValue);
	return false;
}

bool CTinyXmlNode::GetChildAttrDWORD64( const char * pszChildName, const char * pszAttrName, DWORD64 &ddwValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrDWORD64(pszAttrName, ddwValue);
	return false;
}

bool CTinyXmlNode::GetChildAttrFloat( const char * pszChildName, const char * pszAttrName, float &fValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrFloat(pszAttrName, fValue);
	return false;
}

bool CTinyXmlNode::GetChildAttrDouble( const char * pszChildName, const char * pszAttrName, double &dValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if( pNode != NULL )
		return pNode->GetAttrDouble( pszAttrName, dValue );

	return false;
}

bool CTinyXmlNode::GetChildAttrBool( const char * pszChildName, const char * pszAttrName, bool &bValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->GetAttrBool(pszAttrName, bValue);
	return false;
}
//------------------------------------------------------------------------
String CTinyXmlNode::GetChildText( const char * pszChildName )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
		return pNode->Value();
	return "";
}

bool CTinyXmlNode::GetChildBinary( const char *pszChildName, void *pData, int iSize )
{
	XMLNode *pNode = GetChild(pszChildName);
	if ( pNode == NULL )
		return false;

	if ( pNode->GetAttr( "binary") != "true" )
		return false;

	//사이즈가 다르면 그냥 리턴
	if( pNode->GetAttrInt( "length" ) != iSize )
	{
		return false;
	}

	String strTemp = pNode->Value();

	memcpy( pData, strTemp.GetString() , strTemp.GetLens() );
	return true;
}


void CTinyXmlNode::GetChildAttrFloat2( const char * pszChildName, void * pData, int iCount )
{
	assert(pData);

	char szBuffer[256];
	SXmlFloat2 *pFloat2 = static_cast<SXmlFloat2 *>(pData);
	for (int i=0; i<iCount; i++)
	{
		sprintf_s(szBuffer, 256, "x%d", i);
		GetChildAttrFloat( pszChildName, szBuffer, pFloat2[i].x );
		sprintf_s(szBuffer, 256, "y%d", i);
		GetChildAttrFloat( pszChildName, szBuffer, pFloat2[i].y );
	}
}

void CTinyXmlNode::GetChildAttrFloat3( const char * pszChildName, void *pData )
{
	assert(pData);

	SXmlFloat3 *pFloat3 = static_cast<SXmlFloat3 *>(pData);
	GetChildAttrFloat( pszChildName, "x", pFloat3->x );
	GetChildAttrFloat( pszChildName, "y", pFloat3->y );
	GetChildAttrFloat( pszChildName, "z", pFloat3->z );

}

void CTinyXmlNode::GetChildAttrFloat4( const char * pszChildName, void *pData )
{
	assert(pData);
	
	SXmlFloat4 *pFloat4 = static_cast<SXmlFloat4 *>(pData);
	GetChildAttrFloat( pszChildName, "r", pFloat4->r );
	GetChildAttrFloat( pszChildName, "g", pFloat4->g );
	GetChildAttrFloat( pszChildName, "b", pFloat4->b );
	GetChildAttrFloat( pszChildName, "a", pFloat4->a );
}

//-------------------------------------------------------------------------------
CTinyXmlNode* CTinyXmlNode::AddNode(const char *pSzNodeName)
{
	assert(pSzNodeName);
	return ( XMLNode * )InsertEndChild( TiXmlElement( pSzNodeName ) );
}

XMLNode *	CTinyXmlNode::AddNode( const wchar_t * pwszNodeName )
{
	assert( pwszNodeName );
	return ( XMLNode * )InsertEndChild( TiXmlElement( UniToAnsi2( pwszNodeName ) ) );
}

//-----------------------------------------------------------------------------
CTinyXmlNode* CTinyXmlNode::AddNodeFormat(const char *pSzFormat, ...)
{
	assert(pSzFormat);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);

	TiXmlNode *pChildNode;
	pChildNode = InsertEndChild(TiXmlElement(pSzBuf));
	return (XMLNode*)pChildNode;
}

//-----------------------------------------------------------------------------
void CTinyXmlNode::AddAttribute(const char *pSzAttrName, DWORD64 dwValue)
{
	assert(pSzAttrName);

	char buffer[128];
	_i64toa( dwValue, buffer, 10 ); 	
	AddAttribute(pSzAttrName, buffer);
}

//-----------------------------------------------------------------------------
void CTinyXmlNode::AddAttributeFormat(const char *pSzAttrName, const char *pSzFormat, ...)
{
	assert(pSzAttrName);
	assert(pSzFormat);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);
	ToElement()->SetAttribute(pSzAttrName, pSzBuf);
}

//-----------------------------------------------------------------------------
void CTinyXmlNode::AddAttributeFloat2(const void * pData , int iCount)
{
	assert(pData);

	char szBuffer[256];
	const SXmlFloat2 *pFloat2 = static_cast<const SXmlFloat2 *>(pData);
	for (int i=0; i<iCount; i++)
	{
		sprintf_s(szBuffer, 256, "x%d", i);
		AddAttributeFormat(szBuffer, "%.9f", pFloat2[i].x);
		sprintf_s(szBuffer, 256, "y%d", i);
		AddAttributeFormat(szBuffer, "%.9f", pFloat2[i].y);
	}
}

//-----------------------------------------------------------------------------
void CTinyXmlNode::AddAttributeFloat3(const void * pData)
{
	assert(pData);

	const SXmlFloat3 *pFloat3 = static_cast<const SXmlFloat3 *>(pData);
	AddAttributeFormat("x", "%.9f", pFloat3->x);
	AddAttributeFormat("y", "%.9f", pFloat3->y);
	AddAttributeFormat("z", "%.9f", pFloat3->z);
}

//-----------------------------------------------------------------------------
void CTinyXmlNode::AddAttributeFloat4(const void * pData)
{
	assert(pData);

	const SXmlFloat4 *pFloat4 = static_cast<const SXmlFloat4 *>(pData);
	AddAttributeFormat("r", "%.9f", pFloat4->r);
	AddAttributeFormat("g", "%.9f", pFloat4->g);
	AddAttributeFormat("b", "%.9f", pFloat4->b);
	AddAttributeFormat("a", "%.9f", pFloat4->a);
}

//-----------------------------------------------------------------------------
void CTinyXmlNode::AddAttributeText(const char *pSzFormat, ...)
{
	assert(pSzFormat);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);
	InsertEndChild(TiXmlText(pSzBuf));
}

//-----------------------------------------------------------------------------
void CTinyXmlNode::AddAttributeHexDword( const char *pSzAttrName, DWORD dwValue)
{
	String strHex;
	strHex.Format( "%x", dwValue );
	AddAttribute( pSzAttrName, strHex );
}

XMLNode* CTinyXmlNode::AddNodeBinary(const char *pSzNodeName, void *buff, int size)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttribute("binary", "true");
	pNode->AddAttribute("length", size);

	pNode->InsertEndChild( TiXmlText((char*)buff) );

	return pNode;
}

//-----------------------------------------------------------------------------
void CTinyXmlNode::RemoveAttr( const char * pszAttrName )
{
	TiXmlElement* pElement = NULL;
	pElement = ToElement();	
	pElement->RemoveAttribute( pszAttrName );
}

void CTinyXmlNode::SetAttrFloat( const char *pSzAttrName, float &fValue )
{
	assert( pSzAttrName );

	RemoveAttr( pSzAttrName );

	AddAttributeFormat( pSzAttrName, "%f", fValue );
}

void CTinyXmlNode::SetAttrDWORD( const char *pSzAttrName, DWORD &dwValue )
{
	assert( pSzAttrName );

	RemoveAttr( pSzAttrName );

	AddAttributeFormat( pSzAttrName, "%x", dwValue );
}