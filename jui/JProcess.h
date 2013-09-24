#pragma once
#include "JFrame.h"

class JProcess:public JStatic
{
public:
	JProcess():JStatic(L""),m_dst_val(0),m_cur_val(0),m_step(3)
	{

	}

	void OnPaint(Graphics* gr)
	{
		gr->FillRectangle(Res::GetSolidBrush(Color::White),0,0,m_size.Width()-1,m_size.Height()-1);
		gr->DrawRectangle(Res::GetThinPen(Color::Gray),0,0,m_size.Width()-1,m_size.Height()-1);
		gr->FillRectangle(Res::GetSolidBrush(Color(84,181,255)),0,0,(m_size.Width()-1)*m_cur_val/100,m_size.Height()-1);
		gr->DrawRectangle(Res::GetThinPen(Color(32,158,254)),0,0,(m_size.Width()-1)*m_cur_val/100,m_size.Height()-1);
		m_string.Format(L"%d%%",m_cur_val);
		JStatic::OnPaint(gr);
	}

	virtual void SetVal(int i)
	{
		m_dst_val=i;
	}

	virtual void SetRealVal(int i)
	{
		m_dst_val=i;
		m_cur_val=i;
		ByInvalidate();
	}


	virtual void OnTimer()
	{
		if(m_cur_val+m_step<=m_dst_val)
		{
			m_cur_val+=m_step;
			m_parent->InInvalidate();
		}
		else if(m_cur_val-m_step>=m_dst_val)
		{
			m_cur_val-=m_step;
			m_parent->InInvalidate();
		}
		else if(m_cur_val!=m_dst_val)
		{
			m_cur_val=m_dst_val;
			m_parent->InInvalidate();
		}
	}

protected:
	int m_dst_val;
	int m_cur_val;
	int m_step;
};
