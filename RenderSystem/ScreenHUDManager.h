/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ̧ͷHUD��Ļ����
 ʱ�䣺 2015-11-29                                                    
 �޸�ʱ��:                                                            
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
		// ���HUD����
		virtual IScreenHUD* GetScreenHUD(const VRString& strHUDName, const VRString& strViewName = "mainView") const ;
		// ���HUD����
		virtual void AddScreenHUD(const IScreenHUD* pIScreenHUD, const VRString& strViewName = "mainView") ;

	public:
		// ͨ����Ļ���ƻ��HUD����
		ListScreenHUDs GetScreenHUD(CRenderView* pRenderView) const;

	protected:
		typedef std::map<VRString, ListScreenHUDs> ListViewScreenHUDs;

	private:
		ListViewScreenHUDs m_lstScreenHUDs;
	};

}

#endif // !_SCREENHUDMANAGER_H_