#include <osgDB/ReadFile>
#include <osgEarth/SpatialReference>
#include <osgEarth/MapNode>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Sky>
#include <osgEarth/GeoMath>
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/EarthSystem/ISolarConfig.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "SolarConfig.h"
#include "CameraInfo.h"
#include "NorthArrow.h"
#include "EarthSystem.h"
#include "OsgEarth2D.h"
#include "OsgEarth3D.h"
#include "EarthLayerManager.h"
#include "SynchroManipManager.h"
#include "FeatureManager.h"

#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgTextd.lib")
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "osgWidgetd.lib")
#pragma comment(lib, "osgFXd.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgEarthUtild.lib")
#pragma comment(lib, "osgEarthAnnotationd.lib")
#pragma comment(lib, "osgEarthSymbologyd.lib")
#pragma comment(lib, "osgEarthFeaturesd.lib")
#else
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgDB.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgText.lib")
#pragma comment(lib, "osgViewer.lib")
#pragma comment(lib, "osgWidget.lib")
#pragma comment(lib, "osgFX.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgEarthUtil.lib")
#pragma comment(lib, "osgEarthAnnotation.lib")
#pragma comment(lib, "osgEarthSymbology.lib")
#pragma comment(lib, "osgEarthFeatures.lib")
#endif 

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CEarthManagerFactory::FACTORY_TYPE_NAME = EARTHSYSTEM_TYPENAME;
	///////////////////////////////////////////////

	CEarthSystem::CEarthSystem(const VRString& strName)
		:m_pEarth(NULL),m_pOsgEarth2D(NULL), m_pOsgEarth3D(NULL), \
		m_pSynchroManipManager(NULL), m_pEarthLayerManager(NULL), m_pFeatureManager(NULL)
	{
		SetName(strName);
	}

	CEarthSystem::~CEarthSystem(void)
	{
		VRSOFT_DELETE(m_pEarth);
		VRSOFT_DELETE(m_pOsgEarth2D);
		VRSOFT_DELETE(m_pOsgEarth3D);
		VRSOFT_DELETE(m_pSynchroManipManager);
		VRSOFT_DELETE(m_pEarthLayerManager);
		VRSOFT_DELETE(m_pFeatureManager);
	}

	// ��ȡ��������
	const VRString& CEarthSystem::GetTypeName(void) const 
	{
		return CEarthManagerFactory::FACTORY_TYPE_NAME;
	}

	// ��������г�ʼ��
	void CEarthSystem::Init(void) 
	{
		const VRString strPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath();
		IConfigFile *pIConfigFile = CreateConfigFileInstance(strPath + "/Config/EarthSystem/earth.cfg");
		pIConfigFile->ReadConfig();
		m_strFilePath = pIConfigFile->GetItemValue("earth", "filePath");

		InitViewpoint(pIConfigFile, NULL);

		VRSOFT_DELETE(pIConfigFile);

		m_pSynchroManipManager = new CSynchroManipManager;
		m_pEarthLayerManager = new CEarthLayerManager;
		m_pFeatureManager = new CFeatureManager;
	}

	// ��ʼ������
	void CEarthSystem::RenderEarth( const IEarthManager::EARTH_TYPE earthType, IRenderView* pIRendView )
	{
		// ��õ�ͼ�Ľڵ�
		osgEarth::MapNode* pMapNode = NULL;

		// �ж��Ƿ���Ҫ���ⲿ�ļ���ȡ�����ļ�
		if ((NULL == m_pOsgEarth2D) && (NULL == m_pOsgEarth3D))
		{
			// ��ȡ��������
			osg::Node* pNode = osgDB::readNodeFile(m_strFilePath);
			if (NULL == pNode)
			{
				return;
			}

			// ��ȡ��ͼ�ڵ�
			pMapNode = osgEarth::MapNode::findMapNode(pNode);
		}
		else if (NULL != m_pOsgEarth2D)
		{
			pMapNode = m_pOsgEarth2D->GetEarthMap();
		}
		else if (NULL != m_pOsgEarth3D)
		{
			pMapNode = m_pOsgEarth3D->GetEarthMap();
		}


		switch(earthType)
		{
		case IEarthManager::EARTH_2D:
			{
				if (NULL == m_pOsgEarth2D)
				{
					m_pOsgEarth2D = CEarthFactory::CreateEarth2D(pMapNode); //new COsgEarth2D;
					m_pEarthLayerManager->SetEarthMap2D(m_pOsgEarth2D->GetEarthMap());
					//m_pOsgEarth2D->ReadEarthFile(m_strFilePath);
					//m_pEarthLayerManager->SetEarthMap2D(m_pOsgEarth2D->GetEarthMap()->getMap());
					//CConvert::m_pSpatial = const_cast<osgEarth::SpatialReference*>(m_pOsgEarth2D->GetEarthMap()->getMapSRS());
				}

				m_pOsgEarth2D->Attach(pIRendView);
			}
			break;

		case IEarthManager::EARTH_3D:
			{
				if (NULL == m_pOsgEarth3D)
				{
					m_pOsgEarth3D = CEarthFactory::CreateEarth3D(pMapNode); //  new COsgEarth3D;
					m_pEarthLayerManager->SetEarthMap3D(m_pOsgEarth3D->GetEarthMap());
					//m_pOsgEarth3D->ReadEarthFile(m_strFilePath);
					CConvert::m_pSpatial = const_cast<osgEarth::SpatialReference*>(m_pOsgEarth3D->GetEarthMap()->getMapSRS());
					//m_pEarthLayerManager->SetEarthMap(m_pOsgEarth3D->GetEarthMap()->getMap());
				}

				m_pOsgEarth3D->Attach(pIRendView);
			}
			break;

		default:
			return;
		}

		CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
		pSynchroManip->SetViewPoint(NULL, m_viewPoint, 5.0);
	}

	// ���ģ��
	void CEarthSystem::AddEntity(const IEntityBase* pIEntity)
	{
		IEntityBase* pIEntityBase = const_cast<IEntityBase*>(pIEntity);

		if (NULL != m_pOsgEarth2D)
		{
			m_pOsgEarth2D->AddEntity(pIEntityBase);
		}
		
		if (NULL != m_pOsgEarth3D)
		{
			m_pOsgEarth3D->AddEntity(pIEntityBase);
		}
		
		// �������Դ���
		IComManager::GetInstance().GetAttributeManager()->SetCurrentEntityBase(pIEntityBase);
	}

	// �����ʾ��
	void CEarthSystem::AddFeatureGeometry( const IFeatureGeomtry* pIFeatureGeomtry )
	{
		// ��ӵ����ֵ��򳡾���
		if (NULL != m_pOsgEarth2D)
		{
			m_pOsgEarth2D->AddFeatureGeomtry(pIFeatureGeomtry);
		}
		if (NULL != m_pOsgEarth3D)
		{
			m_pOsgEarth3D->AddFeatureGeomtry(pIFeatureGeomtry);
		}
		
	}

	// ���ͬ��������
	ISynchroManIpManager* CEarthSystem::GetSynchroManIpManager( void ) const
	{
		return (m_pSynchroManipManager);
	}

	// ��ʼ���ӵ�
	void CEarthSystem::InitViewpoint( IConfigFile *pIConfigFile, osgEarth::Util::EarthManipulator* pMp )
	{
		double dLong = CVRStringUtil::StringToNumber<double>(pIConfigFile->GetItemValue("Viewpoint", "longitude"));
		double dLat = CVRStringUtil::StringToNumber<double>(pIConfigFile->GetItemValue("Viewpoint", "latitude"));
		double dAlt = CVRStringUtil::StringToNumber<double>(pIConfigFile->GetItemValue("Viewpoint", "altitude"));
		double dHeading = CVRStringUtil::StringToNumber<double>(pIConfigFile->GetItemValue("Viewpoint", "heading"));
		double dPitch = CVRStringUtil::StringToNumber<double>(pIConfigFile->GetItemValue("Viewpoint", "pitch"));
		double dRange = CVRStringUtil::StringToNumber<double>(pIConfigFile->GetItemValue("Viewpoint", "range"));

		m_viewPoint = osgEarth::Viewpoint("Home", dLong, dLat, dAlt, dHeading, dPitch, dRange);
	}

	// ���ͨ��λ�þ�γ�߶�
	osg::Vec3d CEarthSystem::GetLongLatHightByPoint( float x, float y, double& lat, double& lon, double& height, \
		const VRString& strViewName /*= "mainView"*/ )
	{
		osgEarth::MapNode* pMapNode = NULL;
		IRenderView* pIRenderViewe = NULL;
		
		if ((NULL != m_pOsgEarth2D) && (0 == strViewName.compare(m_pOsgEarth2D->GetRenderName())))
		{
			pMapNode = m_pOsgEarth2D->GetEarthMap();
			pIRenderViewe = m_pOsgEarth2D->GetRenderView();
		}
		else if ((NULL != m_pOsgEarth3D) && (0 == strViewName.compare(m_pOsgEarth3D->GetRenderName())))
		{
			pMapNode = m_pOsgEarth3D->GetEarthMap();
			pIRenderViewe = m_pOsgEarth3D->GetRenderView();
		}

		if (NULL == pIRenderViewe || NULL == pMapNode)
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("��ȡ��ͼ"+strViewName+"ʧ��", ERROR_NOT_FIND);
			return (osg::Vec3d(0, 0, 0));
		}

		osg::Vec3d ptWorld = osg::Vec3d(-1.0, -1.0, -1.0);
		bool bSucces = pMapNode->getTerrain()->getWorldCoordsUnderMouse(pIRenderViewe->GetView(), x, y, ptWorld);
		// ��þ�γ�߶�
		if (!bSucces)
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("��ȡ��ͼ��γ�߶�ʧ��", ERROR_NOT_LONGlAT);			
		}

		// �����þ�γ�߶�
		osg::Vec3d vGeo;
		CConvert::WordToLatLongHeight(ptWorld, vGeo);
		osgEarth::GeoPoint geoPoint;
		geoPoint.fromWorld(pMapNode->getMapSRS(), ptWorld);
		lat = geoPoint.x();
		lon = geoPoint.y();
		height = geoPoint.z();

		return (ptWorld);
	}

	// ���ͼ����� 
	IEarthLayerManager* CEarthSystem::GetEarthLayerManager( void ) const
	{
		return (m_pEarthLayerManager);
	}

	// ���������߿���
	void CEarthSystem::SetGraticuleState( bool bShow )
	{
		if (NULL != m_pOsgEarth2D)
		{
			m_pOsgEarth2D->SetGraticuleState(bShow);
		}

		if (NULL != m_pOsgEarth3D)
		{
			m_pOsgEarth3D->SetGraticuleState(bShow);
		}
	}

	// ��������߿���
	bool CEarthSystem::GetGraticuleState( void ) const
	{
		if (NULL != m_pOsgEarth2D)
		{
			return (m_pOsgEarth2D->GetGraticuleState());
		}

		if (NULL != m_pOsgEarth3D)
		{
			return (m_pOsgEarth3D->GetGraticuleState());
		}
		 return (false);
	}

	// ����
	double CEarthSystem::Distance( const std::vector<osg::Vec3d>& listPoints ) const
	{
		return (osgEarth::GeoMath::rhumbDistance(listPoints));
	}

	// ���㿪��
	void CEarthSystem::DistanceEnable( bool bEnable )
	{
		((COsgEarth3D*)m_pOsgEarth3D)->DistanceEnable(bEnable);
	}

	// ������㹦�ܿ���
	bool CEarthSystem::GetDistanceEnable( void ) const
	{
		return (((COsgEarth3D*)m_pOsgEarth3D)->GetDistanceEnable());
	}

	// ���ʸ������
	IFeatureManager* CEarthSystem::GetEarthFeatureManager( void ) const
	{
		return (m_pFeatureManager);
	}

	// ��õ���
	IEarth* CEarthSystem::GetEarth( EARTH_TYPE et )
	{
		if (et == IEarthManager::EARTH_2D)
		{
			return (m_pOsgEarth2D);
		}
		else if (IEarthManager::EARTH_3D == et)
		{
			return (m_pOsgEarth3D);
		}

		return (m_pOsgEarth3D);
	}

}
