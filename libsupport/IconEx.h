typedef struct tagHEADER {
    __word idReserved;  
    __word idType;  
    __word idCount;  
}HEADER, *LPHEADER;  
  
typedef struct tagICONDIRENTRY {  
    __byte bWidth;  
    __byte bHeight;  
    __byte bColorCount;  
    __byte bReserved;  
    __word wPlanes;  
    __word wBitCount;  
    __dword dwBytesInRes;  
    __dword dwImageOffset;  
} ICONDIRENTRY, *LPICONDIRENTRY;  
  
#pragma pack( push )  
#pragma pack( 2 )  
typedef struct tagGRPICONDIRENTRY {  
    __byte bWidth;  
    __byte bHeight;  
    __byte bColorCount;  
    __byte bReserved;  
    __word wPlanes;  
    __word wBitCount;  
    __dword dwBytesInRes;  
    __word nID;  
} GRPICONDIRENTRY, *LPGRPICONDIRENTRY;;  
  
typedef struct tagGRPICONDIR {  
    __word idReserved;  
    __word idType;  
    __word idCount;  
    GRPICONDIRENTRY idEntries[1];  
}GRPICONDIR, *LPGRPICONDIR;  
#pragma pack( pop )
