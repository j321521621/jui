#pragma once

#include <storage/data.h>
#include <GdiPlus.h>
using namespace Gdiplus;

typedef int type_CallbackProcess(void *progress_data,
	double t, /* dltotal */
	double d, /* dlnow */
	double ultotal,
	double ulnow);

vector<UserTask> getTask(CString userid);
int upload(BugInfo bugInfo,type_CallbackProcess callback_process,void *progress_data);
Logresult login(Logininfo userinfo);
Image* downloadimage(CString url);