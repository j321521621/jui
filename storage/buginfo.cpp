#include "stdafx.h"
#include "buginfo.h"
#include "Json.h"
#include "../common/util.h"


BugInfo::BugInfo()
{
}
BugInfo::~BugInfo()
{
}

void BugInfo::setUsername(CString userid)
{
	this->m_userid = userid;
}

void BugInfo::setTaskid(CString taskid)
{
	this->m_taskid = taskid;
}

void BugInfo::SetData(CString k,CString v)
{
	m_data[k] = v;
}
void BugInfo::addPic(BMem bmem )
{
	m_vecpic.push_back(bmem);
}
void BugInfo::addFile(BMem bmem )
{
	m_vecfile.push_back(bmem);
}

//get
CString BugInfo::getUserid(void)
{
	return this->m_userid;
}

CString BugInfo::getTaskid(void)
{
	return this->m_taskid;
}

CString BugInfo::getData(){
	Json::Value root;
	std::map<CString,CString>::iterator it;
	for(it=m_data.begin();it!=m_data.end();++it)
	{
		std::string key = UnicodetoACP(it->first);
		std::string value = UnicodetoACP(it->second);
		root[key] = value;
	}
	return ACPtoUnicode(root.toStyledString().c_str());
}

std::vector <BMem> BugInfo::getpic(void)
{
	return m_vecpic;
}
std::vector <BMem> BugInfo::getfile(void)
{
	return m_vecfile;
}
