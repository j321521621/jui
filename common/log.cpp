#include "stdafx.h"
#include "log.h"
#include "../common/common.h"
#include <time.h>

clog::clog():m_file(INVALID_HANDLE_VALUE)
{
	InitializeCriticalSection(&m_cs);
	CString path=L".";
	if(!PathFileExists(path))
	{
		CreateDirectory(path,NULL);
	}
	path+=L"/run.log";
	m_file = ::CreateFile(path, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_file == INVALID_HANDLE_VALUE)
	{
		return;
	}

	LONG posL = 0;
	LONG posH = 0;
	posL = (LONG)::SetFilePointer(m_file, posL, &posH, FILE_END);
	if (posL == 0 && posH == 0)
	{
		output("\xFF\xFE",2);
	}

	output("\r\0\n\0\r\0\n\0\r\0\n\0\r\0\n\0",16);
	output(L"日志系统初始化成功\r\n");
}

clog::~clog()
{
	automutex at(&m_cs);
	if (m_file != INVALID_HANDLE_VALUE)
	{
		output(L"日志系统反初始化\r\n");
		::CloseHandle(m_file);
		m_file = INVALID_HANDLE_VALUE;
	}
}

void clog::output(CString str)
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime (&rawtime);
	CString newstr;
	newstr.Format(L"%04u-%02u-%02u %02u:%02u:%02u %s",timeinfo->tm_year+1900,timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,str);
	output((LPVOID)(LPCTSTR)newstr, newstr.GetLength()*2);	
}

void clog::output(LPVOID data,int len)
{
	if (m_file != INVALID_HANDLE_VALUE)
	{
		DWORD dw;
		::WriteFile(m_file, data, len,&dw, NULL);
	}
}

clog *g_clog=NULL;