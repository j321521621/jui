#pragma once
//������Ϣ�ṹ��
struct UserTask{

	CString taskID;
	CString taskName;
	int number;
};


struct Logininfo
{
	Logininfo(CString userName,CString password,CString vcodekey=L"",CString vcodevalue=L""):
m_userName(userName),
	m_password(password),
	m_vcodekey(vcodekey),
	m_vcodevalue(vcodevalue)
{}

CString m_userName ;
CString m_password;
CString m_vcodekey;
CString m_vcodevalue;
};


struct Logresult{
	int m_result;
	CString m_vcodekey;                //�������˷��ص���֤��keyֵ
	CString m_imageurl;                 //��֤��url
	Logresult(int result=1, CString vkey=L"", CString m_imageurl=L""){}
};



