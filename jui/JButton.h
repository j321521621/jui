#pragma once
#include "JFrame.h"

class JButton:public JFrame
{
public:
	JButton(JStatic* normal=NULL,JStatic* hover=NULL,JStatic* down=NULL):
	  m_normal(normal),
	  m_hover(hover),
	  m_down(down),
	  m_isdown(false),
	  m_isin(false),
	  m_whenclick(NULL)
	{

	}

	virtual void OnMouseLeftDown(CPoint pt)
	{
		if(!m_enable || !m_show)
		{
			return;
		}

		m_isdown=true;
		m_parent->InSetCapture(this);
		m_parent->InInvalidate();
	}

	virtual void OnMouseLeftUp(CPoint pt)
	{
		if(!m_enable || !m_show)
		{
			return;
		}

		m_isdown=false;
		ByReleaseCapture();
		ByInvalidate();
		if(m_whenclick)
		{
			m_whenclick->run();
		}
	}

	virtual void OnMouseEnter(CPoint pt)
	{
		if(!m_enable || !m_show)
		{
			return;
		}

		m_isin=true;
		ByInvalidate();
	}

	virtual void OnMouseLeave()
	{
		if(!m_enable || !m_show)
		{
			return;
		}

		m_isin=false;
		ByInvalidate();
	}

	virtual void OnPaint(Graphics* gr)
	{

		if(!m_show)
		{
			return;
		}

		if(m_isdown)
		{
			if(m_down)
			{
				m_down->OnPaint(gr);
			}
		}
		else if(m_isin)
		{
			if(m_hover)
			{
				m_hover->OnPaint(gr);
			}
		}
		else
		{
			if(m_normal)
			{
				m_normal->OnPaint(gr);
			}
		}
	}

	virtual void RegistClickEvent(thread::task* tk)
	{
		m_whenclick=tk;
	}


	virtual void SetNormalJStatic(JStatic *jstatic)
	{
		m_normal=jstatic;
	}

	virtual void SetDownJStatic(JStatic *jstatic)
	{
		m_down=jstatic;
	}

	virtual void SetHoverJStatic(JStatic *jstatic)
	{
		m_hover=jstatic;
	}

	virtual JStatic* GetNormalJStatic()
	{
		return m_normal;
	}

	virtual JStatic* GetDownJStatic()
	{
		return m_down;
	}

	virtual JStatic* GetHoverJStatic()
	{
		return m_hover;
	}

	virtual void OnEnable(bool enable)
	{
		if(m_enable && !enable && m_isdown)
		{
			ByReleaseCapture();
			ByInvalidate();
			m_isdown=false;
		}
		m_enable=enable;
	}

	virtual void OnShow(bool show)
	{
		if(m_show && !show && m_isdown)
		{
			ByReleaseCapture();
			ByInvalidate();
			m_isdown=false;
		}
		m_show=show;
	}

protected:
	JStatic *m_normal;
	JStatic *m_hover;
	JStatic *m_down;
	bool m_isdown;
	bool m_isin;

	thread::task* m_whenclick;
	
};