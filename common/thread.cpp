#include "stdafx.h"
#include "thread.h"

namespace thread
{

map<DWORD,HWND> thread_maganer::g_map;
CRITICAL_SECTION thread_maganer::g_cs;


LRESULT CALLBACK WndProcThunk(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if(message==WM_USER)
	{
		task* tsk=(task*)wparam;

		if(tsk!=NULL)
		{
			tsk->run();
			delete tsk;
		}

		return 0;
	}
	else
	{
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
}

unsigned int CALLBACK ThreadProcThunk(VOID* arg)
{
	struct thread_arg* pta=(struct thread_arg*)arg;
	thread_maganer::regist();
	SetEvent(pta->event);
	thread_maganer::enter_taskloop();
	thread_maganer::unregist();
	return 0;
}

}
