#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "OsgEarth2D.h"
#include "SynchroMainpulator2D.h"
#include "SynchroManipManager.h"


#include <osgDB/ReadFile>
#include <osgEarth/MapNode>
#include <osgEarth/Map>
#include <osgEarthUtil/EarthManipulator>
#include <osgViewer/View>

namespace VR_Soft
{
	COsgEarth2D::COsgEarth2D()
	{
		
	}


	COsgEarth2D::~COsgEarth2D(void)
	{
	}

	// �����ͼ
	void COsgEarth2D::Attach( IRenderView* pIRenderView )
	{
		// ���ò�����
		//IManipulatorManager* pIManip = pIRenderView->GetManipulatorManager();
		//osgEarth::Util::EarthManipulator* p2DEarthManipulator = new osgEarth::Util::EarthManipulator;
		//pIRenderView->GetView()->setCameraManipulator(p2DEarthManipulator);
		////MyManipulator* pMyManipulator = new MyManipulator(pIRenderView->getCamera(), pCmic, m_pEarth);
		//pIManip->AddManipulator("2DEarthManipulator", p2DEarthManipulator, false);

	/*	CSynchroMainpultor2D* pMainp2D = new CSynchroMainpultor2D;
		pIRenderView->GetView()->setCameraManipulator(pMainp2D);
		CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
		pSynchroManip->Add(pMainp2D);
//		CSynchroManipManager::GetInstance().Add(pMainp2D);
		COsgEarth::Attach(pIRenderView);
	*/

		GetRoot()->addChild(GetEarthMap());

		COsgEarth::Attach(pIRenderView);

		// ��Ӳ�����
		//		CC3DEarthManipulator* p3DEarthManip = new CC3DEarthManipulator;
		CSynchroMainpultor2D* p3DEarthManip = new CSynchroMainpultor2D;
		CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
		pSynchroManip->Add(p3DEarthManip);
		//		CSynchroManipManager::GetInstance().Add(p3DEarthManip);
		pIRenderView->GetView()->setCameraManipulator(p3DEarthManip);
	}

	// ���õ�������
	osgEarth::MapNode* COsgEarth2D::InitMapNode( osgEarth::MapNode* pNodeMap )
	{
		if (NULL == pNodeMap)
		{
			return (NULL);
		}
		
		// ���ͶӰ��ʽ
		 bool bGeocentric = pNodeMap->isGeocentric();
		if (bGeocentric)
		{
			osgEarth::MapOptions mapOptions;
			mapOptions.coordSysType() = osgEarth::MapOptions::CSTYPE_PROJECTED;
			osgEarth::Map* pMap = new osgEarth::Map(mapOptions);
			pMap->setLayersFromMap(pNodeMap->getMap());
			m_pMapNode = new osgEarth::MapNode(pMap);
		}
		else
		{
			m_pMapNode = pNodeMap;
		}
		

		// �Ƴ����еĸ߳�ͼ��
		osgEarth::ElevationLayerVector ElevationLayerVector;
		m_pMapNode->getMap()->getElevationLayers(ElevationLayerVector);

		osgEarth::Map* pMap = m_pMapNode->getMap();

		for (osgEarth::ElevationLayerVector::iterator itor = ElevationLayerVector.begin(); ElevationLayerVector.end() != itor; ++itor)
		{
			pMap->removeElevationLayer(*itor);
		}

		return (COsgEarth::InitMapNode(m_pMapNode));
	}

	// ���ʵ��
	void COsgEarth2D::AddEntity( IEntityBase* pIEntity )
	{
		// �����Ⱦ����
		IEntityDrawManager* pIDaramManager = pIEntity->GetDrawManager();
		if (NULL == pIDaramManager)
		{
			IComManager::GetInstance().WriteLogMsg("��ȡ��Ⱦ��ʧ�ܣ�AddEntity", ERROR_NOT_FIND);
			return;
		}

		// ��������
		pIDaramManager->SetMapNode2D(GetEarthMap());
		// ��ö�ά��Ⱦ��
		DrawObj* pDrawObj = pIDaramManager->GetDrawObj2D();
		GetRoot()->addChild(pDrawObj);
	}

	// ��Ӽ�����Ⱦ��
	void COsgEarth2D::AddFeatureGeomtry( const IFeatureGeomtry* pIFeatureGoemtry )
	{
		IFeatureGeomtry* pINoConst = const_cast<IFeatureGeomtry*>(pIFeatureGoemtry);
		pINoConst->SetMapNode2D(GetEarthMap());
		GetRoot()->addChild(pIFeatureGoemtry->GetDrawObj2D());
	}

}
