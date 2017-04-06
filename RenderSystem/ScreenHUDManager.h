/************************************************************************
 作者： LJ                                                            
 用途:  抬头HUD屏幕管理
 时间： 2015-11-29                                                    
 修改时间:                                                            
************************************************************************/

#ifndef _SCREENHUDMANAGER_H_
#define _SCREENHUDMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CScreenHUD;
	class CRenderView;

	class CScreenHUDManager : public IScreenHUDManager
	{
	public:
		typedef std::list<CScreenHUD*> ListScreenHUDs;
	public:
		CScreenHUDManager(void);
		virtual ~CScreenHUDManager(void);

	public:
		// 获得HUD窗口
		virtual IScreenHUD* GetScreenHUD(const VRString& strHUDName, const VRString& strViewName = "mainView") const ;
		// 添加HUD窗口
		virtual void AddScreenHUD(const IScreenHUD* pIScreenHUD, const VRString& strViewName = "mainView") ;

	public:
		// 通过屏幕名称获得HUD窗口
		ListScreenHUDs GetScreenHUD(CRenderView* pRenderView) const;

	protected:
		typedef std::map<VRString, ListScreenHUDs> ListViewScreenHUDs;

	private:
		ListViewScreenHUDs m_lstScreenHUDs;
	};

}

#endif // !_SCREENHUDMANAGER_H_