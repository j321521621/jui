#pragma 
#include <string>

inline CStringW UTF8toUnicode( const char* strSource)
{
	int iWstrLen = ::MultiByteToWideChar(CP_UTF8,0,strSource,-1,NULL,0);
	wchar_t *tempBuffer = new wchar_t[iWstrLen + 1];
	::MultiByteToWideChar(CP_UTF8,0,strSource,-1,tempBuffer,iWstrLen);
	tempBuffer[iWstrLen] = L'\0';
	CStringW ret = tempBuffer;
	delete tempBuffer;
	return ret;
}

inline CStringW ACPtoUnicode( const char* strSource)
{
	int iWstrLen = ::MultiByteToWideChar(CP_ACP,0,strSource,-1,NULL,0);
	wchar_t *tempBuffer = new wchar_t[iWstrLen + 1];
	::MultiByteToWideChar(CP_ACP,0,strSource,-1,tempBuffer,iWstrLen);
	tempBuffer[iWstrLen] = L'\0';
	CStringW ret = tempBuffer;
	delete tempBuffer;
	return ret;
}


inline CStringA UnicodetoUTF8( const wchar_t* strSource)
{
	int iStrLen = ::WideCharToMultiByte(CP_UTF8,0,strSource,-1,0,0,NULL,NULL);
	char *pStrOut = new char[iStrLen + 1];
	::WideCharToMultiByte(CP_UTF8,0,strSource,-1,pStrOut,iStrLen,NULL,NULL);
	pStrOut[iStrLen] = '\0';
	CStringA ret=pStrOut;
	delete pStrOut;
	return ret;
}

inline CStringA UnicodetoACP( const wchar_t* strSource)
{
	int iStrLen = ::WideCharToMultiByte(CP_ACP,0,strSource,-1,0,0,NULL,NULL);
	char *pStrOut = new char[iStrLen + 1];
	::WideCharToMultiByte(CP_ACP,0,strSource,-1,pStrOut,iStrLen,NULL,NULL);
	pStrOut[iStrLen] = '\0';
	CStringA ret=pStrOut;
	delete pStrOut;
	return ret;
}

inline std::string JSONSafeUnicode(std::string strSource)
{
	int len=strlen(strSource.c_str())+1;
	char outch[MAX_PATH];
	WCHAR * wChar=new WCHAR[len];
	wChar[0]=0;
	MultiByteToWideChar(CP_UTF8, 0, strSource.c_str(), len, wChar, len);
	WideCharToMultiByte(CP_ACP, 0, wChar, len, outch , len, 0, 0);
	delete [] wChar;
	char* pchar = (char*)outch;
	return pchar;
}