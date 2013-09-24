// UserTest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "UserTest.h"
#include "common/thread.h"
#include "ui/maindialog.h"
#include "ui/repotdialog.h"
#include "jui/JUtil.h"
#include "logic/logic.h"
#include "storage/userinfo.h"
#include "storage/buginfo.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance


DWORD uitid;
DWORD nettid;
DWORD hungtid;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	CreateMutex(NULL,TRUE,L"{2FA8B894-A1E9-460C-A6A9-5CA6DAD4FE7E}");
	if(GetLastError()==ERROR_ALREADY_EXISTS) return 321521;

	curl_global_init(CURL_GLOBAL_WIN32);

	thread::thread_maganer::init();
	thread::thread_maganer::regist();

	nettid=thread::thread_maganer::startthread();
	//hungtid=thread::thread_maganer::startthread();
	uitid=GetCurrentThreadId();

 	GdiPlusModule gdipusmodule;

	reportdialog md;
	md.create();

	thread::thread_maganer::enter_taskloop();
	thread::thread_maganer::unregist();

	return 0;
}