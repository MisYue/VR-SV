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
		// ��������
		SetName(strName);
	}

	CRenderSystem::~CRenderSystem()
	{
		/*m_renderThread.Join();
		((CViewManager*)m_pIViewManager)->RemoveAllView();*/
		// �ȴ���Ⱦ�߳̽���
		//while (!m_renderThread.IsEndTheard()) { };
		// ��ӽ������Թ�������
		IAttributeManager* pIAttributeManager = IAttributeManager::GetInstancePtr();
		if (NULL != pIAttributeManager)
		{
			IAttributeManager::GetInstance().RemoveFactory("��άģ������");
		}
		
		VRSOFT_DELETE(m_pDrawTrajectoryManager);
		VRSOFT_DELETE(m_pDrawAttributeFactory);
		VRSOFT_DELETE(m_pScreenHUDManager);
		VRSOFT_DELETE(m_pIViewManager);

		if (NULL != m_pRenderThread)
		{
			m_pRenderThread->Join();
			boost::this_thread::sleep(boost::posix_time::seconds(5));
			// �ȴ���Ⱦ�߳̽���
			while (!m_pRenderThread->IsEndTheard()) { };
		}
		
		VRSOFT_DELETE(m_pRenderThread);
	}

	// ��ȡ��������
	const VRString& CRenderSystem::GetTypeName(void) const
	{
		return (CRenderManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��ʼ��ϵͳ
	void CRenderSystem::Init(void)
	{
		// ������ͼ
		m_pIViewManager = new CViewManager;
		// д��ϵͳ��־
		IComManager::GetInstance().WriteLogMsg("�ɹ�������ͼ�������");

		// д��ϵͳ��־
		IComManager::GetInstance().WriteLogMsg("�ɹ������¼��б�");

		m_pScreenHUDManager = new CScreenHUDManager;
		// д��ϵͳ��־
		IComManager::GetInstance().WriteLogMsg("�ɹ�������Ļ���ڶ���"); 

		m_pDrawAttributeFactory = new CDrawAttributeFactory;

		// ʵ��ģ�͹�����
		m_pMeshManager = new CMeshManager;
		// ���������
		m_pDrawTrajectoryManager = new CDrawTrajectoryManager;

		// ע����άģ����Ⱦ����
		CMeshAttributeFactory* pDrawAttributeFactory = new CMeshAttributeFactory;
		// ��ӽ������Թ�������
		IAttributeManager::GetInstance().AddFactory(pDrawAttributeFactory);
	}

	// ��ȡ��ͼ������
	IViewManager* CRenderSystem::GetViewManager(void) const
	{
		return (m_pIViewManager);
	}

	// ��ѯ��ͼ����
	IRenderView* CRenderSystem::QuaryViewBayName(const VRString& strViewName) const
	{
		VR_MUTEX_AUTO;

		return (m_pIViewManager->GetRenderView(strViewName));
	}

	// ִ����Ⱦ
	void CRenderSystem::Render(void)
	{
		// ������Ⱦ
		//m_pIViewManager->Flush();
		if (NULL == m_pRenderThread)
		{
			m_pRenderThread = new CRenderThread;
		}
		m_pRenderThread->SetViewManager(m_pIViewManager);
		m_pRenderThread->Start();
	}

	// ע���¼�
	void CRenderSystem::RegisterEvnet(IEvent* pIEvent, const VRString& strViewName)
	{
		CEventList::GetInstance().RegisterEvent(pIEvent, strViewName);
	}

	// ��ע���¼�
	void CRenderSystem::UnRegisterEvnet(IEvent* pIEvent, const VRString& strViewName)
	{
		CEventList::GetInstance().UnRegisterEvent(pIEvent, strViewName);
	}

	// �����Ⱦ���Թ���
	IDrawAttributeFactory* CRenderSystem::GetDrawAttributeFactory(void) const
	{
		return (m_pDrawAttributeFactory);
	}

	// �����άʵ�������
	IMeshManager* CRenderSystem::GetMeshManager(void)
	{
		return (m_pMeshManager);
	}

	// ��ù켣������
	IDrawTrajectoryManager* CRenderSystem::GetTrajectoryManager(void)
	{
		return (m_pDrawTrajectoryManager);
	}

	// �����Ļ���ڹ������
	IScreenHUDManager* CRenderSystem::GetScreenManager( void ) const
	{
		return (m_pScreenHUDManager);
	}

}

