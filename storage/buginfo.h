#pragma once

#include <vector>
#include <map>

struct BMem{
	BMem(PBYTE pb,DWORD l):pbyte(pb),len(l),filePath(L"")
	{
	}

	PBYTE pbyte;
	DWORD len;

	CString filePath;
};

class BugInfo
{
//bug–≈œ¢
private:

	CString m_userid;
	CString m_taskid;
	std::map<CString,CString> m_data;
	std::vector <BMem> m_vecpic;
	std::vector <BMem> m_vecfile;

public:
	BugInfo();
	~BugInfo();
	//set
	void setUsername(CString tilte);
	void setTaskid(CString content);
	void SetData(CString k,CString v);
	void addPic(BMem bmem );
	void addFile(BMem bmem );

	//get
	CString getUserid(void);
	CString getTaskid(void);
	CString getData(void);
	std::vector <BMem> getpic(void);
	std::vector <BMem> getfile(void);
};



