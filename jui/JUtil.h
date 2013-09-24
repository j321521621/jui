#pragma once
#include "../Resource.h"
#include <GdiPlus.h>
#include <map>
using namespace Gdiplus;
using std::map;

class GdiPlusModule
{
public:
	GdiPlusModule()
	{
		Gdiplus::GdiplusStartupInput StartupInput;  
		GdiplusStartup(&m_gdiplusToken,&StartupInput,NULL); 
	}
	
	~GdiPlusModule()
	{
		Gdiplus::GdiplusShutdown(m_gdiplusToken);  
	}

private:
	ULONG_PTR m_gdiplusToken;
};

class FontProperty
{
public:
	FontProperty(CString f,int sz,int st)
	{
		family=f;
		size=sz;
		style=st;
	}

	CString family;
	int size;
	int style;

	

};

inline bool operator<(const FontProperty& fp1, const FontProperty& fp2)
{
	int l1=fp1.family.GetLength();
	int l2=fp2.family.GetLength();
	for(int i=0;i<l1 && i<l2;++i)
	{
		if(fp1.family[i]==fp2.family[i])
		{
			continue;
		}
		return fp1.family[i]<fp2.family[i];
	}
	
	if(l1!=l2)
	{
		return l1<l2;
	}
	else if(fp1.size<fp2.size)
	{
		return true;
	}
	else if(fp1.style<fp2.style)
	{
		return true;
	}

	return false;
}

class Res
{
public:

	static Image* GetImage(CString path)
	{
		if(m_map_img.count(path)==0)
		{
			m_map_img[path]=LoadImageFromPERes(path);
		}

		return m_map_img[path];
	}

	static Brush* GetSolidBrush(Color color)
	{
		ARGB key=color.GetValue();
		if(m_map_solidbrush.count(key)==0)
		{
			m_map_solidbrush[key]=new SolidBrush(color);
		}

		return m_map_solidbrush[key];
	}

	static Pen* GetThinPen(Color color)
	{
		ARGB key=color.GetValue();
		if(m_map_thinpen.count(key)==0)
		{
			m_map_thinpen[key]=new Pen(color);
		}

		return m_map_thinpen[key];
	}


	static Font* GetFont(CString family=CString(L"Î¢ÈíÑÅºÚ"),int size=10,int style=0)
	{
		FontProperty key(family,size,style);

		if(m_map_font.count(key)==0)
		{
			
			m_map_font[key]=new Font(family,size,style);
		}

		return m_map_font[key];
	}

	static StringFormat* GetStringFormat(StringAlignment horalign=StringAlignmentCenter,StringAlignment veralign=StringAlignmentCenter)
	{
		DWORD key=horalign|(veralign<<2);
		if(m_map_stringalign.count(key)==0)
		{
			StringFormat *psf=new StringFormat();
			psf->SetAlignment(horalign);
			psf->SetLineAlignment(veralign);
			m_map_stringalign[key]=psf;
		}

		return m_map_stringalign[key];
	}

private:

	static Image* LoadImageFromPERes(CString path)
	{
		static bool inited=false;
		if(!inited)
		{
			inited=true;

			/**** add path to rid ****/
			m_map_img_id[L"back.png"]=IDB_PNG1;
			m_map_img_id[L"sysbtn_bkg_left.png"]=IDB_PNG2;
			m_map_img_id[L"close_down.png"]=IDB_PNG3;
			m_map_img_id[L"close_hover.png"]=IDB_PNG4;
			m_map_img_id[L"close_normal.png"]=IDB_PNG5;
			m_map_img_id[L"button_down.png"]=IDB_PNG6;
			m_map_img_id[L"button_hover.png"]=IDB_PNG7;
			m_map_img_id[L"button_normal.png"]=IDB_PNG8;
			m_map_img_id[L"min_down.png"]=IDB_PNG9;
			m_map_img_id[L"min_hover.png"]=IDB_PNG10;
			m_map_img_id[L"min_normal.png"]=IDB_PNG11;
			m_map_img_id[L"newback.png"]=IDB_PNG12;
			m_map_img_id[L"mini_close_down.png"]=IDB_PNG13;
			m_map_img_id[L"mini_close_hover.png"]=IDB_PNG14;
			m_map_img_id[L"mini_close_normal.png"]=IDB_PNG15;

		}

		if(m_map_img_id.count(path)==0)
		{
			return NULL;
		}

		UINT nID = m_map_img_id[path];
		LPCTSTR sTR = _T("PNG");

		HRSRC hRsrc = ::FindResource (NULL,MAKEINTRESOURCE(nID),sTR);
		DWORD len = SizeofResource(NULL, hRsrc);
		BYTE* lpRsrc = (BYTE*)LoadResource(NULL, hRsrc);

		HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
		BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
		memcpy(pmem,lpRsrc,len);
		IStream* pstm;
		CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);

		Image *ret=new Image(pstm);
		GlobalUnlock(m_hMem);
		pstm->Release();
		FreeResource(lpRsrc);

		return ret;
	}

	static map<CString,int> m_map_img_id;
	static map<CString,Image*> m_map_img;
	static map<ARGB,Pen*> m_map_thinpen;
	static map<ARGB,Brush*> m_map_solidbrush;
	static map<FontProperty,Font*> m_map_font;
	static map<DWORD,StringFormat*> m_map_stringalign;
};

__declspec(selectany) map<CString,int> Res::m_map_img_id;
__declspec(selectany) map<CString,Image*> Res::m_map_img;
__declspec(selectany) map<ARGB,Pen*> Res::m_map_thinpen;
__declspec(selectany) map<ARGB,Brush*> Res::m_map_solidbrush;
__declspec(selectany) map<FontProperty,Font*> Res::m_map_font;
__declspec(selectany) map<DWORD,StringFormat*> Res::m_map_stringalign;
