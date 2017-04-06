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

	// 添加视图
	void COsgEarth2D::Attach( IRenderView* pIRenderView )
	{
		// 设置操作器
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

		// 添加操作器
		//		CC3DEarthManipulator* p3DEarthManip = new CC3DEarthManipulator;
		CSynchroMainpultor2D* p3DEarthManip = new CSynchroMainpultor2D;
		CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
		pSynchroManip->Add(p3DEarthManip);
		//		CSynchroManipManager::GetInstance().Add(p3DEarthManip);
		pIRenderView->GetView()->setCameraManipulator(p3DEarthManip);
	}

	// 配置地球数据
	osgEarth::MapNode* COsgEarth2D::InitMapNode( osgEarth::MapNode* pNodeMap )
	{
		if (NULL == pNodeMap)
		{
			return (NULL);
		}
		
		// 获得投影方式
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
		

		// 移除所有的高程图层
		osgEarth::ElevationLayerVector ElevationLayerVector;
		m_pMapNode->getMap()->getElevationLayers(ElevationLayerVector);

		osgEarth::Map* pMap = m_pMapNode->getMap();

		for (osgEarth::ElevationLayerVector::iterator itor = ElevationLayerVector.begin(); ElevationLayerVector.end() != itor; ++itor)
		{
			pMap->removeElevationLayer(*itor);
		}

		return (COsgEarth::InitMapNode(m_pMapNode));
	}

	// 添加实体
	void COsgEarth2D::AddEntity( IEntityBase* pIEntity )
	{
		// 获得渲染属性
		IEntityDrawManager* pIDaramManager = pIEntity->GetDrawManager();
		if (NULL == pIDaramManager)
		{
			IComManager::GetInstance().WriteLogMsg("获取渲染体失败，AddEntity", ERROR_NOT_FIND);
			return;
		}

		// 设置球体
		pIDaramManager->SetMapNode2D(GetEarthMap());
		// 获得二维渲染体
		DrawObj* pDrawObj = pIDaramManager->GetDrawObj2D();
		GetRoot()->addChild(pDrawObj);
	}

	// 添加几何渲染体
	void COsgEarth2D::AddFeatureGeomtry( const IFeatureGeomtry* pIFeatureGoemtry )
	{
		IFeatureGeomtry* pINoConst = const_cast<IFeatureGeomtry*>(pIFeatureGoemtry);
		pINoConst->SetMapNode2D(GetEarthMap());
		GetRoot()->addChild(pIFeatureGoemtry->GetDrawObj2D());
	}

}
