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
		// 删除视图
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

	// 创建视图
	void CViewManager::CreateView(const VRString& strViewName, int x, int y, int width, int height)
	{
		// 写入系统日志
		IComManager::GetInstance().WriteLogMsg("开始创建视图："+strViewName);

		if (!m_bFirst)
		{
			// 设置线程模式
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

		
		// 初始化窗口
		MapStrViewUI::iterator itor = m_mapStrViewUI.find(strViewName);
		if (m_mapStrViewUI.end() == itor)
		{
			return;
		}

		// 初始化界面
		itor->second->InitUI(pTraits);

		// 创建视图
		IRenderView* pIView = new CRenderView;
		pIView->SetName(strViewName.c_str());

		// 添加到名称
		m_listRenderViews.push_back(pIView);
		m_pCompositeViewer->addView(pIView->GetView());

		// 初始化相机
		osg::Camera* pCamera = pIView->GetView()->getCamera();
		itor->second->InitCamera(pCamera);

		// 设置属性
		pIView->GetView()->addEventHandler( new osgViewer::StatsHandler );
		pIView->GetView()->setCameraManipulator( new osgGA::TrackballManipulator );

		itor->second->CreateVRWindow(pIView->GetView());

		// 写入系统日志
		IComManager::GetInstance().WriteLogMsg("成功创建视图："+strViewName);
	}

	// 注册UI
	void CViewManager::RegisterViewUI(IRenderViewUI* pRenderViewUI)
	{
		// 查询是否存在当前界面
		MapStrViewUI::const_iterator cstItor = m_mapStrViewUI.find(pRenderViewUI->GetUIName());
		if (m_mapStrViewUI.end() == cstItor)
		{
			m_mapStrViewUI[pRenderViewUI->GetUIName()] = pRenderViewUI;
		}		
	}

	// 反注册UI
	void CViewManager::UnReginsterViewUI(IRenderViewUI* pRenderViewUI)
	{

		// 删除当前的界面
		MapStrViewUI::iterator itor = m_mapStrViewUI.find(pRenderViewUI->GetUIName());
		m_mapStrViewUI.erase(itor);
	}

	// 刷新
	void CViewManager::Flush(void)
	{
		PreFrame();
		Frame();
		PostFrame();
		
	}

	// 进行归一初始化
	void CViewManager::Realize(void) 
	{
		if (!m_pCompositeViewer->isRealized())
		{
			m_pCompositeViewer->realize();
		}
	}

	// 查询视图
	IRenderView* CViewManager::GetRenderView(const VRString& strViewName) const
	{
		// 查询视图
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

	// 删除所有的界面
	void CViewManager::RemoveAllViewUI(void)
	{
		// 线程安全
//		VR_MUTEX_AUTO;

		for (MapStrViewUI::iterator itor = m_mapStrViewUI.begin(); m_mapStrViewUI.end() != itor; ++itor)
		{
			itor->second = NULL;
		}
		m_mapStrViewUI.clear();
	}

	// 删除所有的View
	void CViewManager::RemoveAllView(void)
	{
		// 线程安全
//		VR_MUTEX_AUTO;

		for (ListRenderViews::iterator itor = m_listRenderViews.begin(); m_listRenderViews.end() != itor; ++itor)
		{
			IRenderView* pRenderView = *itor;
			osgViewer::View* pVew = pRenderView->GetView();
			// 清空数据
			pRenderView->ClearData();
			// 删除数据
			VRSOFT_DELETE(pRenderView);
			// 移除当前视图
			//m_pCompositeViewer->removeView(pVew);
			
		}
		m_mapStrViewUI.clear();
	}

	// 添加渲染属性
	void CViewManager::AddEntityDrawManager(IEntityDrawManager* pIEntityDrawManager)
	{
		// 查找是否存在 存在则无需重复添加
		if (IsHandEntityDrawManager(pIEntityDrawManager))
		{
			m_lstEntityDrawManagers.push_back(pIEntityDrawManager);
		}

		// 添加成功
		IComManager::GetInstance().WriteLogMsg("添加当前渲染属性成功", ERROR_NOT_FIND);

	}

	// 查询渲染属性是否存在
	bool CViewManager::IsHandEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) const 
	{
		// 遍历查询
		ListEntityDrawManagers::const_iterator cstItor = std::find(m_lstEntityDrawManagers.begin(), m_lstEntityDrawManagers.end(), pIEntityDrawManager);
		return (m_lstEntityDrawManagers.end() == cstItor);
	}

	// 每一帧前调用
	void CViewManager::PreFrame(void)
	{
		// 初始化事件列表
		IEvent::GetInstance().Init();

		// 调用消息
		IMessageManager::GetInstance().DispatchDelayedMessages();

		//// 判断是否属于编辑仿真过程
		//if (ISimManager::Stop == ISimManager::GetInstance().GetSimCmd())
		//{
		//	// 对当前的实体进行编辑
		//	IAttributeManager::GetInstance().EidtCurrentEntityBase();
		//}
	}

	// 调用更新
	void CViewManager::Frame(void)
	{
		// 是否已经更新完一帧
		if (m_pCompositeViewer->done())
		{
			return ;
		}
			
		// 更新所有的渲染体
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

	// 每一帧后调用
	void CViewManager::PostFrame(void)
	{
	}

	// 移除渲染属性
	void CViewManager::RemoveEntityDrawManager(IEntityDrawManager* pIEntityDrawManager)
	{
		// 查询属性的位置
		ListEntityDrawManagers::iterator itor = std::find(m_lstEntityDrawManagers.begin(), m_lstEntityDrawManagers.end(), pIEntityDrawManager);
		if (m_lstEntityDrawManagers.end() != itor)
		{
			m_lstEntityDrawManagers.erase(itor);
			IComManager::GetInstance().WriteLogMsg("删除当前属性成功");
		}
	}

	// 获得索引
	int CViewManager::GetIndexEntityDrawManager(IEntityDrawManager* pIEntityDrawManager)
	{
		// 遍历所有的渲染属性
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

	// 通过索引获得渲染属性
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
