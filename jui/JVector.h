#pragma once
#include "JUtil.h"
#include "JFrame.h"
#include <vector>
#include <algorithm>
using std::vector;

class JVector:public JFrame
{
public:
	JVector():
	m_last_enter(NULL),m_captured_frame(NULL),m_lcokchild(false),m_created(false)
	{

	}

	virtual void OnCreate()
	{
		m_created=true;

		LcokChild();
		for(vector<JFrame*>::iterator it=m_children.begin();it!=m_children.end();++it)
		{
			JFrame *pjf=*it;
			pjf->OnCreate();
		}
		UnLcokChild();
	}

	virtual void OnDestroy()
	{
		if(!m_created)
		{
			return;
		}

		LcokChild();
		for(vector<JFrame*>::iterator it=m_children.begin();it!=m_children.end();++it)
		{
			JFrame *pjf=*it;
			pjf->OnDestroy();
		}
		UnLcokChild();

		m_created=false;
	}

	virtual UINT OnNcHitTest(CPoint point)
	{
		JFrame *pjf=FindChildInPoint(point);
		if(pjf==NULL)
		{
			return HTCAPTION;
		}
		else
		{
			return pjf->OnNcHitTest(point-(pjf->GetSize()).TopLeft());
		}
	}

	virtual void Add(JFrame *child,CRect rc)
	{
		child->SetSize(rc);
		Add(child);
	}

	virtual void Add(JFrame *child)
	{
		if(m_lcokchild)
		{
			vector<JFrame*>::iterator it=std::find(m_temp_remove_children.begin(),m_temp_remove_children.end(),child);

			if(it!=m_temp_remove_children.end())
			{
				m_temp_remove_children.erase(it);
			}
			else
			{
				m_temp_add_children.push_back(child);
			}
		}
		else
		{
			if(IsInChildren(child))
			{
				m_children.push_back(child);
				child->SetParent(this);
				if(m_created)
				{
					child->OnCreate();
				}
			}
		}
		ByInvalidate();
	}

	virtual void Remove(JFrame *child)
	{
		if(m_lcokchild)
		{
			vector<JFrame*>::iterator it=std::find(m_temp_add_children.begin(),m_temp_add_children.end(),child);

			if(it!=m_temp_add_children.end())
			{
				m_temp_add_children.erase(it);
			}
			else
			{
				m_temp_remove_children.push_back(child);
			}
		}
		else
		{
			vector<JFrame*>::iterator it=std::find(m_children.begin(),m_children.end(),child);
			if(it!=m_children.end())
			{
				m_children.erase(it);
				child->SetParent(NULL);
				if(m_created)
				{
					child->OnDestroy();
				}
			}
		}
		ByInvalidate();
	}

	virtual void OnPaint(Graphics *gr)
	{
		if(!m_show)
		{
			return;
		}

		LcokChild();
		for(vector<JFrame*>::iterator it=m_children.begin();it!=m_children.end();++it)
		{
			JFrame *pjf=*it;
			CRect &rc=pjf->GetSize();
			gr->SetClip(RectF(rc.left,rc.top,rc.right,rc.bottom));
			gr->TranslateTransform(rc.left,rc.top);
			pjf->OnPaint(gr);
			gr->ResetTransform(); 
			gr->SetClip(RectF(0,0,m_size.Width(),m_size.Height()));
		}
		UnLcokChild();
	}

	virtual void OnShow(bool show)
	{
		LcokChild();
		JFrame::OnShow(show);
		for(vector<JFrame*>::iterator it=m_children.begin();it!=m_children.end();++it)
		{
			JFrame *pjf=*it;
			pjf->OnShow(show);
		}
		ByInvalidate();
		UnLcokChild();
	}

	virtual void OnMouseEnter(CPoint pt)
	{
		if(!m_show)
		{
			return;
		}

		return;
	}

	virtual void OnMouseMove(CPoint pt)
	{
		if(!m_show)
		{
			return;
		}

		if(m_captured_frame==NULL)
		{
			JFrame *movejf=FindChildInPoint(pt);

			if(movejf==NULL)
			{
				if(m_last_enter!=NULL)
				{
					m_last_enter->OnMouseLeave();
					m_last_enter=NULL;
				}
			}
			else
			{
				if(movejf==m_last_enter)
				{
					movejf->OnMouseMove(pt-(movejf->GetSize()).TopLeft());
				}
				else if(m_last_enter==NULL)
				{
					m_last_enter=movejf;
					movejf->OnMouseEnter(pt-(movejf->GetSize()).TopLeft());
					movejf->OnMouseMove(pt-(movejf->GetSize()).TopLeft());
				}
				else
				{
					m_last_enter->OnMouseLeave();
					m_last_enter=movejf;
					movejf->OnMouseEnter(pt-(movejf->GetSize()).TopLeft());
					movejf->OnMouseMove(pt-(movejf->GetSize()).TopLeft());
				}
			}
		}
		else
		{
			m_captured_frame->OnMouseMove(pt-(m_captured_frame->GetSize()).TopLeft());
		}
	}

	virtual void OnMouseLeave()
	{
		if(!m_show)
		{
			return;
		}

		if(m_last_enter!=NULL)
		{
			m_last_enter->OnMouseLeave();
			m_last_enter=NULL;
		}
	}

	virtual void OnMouseLeftDown(CPoint pt)
	{
		if(!m_show)
		{
			return;
		}

		if(m_captured_frame==NULL)
		{
			JFrame *downjf=FindChildInPoint(pt);
			if(downjf!=NULL)
			{
				downjf->OnMouseLeftDown(pt-(downjf->GetSize()).TopLeft());
			}
		}
		else
		{
			m_captured_frame->OnMouseLeftDown(pt-(m_captured_frame->GetSize()).TopLeft());
		}
	}

	virtual void OnTimer()
	{
		if(!m_show)
		{
			return;
		}

		LcokChild();
		for(vector<JFrame*>::iterator it=m_children.begin();it!=m_children.end();++it)
		{
			JFrame *pjf=*it;
			pjf->OnTimer();
		}
		UnLcokChild();
	}

	virtual void OnMouseLeftUp(CPoint pt)
	{
		if(!m_show)
		{
			return;
		}

		if(m_captured_frame==NULL)
		{
			JFrame *upjf=FindChildInPoint(pt);
			if(upjf!=NULL)
			{
				upjf->OnMouseLeftUp(pt-(upjf->GetSize()).TopLeft());
			}
		}
		else
		{
			m_captured_frame->OnMouseLeftUp(pt-(m_captured_frame->GetSize()).TopLeft());
		}
	}

	virtual void InSetCapture(JFrame *capturefocus)
	{
		m_captured_frame=capturefocus;
		BySetCapture(this);
	}

	virtual void InReleaseCapture()
	{
		m_captured_frame=NULL;
		ByReleaseCapture();
	}

	virtual void InInvalidate()
	{
		ByInvalidate();
	}

	virtual HWND InGetHwnd()
	{
		return ByGetHwnd();
	}

	virtual CRect InGetAbSize(JFrame *child)
	{
		CPoint pt=ByGetAbSize().TopLeft();
		return (child->GetSize())+pt;
	}
	
	virtual bool IsInChildren(JFrame *child)
	{
		return std::find(m_children.begin(),m_children.end(),child)==m_children.end();
	}

protected:

	virtual JFrame* FindChildInPoint(CPoint pt)
	{
		JFrame *ret=NULL;
		LcokChild();
		for(vector<JFrame*>::iterator it=m_children.begin();it!=m_children.end();++it)
		{
			JFrame *pjf=*it;
			CRect rc=pjf->GetSize();
			if(pjf->IsShow() && rc.PtInRect(pt))
			{
				ret=pjf;
				break;
			}
		}
		UnLcokChild();
		return ret;
	}

	virtual void LcokChild()
	{
		if(m_lcokchild==true)
		{
			ATLASSERT(TRUE);
			return;
		}

		m_lcokchild=true;
		m_temp_add_children.resize(0);
		m_temp_remove_children.resize(0);
	}

	virtual void UnLcokChild()
	{
		if(m_lcokchild==false)
		{
			ATLASSERT(TRUE);
			return;
		}

		m_lcokchild=false;
		for(vector<JFrame*>::iterator it=m_temp_add_children.begin();it!=m_temp_add_children.end();++it)
		{
			Add(*it,(*it)->GetSize());
		}
		for(vector<JFrame*>::iterator it=m_temp_remove_children.begin();it!=m_temp_remove_children.end();++it)
		{
			Remove(*it);
		}
	}

	vector<JFrame*> m_children;
	vector<JFrame*> m_temp_add_children;
	vector<JFrame*> m_temp_remove_children;
	JFrame *m_last_enter;
	JFrame *m_captured_frame;
	bool m_created;

	bool m_lcokchild;
};