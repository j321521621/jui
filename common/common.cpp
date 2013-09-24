#include "stdafx.h"



HRESULT ReadRegister(HKEY root,LPCTSTR path,LPCTSTR name,CString& value)
{
	HKEY hkey; 
	DWORD type;
	DWORD sz=256;

	DWORD hret=RegOpenKeyEx(root,path,NULL,KEY_READ,&hkey);
	if(hret==ERROR_SUCCESS)
	{
		HRESULT hret=RegQueryValueEx(hkey,name, NULL, &type,(LPBYTE)value.GetBuffer(sz), &sz);
		if(hret==ERROR_MORE_DATA )
		{
			hret=RegQueryValueEx(hkey,name, NULL, &type,(LPBYTE)value.GetBuffer(sz), &sz);
		}
		value.ReleaseBuffer();
		if(hret==ERROR_SUCCESS)
		{
			if(type!=REG_SZ)
			{
				value=L"";
				RegCloseKey(hkey); 
				return E_FAIL;
			}
			else
			{

				RegCloseKey(hkey); 
				return S_OK;
			}
		}
		else
		{
			value=L"";
			RegCloseKey(hkey); 
			return E_FAIL;
		}
	}
	else
	{
		value=L"";
		RegCloseKey(hkey); 
		return E_FAIL;
	}
}

HRESULT QueryRegister(HKEY root,LPCTSTR path)
{
	HKEY hkey;
	DWORD sz=256;

	DWORD hret=RegOpenKeyEx(root,path,NULL,KEY_READ,&hkey);
	if(hret==ERROR_SUCCESS)
	{
		RegCloseKey(hkey); 
		return S_OK;
	}
	else
	{
		RegCloseKey(hkey); 
		return E_FAIL;
	}
}


HRESULT WriteRegister(HKEY root,LPCTSTR path,LPCTSTR name,CString value)
{
	HKEY hkey; 
	DWORD sz=256;

	DWORD hret=RegOpenKeyEx(root,path,NULL,KEY_SET_VALUE,&hkey);
	if(hret=ERROR_FILE_NOT_FOUND)
	{
		HKEY hkeytemp;
		DWORD hrettemp=RegCreateKeyEx(root,path,NULL,NULL,NULL,KEY_READ,NULL,&hkeytemp,NULL);
		RegCloseKey(hkeytemp);
		hret=RegOpenKeyEx(root,path,NULL,KEY_SET_VALUE,&hkey);
	}

	if(hret==ERROR_SUCCESS)
	{
		HRESULT hret=RegSetValueEx(hkey,name, NULL, REG_SZ,(LPBYTE)(LPCTSTR)value, value.GetLength()*2+2);
		if(hret==ERROR_SUCCESS)
		{
			RegCloseKey(hkey); 
			return S_OK;
		}
		else
		{
			RegCloseKey(hkey); 
			return E_FAIL;
		}
	}
	else
	{
		RegCloseKey(hkey); 
		return E_FAIL;
	}
}