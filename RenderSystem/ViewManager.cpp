#define OSGRENDER_PLUGIN_EXPORT
#include <algorithm>
#include <boost/foreach.hpp>
#include <osgViewer/View>
#include <osgViewer/CompositeViewer>
#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "RenderView.h"
#include "ViewManager.h"

namespace VR_Soft
{
	CViewManager::CViewManager(void):m_bFirst(false)
	{
		m_mapStrViewUI.clear();

		m_pCompositeViewer = new osgViewer::CompositeViewer;
	}


	CViewManager::~CViewManager(void)
	{
		m_pCompositeViewer->stopThreading();
		//m_pCompositeViewer = NULL;
		RemoveAllViewUI();
		// ɾ����ͼ
		RemoveAllView();

		int nCount = m_pCompositeViewer->referenceCount();
		int nViewCount = m_pCompositeViewer->getNumViews();
		for (int index = 0; index < nViewCount; ++index)
		{
			osgViewer::View* pViewe = m_pCompositeViewer->getView(index);
		//	m_pCompositeViewer->removeView(pViewe);
		}
		//VRSOFT_DELETE(m_pCompositeViewer);
	}

	// ������ͼ
	void CViewManager::CreateView(const VRString& strViewName, int x, int y, int width, int height)
	{
		// д��ϵͳ��־
		IComManager::GetInstance().WriteLogMsg("��ʼ������ͼ��"+strViewName);

		if (!m_bFirst)
		{
			// �����߳�ģʽ
			m_pCompositeViewer->setThreadingModel(osgViewer::CompositeViewer::DrawThreadPerContext);

			// disable the default setting of viewer.done() by pressing Escape.
			m_pCompositeViewer->setKeyEventSetsDone(0);
			m_pCompositeViewer->setQuitEventSetsDone(false);
			m_bFirst = true;
		}
		
		osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
		osg::GraphicsContext::Traits* pTraits = new osg::GraphicsContext::Traits;
// 		pTraits->windowName = strViewName;
// 		pTraits->windowDecoration = false;
// 		pTraits->x = x;
// 		pTraits->y = y;
// 		pTraits->width = width;
// 		pTraits->height = height ;
// 		pTraits->doubleBuffer = true;

		pTraits->readDISPLAY();
		if (pTraits->displayNum<0) pTraits->displayNum = 0;

		pTraits->screenNum = 0;
		pTraits->x = x;
		pTraits->y = y;
		pTraits->width = width;
		pTraits->height = height ;
		pTraits->alpha = ds->getMinimumNumAlphaBits();
		pTraits->stencil = ds->getMinimumNumStencilBits();
		pTraits->windowDecoration = false;
		pTraits->doubleBuffer = true;
		pTraits->sharedContext = 0;
		pTraits->sampleBuffers = ds->getMultiSamples();
		pTraits->samples = ds->getNumMultiSamples();

		pTraits->setInheritedWindowPixelFormat = true;

		
		// ��ʼ������
		MapStrViewUI::iterator itor = m_mapStrViewUI.find(strViewName);
		if (m_mapStrViewUI.end() == itor)
		{
			return;
		}

		// ��ʼ������
		itor->second->InitUI(pTraits);

		// ������ͼ
		IRenderView* pIView = new CRenderView;
		pIView->SetName(strViewName.c_str());

		// ��ӵ�����
		m_listRenderViews.push_back(pIView);
		m_pCompositeViewer->addView(pIView->GetView());

		// ��ʼ�����
		osg::Camera* pCamera = pIView->GetView()->getCamera();
		itor->second->InitCamera(pCamera);

		// ��������
		pIView->GetView()->addEventHandler( new osgViewer::StatsHandler );
		pIView->GetView()->setCameraManipulator( new osgGA::TrackballManipulator );

		itor->second->CreateVRWindow(pIView->GetView());

		// д��ϵͳ��־
		IComManager::GetInstance().WriteLogMsg("�ɹ�������ͼ��"+strViewName);
	}

	// ע��UI
	void CViewManager::RegisterViewUI(IRenderViewUI* pRenderViewUI)
	{
		// ��ѯ�Ƿ���ڵ�ǰ����
		MapStrViewUI::const_iterator cstItor = m_mapStrViewUI.find(pRenderViewUI->GetUIName());
		if (m_mapStrViewUI.end() == cstItor)
		{
			m_mapStrViewUI[pRenderViewUI->GetUIName()] = pRenderViewUI;
		}		
	}

	// ��ע��UI
	void CViewManager::UnReginsterViewUI(IRenderViewUI* pRenderViewUI)
	{

		// ɾ����ǰ�Ľ���
		MapStrViewUI::iterator itor = m_mapStrViewUI.find(pRenderViewUI->GetUIName());
		m_mapStrViewUI.erase(itor);
	}

	// ˢ��
	void CViewManager::Flush(void)
	{
		PreFrame();
		Frame();
		PostFrame();
		
	}

	// ���й�һ��ʼ��
	void CViewManager::Realize(void) 
	{
		if (!m_pCompositeViewer->isRealized())
		{
			m_pCompositeViewer->realize();
		}
	}

	// ��ѯ��ͼ
	IRenderView* CViewManager::GetRenderView(const VRString& strViewName) const
	{
		// ��ѯ��ͼ
		ListRenderViews::const_iterator cstItor = m_listRenderViews.begin();
		for (; m_listRenderViews.end() != cstItor; ++cstItor)
		{
			if (0 == strViewName.compare((*cstItor)->GetName()))
			{
				return (*cstItor);
			}
		}
		
		return (NULL);
	}

	// ɾ�����еĽ���
	void CViewManager::RemoveAllViewUI(void)
	{
		// �̰߳�ȫ
//		VR_MUTEX_AUTO;

		for (MapStrViewUI::iterator itor = m_mapStrViewUI.begin(); m_mapStrViewUI.end() != itor; ++itor)
		{
			itor->second = NULL;
		}
		m_mapStrViewUI.clear();
	}

	// ɾ�����е�View
	void CViewManager::RemoveAllView(void)
	{
		// �̰߳�ȫ
//		VR_MUTEX_AUTO;

		for (ListRenderViews::iterator itor = m_listRenderViews.begin(); m_listRenderViews.end() != itor; ++itor)
		{
			IRenderView* pRenderView = *itor;
			osgViewer::View* pVew = pRenderView->GetView();
			// �������
			pRenderView->ClearData();
			// ɾ������
			VRSOFT_DELETE(pRenderView);
			// �Ƴ���ǰ��ͼ
			//m_pCompositeViewer->removeView(pVew);
			
		}
		m_mapStrViewUI.clear();
	}

	// �����Ⱦ����
	void CViewManager::AddEntityDrawManager(IEntityDrawManager* pIEntityDrawManager)
	{
		// �����Ƿ���� �����������ظ����
		if (IsHandEntityDrawManager(pIEntityDrawManager))
		{
			m_lstEntityDrawManagers.push_back(pIEntityDrawManager);
		}

		// ��ӳɹ�
		IComManager::GetInstance().WriteLogMsg("��ӵ�ǰ��Ⱦ���Գɹ�", ERROR_NOT_FIND);

	}

	// ��ѯ��Ⱦ�����Ƿ����
	bool CViewManager::IsHandEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) const 
	{
		// ������ѯ
		ListEntityDrawManagers::const_iterator cstItor = std::find(m_lstEntityDrawManagers.begin(), m_lstEntityDrawManagers.end(), pIEntityDrawManager);
		return (m_lstEntityDrawManagers.end() == cstItor);
	}

	// ÿһ֡ǰ����
	void CViewManager::PreFrame(void)
	{
		// ��ʼ���¼��б�
		IEvent::GetInstance().Init();

		// ������Ϣ
		IMessageManager::GetInstance().DispatchDelayedMessages();

		//// �ж��Ƿ����ڱ༭�������
		//if (ISimManager::Stop == ISimManager::GetInstance().GetSimCmd())
		//{
		//	// �Ե�ǰ��ʵ����б༭
		//	IAttributeManager::GetInstance().EidtCurrentEntityBase();
		//}
	}

	// ���ø���
	void CViewManager::Frame(void)
	{
		// �Ƿ��Ѿ�������һ֡
		if (m_pCompositeViewer->done())
		{
			return ;
		}
			
		// �������е���Ⱦ��
		ListEntityDrawManagers::iterator drawItor = m_lstEntityDrawManagers.begin();
		for (; m_lstEntityDrawManagers.end() != drawItor; ++drawItor)
		{
			(*drawItor)->Update();
		}

		ListRenderViews::iterator viewItor = m_listRenderViews.begin();
		for (; m_listRenderViews.end() != viewItor; ++viewItor)
		{
			CRenderView* pRenderView = dynamic_cast<CRenderView*>(*viewItor);
			pRenderView->UpdateView();
		}

		m_pCompositeViewer->frame();

	}

	// ÿһ֡�����
	void CViewManager::PostFrame(void)
	{
	}

	// �Ƴ���Ⱦ����
	void CViewManager::RemoveEntityDrawManager(IEntityDrawManager* pIEntityDrawManager)
	{
		// ��ѯ���Ե�λ��
		ListEntityDrawManagers::iterator itor = std::find(m_lstEntityDrawManagers.begin(), m_lstEntityDrawManagers.end(), pIEntityDrawManager);
		if (m_lstEntityDrawManagers.end() != itor)
		{
			m_lstEntityDrawManagers.erase(itor);
			IComManager::GetInstance().WriteLogMsg("ɾ����ǰ���Գɹ�");
		}
	}

	// �������
	int CViewManager::GetIndexEntityDrawManager(IEntityDrawManager* pIEntityDrawManager)
	{
		// �������е���Ⱦ����
		ListEntityDrawManagers::const_iterator cstItor = m_lstEntityDrawManagers.begin();
		for (int index = 0; cstItor != m_lstEntityDrawManagers.end(); ++index, ++cstItor)
		{
			if ((*cstItor) == pIEntityDrawManager)
			{
				return (index);
			}
		}

		return (-1);
	}

	// ͨ�����������Ⱦ����
	IEntityDrawManager* CViewManager::GetEntityDrawManager(const int index)
	{
		ListEntityDrawManagers::iterator itor = m_lstEntityDrawManagers.begin();
		for (int nindex = 0; itor != m_lstEntityDrawManagers.end(); ++nindex, ++itor)
		{
			if (nindex == index)
			{
				return (*itor);
			}
		}

		return (NULL);
	}

}
