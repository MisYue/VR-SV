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

	// ��������
	CManipulatorManager::~CManipulatorManager(void)
	{

	}

	// ���ò�����
	bool CManipulatorManager::SetCurrentManipulator(const VRString& strManipulator)
	{
		// ���Ҷ��ڵĲ�����
		ListManipulators::const_iterator itor = m_lstManipulators.find(strManipulator);
		if (m_lstManipulators.end() != itor)
		{
			//m_pSwitchManipulator->selectMatrixManipulator(1);
			m_pRenderView->GetView()->setCameraManipulator(itor->second);
			return (true);
		}

		return (false);
	}

	// ��Ӳ�����
	void CManipulatorManager::AddManipulator(const VRString& strManipulator, osgGA::CameraManipulator* pCmp,  bool bSelect )
	{
		// ���Ҷ��ڵĲ�����
		ListManipulators::const_iterator itor = m_lstManipulators.find(strManipulator);
		if (m_lstManipulators.end() != itor)
		{
			return ;
		}

		// 		int nCount = m_pSwitchManipulator->getNumMatrixManipulators();
		// 		m_pSwitchManipulator->addMatrixManipulator(nCount, strManipulator, pCmp);
		m_lstManipulators[strManipulator] = pCmp;

		// �Ƿ�����Ϊѡ����
		if (bSelect)
		{
			//m_pSwitchManipulator->selectMatrixManipulator(nCount);
			m_pRenderView->GetView()->setCameraManipulator(pCmp);
		}

	}

	// ��ò�����
	osgGA::CameraManipulator* CManipulatorManager::GetManipulator(const VRString& strManipulator) const
	{
		osgGA::CameraManipulator* pCmp = NULL;
		// ���Ҷ��ڵĲ�����
		ListManipulators::const_iterator itor = m_lstManipulators.find(strManipulator);
		if (m_lstManipulators.end() != itor)
		{
			pCmp = itor->second;
			return pCmp;
		}

		return (NULL);
	}

	// ����ʵ��
	void CManipulatorManager::TrakerEntity(const uint64_t ID)
	{
		// ���ʵ��������
		IEntityBase* pIEntityBase = IEntityManager::GetInstance().GetEntity(ID);
		if (NULL == pIEntityBase)
		{
			return;
		}

		TrakerEntity(pIEntityBase);

	}

	// ����ʵ��
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

		// �����Ⱦ��
		IEntityDrawManager* pIEntityDrawManager = pIEntity->GetDrawManager();
		if (NULL == pIEntityDrawManager)
		{
			return;
		}

		DrawObj* pDrawObj = pIEntityDrawManager->GetRootDrawObj();

		// �����Χ��
		const osg::BoundingSphere& bs = pDrawObj->getBound();
		//pNodeTrackMp->setDistance(bs.radius() * 2); bs.radius() * 2
		pNodeTrackMp->setTetherNode(pDrawObj,5.0, osg::DegreesToRadians(60.0f), osg::PI_4,  5.5);
		//pNodeTrackMp->getSettings()->setArcViewpointTransitions( false );
		////pNodeTrackMp->setViewpoint(osgEarth::Viewpoint(osg::Vec3d(0,0,0), 90, -12, 600),5);
		//pNodeTrackMp->getSettings()->setArcViewpointTransitions( true );
		//pNodeTrackMp->getSettings()->setTetherMode(osgEarth::Util::EarthManipulator::TETHER_CENTER);

		// ���ø��پ���

		//	m_pRenderView->GetView()->setCameraManipulator(pNodeTrackMp);

	}

	// ��ʼ��
	void CManipulatorManager::Init(void)
	{
		// �������������
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