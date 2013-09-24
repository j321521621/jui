#pragma once

class automutex
{
public:

	static void init(LPCRITICAL_SECTION cs)
	{
		InitializeCriticalSection(cs); 
	}

	automutex(LPCRITICAL_SECTION cs)
	{
		m_cs=cs;
		EnterCriticalSection(m_cs);
	};
	~automutex()
	{
		LeaveCriticalSection(m_cs);
	};
private:
	LPCRITICAL_SECTION m_cs;
};


HRESULT ReadRegister(HKEY root,LPCTSTR path,LPCTSTR name,CString& value);
HRESULT WriteRegister(HKEY root,LPCTSTR path,LPCTSTR name,CString value);
HRESULT QueryRegister(HKEY root,LPCTSTR path);