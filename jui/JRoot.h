#pragma once
#include "JVector.h"

class JRoot:public JVector
{
public:
	JRoot(CWindow *jwindow):
	  m_jwindow(jwindow),
	 m_tick(0),
	 m_w(0),
	 m_round(5000)
	{

	}

	void OnPaint(Graphics *gr)
	{
		gr->DrawImage(Res::GetImage(L"newback.png"),0,0,m_w,0,m_w+m_size.Width(),m_size.Height(),UnitPixel);
		gr->DrawRectangle(Res::GetThinPen(Color::Gray),0,0,m_size.Width()-1,m_size.Height()-1);
		__super::OnPaint(gr);
	}

	virtual void OnTimer()
	{
		JVector::OnTimer();
		Image* bk=Res::GetImage(L"newback.png");
		int maxw=bk->GetWidth()-m_size.Width();
		m_tick++;
		if(m_tick==m_round)
		{
			m_tick=0;
		}

		int w=0;
		if(m_tick<=m_round/2)
		{
			w=maxw*m_tick/(m_round/2);
		}
		else
		{
			w=maxw*2-maxw*m_tick/(m_round/2);
		}

		if(m_w!=w)
		{
			m_w=w;
			m_jwindow->Invalidate();
		}
	}

protected:
	virtual void BySetCapture(JFrame *capturefocus)
	{
		if(m_jwindow->IsWindow())
		{
			m_jwindow->SetCapture();
		}
	}

	virtual void ByReleaseCapture()
	{
		::ReleaseCapture();
	}

	virtual void ByInvalidate()
	{
		if(m_jwindow->IsWindow())
		{
			m_jwindow->Invalidate();
		}
	}

	virtual HWND ByGetHwnd()
	{
		return (HWND)(*m_jwindow);
	}

	virtual CRect ByGetAbSize()
	{
		return m_size;
	}


private:

	CWindow *m_jwindow;
	int m_tick;
	int m_w;
	int m_round;
};