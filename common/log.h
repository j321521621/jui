#pragma once
class clog
{
public:
	clog();
	~clog();
	void output(CString str);
	void output(LPVOID data,int len);
private:
	HANDLE m_file;
	CRITICAL_SECTION m_cs;
};


extern clog *g_clog;

#define logging(fmt,...) {CString tmp;tmp.Format(fmt,##__VA_ARGS__);tmp.Append(L"\r\n");g_clog->output(tmp);}