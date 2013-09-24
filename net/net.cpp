#include "stdafx.h"
#include "common/util.h"
#include <Json.h>
#include <string>
#include "storage/userinfo.h"
#include "storage\buginfo.h"
#include "common\log.h"
#include "common\Base64.h"

#include "net.h"



static VOID mycurl_addstr(CURL *handle,struct curl_httppost *&post,struct curl_httppost *&last,LPCSTR name,LPCWSTR value)
{
	char* out=curl_easy_escape(handle,UnicodetoUTF8(value),0);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, name, CURLFORM_COPYCONTENTS ,out, CURLFORM_END);
	curl_free(out);
}

static VOID mycurl_addstr(CURL *handle,struct curl_httppost *&post,struct curl_httppost *&last,LPCSTR name,LPCSTR value)
{
	char* out=curl_easy_escape(handle,value,0);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, name, CURLFORM_COPYCONTENTS ,out, CURLFORM_END);
	curl_free(out);
}

size_t callback_curl( char *ptr, size_t size, size_t nmemb, void *userdata)
{
	Data *data=(Data*)userdata;
	data->adddatablock(Data(ptr,size*nmemb));
	return size*nmemb;
}

vector<UserTask> getTask(CString userid)
{

	CURL *handle=curl_easy_init();
	struct curl_httppost *post = NULL;
	struct curl_httppost *last  = NULL;

	mycurl_addstr(handle,post,last,"userid", userid);

	Data data;
	curl_easy_setopt(handle,CURLOPT_HTTPPOST,post);
	curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,callback_curl);
	curl_easy_setopt(handle,CURLOPT_WRITEDATA,&data);
	curl_easy_setopt(handle,CURLOPT_URL,"http://advice.client.baidu.com/api/gettask.php");
	curl_easy_perform(handle);
	curl_formfree(post);
	curl_easy_cleanup(handle);

	data.addword(0);

	vector<UserTask> ret;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(data.getdata(), root))
	{
		int intStatus = root["status"].asInt();
		std::string strDesc =JSONSafeUnicode(root["desc"].asString());
		//通过子串实现嵌套字元的解析
		int file_size = root["tasklist"].size();
		// 遍历数组
		if (file_size >=0)
		{
			for(int i = 0; i < file_size; ++i)
			{
				UserTask userTask;
				if(root["tasklist"][i]["taskid"].isString())
				{
					userTask.taskID = ACPtoUnicode(root["tasklist"][i]["taskid"].asString().c_str());
				}
				else
				{
					continue;
				}

				if(root["tasklist"][i]["taskname"].isString())
				{
					userTask.taskName = ACPtoUnicode(JSONSafeUnicode(root["tasklist"][i]["taskname"].asString()).c_str());
				}
				else
				{
					continue;
				}

				if(root["tasklist"][i]["number"].isInt())
				{
					userTask.number=root["tasklist"][i]["number"].asInt();
				}
				else
				{
					continue;
				}

				ret.push_back(userTask);
			}
		}
	}

	return ret;
}



int upload(BugInfo bugInfo,type_CallbackProcess callback_process,void *progress_data)
{
	CURL *handle=curl_easy_init();

	struct curl_httppost *post = NULL;
	struct curl_httppost *last  = NULL;

	mycurl_addstr(handle,post,last,"userid",bugInfo.getUserid());
	mycurl_addstr(handle,post,last,"taskid", bugInfo.getTaskid());
	mycurl_addstr(handle,post,last,"data",bugInfo.getData());
	vector<BMem> ppiclist = bugInfo.getpic();
	vector<BMem> pfilelist = bugInfo.getfile();
	vector<BMem>::iterator iter;
	int num =0;
	for (iter=ppiclist.begin();iter!=ppiclist.end();iter++)  
	{
		CStringA picName;
		picName.Format("pic%d",num);
		if (iter->pbyte!=NULL)
		{
			curl_formadd(&post, &last, CURLFORM_COPYNAME, picName, CURLFORM_BUFFER,picName,CURLFORM_BUFFERPTR,iter->pbyte,CURLFORM_BUFFERLENGTH,iter->len,CURLFORM_END);
		}
		num++;
	}
	num =0;
	for (iter=pfilelist.begin();iter!=pfilelist.end();iter++)  
	{  
		CStringA fileName;
		fileName.Format("file%d",num);
		if (iter->pbyte!=NULL)
		{
			curl_formadd(&post, &last, CURLFORM_COPYNAME, fileName, CURLFORM_BUFFER,fileName,CURLFORM_BUFFERPTR,iter->pbyte,CURLFORM_BUFFERLENGTH,iter->len,CURLFORM_END);
		}
		num++;
	} 

	Data data;
	curl_easy_setopt(handle,CURLOPT_HTTPPOST,post);
	curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(handle, CURLOPT_PROGRESSFUNCTION, callback_process);
	curl_easy_setopt(handle, CURLOPT_PROGRESSDATA, progress_data);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, &data);
	curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,callback_curl);
	curl_easy_setopt(handle,CURLOPT_URL,"http://advice.client.baidu.com/api/bugreport.php");
	curl_easy_perform(handle);
	curl_formfree(post);
	curl_easy_cleanup(handle);

	data.addword(0);
	int ret=1;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(data.getdata(), root))
	{
		if(root["status"].isInt())
		{
			ret=root["status"].asInt();
		}
	}

	return ret;
}



Logresult login(Logininfo userinfo)
{
	CURL *handle=curl_easy_init();
	struct curl_httppost *post = NULL;
	struct curl_httppost *last  = NULL;

	mycurl_addstr(handle,post,last,"userid", userinfo.m_userName);

	string password = UnicodetoACP(userinfo.m_password);
	unsigned char pIn[100];  
	memcpy(pIn,password.c_str(),strlen(password.c_str())+1);  
	string strout;  
	int i=0;
	while(pIn[i]!='\0'){i++;}
	CBase64::Encode(pIn, i, strout);
	mycurl_addstr(handle,post,last,"password",strout.c_str());
	mycurl_addstr(handle,post,last,"vcodekey",userinfo.m_vcodekey);
	mycurl_addstr(handle,post,last,"vcodevalue",userinfo.m_vcodevalue);

	Data data;
	curl_easy_setopt(handle,CURLOPT_HTTPPOST,post);
	curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,callback_curl);
	curl_easy_setopt(handle,CURLOPT_WRITEDATA,(VOID*)&data);
	curl_easy_setopt(handle,CURLOPT_URL,"http://advice.client.baidu.com/api/login.php");
	curl_easy_perform(handle);
	curl_formfree(post);
	curl_easy_cleanup(handle);
	data.addword(0);

	Logresult ret;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(std::string(data.getdata()), root))
	{
		Json::Value result=root["passport"]["result"];
		Json::Value key=root["passport"]["key"];
		Json::Value imageurl=root["passport"]["url"];
		if(result.isInt()&&key.isString()&&imageurl.isString())
		{
			ret.m_result=result.asInt();
			ret.m_imageurl= ACPtoUnicode(imageurl.asString().c_str());
			ret.m_vcodekey = ACPtoUnicode(key.asString().c_str());
		}
	}

	return ret;
}


Image* downloadimage(CString url)
{
	CURL *handle=curl_easy_init();
	struct curl_httppost *post = NULL;
	struct curl_httppost *last  = NULL;

	Data data;

	curl_easy_setopt(handle,CURLOPT_HTTPGET,post);
	curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,callback_curl);
	curl_easy_setopt(handle,CURLOPT_WRITEDATA,(VOID*)&data);
	curl_easy_setopt(handle,CURLOPT_URL,UnicodetoUTF8(url));
	curl_easy_perform(handle);
	curl_formfree(post);
	curl_easy_cleanup(handle);

	Image* ret=NULL;
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, data.getsize());
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
	memcpy(pmem,data.getdata(),data.getsize());
	IStream* pstm;
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);

	ret=new Image(pstm);
	GlobalUnlock(m_hMem);
	pstm->Release();

	return ret;
}
