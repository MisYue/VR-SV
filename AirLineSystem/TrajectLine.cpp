#define VRSOFT_PLUGIN_EXPORT

#include <vector>
#include <fstream>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthFeatures/Feature>
#include <osgEarthSymbology/Geometry>

#include "../../Public/VRSoft.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "AirLineAttribute.h"
#include "AirLineSystem.h"
#include "TrajectLine.h"

namespace VR_Soft
{
	CTrajectLine::CTrajectLine(void)
		:m_bEidt(true),m_pFeatureNode(NULL), \
		m_pFeature(NULL), m_pLineString(NULL)
	{
	}

	CTrajectLine::~CTrajectLine(void)
	{
		
		/*VRSOFT_DELETE(m_pFeatureNode);
		VRSOFT_DELETE(m_pFeature);
		VRSOFT_DELETE(m_pLineString);*/
	}

	// 初始化
	void CTrajectLine::Init(void)
	{
		// 设置可编辑状态
//		((CAirLineSystem*)(IAirLineManager::GetInstancePtr()))->SetEditAriLine(this);
	}

	// 获得弹道数据
	const ITrajectory::ListTrajectoryInfo& CTrajectLine::GetTrajectoryPoint(void) const
	{
		return (m_listTrajectroryPoint);
	}

	// 弹道算法
	void CTrajectLine::AlgorithmTrajectoryPoint(void)
	{

	}

	// 设置弹道对象
	void CTrajectLine::SetTrajectoryEntity(IEntityBase* pITrajectoryEntity)
	{
		m_pIEntityBase = pITrajectoryEntity;
	}

	// 获得渲染节点
	/*osg::Node* CTrajectLine::GetDrawObj(osgEarth::MapNode* pMapNode)
	{
		m_pLineString = new osgEarth::Symbology::LineString;
		osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(m_pLineString, pMapNode->getMapSRS());
		m_pFeatureNode = new osgEarth::Annotation::FeatureNode(pMapNode, pFeature);

		osgEarth::Symbology::Style style = BuildStyle();

		m_pFeatureNode->setStyle(style);
		GetModelRoot()->addChild(m_pFeatureNode);
		return (GetModelRoot());
	}*/

	// 获得渲染节点
	//osg::Node* CTrajectLine::GetDrawObj(void)
	//{
	//	/*m_pLineString = new osgEarth::Symbology::LineString;
	//	osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(m_pLineString, pMapNode->getMapSRS());
	//	m_pFeatureNode = new osgEarth::Annotation::FeatureNode(pMapNode, pFeature);*/
	//	return (m);
	//}

	// 获得类型
	/*const VRString CTrajectLine::GetEntityType(void) const
	{
		return ("AirLine");
	}*/

	// 创建属性对象
	/*IAttribute* CTrajectLine::CreateAttribute(void)
	{
		return (new CAirLineAttribute(this, "AirLine"));
	}*/

	// 添加点
	void CTrajectLine::AddAirLinePoint(const TrajectoryInfo& airLinePoint)
	{
		VR_MUTEX_AUTO;

		// 是否开启编辑状态
		if (!m_bEidt)
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("当前航线处于关闭编辑状态", ERROR_NOT_EIDT);
			return;
		}

		// 添加航线
//		m_lstAirPoint.push_back(airLinePoint);

		m_listTrajectroryPoint.push_back(airLinePoint);

		// 不显示 则不需要进行显示
		if (NULL == m_pLineString)
		{
			return;
		}
		// 重新拟合航线
		//m_pLineString->push_back(airLinePoint.GetPoint() );
		//m_pFeatureNode->init();     
	}

	// 移除点
	void CTrajectLine::RemoveAirLinePoint(const int index)
	{
		VR_MUTEX_AUTO;

		//// 是否开启编辑状态
		//if (!m_bEidt)
		//{
		//	// 写入日志
		//	IComManager::GetInstance().WriteLogMsg("当前航线处于关闭编辑状态", ERROR_NOT_EIDT);
		//	return;
		//}

		//// 判断是否超过值
		//if ((int)m_lstAirPoint.size() <= index)
		//{
		//	return;
		//}

		//// 移除点
		//LstAirLinePoint::iterator itor = m_lstAirPoint.begin();
		//int i = 0;
		//for (; m_lstAirPoint.end() != itor, i < index; ++i, ++itor);

		//if (i == index)
		//{
		//	m_lstAirPoint.erase(itor);
		//}
	}

	//保存点到文件中
	void CTrajectLine::Save(const VRString& strFile) const
	{
		//std::ofstream of(strFile, )
	}

	// 编辑状态开关
	void CTrajectLine::EnableEidt(bool bEidt)
	{
		m_bEidt = bEidt;
	}

	// 获得编辑状态
	bool CTrajectLine::EidtState(void) const 
	{
		return (m_bEidt);
	}

	void CTrajectLine::InitStateMachine(IStateMachine* pIStateMachine)
	{

	}

	osgEarth::Symbology::Style CTrajectLine::BuildStyle(void)
	{
		osgEarth::Symbology::Style style;

		osgEarth::Symbology::LineSymbol* ls = style.getOrCreateSymbol<osgEarth::Symbology::LineSymbol>();
		ls->tessellation() = 10;

		osgEarth::Symbology::AltitudeSymbol* as = style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>();
		as->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
		as->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_SCENE;

		osgEarth::Symbology::RenderSymbol* rs = style.getOrCreateSymbol<osgEarth::Symbology::RenderSymbol>();
		rs->depthOffset()->enabled() = true;
		rs->depthOffset()->minBias() = 1;

		return style;    
	}

}
