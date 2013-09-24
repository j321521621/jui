#pragma once
#include "JFrame.h"
#include "JVector.h"

class JInternalEdit :public CWindowImpl<JInternalEdit,CEdit,CWinTraitsOR<ES_LEFT,WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_NOPARENTNOTIFY,CControlWinTraits>>
{
public:
	JInternalEdit():m_numberonly(false)
	{

	}

	BEGIN_MSG_MAP_EX(JInternalEdit)
		MSG_WM_CHAR(OnChar)
	END_MSG_MAP()

	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		SetMsgHandled(FALSE);
		if(m_numberonly)
		{
			if( L'0' <= nChar && nChar <= L'9' || nChar==8 )
			{
				SetMsgHandled(FALSE);
			}
			else
			{
				SetMsgHandled(TRUE);
			}
		}
	}

	bool m_numberonly;
};

class JMultilineEdit :public CWindowImpl<JMultilineEdit,CEdit,CWinTraitsOR<WS_VSCROLL|ES_LEFT|ES_MULTILINE,WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_NOPARENTNOTIFY,CControlWinTraits>>
{
public:

	JMultilineEdit():m_numberonly(false)
	{

	}

	BEGIN_MSG_MAP_EX(JMultilineEdit)
		MSG_WM_CHAR(OnChar)
	END_MSG_MAP()

	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		SetMsgHandled(FALSE);
		if(m_numberonly)
		{
			if( L'0' <= nChar && nChar <= L'9' )
			{
				SetMsgHandled(FALSE);
			}
			else
			{
				SetMsgHandled(TRUE);
			}
		}
	}

	bool m_numberonly;
};


class JEdit:public JFrame
{
public:
	JEdit(bool multiline=false,bool password=false):m_padding(2),m_password(password),m_multiline(multiline),m_cedit(NULL),m_numberonly(false)
	{
	
	}

	virtual void OnCreate()
	{
		HWND hwnd=m_parent->InGetHwnd();
		CRect rc=m_parent->InGetAbSize(this);
		if(m_multiline)
		{
			m_medit.Create(hwnd,CRect(rc.left+m_padding,rc.top+m_padding,rc.right-m_padding,rc.bottom-m_padding));
			m_cedit=&m_medit;
		}
		else
		{
			m_iedit.Create(hwnd,CRect(rc.left+m_padding,rc.top+m_padding,rc.right-m_padding,rc.bottom-m_padding));
			m_cedit=&m_iedit;
		}
		m_font.CreateFont(18,0,0,0,0,0,0,0,0,0,0,0,0,L"Î¢ÈíÑÅºÚ");
		m_cedit->SetFont(m_font);
		if(m_password)
		{
			m_cedit->SetPasswordChar(TEXT('*'));
			m_cedit->ModifyStyle(NULL,ES_PASSWORD);
		}
		SetText(m_buffer_text);
		if(m_cedit && m_cedit->IsWindow())
		{
			m_cedit->ShowWindow(m_show?SW_SHOW:SW_HIDE);
		}
	}

	

	virtual void OnPaint(Graphics* gr)
	{
		if(!m_show)
		{
			return;
		}

		gr->FillRectangle(Res::GetSolidBrush(Color::White),0,0,m_size.Width()-1,m_size.Height()-1);
		gr->DrawRectangle(Res::GetThinPen(Color::Gray),0,0,m_size.Width()-1,m_size.Height()-1);
	}

	virtual void OnDestroy()
	{
		m_buffer_text=GetText();
		if(m_cedit && m_cedit->IsWindow())
		{
			m_cedit->DestroyWindow();
			m_font.DeleteObject();
		}
	}

	virtual CString GetText()
	{
		if(m_cedit && m_cedit->IsWindow())
		{
			m_cedit->GetWindowText(m_buffer_text);
		}

		return m_buffer_text;
	}

	virtual void SetText(CString text)
	{
		m_buffer_text=text;

		if(m_cedit && m_cedit->IsWindow())
		{
			m_cedit->SetWindowText(text);
		}
	}

	virtual void Show(bool show)
	{
		__super::Show(show);
		if(m_cedit && m_cedit->IsWindow())
		{
			m_cedit->ShowWindow(m_show?SW_SHOW:SW_HIDE);
		}
	}

	virtual void SetNumberOnly(bool numberonly)
	{
		m_numberonly=numberonly;
		m_iedit.m_numberonly=numberonly;
		m_medit.m_numberonly=numberonly;
	}

protected:

	DWORD m_padding;
	JInternalEdit m_iedit;
	JMultilineEdit m_medit;
	CEdit *m_cedit;
	CFont m_font;
	bool m_password;
	bool m_multiline;
	bool m_numberonly;
	CString m_buffer_text;

private:
	virtual void OnDataChange()
	{

	}
};
