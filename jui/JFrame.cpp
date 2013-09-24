#include "stdafx.h"
#include "JFrame.h"
#include "JVector.h"


void JFrame::ByInvalidate()
{
	if(m_parent)
	{
		m_parent->InInvalidate();
	}
}

void JFrame::BySetCapture(JFrame *capturefocus)
{
	if(m_parent)
	{
		m_parent->InSetCapture(this);
	}
}

void JFrame::ByReleaseCapture()
{
	if(m_parent)
	{
		m_parent->InReleaseCapture();
	}
}

HWND JFrame::ByGetHwnd()
{
	if(m_parent)
	{
		return m_parent->InGetHwnd();
	}
}

CRect JFrame::ByGetAbSize()
{
	if(m_parent)
	{
		return m_parent->InGetAbSize(this);
	}
}