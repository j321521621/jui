#pragma once
#include "jui/JWindow.h"
#include "jui/JFrame.h"
#include "jui/JStaitc.h"
#include "jui/JButton.h"
#include "jui/JEdit.h"
#include "jui/JProcess.h"
#include "jui/JPicView.h"
#include "common/thread.h"
#include "storage/userinfo.h"
#include "storage/buginfo.h"
#include "net/net.h"
#include "logic/logic.h"
#include "common/util.h"

#define  MAX_STR_LIMIT 250
#define  TASKURL L"http://advice.client.baidu.com/anonymous.php?"
#define  SHOPURL L"http://www.baidujifen.com/mobanme_lpzx-good.html?"
class reportdialog;

void DoLogin(reportdialog* This,Logininfo lo);
void DoCommit(reportdialog* This,BugInfo buginfo);
void DoDownloadImg(reportdialog* This,CString url);

int   GetEncoderClsid(const   WCHAR*   format,   CLSID*   pClsid)   
{   
	UINT     num   =   0;                     //   number   of   image   encoders   
	UINT     size   =   0;                   //   size   of   the   image   encoder   array   in   bytes   

	ImageCodecInfo*   pImageCodecInfo   =   NULL;   

	GetImageEncodersSize(&num,   &size);   
	if(size   ==   0)   
		return   -1;     //   Failure   

	pImageCodecInfo   =   (ImageCodecInfo*)(malloc(size));   
	if(pImageCodecInfo   ==   NULL)   
		return   -1;     //   Failure   

	GetImageEncoders(num,   size,   pImageCodecInfo);   

	for(UINT   j   =   0;   j   <   num;   ++j)   
	{   
		if(   wcscmp(pImageCodecInfo[j].MimeType,   format)   ==   0   )   
		{   
			*pClsid   =   pImageCodecInfo[j].Clsid;   
			free(pImageCodecInfo);   
			return   j;     //   Success   
		}           
	}   

	free(pImageCodecInfo);   
	return   -1;     //   Failure   
}

class reportdialog
{
public:
	reportdialog():
	  m_js_username(L"",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear)),
	  m_js_username_q(L"",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear)),
	  m_js_vcode(L"",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear)),
	  m_js_logininfo(L"",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear),Res::GetSolidBrush(Color::Red)),
	  m_js_commitinfo(L"",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear),Res::GetSolidBrush(Color::Red)),
	  m_edit_password(false,true),
	  m_jedit_content(true,false),
	  m_usertask_title(L"任务反馈和积分查看：",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear),Res::GetSolidBrush(Color::Black)),
	  m_scoreshop_title(L"积分商城和礼物兑换：",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear),Res::GetSolidBrush(Color::Black))
	{
		{
			{

				int w=Res::GetImage(L"close_normal.png")->GetWidth();
				int h=Res::GetImage(L"close_normal.png")->GetHeight();
				JButton *b=new JButton(new JStatic(Res::GetImage(L"close_normal.png"),false,true),new JStatic(Res::GetImage(L"close_hover.png"),false,true),new JStatic(Res::GetImage(L"close_down.png"),false,true));
				b->RegistClickEvent(thread::cctask(this,&reportdialog::WhenClose));
				m_vec_login.Add(b,CRect(400-w,0,400,h));

				int w2=Res::GetImage(L"min_normal.png")->GetWidth();
				int h2=Res::GetImage(L"min_normal.png")->GetHeight();
				JButton *b2=new JButton(new JStatic(Res::GetImage(L"min_normal.png"),false,true),new JStatic(Res::GetImage(L"min_hover.png"),false,true),new JStatic(Res::GetImage(L"min_down.png"),false,true));
				b2->RegistClickEvent(thread::cctask(this,&reportdialog::WhenMin));
				m_vec_login.Add(b2,CRect(400-w-w2,0,400-w,h2));
			}

			m_vec_login.Add(new JStatic(L"帐号"),CRect(100,250,150,272));
			m_vec_login.Add(new JStatic(L"密码"),CRect(100,280,150,302));
			m_js_vcode.SetText(L"验证码");
			m_js_vcode.Show(false);
			m_vec_login.Add(&m_js_vcode,CRect(100,310,150,332));
			m_vec_login.Add(&m_edit_username,CRect(160,250,300,272));
			m_vec_login.Add(&m_edit_password,CRect(160,280,300,302));
			m_js_vcodeimg.Show(false);
			m_vec_login.Add(&m_js_vcodeimg,CRect(230,305,300,338));
			m_jedit_vcode.Show(false);
			m_vec_login.Add(&m_jedit_vcode,CRect(160,310,220,332));
			m_edit_username.SetText(GetUsername());
			m_edit_password.SetText(GetPassword());

			{
				int w=Res::GetImage(L"button_normal.png")->GetWidth();
				int h=Res::GetImage(L"button_normal.png")->GetHeight();
				m_pjb_login.SetNormalJStatic(new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"登录",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_pjb_login.SetDownJStatic(new JStatic(Res::GetImage(L"button_down.png"),false,true,L"登录",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_pjb_login.SetHoverJStatic(new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"登录",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_pjb_login.RegistClickEvent(thread::cctask(this,&reportdialog::WhenLogin));
				m_vec_login.Add(&m_pjb_login,CRect(160,340,160+w,340+h));
			}

		

			m_vec_login.Add(&m_js_logininfo,CRect(160,380,380,400));

		}

		/////////////// quest /////////////////
		{
			m_vec_quest.Add(&m_js_username_q,CRect(10,0,200,30));

			{

				int w=Res::GetImage(L"close_normal.png")->GetWidth();
				int h=Res::GetImage(L"close_normal.png")->GetHeight();
				JButton *b=new JButton(new JStatic(Res::GetImage(L"close_normal.png"),false,true),new JStatic(Res::GetImage(L"close_hover.png"),false,true),new JStatic(Res::GetImage(L"close_down.png"),false,true));
				b->RegistClickEvent(thread::cctask(this,&reportdialog::WhenClose));
				m_vec_quest.Add(b,CRect(400-w,0,400,h));

				int w2=Res::GetImage(L"min_normal.png")->GetWidth();
				int h2=Res::GetImage(L"min_normal.png")->GetHeight();
				JButton *b2=new JButton(new JStatic(Res::GetImage(L"min_normal.png"),false,true),new JStatic(Res::GetImage(L"min_hover.png"),false,true),new JStatic(Res::GetImage(L"min_down.png"),false,true));
				b2->RegistClickEvent(thread::cctask(this,&reportdialog::WhenMin));
				m_vec_quest.Add(b2,CRect(400-w-w2,0,400-w,h2));
			}

			m_vec_quest.Add(new JStatic(L"当前已领取的任务:",Res::GetFont(L"微软雅黑",20),Res::GetStringFormat(StringAlignmentNear),Res::GetSolidBrush(Color::Blue)),CRect(20,40,380,80));

			int w2=Res::GetImage(L"button_normal.png")->GetWidth();
			int h2=Res::GetImage(L"button_normal.png")->GetHeight();
			CRect rc(20,100,260,120);
			CRect rcb(280,100,280+w2,100+h2);

			for(int i=0;i<10;++i)
			{
				m_js_info.push_back(new JStatic(L"111",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear)));
				m_js_info[i]->SetSize(rc);
				rc+=CPoint(0,30);

				JStatic *js1=new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"开始反馈",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
				JStatic *js2=new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"开始反馈",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
				JStatic *js3=new JStatic(Res::GetImage(L"button_down.png"),false,true,L"开始反馈",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
				JButton *b=new JButton(js1,js2,js3);
				b->SetSize(rcb);
				b->RegistClickEvent(thread::cctask(this,&reportdialog::WhenSelectQuest,i));
				rcb+=CPoint(0,30);
				m_jb_select.push_back(b);
			}

			{
				int w=Res::GetImage(L"button_normal.png")->GetWidth();
				int h=Res::GetImage(L"button_normal.png")->GetHeight();
				JStatic *js1=new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"退出登录",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
				JStatic *js2=new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"退出登录",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
				JStatic *js3=new JStatic(Res::GetImage(L"button_down.png"),false,true,L"退出登录",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
				JButton *b=new JButton(js1,js2,js3);
				m_vec_quest.Add(b,CRect(20,550,20+w,550+h));
				b->RegistClickEvent(thread::cctask(this,&reportdialog::WhenRetLogin));
			}
	
// 			{
// 			int w=Res::GetImage(L"button_normal.png")->GetWidth();
// 			int h=Res::GetImage(L"button_normal.png")->GetHeight();
// 			JStatic *normal = new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"积分查看",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
// 			JStatic *hover = new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"积分查看",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
// 			JStatic *down = new JStatic(Res::GetImage(L"button_down.png"),false,true,L"积分查看",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
// 			m_btnusertaskurl.SetNormalJStatic(normal);
// 			m_btnusertaskurl.SetHoverJStatic(hover);
// 			m_btnusertaskurl.SetDownJStatic(down);
// 			m_btnscoreshopurl.RegistClickEvent(thread::cctask(this,&reportdialog::WhenOpenUrl,SHOPURL));
// 			m_vec_quest.Add(&m_btnusertaskurl,CRect(20,490,20+w,490+h));
// 
// 			}
// 			{
// 				int w=Res::GetImage(L"button_normal.png")->GetWidth();
// 				int h=Res::GetImage(L"button_normal.png")->GetHeight();
// 				JStatic *normal = new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"礼物兑换",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
// 				JStatic *hover = new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"礼物兑换",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
// 				JStatic *down = new JStatic(Res::GetImage(L"button_down.png"),false,true,L"礼物兑换",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black));
// 				m_btnscoreshopurl.SetNormalJStatic(normal);
// 				m_btnscoreshopurl.SetHoverJStatic(hover);
// 				m_btnscoreshopurl.SetDownJStatic(down);
// 				m_btnusertaskurl.RegistClickEvent(thread::cctask(this,&reportdialog::WhenOpenUrl,TASKURL));
// 				m_vec_quest.Add(&m_btnscoreshopurl,CRect(20,520,20+w,520+h));
// 
// 			}
			
		}

		//////////////// commit //////////////
		{
			{
				int w=Res::GetImage(L"close_normal.png")->GetWidth();
				int h=Res::GetImage(L"close_normal.png")->GetHeight();
				JButton *b=new JButton(new JStatic(Res::GetImage(L"close_normal.png"),false,true),new JStatic(Res::GetImage(L"close_hover.png"),false,true),new JStatic(Res::GetImage(L"close_down.png"),false,true));
				b->RegistClickEvent(thread::cctask(this,&reportdialog::WhenClose));
				m_vec_report.Add(b,CRect(400-w,0,400,h));

				int w2=Res::GetImage(L"min_normal.png")->GetWidth();
				int h2=Res::GetImage(L"min_normal.png")->GetHeight();
				JButton *b2=new JButton(new JStatic(Res::GetImage(L"min_normal.png"),false,true),new JStatic(Res::GetImage(L"min_hover.png"),false,true),new JStatic(Res::GetImage(L"min_down.png"),false,true));
				b2->RegistClickEvent(thread::cctask(this,&reportdialog::WhenMin));
				m_vec_report.Add(b2,CRect(400-w-w2,0,400-w,h2));
			}

			m_vec_report.Add(&m_js_questtitle,CRect(20,30,380,50));

			m_vec_report.Add(&m_js_username,CRect(10,0,200,30));

			m_vec_report.Add(new JStatic(L"标题",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear)),CRect(20,60,380,80));

			m_vec_report.Add(&m_jedit_title,CRect(20,88,380,112));

			m_vec_report.Add(new JStatic(L"内容",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear)),CRect(20,120,380,140));

			m_vec_report.Add(&m_jedit_content,CRect(20,150,380,348));

			m_vec_report.Add(new JStatic(L"请留下您的QQ号",Res::GetFont(),Res::GetStringFormat(StringAlignmentNear)),CRect(20,360,200,380));

			m_jedit_qq.SetNumberOnly(true);
			m_vec_report.Add(&m_jedit_qq,CRect(200,359,380,382));
			
			{
 				int w=Res::GetImage(L"button_normal.png")->GetWidth();
 				int h=Res::GetImage(L"button_normal.png")->GetHeight();
 				m_jb_pic.SetNormalJStatic(new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"添加截图ctr+z",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
 				m_jb_pic.SetHoverJStatic(new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"添加截图ctr+z",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
 				m_jb_pic.SetDownJStatic(new JStatic(Res::GetImage(L"button_down.png"),false,true,L"添加截图ctr+z",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
 				m_jb_pic.RegistClickEvent(thread::cctask(this,&reportdialog::WhenShot));
 				m_vec_report.Add(&m_jb_pic,CRect(20,390,20+w,390+h));

			
				m_jb_localpic.SetNormalJStatic(new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"本地图片",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_jb_localpic.SetHoverJStatic(new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"本地图片",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_jb_localpic.SetDownJStatic(new JStatic(Res::GetImage(L"button_down.png"),false,true,L"本地图片",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_jb_localpic.RegistClickEvent(thread::cctask(this,&reportdialog::WhenLocalPic));
				m_vec_report.Add(&m_jb_localpic,CRect(120,390,120+w,390+h));
			}
				
			for(int i=0;i<5;++i)
			{
				int x=i;
				m_vec_report.Add(&m_js_pic[i],CRect(30+x*70,432,90+x*70,492));
				m_js_pic[i].RegistDeleteEvent(thread::cctask(this,&reportdialog::WhenDeletePic));
			}

			{
				int w=Res::GetImage(L"button_normal.png")->GetWidth();
				int h=Res::GetImage(L"button_normal.png")->GetHeight();
				m_pjb_commit.SetNormalJStatic(new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"提交",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_pjb_commit.SetHoverJStatic(new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"提交",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_pjb_commit.SetDownJStatic(new JStatic(Res::GetImage(L"button_down.png"),false,true,L"提交",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_vec_report.Add(&m_pjb_commit,CRect(20,510,20+w,510+h));
				m_pjb_commit.RegistClickEvent(thread::cctask(this,&reportdialog::WhenReport));
			}

			m_vec_report.Add(&m_js_commitinfo,CRect(140,514,380,538));
			m_jp.SetSize(CRect(140,514,380,538));

			{
				int w=Res::GetImage(L"button_normal.png")->GetWidth();
				int h=Res::GetImage(L"button_normal.png")->GetHeight();
				m_pjb_retquest.SetNormalJStatic(new JStatic(Res::GetImage(L"button_normal.png"),false,true,L"返回任务选择",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_pjb_retquest.SetDownJStatic(new JStatic(Res::GetImage(L"button_hover.png"),false,true,L"返回任务选择",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_pjb_retquest.SetHoverJStatic(new JStatic(Res::GetImage(L"button_down.png"),false,true,L"返回任务选择",Res::GetFont(),Res::GetStringFormat(),Res::GetSolidBrush(Color::Black)));
				m_vec_report.Add(&m_pjb_retquest,CRect(20,550,20+w,550+h));
				m_pjb_retquest.RegistClickEvent(thread::cctask(this,&reportdialog::WhenRetSelectQuest));
			}
		}
	}

	void create()
	{
		m_window.Create(NULL,CRect(0,0,400,600));
		m_window.SetIcon(LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(IDI_USERTEST)));
		JVector *root=m_window.GetRootFrame();
		m_window.SetReportdilog(this);

		root->Add(&m_vec_login,CRect(0,0,400,600));

		m_window.CenterWindow();
		m_window.ShowWindow(SW_SHOW);
		m_window.UpdateWindow();
		m_window.RegsiterKeyDown(thread::cctask(this,&reportdialog::WhenShot));

	}

	void WhenClose()
	{
		m_window.SendMessage(WM_CLOSE);
	}

	void WhenLogin()
	{
		CString username=m_edit_username.GetText();
		CString password=m_edit_password.GetText();
		if(username.IsEmpty())
		{
			m_js_logininfo.SetText(L"用户名不能为空");
			return;
		}

		if(password.IsEmpty())
		{
			m_js_logininfo.SetText(L"密码不能为空");
			return;
		}

		// disable ui
		m_pjb_login.GetNormalJStatic()->SetText(L"登录中..");
		m_pjb_login.GetDownJStatic()->SetText(L"登录中..");
		m_pjb_login.GetHoverJStatic()->SetText(L"登录中..");
		m_js_logininfo.SetText(L"");
		m_pjb_login.Enable(false);

		Logininfo lo(username,password,m_vcodekey,m_jedit_vcode.GetText());
		thread::thread_maganer::posttask(nettid,thread::cftask(DoLogin,this,lo));
	}

	void WhenLoginFail(Logresult logresult)
	{

		m_pjb_login.GetNormalJStatic()->SetText(L"登录");
		m_pjb_login.GetDownJStatic()->SetText(L"登录");
		m_pjb_login.GetHoverJStatic()->SetText(L"登录");
		m_pjb_login.Enable(true);

		if(logresult.m_imageurl==L"")
		{
			m_vcodekey=L"";
			m_js_logininfo.SetText(L"登录失败,请检查用户名密码");
			m_js_vcode.Show(false);
			m_js_vcodeimg.SetImage(NULL);
			m_js_vcodeimg.Show(false);
			m_jedit_vcode.SetText(L"");
			m_jedit_vcode.Show(false);
		}
		else
		{
			m_vcodekey=logresult.m_vcodekey;
			m_js_logininfo.SetText(L"请输入验证码");
			m_js_vcode.Show(true);
			m_js_vcodeimg.SetImage(NULL);
			m_js_vcodeimg.SetText(L"加载中");
			m_js_vcodeimg.Show(true);
			m_jedit_vcode.SetText(L"");
			m_jedit_vcode.Show(true);
			thread::thread_maganer::posttask(nettid,thread::cftask(DoDownloadImg,this,logresult.m_imageurl));
		}
		m_window.UpdateWindow();
	}

	void WhenLoginSuccess(CString username,vector<UserTask> taskinfo)
	{
		m_username=username;
		m_quest_info=taskinfo;

		SetUsername(m_edit_username.GetText());
		SetPassword(m_edit_password.GetText());

		m_js_username_q.SetText(m_username);
		m_window.GetRootFrame()->Remove(&m_vec_login);

		for(int i=0;i<10;++i)
		{
			m_vec_quest.Remove(m_js_info[i]);
			m_vec_quest.Remove(m_jb_select[i]);
		}

		for(int i=0;i<10;++i)
		{
			if(i<m_quest_info.size())
			{
				m_js_info[i]->SetText(m_quest_info[i].taskName);
				m_vec_quest.Add(m_js_info[i]);
				m_vec_quest.Add(m_jb_select[i]);
			}
		}

		CRect rc;
		m_window.GetClientRect(&rc);
		m_window.GetRootFrame()->Add(&m_vec_quest,rc);
		m_window.SetActiveState(QUEST);
		m_jedit_qq.SetText(GetQQ());
		m_window.UpdateWindow();
	}

	void WhenGetVcodeImg(Image *img)
	{
		m_js_vcodeimg.SetText(L"");
		m_js_vcodeimg.SetImage(img);
		m_window.UpdateWindow();
	}
	void WhenLocalPic()
	{
		m_jb_pic.Enable(false);
		m_jb_localpic.Enable(false);

		static OPENFILENAME ofn;      // 公共对话框结构。   
		TCHAR szFile[MAX_PATH]; // 保存获取文件名称的缓冲区。             
		// 初始化选择文件对话框。   
		ZeroMemory(&ofn, sizeof(OPENFILENAME));  
		ofn.lStructSize = sizeof(OPENFILENAME);  
		ofn.hwndOwner = NULL;  
		ofn.lpstrFile = szFile;  
		ofn.lpstrFile[0] = L'\0'; 
		ofn.nMaxFile = sizeof(szFile);  
		ofn.lpstrFilter = L"jpg(*.jpg)\0*.jpg\0png(*.png)\0*.png\0\0";  
		ofn.nFilterIndex = 1;  
		ofn.lpstrFileTitle =NULL;  
		ofn.nMaxFileTitle = 0;  
		ofn.lpstrInitialDir = NULL;  
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;  

		if (0 == ::GetOpenFileName(&ofn))
		{
			m_jb_pic.Enable(true);
			m_jb_localpic.Enable(true);
			return;
		}
		

		if (ofn.lpstrFile ==NULL)
		{
			return;
		}

		HBITMAP hbit=Getlocalpic(ofn.lpstrFile);
		if (hbit == NULL)
		{
			return;
		}
	
		for(int i=0;i<5;++i)
		{
			if(m_js_pic[i].GetImage()==NULL)
			{
				m_js_pic[i].SetImage(new Bitmap(hbit,NULL));
				break;
			}
		}
		bool full=true;
		for(int i=0;i<5;++i)
		{
			if(m_js_pic[i].GetImage()==NULL)
			{
				full=false;
			}
		}
		if(full)
		{
			m_jb_pic.Enable(false);
			m_jb_localpic.Enable(false);
		}
		else
		{
			m_jb_pic.Enable(true);
			m_jb_localpic.Enable(true);
		}
		return;
	}
	void WhenShot()
	{
		if (m_jb_pic.GetEnable() != true)
		{
			return;
		}
		
		m_window.ShowWindow(SW_HIDE);
		HBITMAP hbit=Snapshot();
		m_window.ShowWindow(SW_SHOW);
		if (hbit == NULL)
		{
			return;
		}
	
		for(int i=0;i<5;++i)
		{
			if(m_js_pic[i].GetImage()==NULL)
			{
				m_js_pic[i].SetImage(new Bitmap(hbit,NULL));
				break;
			}
		}
		bool full=true;
		for(int i=0;i<5;++i)
		{
			if(m_js_pic[i].GetImage()==NULL)
			{
				full=false;
			}
		}
		if(full)
		{
			m_jb_pic.Enable(false);
		}
	}

	void WhenDeletePic()
	{
		m_jb_pic.Enable(true);
		m_jb_localpic.Enable(true);
	}

	void WhenRetLogin()
	{
		m_js_logininfo.SetText(L"");
		m_edit_username.SetText(GetUsername());
		m_edit_password.SetText(GetPassword());
		m_window.GetRootFrame()->Remove(&m_vec_quest);
		m_pjb_login.GetNormalJStatic()->SetText(L"登录");
		m_pjb_login.GetDownJStatic()->SetText(L"登录");
		m_pjb_login.GetHoverJStatic()->SetText(L"登录");
		m_pjb_login.Enable(true);
		CRect rc;
		m_window.GetClientRect(&rc);
		m_jedit_vcode.SetText(L"");
		m_js_vcode.Show(false);
		m_js_vcodeimg.Show(false);
		m_jedit_vcode.Show(false);
		m_window.GetRootFrame()->Add(&m_vec_login,rc);
		m_window.SetActiveState(LOGIN);
	}

	void WhenMin()
	{
		m_window.ShowWindow(SW_MINIMIZE);
	}

	void WhenReport()
	{
		BugInfo buginfo;
		buginfo.setUsername(m_username);
		buginfo.setTaskid(m_quest_id);
	
		
		if(m_jedit_title.GetText().Trim().GetLength()!=0)
		{
			buginfo.SetData(L"title",m_jedit_title.GetText());
		}
		else
		{
			m_js_commitinfo.SetText(L"标题不能为空");
			return;
		}
		if(m_jedit_content.GetText().Trim().GetLength()!=0)
		{
			buginfo.SetData(L"content",m_jedit_content.GetText());
		}
		else
		{
			m_js_commitinfo.SetText(L"内容不能为空");
			return;
		}
		//增加字数判空
		if(m_jedit_content.GetText().GetLength()>=MAX_STR_LIMIT)
		{
			m_js_commitinfo.SetText(L"字数最多为250个汉字");
			return;
		}

		if(m_jedit_qq.GetText().GetLength()!=0)
		{
			buginfo.SetData(L"qq",m_jedit_qq.GetText());
			SetQQ(m_jedit_qq.GetText());
		}
		else
		{
			m_js_commitinfo.SetText(L"请填写您的qq号");
			return;
		}
		buginfo.SetData(L"os_ver",GetOsVer());
		buginfo.SetData(L"ie_ver",GetIeVer());
		for(int i=0;i<5;++i)
		{
			Image* pimg=m_js_pic[i].GetImage();
			if(pimg!=NULL)
			{
				HGLOBAL hGlobal = NULL;
				int len=0;
				IStream* pStream = NULL;
				CreateStreamOnHGlobal(NULL, TRUE, &pStream);
				CLSID clsid;
				GetEncoderClsid(L"image/png", &clsid);
				pimg->Save(pStream,&clsid);
				GetHGlobalFromStream(pStream, &hGlobal); // 获取 IStream 的内存句柄
				LPBYTE pBits = (LPBYTE)GlobalLock(hGlobal); // pBits 就是存储JPEG内容的内存指针
				len=GlobalSize(hGlobal);
				buginfo.addPic(BMem(pBits,len));
			}
		}
		m_pjb_retquest.Enable(false);
		m_pjb_commit.Enable(false);
		m_vec_report.Remove(&m_js_commitinfo);
		m_vec_report.Add(&m_jp);
		thread::thread_maganer::posttask(nettid,thread::cftask(DoCommit,this,buginfo));
	}

	void WhenCommitSuccess()
	{
		m_pjb_retquest.Enable(true);
		m_pjb_commit.Enable(true);
		m_jp.SetRealVal(100);
		m_window.UpdateWindow();
		m_jedit_title.SetText(L"");
		m_jedit_content.SetText(L"");
		m_js_commitinfo.SetText(L"");
		m_vec_report.Add(&m_js_commitinfo);
		m_vec_report.Remove(&m_jp);
		m_jp.SetRealVal(0);
		m_jb_pic.Enable(true);
		m_jb_localpic.Enable(true);

		for(int i=0;i<5;++i)
		{
			m_js_pic[i].SetImage(NULL);
		}
		::MessageBox(m_window,L"提交成功",L"成功",MB_OK);
		m_window.UpdateWindow();
	}

	void WhenCommitFail()
	{
		m_pjb_retquest.Enable(true);
		m_pjb_commit.Enable(true);
		m_window.UpdateWindow();
		::MessageBox(m_window,L"提交失败",L"失败",MB_OK);
		m_js_commitinfo.SetText(L"");
		m_vec_report.Add(&m_js_commitinfo);
		m_vec_report.Remove(&m_jp);
		m_jp.SetRealVal(0);
		m_jb_pic.Enable(true);
		m_jb_localpic.Enable(true);
		for(int i=0;i<5;++i)
		{
			m_js_pic[i].SetImage(NULL);
		}
		m_window.UpdateWindow();
	}

	void WhenSelectQuest(int i)
	{
		m_quest_title=m_quest_info[i].taskName;
		m_quest_id=m_quest_info[i].taskID;

		m_js_questtitle.SetText(m_quest_title);
		m_js_username.SetText(m_username);

		m_jedit_title.SetText(L"");
		m_jedit_content.SetText(L"");
		m_jedit_qq.SetText(GetQQ());
		m_jb_pic.Enable(true);
		m_jb_localpic.Enable(true);
		for(int i=0;i<5;++i)
		{
			m_js_pic[i].SetImage(NULL);
		}

		m_window.GetRootFrame()->Remove(&m_vec_quest);

		CRect rc;
		m_window.GetClientRect(&rc);
		m_window.GetRootFrame()->Add(&m_vec_report,rc);
		m_window.SetActiveState(COMMIT);
	}

	void WhenRetSelectQuest()
	{
		m_window.GetRootFrame()->Remove(&m_vec_report);
		CRect rc;
		m_window.GetClientRect(&rc);
		m_window.GetRootFrame()->Add(&m_vec_quest,rc);
		m_window.SetActiveState(QUEST);
	}

	void WhenProcess(int i)
	{
		m_jp.SetVal(i);
	}
	void WhenOpenUrl(CString url)
	{
		CString cmdline;
		cmdline.Format(L"cmd /c start %s",url);
		WinExec((LPCSTR)(LPCSTR)UnicodetoACP(cmdline),SW_HIDE);
		return;
	}

private:
	JWindow m_window;
	JVector m_vec_login;
	JStatic m_js_logininfo;
	JEdit m_edit_username;
	JEdit m_edit_password;
	JButton m_pjb_login;
	CString m_username;
	CString m_password;
	JStatic m_js_vcode;
	JStatic m_js_vcodeimg;
	JEdit m_jedit_vcode;
	CString m_vcodekey;

	JVector m_vec_quest;
	vector<UserTask> m_quest_info;
	vector<JStatic*> m_js_info;
	vector<JButton*> m_jb_select;
	JStatic m_js_username_q;
	JStatic m_usertask_title;
	JStatic m_scoreshop_title;
	JButton m_btnusertaskurl;
	JButton m_btnscoreshopurl;

	JVector m_vec_report;
	JStatic m_js_username;
	JStatic m_js_questtitle;
	JEdit m_jedit_title;
	JEdit m_jedit_content;
	JEdit m_jedit_qq;
	JStatic m_js_commitinfo;
	JButton m_pjb_retquest;
	JButton m_pjb_commit;
	JProcess m_jp;
	CString m_quest_title;
	CString m_quest_id;
	JButton m_jb_pic;
	JButton m_jb_picclose[5];
	JButton m_jb_localpic;
	JPicView m_js_pic[5];

};



int CallbackProcess(void *progress_data,
	double t, /* dltotal */
	double d, /* dlnow */
	double ultotal,
	double ulnow)
{
	reportdialog* This=(reportdialog*)progress_data;

	if(ultotal>0)
	{
		int prg=ulnow*100/ultotal;
		if (prg<0)
		{	
			prg=0;
		}
		if(prg>99)
		{
			prg=99;
		}
		thread::thread_maganer::posttask(uitid,thread::cctask(This,&reportdialog::WhenProcess,prg));
	}
	return 0;
}

void DoLogin(reportdialog* This,Logininfo lo)
{
	Logresult result=login(lo);
	if(result.m_result==0)
	{
		vector<UserTask> info=getTask(lo.m_userName);
		thread::thread_maganer::posttask(uitid,thread::cctask(This,&reportdialog::WhenLoginSuccess,lo.m_userName,info));
	}
	else
	{
		thread::thread_maganer::posttask(uitid,thread::cctask(This,&reportdialog::WhenLoginFail,result));
	}
}

void DoCommit(reportdialog* This,BugInfo buginfo)
{
	int ret=upload(buginfo,CallbackProcess,(void *)This);
	if(ret==0)
	{
		thread::thread_maganer::posttask(uitid,thread::cctask(This,&reportdialog::WhenCommitSuccess));
	}
	else
	{
		thread::thread_maganer::posttask(uitid,thread::cctask(This,&reportdialog::WhenCommitFail));
	}
}

void DoDownloadImg(reportdialog* This,CString url)
{
	Image* ret=downloadimage(url);
	if(ret!=NULL)
	{
		thread::thread_maganer::posttask(uitid,thread::cctask(This,&reportdialog::WhenGetVcodeImg,ret));
	}
}