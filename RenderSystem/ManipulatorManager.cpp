#define OSGRENDER_PLUGIN_EXPORT
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/Viewpoint>
#include <osgViewer/View>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "RenderView.h"
#include "ManipulatorManager.h"

namespace VR_Soft
{
	CManipulatorManager::CManipulatorManager(CRenderView* pRenderView)
		:m_pRenderView(pRenderView)
	{
		m_pSwitchManipulator = new osgGA::KeySwitchMatrixManipulator;
		m_pRenderView->GetView()->setCameraManipulator(m_pSwitchManipulator);
		Init();
	}

	// 析构函数
	CManipulatorManager::~CManipulatorManager(void)
	{

	}

	// 设置操作器
	bool CManipulatorManager::SetCurrentManipulator(const VRString& strManipulator)
	{
		// 查找对于的操作器
		ListManipulators::const_iterator itor = m_lstManipulators.find(strManipulator);
		if (m_lstManipulators.end() != itor)
		{
			//m_pSwitchManipulator->selectMatrixManipulator(1);
			m_pRenderView->GetView()->setCameraManipulator(itor->second);
			return (true);
		}

		return (false);
	}

	// 添加操作器
	void CManipulatorManager::AddManipulator(const VRString& strManipulator, osgGA::CameraManipulator* pCmp,  bool bSelect )
	{
		// 查找对于的操作器
		ListManipulators::const_iterator itor = m_lstManipulators.find(strManipulator);
		if (m_lstManipulators.end() != itor)
		{
			return ;
		}

		// 		int nCount = m_pSwitchManipulator->getNumMatrixManipulators();
		// 		m_pSwitchManipulator->addMatrixManipulator(nCount, strManipulator, pCmp);
		m_lstManipulators[strManipulator] = pCmp;

		// 是否设置为选择项
		if (bSelect)
		{
			//m_pSwitchManipulator->selectMatrixManipulator(nCount);
			m_pRenderView->GetView()->setCameraManipulator(pCmp);
		}

	}

	// 获得操作器
	osgGA::CameraManipulator* CManipulatorManager::GetManipulator(const VRString& strManipulator) const
	{
		osgGA::CameraManipulator* pCmp = NULL;
		// 查找对于的操作器
		ListManipulators::const_iterator itor = m_lstManipulators.find(strManipulator);
		if (m_lstManipulators.end() != itor)
		{
			pCmp = itor->second;
			return pCmp;
		}

		return (NULL);
	}

	// 跟踪实体
	void CManipulatorManager::TrakerEntity(const uint64_t ID)
	{
		// 获得实体管理对象
		IEntityBase* pIEntityBase = IEntityManager::GetInstance().GetEntity(ID);
		if (NULL == pIEntityBase)
		{
			return;
		}

		TrakerEntity(pIEntityBase);

	}

	// 跟踪实体
	void CManipulatorManager::TrakerEntity( const IEntityBase* pIEntity )
	{
		ListManipulators::iterator itor = m_lstManipulators.find("MyEarthManipulator");
		if (m_lstManipulators.end() == itor)
		{
			return;
		}

		osgEarth::Util::EarthManipulator* pNodeTrackMp = dynamic_cast<osgEarth::Util::EarthManipulator*>(itor->second);
		if (NULL == pNodeTrackMp)
		{
			return;
		}

		// 获得渲染体
		IEntityDrawManager* pIEntityDrawManager = pIEntity->GetDrawManager();
		if (NULL == pIEntityDrawManager)
		{
			return;
		}

		DrawObj* pDrawObj = pIEntityDrawManager->GetRootDrawObj();

		// 计算包围球
		const osg::BoundingSphere& bs = pDrawObj->getBound();
		//pNodeTrackMp->setDistance(bs.radius() * 2); bs.radius() * 2
		pNodeTrackMp->setTetherNode(pDrawObj,5.0, osg::DegreesToRadians(60.0f), osg::PI_4,  5.5);
		//pNodeTrackMp->getSettings()->setArcViewpointTransitions( false );
		////pNodeTrackMp->setViewpoint(osgEarth::Viewpoint(osg::Vec3d(0,0,0), 90, -12, 600),5);
		//pNodeTrackMp->getSettings()->setArcViewpointTransitions( true );
		//pNodeTrackMp->getSettings()->setTetherMode(osgEarth::Util::EarthManipulator::TETHER_CENTER);

		// 设置跟踪距离

		//	m_pRenderView->GetView()->setCameraManipulator(pNodeTrackMp);

	}

	// 初始化
	void CManipulatorManager::Init(void)
	{
		// 创建地球操作器
		osgEarth::Util::EarthManipulator* pEmp = new osgEarth::Util::EarthManipulator;
		AddManipulator("EarthManipulator", pEmp);
		osgGA::NodeTrackerManipulator* pNodeTrack = new osgGA::NodeTrackerManipulator;
		AddManipulator("NodeTracker", pNodeTrack);
		osgGA::NodeTrackerManipulator::TrackerMode trackerMode = osgGA::NodeTrackerManipulator::NODE_CENTER;
		osgGA::NodeTrackerManipulator::RotationMode rotationMode = osgGA::NodeTrackerManipulator::TRACKBALL;
		pNodeTrack->setTrackerMode(trackerMode);
		pNodeTrack->setRotationMode(rotationMode);
	}

}