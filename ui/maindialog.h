#pragma once
#include "jui/JWindow.h"
#include "jui/JFrame.h"
#include "jui/JStaitc.h"
#include "jui/JButton.h"
#include "jui/JEdit.h"
#include "jui/JProcess.h"
#include "common/thread.h"

class maindialog
{
public:
	void create()
	{
		m_window.Create(NULL,CRect(0,0,600,500));
		JVector *root=m_window.GetRootFrame();
		
		//JFrame *b1=new JButton();
		//root->Add(b1,CRect(10,10,90,90));
		
		int w=Res::GetImage(L"close_normal.png")->GetWidth();
		int h=Res::GetImage(L"close_normal.png")->GetHeight();
		JButton *b2=new JButton(new JStatic(Res::GetImage(L"close_normal.png"),false,true),new JStatic(Res::GetImage(L"close_hover.png"),false,true),new JStatic(Res::GetImage(L"close_down.png"),false,true));
		root->Add(b2,CRect(600-w,0,600,h));
		
		JEdit* e1=new JEdit();
		root->Add(e1,CRect(260,250,400,272));

		JEdit* e2=new JEdit(false,true);
		root->Add(e2,CRect(260,280,400,302));

		root->Add(new JStatic(L"’ ∫≈"),CRect(200,250,260,272));
		root->Add(new JStatic(L"√‹¬Î"),CRect(200,280,260,302));

		
		m_window.CenterWindow();
		m_window.ShowWindow(SW_SHOW);
		m_window.UpdateWindow();
	}

private:
	JWindow m_window;
};