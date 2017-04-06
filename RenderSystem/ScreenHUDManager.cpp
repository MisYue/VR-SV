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

	// ���HUD����
	IScreenHUD* CScreenHUDManager::GetScreenHUD( const VRString& strHUDName, const VRString& strViewName /*= "mainView"*/ ) const
	{
		// ���Ҷ��ڵ���ͼ
		ListViewScreenHUDs::const_iterator cstItor = m_lstScreenHUDs.find(strViewName);
		if (m_lstScreenHUDs.end() == cstItor)
		{
			// û���ҵ�
			IComManager::GetInstance().WriteLogMsg("��ǰ��ͼ������", ERROR_NOT_FIND);
			return (NULL);
		}

		// ���Ҷ��ڴ���
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

	// ͨ����Ļ���ƻ��HUD����
	CScreenHUDManager::ListScreenHUDs CScreenHUDManager::GetScreenHUD( CRenderView* pRenderView ) const
	{
		ListScreenHUDs lstScreenHUDs;
		// ���Ҷ��ڵ���ͼ
		ListViewScreenHUDs::const_iterator cstItor = m_lstScreenHUDs.find(pRenderView->GetName());
		if (m_lstScreenHUDs.end() != cstItor)
		{
			lstScreenHUDs = cstItor->second;
		
		}

		return (lstScreenHUDs);
	}

	// ���HUD����
	void CScreenHUDManager::AddScreenHUD( const IScreenHUD* pIScreenHUD, const VRString& strViewName /*= "mainView"*/ )
	{
		// ���Ҷ��ڵ���ͼ
		ListViewScreenHUDs::iterator itor = m_lstScreenHUDs.find(strViewName);
		if (m_lstScreenHUDs.end() == itor)
		{
			// û���ҵ�
			ListScreenHUDs lstScreenHUD;
			lstScreenHUD.push_back((CScreenHUD*)pIScreenHUD);
			m_lstScreenHUDs[strViewName] = lstScreenHUD;
			// ��ӳɹ�
			IComManager::GetInstance().WriteLogMsg(strViewName + "�����Ļ����" + pIScreenHUD->GetHUDName() + "�ɹ�");
			return;
		}

		// ���Ҷ��ڴ���
		ListScreenHUDs& lstScreenHUD = itor->second;
		lstScreenHUD.push_back((CScreenHUD*)pIScreenHUD);
		// ��ӳɹ�
		IComManager::GetInstance().WriteLogMsg(strViewName + "�����Ļ����" + pIScreenHUD->GetHUDName() + "�ɹ�");
	}

}
