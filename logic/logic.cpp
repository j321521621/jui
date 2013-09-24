#include "stdafx.h"
#include <shellapi.h>
#include "common\common.h"


CString GetQQ()
{
	CString ret;
	ReadRegister(HKEY_CURRENT_USER,L"Software\\baidu\\UsetTest",L"qq",ret);
	return ret;
}

void SetQQ(CString qq)
{
	
	WriteRegister(HKEY_CURRENT_USER,L"Software\\baidu\\UsetTest",L"qq",qq);
}

CString GetUsername()
{
	CString ret;
	ReadRegister(HKEY_CURRENT_USER,L"Software\\baidu\\UsetTest",L"username",ret);
	return ret;
}

void SetUsername(CString str)
{
	WriteRegister(HKEY_CURRENT_USER,L"Software\\baidu\\UsetTest",L"username",str);
}


CString GetPassword()
{
	CString ret;
	ReadRegister(HKEY_CURRENT_USER,L"Software\\baidu\\UsetTest",L"info",ret);
	return ret;
}

void SetPassword(CString str)
{
	WriteRegister(HKEY_CURRENT_USER,L"Software\\baidu\\UsetTest",L"info",str);
}

CString GetOsVer()
{
	CString winver;
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if( GetVersionEx((LPOSVERSIONINFOW)&osvi))
	{
		winver.Format(L"%d.%d.%d",osvi.dwMajorVersion,osvi.dwMinorVersion,osvi.dwBuildNumber);
	}

	return winver;
}

CString GetIeVer()
{
	CString iever;
	HKEY key;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Microsoft\\Internet Explorer",0,KEY_READ,&key)== ERROR_SUCCESS)
	{
		WCHAR tdata[100]=L"\0";
		DWORD sz=100;
		if(RegQueryValueEx(key,L"Version",NULL,NULL,(LPBYTE)&tdata,&sz)==ERROR_SUCCESS)
		{
			iever=tdata;
		}
		RegCloseKey(key);
	}

	return iever;
}


HBITMAP Snapshot()
{
	if (OpenClipboard(NULL))
	{
		EmptyClipboard();
		CloseClipboard();
	}

	STARTUPINFO si={};
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi={};
	WCHAR cmd[32768]=L"screensnapshot.exe";
	if(CreateProcess(NULL,cmd,NULL,NULL,FALSE,NULL,NULL,NULL,&si,&pi))
	{
		WaitForSingleObject(pi.hProcess,INFINITE);
	}

	HBITMAP hret=NULL;

	if (OpenClipboard(NULL))
	{
		HBITMAP hbit=(HBITMAP)GetClipboardData(CF_BITMAP);
		if(hbit)
		{
			CImage src;
			src.Attach(hbit);
			CImage dst;
			dst.Create(src.GetWidth(),src.GetHeight(),24);
			::BitBlt(CImageDC(dst),0,0,dst.GetWidth(),dst.GetHeight(),CImageDC(src),0,0,SRCCOPY);
			src.Detach();
			hret=dst.Detach();
		}
		CloseClipboard();
	}

	return hret;
}


HBITMAP Getlocalpic(CString path)
{
	HBITMAP hret=NULL;
	CImage src;
	src.Load(path);
	hret = src.Detach();
	return hret;
}
BOOL UpgradeProcessPrivilege(HANDLE hProcess,LPCTSTR lpPrivilegeName = SE_DEBUG_NAME)
{
	HANDLE hToken = NULL;
	if(OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken)) 
	{
		LUID Luid;
		if(LookupPrivilegeValue(NULL, lpPrivilegeName, &Luid)) 
		{
			TOKEN_PRIVILEGES tp;
			tp.PrivilegeCount = 1;
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			tp.Privileges[0].Luid = Luid;
			return( AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL) );
		}
	}
	return FALSE;
}

void startupdate(CString name)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	LPTSTR szCmdline=_tcsdup(name);
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	if( !CreateProcess( NULL,   // No module name (use command line)
		szCmdline,      // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory
		&si,            // Pointer to STARTUPINFO structure
		&pi )           // Pointer to PROCESS_INFORMATION structure
		)
	{
		return;
	}
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}