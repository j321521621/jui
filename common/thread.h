#pragma once
#include "task.h"
#include <vector>
#include <map>
#include <utility>
#include <deque>
using std::vector;
using std::deque;
using std::map;
using std::pair;
#include "common.h"

namespace thread
{

LRESULT CALLBACK WndProcThunk(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

struct thread_arg 
{
	HANDLE event;
	task* init_task;
};
unsigned int CALLBACK ThreadProcThunk(VOID* arg);

class thread_maganer
{
public:
	static void init()
	{
		automutex::init(&g_cs);

		WNDCLASSEX wc = {0};
		wc.cbSize = sizeof(wc);
		wc.lpfnWndProc = WndProcThunk;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = L"JT_MessagePumpWindow";
		RegisterClassEx(&wc);
	}

	static HWND regist()
	{
		automutex lock(&g_cs);

		DWORD id=GetCurrentThreadId();
		if(g_map.count(id)==0)
		{
			WCHAR classname[] = L"JT_MessagePumpWindow";
			g_map[id]=CreateWindow(classname, 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, GetModuleHandle(NULL), 0);
		}

		return g_map[id];
	}

	static void unregist()
	{
		automutex lock(&g_cs);

		DWORD id=GetCurrentThreadId();
		if(g_map.count(id)>0)
		{
			DestroyWindow(g_map[id]);
		}
	}

	static HWND get_task_window(DWORD id)
	{
		automutex lock(&g_cs);

		if(g_map.count(id)>0)
		{
			return g_map[id];
		}
		return NULL;
	}

	static void enter_taskloop()
	{
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

	}

	static DWORD startthread()
	{
		HANDLE hevent=CreateEvent(NULL,FALSE,FALSE,NULL);
		struct thread_arg ta={hevent,NULL};
		DWORD tid;
		HANDLE hthread=(HANDLE)_beginthreadex(NULL, 0, ThreadProcThunk, PVOID(&ta), 0, (unsigned int*)&tid);
		WaitForSingleObject(hevent,INFINITE);
		DeleteObject(hevent);
		return tid;
	}

	static void posttask(DWORD threadid,task* ts,int delay=0)
	{
		if(threadid==0)
		{
			threadid=GetCurrentThreadId();
		}

		HWND hwnd=thread_maganer::get_task_window(threadid);
		if(hwnd)
		{
			PostMessage(hwnd,WM_USER,(WPARAM)(ts),0);
		}
		else
		{
			delete ts;
		}
	}

private:
	static CRITICAL_SECTION g_cs;
	static map<DWORD,HWND> g_map;
};

}