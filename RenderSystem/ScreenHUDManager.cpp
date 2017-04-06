#define OSGRENDER_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "ScreenHUD.h"
#include "RenderView.h"
#include "ScreenHUDManager.h"

namespace VR_Soft
{
	CScreenHUDManager::CScreenHUDManager(void)
	{
	}


	CScreenHUDManager::~CScreenHUDManager(void)
	{
	}

	// 获得HUD窗口
	IScreenHUD* CScreenHUDManager::GetScreenHUD( const VRString& strHUDName, const VRString& strViewName /*= "mainView"*/ ) const
	{
		// 查找对于的试图
		ListViewScreenHUDs::const_iterator cstItor = m_lstScreenHUDs.find(strViewName);
		if (m_lstScreenHUDs.end() == cstItor)
		{
			// 没有找到
			IComManager::GetInstance().WriteLogMsg("当前视图不存在", ERROR_NOT_FIND);
			return (NULL);
		}

		// 查找对于窗口
		const ListScreenHUDs& lstScreenHUD = cstItor->second;

		ListScreenHUDs::const_iterator cstHUDItor = lstScreenHUD.begin();
		for (; lstScreenHUD.end() != cstHUDItor; ++cstHUDItor)
		{
			if (0 == (*cstHUDItor)->GetHUDName().compare(strHUDName))
			{
				return (*cstHUDItor);
			}
		}

		return (NULL);
	}

	// 通过屏幕名称获得HUD窗口
	CScreenHUDManager::ListScreenHUDs CScreenHUDManager::GetScreenHUD( CRenderView* pRenderView ) const
	{
		ListScreenHUDs lstScreenHUDs;
		// 查找对于的试图
		ListViewScreenHUDs::const_iterator cstItor = m_lstScreenHUDs.find(pRenderView->GetName());
		if (m_lstScreenHUDs.end() != cstItor)
		{
			lstScreenHUDs = cstItor->second;
		
		}

		return (lstScreenHUDs);
	}

	// 添加HUD窗口
	void CScreenHUDManager::AddScreenHUD( const IScreenHUD* pIScreenHUD, const VRString& strViewName /*= "mainView"*/ )
	{
		// 查找对于的试图
		ListViewScreenHUDs::iterator itor = m_lstScreenHUDs.find(strViewName);
		if (m_lstScreenHUDs.end() == itor)
		{
			// 没有找到
			ListScreenHUDs lstScreenHUD;
			lstScreenHUD.push_back((CScreenHUD*)pIScreenHUD);
			m_lstScreenHUDs[strViewName] = lstScreenHUD;
			// 添加成功
			IComManager::GetInstance().WriteLogMsg(strViewName + "添加屏幕窗口" + pIScreenHUD->GetHUDName() + "成功");
			return;
		}

		// 查找对于窗口
		ListScreenHUDs& lstScreenHUD = itor->second;
		lstScreenHUD.push_back((CScreenHUD*)pIScreenHUD);
		// 添加成功
		IComManager::GetInstance().WriteLogMsg(strViewName + "添加屏幕窗口" + pIScreenHUD->GetHUDName() + "成功");
	}

}
