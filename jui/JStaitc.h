#pragma once
#include "JFrame.h"

class JStatic:public JFrame
{
public:
	JStatic(CString string=L"",Font *font=Res::GetFont(),StringFormat* strfmt=Res::GetStringFormat(),Brush *brush=Res::GetSolidBrush(Color::Black),bool isdownline= false ):
		m_string(string),
		m_strfmt(strfmt),
		m_font(font),
		m_brush(brush),
		m_img(NULL),
		m_strech(false),
		m_fit(false)
	{
	}


	JStatic(Image *img,bool strech=true,bool fit=false,CString string=L"",Font *font=Res::GetFont(),StringFormat* strfmt=Res::GetStringFormat(),Brush *brush=Res::GetSolidBrush(Color::Black),bool isdownline= false):
		m_string(string),
		m_strfmt(strfmt),
		m_font(font),
		m_brush(brush),
		m_img(img),
		m_strech(strech),
		m_fit(fit)
	{
		if(m_fit)
		{
			SetSize(CRect(m_size.left,m_size.top,m_size.left+img->GetWidth(),m_size.Height()+img->GetHeight()));
		}

	}
		

	void setisdownline(bool isdownline)
	{
		

	}
	
	void OnPaint(Graphics* gr)
	{
		if(!m_show)
		{
			return;
		}

		if(m_img)
		{
			gr->DrawImage(m_img,0,0,m_size.Width(),m_size.Height());
		}

		if(!m_string.IsEmpty())
		{
			StringFormat strfmt;
			RectF rc(0,0,m_size.Width(),m_size.Height());
			gr->DrawString(m_string,m_string.GetLength(),m_font,rc,m_strfmt,m_brush);
	
		}
	}


	virtual void SetText(CString str)
	{
		m_string=str;
		ByInvalidate();
	}

	virtual void SetImage(Image *img)
	{
		m_img=img;
		ByInvalidate();
	}

	virtual UINT OnNcHitTest(CPoint point)
	{
		return HTCAPTION;
	}

	virtual Image* GetImage()
	{
		return m_img;
	}

protected:
	CString m_string;
	StringFormat *m_strfmt;
	Font *m_font;
	Brush *m_brush;
	Image* m_img;
	bool m_strech;
	bool m_fit;

};