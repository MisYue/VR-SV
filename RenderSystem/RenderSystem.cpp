#define OSGRENDER_PLUGIN_EXPORT

#include <boost/thread/thread.hpp>
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "ViewManager.h"
#include "ScreenHUDManager.h"
#include "EventList.h"
#include "DrawAttributeFacoty.h"
#include "RenderSystem.h"

#include "MeshManager.h"
#include "DrawTrajectoryManager.h"
#include "DrawAttribute.h"


//#ifdef _DEBUG
//#pragma comment(lib, "osgd.lib")
//#pragma comment(lib, "osgViewerd.lib")
//#pragma comment(lib, "osgGAd.lib")
//#pragma comment(lib, "osgUtild.lib")
//#pragma comment(lib, "osgEarthUtild.lib")
//#else
//#pragma comment(lib, "osg.lib")
//#pragma comment(lib, "osgViewer.lib")
//#pragma comment(lib, "osgGA.lib")
//#pragma comment(lib, "osgUtil.lib")
//#pragma comment(lib, "osgEarthUtil.lib")
//#endif


#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgFXd.lib")
#pragma comment(lib, "osgEarthUtild.lib")
#pragma comment(lib, "osgTextd.lib")
#pragma comment(lib, "osgTerraind.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgEarthSymbologyd.lib")
#pragma comment(lib, "osgEarthAnnotationd.lib")
#else
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgViewer.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgDB.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgFX.lib")
#pragma comment(lib, "osgEarthUtil.lib")
#pragma comment(lib, "osgText.lib")
#pragma comment(lib, "osgTerrain.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgEarthSymbology.lib")
#pragma comment(lib, "osgEarthAnnotation.lib")
#endif // _DEBUG


namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CRenderManagerFactory::FACTORY_TYPE_NAME = RENDERSYSTEM_TYPENAME;
	///////////////////////////////////////////////

	CRenderSystem::CRenderSystem(const VRString& strName):m_pIViewManager(NULL), \
		m_pDrawAttributeFactory(NULL),m_pRenderThread(NULL)
	{
		// 设置名称
		SetName(strName);
	}

	CRenderSystem::~CRenderSystem()
	{
		/*m_renderThread.Join();
		((CViewManager*)m_pIViewManager)->RemoveAllView();*/
		// 等待渲染线程结束
		//while (!m_renderThread.IsEndTheard()) { };
		// 添加进入属性工厂管理
		IAttributeManager* pIAttributeManager = IAttributeManager::GetInstancePtr();
		if (NULL != pIAttributeManager)
		{
			IAttributeManager::GetInstance().RemoveFactory("三维模型属性");
		}
		
		VRSOFT_DELETE(m_pDrawTrajectoryManager);
		VRSOFT_DELETE(m_pDrawAttributeFactory);
		VRSOFT_DELETE(m_pScreenHUDManager);
		VRSOFT_DELETE(m_pIViewManager);

		if (NULL != m_pRenderThread)
		{
			m_pRenderThread->Join();
			boost::this_thread::sleep(boost::posix_time::seconds(5));
			// 等待渲染线程结束
			while (!m_pRenderThread->IsEndTheard()) { };
		}
		
		VRSOFT_DELETE(m_pRenderThread);
	}

	// 获取类型名称
	const VRString& CRenderSystem::GetTypeName(void) const
	{
		return (CRenderManagerFactory::FACTORY_TYPE_NAME);
	}

	// 初始化系统
	void CRenderSystem::Init(void)
	{
		// 创建视图
		m_pIViewManager = new CViewManager;
		// 写入系统日志
		IComManager::GetInstance().WriteLogMsg("成功创建视图管理对象");

		// 写入系统日志
		IComManager::GetInstance().WriteLogMsg("成功创建事件列表");

		m_pScreenHUDManager = new CScreenHUDManager;
		// 写入系统日志
		IComManager::GetInstance().WriteLogMsg("成功创建屏幕窗口对象"); 

		m_pDrawAttributeFactory = new CDrawAttributeFactory;

		// 实体模型管理类
		m_pMeshManager = new CMeshManager;
		// 轨道管理类
		m_pDrawTrajectoryManager = new CDrawTrajectoryManager;

		// 注册三维模型渲染属性
		CMeshAttributeFactory* pDrawAttributeFactory = new CMeshAttributeFactory;
		// 添加进入属性工厂管理
		IAttributeManager::GetInstance().AddFactory(pDrawAttributeFactory);
	}

	// 获取视图管理器
	IViewManager* CRenderSystem::GetViewManager(void) const
	{
		return (m_pIViewManager);
	}

	// 查询视图对象
	IRenderView* CRenderSystem::QuaryViewBayName(const VRString& strViewName) const
	{
		VR_MUTEX_AUTO;

		return (m_pIViewManager->GetRenderView(strViewName));
	}

	// 执行渲染
	void CRenderSystem::Render(void)
	{
		// 调用渲染
		//m_pIViewManager->Flush();
		if (NULL == m_pRenderThread)
		{
			m_pRenderThread = new CRenderThread;
		}
		m_pRenderThread->SetViewManager(m_pIViewManager);
		m_pRenderThread->Start();
	}

	// 注册事件
	void CRenderSystem::RegisterEvnet(IEvent* pIEvent, const VRString& strViewName)
	{
		CEventList::GetInstance().RegisterEvent(pIEvent, strViewName);
	}

	// 反注册事件
	void CRenderSystem::UnRegisterEvnet(IEvent* pIEvent, const VRString& strViewName)
	{
		CEventList::GetInstance().UnRegisterEvent(pIEvent, strViewName);
	}

	// 获得渲染属性工厂
	IDrawAttributeFactory* CRenderSystem::GetDrawAttributeFactory(void) const
	{
		return (m_pDrawAttributeFactory);
	}

	// 获得三维实体管理类
	IMeshManager* CRenderSystem::GetMeshManager(void)
	{
		return (m_pMeshManager);
	}

	// 获得轨迹管理类
	IDrawTrajectoryManager* CRenderSystem::GetTrajectoryManager(void)
	{
		return (m_pDrawTrajectoryManager);
	}

	// 获得屏幕窗口管理对象
	IScreenHUDManager* CRenderSystem::GetScreenManager( void ) const
	{
		return (m_pScreenHUDManager);
	}

}

