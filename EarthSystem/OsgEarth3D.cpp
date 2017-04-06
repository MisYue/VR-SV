#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "OsgEarth3D.h"
#include "CameraInfo.h"
#include "NorthArrow.h"
#include "EarthManipulator3D.h"
#include "SynchroManipManager.h"
#include "OceanEarth/OceanEarth.h"
#include "EarthUtil.h"

#include <osgEarthUtil/Sky>
#include <osgViewer/View>
#include <osgEarth/Registry>
#include <osgEarth/Terrain>
#include <osgEarth/TerrainEngineNode>
#include <osgEarth/ElevationQuery>
#include <osgEarthUtil/LatLongFormatter>
#include <osgEarthUtil/FeatureQueryTool>

namespace VR_Soft
{
	COsgEarth3D::COsgEarth3D(void)
		:COsgEarth(),m_pMeasureToolHandler(NULL),m_pView(NULL),m_pCanvas(NULL) \
		,m_bDistanceEnable(false)
	{
		
	}


	COsgEarth3D::~COsgEarth3D(void)
	{
	}

	// �����ͼ
	void COsgEarth3D::Attach( IRenderView* pIRenderView )
	{
		osgViewer::View* pIView = pIRenderView->GetView();
		if (m_pSkyNode.valid())
		{
			m_pSkyNode->attach( pIView, 0 );
		}

		osgEarth::Util::AutoClipPlaneCullCallback* pAutoClipPlaneCull = new osgEarth::Util::AutoClipPlaneCullCallback(GetEarthMap());
		pAutoClipPlaneCull->setHeightThreshold(20);
		pAutoClipPlaneCull->setMinNearFarRatio(0.0002);
		pAutoClipPlaneCull->setMaxNearFarRatio(0.0002);
		pIView->getCamera()->addCullCallback(pAutoClipPlaneCull);
	//	pIView->addEventHandler(new );
		

		COsgEarth::Attach(pIRenderView);

		// ��Ӳ�����
		CEarthManipulator3D* p3DEarthManip = new CEarthManipulator3D;
		CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
		pSynchroManip->Add(p3DEarthManip);
		pIRenderView->GetView()->setCameraManipulator(p3DEarthManip);
		p3DEarthManip->SetEarthMapNode(GetEarthMap());

		// ���ָ����
		AddNorthArrow(p3DEarthManip, pIRenderView);


		// ��ʼ�����
		InitEarthTool(pIRenderView);
	}

	// ����ǿ���պ���
	void COsgEarth3D::AddSkyBox(osgEarth::MapNode* pMapNode )
	{
		const osgEarth::Config& externals = pMapNode->externalConfig();

		const osgEarth::Config& skyConf         = externals.child("sky");
		osgEarth::Util::SkyOptions options(skyConf);
		if ( options.getDriver().empty() )
		{
			if ( pMapNode->getMapSRS()->isGeographic() )
				options.setDriver("simple");
			else
				options.setDriver("gl");
		}


		m_pSkyNode = osgEarth::Util::SkyNode::create(options, pMapNode);
		if ( !m_pSkyNode.valid() )
		{
			return;
		}

		m_pSkyNode->setMinimumAmbient(osg::Vec4(0.5,0.5,0.5, .50));
		if ( pMapNode->getNumParents() > 0 )
		{
			osgEarth::insertGroup(m_pSkyNode, pMapNode->getParent(0));
		}
		else
		{
			m_pSkyNode->addChild( pMapNode );
			GetRoot()->addChild(m_pSkyNode);
		}
	}

	// ���ָ����
	void COsgEarth3D::AddNorthArrow(CSynchroManipulator* pSynchroManip, IRenderView* pIView )
	{
		osg::Group* pGroup = new osg::Group;
		pGroup->setDataVariance(osg::Object::DYNAMIC);

		osgViewer::View* pView = pIView->GetView();
		osg::Viewport* vp = pView->getCamera()->getViewport();
		CameraInfoCallback* pCmic = new CameraInfoCallback(pGroup, 720, 690/*1020, 1080*/);
		pGroup->setUpdateCallback(pCmic);
		GetRoot()->addChild(pGroup);

		// ���ò�����
		

// 		IManipulatorManager* pIManip = pIView->GetManipulatorManager();
// 		/*MyManipulator* pMyManipulator = new MyManipulator(pView->getCamera(), pCmic, m_pRoot);
// 		pIManip->AddManipulator("MyEarthManipulator", pMyManipulator, true);*/
// 		pIManip->AddManipulator("MyEarthManipulator", new osgEarth::Util::EarthManipulator, true);

		// ��ʼ���ӵ�
		//	InitViewpoint(pIConfigFile, pMyManipulator);

		CNorthArrow* m_pNorthArrow = new CNorthArrow(pSynchroManip, pGroup, pView, pCmic, 0, 0);
	}

	// ���ʵ��
	void COsgEarth3D::AddEntity( IEntityBase* pIEntity )
	{
		// �����Ⱦ����
		IEntityDrawManager* pIDaramManager = pIEntity->GetDrawManager();
		if (NULL == pIDaramManager)
		{
			IComManager::GetInstance().WriteLogMsg("��ȡ��Ⱦ��ʧ�ܣ�AddEntity", ERROR_NOT_FIND);
			return;
		}

		// ���õ�ͼ�ڵ�
		pIDaramManager->SetMapNode3D(GetEarthMap());
		// ��ö�ά��Ⱦ��
		DrawObj* pDrawObj = pIDaramManager->GetDrawObj();
		GetRoot()->addChild(pDrawObj);
	}

	// ��Ӽ�����
	void COsgEarth3D::AddFeatureGeomtry( const IFeatureGeomtry* pIFeatureGoemtry )
	{
		IFeatureGeomtry* pINoConst = const_cast<IFeatureGeomtry*>(pIFeatureGoemtry);
		pINoConst->SetMapNode3D(GetEarthMap());
		GetRoot()->addChild(pIFeatureGoemtry->GetDrawObj3D());
	}

	// ��ʼ��������ع���
	void COsgEarth3D::InitEarthTool(IRenderView* pIRenderView)
	{
		m_pMeasureToolHandler = new CMeasureToolHandler(GetRoot(), GetEarthMap()); //osgEarth::Util::MeasureToolHandler(GetRoot(), GetEarthMap());
		m_pMeasureToolHandler->setIntersectionMask( 0x00 );
		GetEarthMap()->setNodeMask(0x01);
		m_pMeasureToolHandler->setIsPath(true);
		m_pMeasureToolHandler->setGeoInterpolation(osgEarth::GEOINTERP_GREAT_CIRCLE);

		osgEarth::Symbology::Style style = m_pMeasureToolHandler->getLineStyle();
		style.getOrCreate<osgEarth::Symbology::LineSymbol>()->stroke()->color() = osgEarth::Symbology::Color::Red;
		style.getOrCreate<osgEarth::Symbology::LineSymbol>()->stroke()->width() = 4.0f;
		style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
		m_pMeasureToolHandler->setLineStyle(style);

		m_pView = pIRenderView->GetView();
		m_pView->addEventHandler(m_pMeasureToolHandler);
		m_pCanvas = new osgEarth::Util::Controls::ControlCanvas();
		GetRoot()->addChild( m_pCanvas );
		m_pCanvas->setNodeMask( 0x00 );

		osgEarth::Util::Controls::Grid* grid = new osgEarth::Util::Controls::Grid();
		grid->setBackColor(0,0,0,0.5);
		grid->setMargin( 10 );
		grid->setPadding( 10 );
		grid->setChildSpacing( 10 );
		grid->setChildVertAlign( osgEarth::Util::Controls::Control::ALIGN_CENTER );
		grid->setAbsorbEvents( true );
		grid->setVertAlign( osgEarth::Util::Controls::Control::ALIGN_BOTTOM );    

		m_pCanvas->addControl( grid );
		osgEarth::Util::Controls::LabelControl* pLabelControl = new osgEarth::Util::Controls::LabelControl();
		pLabelControl->setEncoding(osgText::String::ENCODING_UTF8);
		pLabelControl->setText(CVRStringUtil::GB2312ToUTF8("����"));
		grid->setControl( 0, 0, pLabelControl );
		osgEarth::Util::Controls::LabelControl* label = new osgEarth::Util::Controls::LabelControl();
		label->setFont( osgEarth::Registry::instance()->getDefaultFont() );
		label->setFontSize( 24.0f );
		label->setHorizAlign( osgEarth::Util::Controls::Control::ALIGN_LEFT );    
		label->setText("");
		grid->setControl( 1, 0, label );

		m_pMeasureToolHandler->addEventHandler( new CMeasureToolCallback(label) );

		// ���ʸ���༭��������ʾ
		{
			using namespace osgEarth::Util::Controls;
			ControlCanvas* canvas = new osgEarth::Util::Controls::ControlCanvas();
			GetRoot()->addChild( canvas );
			//m_pCanvas->setNodeMask( 0x00 );

			// ���ʸ��ѡ����
			osgEarth::Util::FeatureQueryTool* pFeatureQueryTool = new osgEarth::Util::FeatureQueryTool;
			pIRenderView->GetView()->addEventHandler(pFeatureQueryTool);
			pFeatureQueryTool->addChild(GetEarthMap());
			pFeatureQueryTool->setDefaultCallback(new CFeatureQuery(canvas));
		}
	}

	// ���㿪��
	void COsgEarth3D::DistanceEnable( bool bEnable )
	{
		if (bEnable)
		{
			m_pMeasureToolHandler->setIntersectionMask(0x01);
			m_pCanvas->setNodeMask(0x01);
		}
		else
		{
			m_pMeasureToolHandler->clear();
		//	m_pMeasureToolHandler->
			m_pMeasureToolHandler->setIntersectionMask(0x00);
			m_pCanvas->setNodeMask(0x00);
		}

		m_bDistanceEnable = bEnable;
	}

	// ������㹦�ܿ���
	bool COsgEarth3D::GetDistanceEnable() const
	{
		return (m_bDistanceEnable);
	}

	// ���õ�������
	osgEarth::MapNode* COsgEarth3D::InitMapNode( osgEarth::MapNode* pNodeMap )
	{
		if (NULL == pNodeMap)
		{
			return (NULL);
		}

		// ���ͶӰ��ʽ
		bool bGeocentric = pNodeMap->isGeocentric();
		if (bGeocentric)
		{
			m_pMapNode = pNodeMap;
		}
		else
		{
			osgEarth::MapOptions mapOptions;
			mapOptions.coordSysType() = osgEarth::MapOptions::CSTYPE_GEOCENTRIC;
			osgEarth::Map* pMap = new osgEarth::Map(mapOptions);
			pMap->setLayersFromMap(pNodeMap->getMap());
			m_pMapNode = new osgEarth::MapNode(pMap);
		}

		// ����ǿ���պ���
		AddSkyBox(m_pMapNode);

		// ��ʼ������
		{
			/*	COceanEarth *ocean = new COceanEarth(pNodeMap);
			m_pSkyNode->addChild(ocean);*/
		}
		

		return (COsgEarth::InitMapNode(m_pMapNode));
	}

}

