#pragma once
#include "JFrame.h"

class JPicView:public JVector
{
public:
	JPicView():
	  m_img(NULL),
	 m_task(NULL)
	  {
		m_jb_close.SetNormalJStatic(new JStatic(Res::GetImage(L"mini_close_normal.png"),false,true));
		m_jb_close.SetDownJStatic(new JStatic(Res::GetImage(L"mini_close_down.png"),false,true));
		m_jb_close.SetHoverJStatic(new JStatic(Res::GetImage(L"mini_close_hover.png"),false,true));
		m_jb_close.Show(false);
		Add(&m_jb_close);
	}

	  virtual void SetSize(CRect rc)
	  {
		  __super::SetSize(rc);

		  int w=Res::GetImage(L"mini_close_normal.png")->GetWidth();
		  int h=Res::GetImage(L"mini_close_normal.png")->GetHeight();
		  m_jb_close.SetSize(CRect(m_size.Width()-2-w,2,m_size.Width()-2,2+h));
		  m_jb_close.RegistClickEvent(thread::cctask(this,&JPicView::WhenCloseClick));
	  }

	 virtual void WhenCloseClick()
	  {
		  SetImage(NULL);
	  }

	virtual void OnPaint(Graphics* gr)
	{
		gr->DrawRectangle(Res::GetThinPen(Color::Gray),0,0,m_size.Width()-1,m_size.Height()-1);
		gr->DrawRectangle(Res::GetThinPen(Color::Gray),1,1,m_size.Width()-3,m_size.Height()-3);
		int padding=2;
		if(m_img)
		{
			int maxw=m_size.Width()-2*padding;
			int maxh=m_size.Height()-2*padding;
			RectF dst(padding,padding,m_size.Width()-2*padding,m_size.Height()-2*padding);
			int w=m_img->GetWidth();
			int h=m_img->GetHeight();
			if(w>h)
			{
				int rh=h*maxw/w;
				dst.Height=rh;
				dst.Y+=(maxh-dst.Height)/2;
			}
			else
			{
				int rw=w*maxh/h;
				dst.Width=rw;
				dst.X+=(maxw-dst.Width)/2;
			}
//			gr->FillRectangle(Res::GetSolidBrush(Color::White),0,0,m_size.Width()-1,m_size.Height()-1);
			gr->DrawImage(m_img,dst,0,0,w,h,UnitPixel);
		}
		__super::OnPaint(gr);
	}

	virtual void SetImage(Image *img)
	{
		if(img==NULL)
		{
			if(m_img)
			{
				delete m_img;
			}
			m_jb_close.Show(false);
			if(m_task)
			{
				m_task->run();
			}
		}
		else
		{
			m_jb_close.Show(true);
		}
		m_img=img;
	}

	virtual Image* GetImage()
	{
		return m_img;
	}

	virtual void RegistDeleteEvent(thread::task* ts)
	{
		m_task=ts;
	}

protected:
	Image* m_img;
	JButton m_jb_close;
	thread::task *m_task;
};
