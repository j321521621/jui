#pragma once
#include "JUtil.h"

class JVector;

class JFrame
{
public:
	JFrame():m_size(0,0,0,0),m_parent(NULL),m_show(true),m_enable(true)
	{

	}

	virtual void SetParent(JVector* parent)
	{
		m_parent=parent;
	}

	virtual void OnCreate()
	{
		return;
	}

	virtual void OnDestroy()
	{
		return;
	}

	virtual UINT OnNcHitTest(CPoint point)
	{
		return HTCLIENT;
	}

	virtual void SetSize(CRect rect)
	{
		m_size=rect;
		ByInvalidate();
	}

	virtual void Enable(bool enable)
	{
		m_enable=enable;
		ByInvalidate();
	}

	virtual void Show(bool show)
	{
		m_show=show;
		ByInvalidate();
	}

	virtual CRect GetSize()
	{
		return m_size;
	}

	virtual void OnTimer()
	{
		return;
	}

	virtual void OnPaint(Graphics *gr)
	{
		return;
	}

	virtual void OnMouseEnter(CPoint pt)
	{
		return;
	}

	virtual void OnMouseMove(CPoint pt)
	{
		return;
	}

	virtual void OnMouseLeave()
	{
		return;
	}

	virtual void OnMouseLeftDown(CPoint pt)
	{
		return;
	}

	virtual void OnMouseLeftUp(CPoint pt)
	{
		return;
	}

	virtual void OnShow(bool show)
	{
		return;
	}

	virtual bool IsShow()
	{
		return m_show;
	}

	bool GetEnable()
	{
		return m_enable;
	} 


protected:

	virtual void ByInvalidate();
	virtual void BySetCapture(JFrame *capturefocus);
	virtual void ByReleaseCapture();
	virtual HWND ByGetHwnd();
	virtual CRect ByGetAbSize();

	CRect m_size;
	JVector *m_parent;
	bool m_show;
	bool m_enable;
};