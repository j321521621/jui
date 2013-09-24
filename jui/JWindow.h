// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "JFrame.h"
#include "JRoot.h"
#include "JUtil.h"
#include "logic/logic.h"
#define  PRSCRM L"SNAPSHOT"

#define UPDATATIMERID 758
enum ACTIVESTATE{
	LOGIN = 0,
	QUEST =1,
	COMMIT = 2
};
class reportdialog;
class JWindow :	public CWindowImpl<JWindow,CWindow,CWinTraits<WS_POPUP|WS_MINIMIZEBOX|WS_CLIPCHILDREN,NULL>>
{

public:
	JWindow():m_rootframe(NULL),m_mousein(false),m_activestate(LOGIN),m_nHotKeyID(0)
	{
		m_rootframe=new JRoot(this);
	}

	~JWindow()
	{
	}

	DECLARE_WND_CLASS_EX(_T("JuiMainWindow"), CS_DROPSHADOW, -1)

	BEGIN_MSG_MAP_EX(JWindow)

		MSG_WM_CREATE(OnCreate)
		MSG_WM_SIZING(OnSizing)

		MSG_WM_NCHITTEST(OnNcHitTest)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_PRINTCLIENT(OnPrintClient)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)

		MSG_WM_TIMER(OnTimer)
		MSG_WM_CLOSE(OnClose)

		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)

		//实现快捷键
		MSG_WM_HOTKEY(OnHotKey)
		
		REFLECT_NOTIFICATIONS()

	END_MSG_MAP()

	void SetIcon(HICON hIcon)
	{
		SendMessage(   WM_SETICON,   ICON_BIG,   (LPARAM)hIcon   );   
		SendMessage(   WM_SETICON,   ICON_SMALL,   (LPARAM)hIcon   );
	}

	int OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		CRect rc;
		GetClientRect(rc);
		m_rootframe->SetSize(rc);
		m_rootframe->OnCreate();
		SetTimer(0,20,NULL);
		m_nHotKeyID =::GlobalAddAtom(PRSCRM)-0xC000; 
		BOOL m_isKeyRegistered = RegisterHotKey(m_hWnd,m_nHotKeyID,MOD_CONTROL,'Z');
		ATLASSERT(m_isKeyRegistered != FALSE);



		//设置启动update程序,10s后启动
		//SetTimer(UPDATATIMERID, 10000,0);
		return TRUE;
	}

	void OnClose()
	{
		//必须注销热键
		BOOL m_iskeyUnregistered = UnregisterHotKey(m_hWnd, m_nHotKeyID);
		DestroyWindow();
		PostQuitMessage(0);
	}

	void OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		OnLButtonDown(nFlags,point);
	}

	void OnSizing(UINT fwSide, LPRECT pRect)
	{
		m_rootframe->SetSize(*pRect);
		UpdateWindow();
	}

	void OnLButtonDown(UINT nFlags, CPoint point)
	{
		m_rootframe->OnMouseLeftDown(point);
		UpdateWindow();
	}

	void OnLButtonUp(UINT nFlags, CPoint point)
	{
		m_rootframe->OnMouseLeftUp(point);
		UpdateWindow();
	}

	void OnMouseMove(UINT nFlags, CPoint point)
	{
		if(!m_mousein)
		{
			m_mousein=true;

			TRACKMOUSEEVENT tme = { 0 };
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = m_hWnd;
			_TrackMouseEvent(&tme);

			m_rootframe->OnMouseEnter(point);
		}

		m_rootframe->OnMouseMove(point);
		UpdateWindow();
	}

	void OnMouseLeave()
	{
		m_mousein=false;
		m_rootframe->OnMouseLeave();
		UpdateWindow();
	}

	void OnPrintClient(CDCHandle dc, UINT uFlags)
	{
		CRect rc;
		GetClientRect(rc);
		{
			CMemoryDC buffdc(dc,rc);
			Graphics grapics((HDC)buffdc);
			_OnDraw(&grapics);
		}
	}

	void OnTimer(UINT_PTR nIDEvent)
	{

		if (nIDEvent == UPDATATIMERID)
		{
			startupdate(L"update.exe");
			KillTimer(UPDATATIMERID);
		}


		m_rootframe->OnTimer();
		UpdateWindow();
	}


	UINT OnNcHitTest(CPoint point)
	{
		ScreenToClient(&point);
		return m_rootframe->OnNcHitTest(point);
	}

	void OnPaint(CDCHandle dc)
	{

		PAINTSTRUCT lp;
		dc=BeginPaint(&lp);
		CRect rc;
		GetClientRect(rc);
		{
			CMemoryDC buffdc(dc,rc);
			Graphics grapics((HDC)buffdc);
			_OnDraw(&grapics);
		}
		EndPaint(&lp);
	}

	void _OnDraw(Graphics *gr)
	{

		m_rootframe->OnPaint(gr);
	}

	BOOL OnEraseBkgnd(CDCHandle dc)
	{
		return TRUE;
	}

	void OnClose(UINT uNotifyCode, int nID, CWindow wndCtl)
	{

	}


	void SetTransparent(BYTE b)
	{
		if(b>0)
		{
			SetWindowLong(	GWL_EXSTYLE,GetWindowLong( GWL_EXSTYLE) | WS_EX_LAYERED);
			::SetLayeredWindowAttributes(m_hWnd, 0,b, LWA_ALPHA);
		}
		else
		{
			SetWindowLong(	GWL_EXSTYLE,GetWindowLong( GWL_EXSTYLE) & ~WS_EX_LAYERED);
		}
	}

	JRoot* GetRootFrame()
	{
		return m_rootframe;
	}
	void SetActiveState(ACTIVESTATE activeState)
	{
		this->m_activestate = activeState;
	}
	void SetReportdilog(reportdialog * ptr_reportdilog)
	{
		m_ptrreportdilog = ptr_reportdilog;
	}
	void RegsiterKeyDown(thread::task* ts)
	{
		m_keydown = ts;
		return;
	}
	void OnHotKey(int nHotKeyID, UINT uModifiers, UINT uVirtKey)
	{
		if (this->m_activestate == COMMIT)
		{
			m_keydown->run();
		}
		return;
	}

private:
	JRoot *m_rootframe;
	bool m_mousein;
	ACTIVESTATE m_activestate;
	reportdialog * m_ptrreportdilog;
	thread::task* m_keydown;
	int m_nHotKeyID;
};