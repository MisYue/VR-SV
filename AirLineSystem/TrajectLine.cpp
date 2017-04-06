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

	// ��ʼ��
	void CTrajectLine::Init(void)
	{
		// ���ÿɱ༭״̬
//		((CAirLineSystem*)(IAirLineManager::GetInstancePtr()))->SetEditAriLine(this);
	}

	// ��õ�������
	const ITrajectory::ListTrajectoryInfo& CTrajectLine::GetTrajectoryPoint(void) const
	{
		return (m_listTrajectroryPoint);
	}

	// �����㷨
	void CTrajectLine::AlgorithmTrajectoryPoint(void)
	{

	}

	// ���õ�������
	void CTrajectLine::SetTrajectoryEntity(IEntityBase* pITrajectoryEntity)
	{
		m_pIEntityBase = pITrajectoryEntity;
	}

	// �����Ⱦ�ڵ�
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

	// �����Ⱦ�ڵ�
	//osg::Node* CTrajectLine::GetDrawObj(void)
	//{
	//	/*m_pLineString = new osgEarth::Symbology::LineString;
	//	osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(m_pLineString, pMapNode->getMapSRS());
	//	m_pFeatureNode = new osgEarth::Annotation::FeatureNode(pMapNode, pFeature);*/
	//	return (m);
	//}

	// �������
	/*const VRString CTrajectLine::GetEntityType(void) const
	{
		return ("AirLine");
	}*/

	// �������Զ���
	/*IAttribute* CTrajectLine::CreateAttribute(void)
	{
		return (new CAirLineAttribute(this, "AirLine"));
	}*/

	// ��ӵ�
	void CTrajectLine::AddAirLinePoint(const TrajectoryInfo& airLinePoint)
	{
		VR_MUTEX_AUTO;

		// �Ƿ����༭״̬
		if (!m_bEidt)
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("��ǰ���ߴ��ڹرձ༭״̬", ERROR_NOT_EIDT);
			return;
		}

		// ��Ӻ���
//		m_lstAirPoint.push_back(airLinePoint);

		m_listTrajectroryPoint.push_back(airLinePoint);

		// ����ʾ ����Ҫ������ʾ
		if (NULL == m_pLineString)
		{
			return;
		}
		// ������Ϻ���
		//m_pLineString->push_back(airLinePoint.GetPoint() );
		//m_pFeatureNode->init();     
	}

	// �Ƴ���
	void CTrajectLine::RemoveAirLinePoint(const int index)
	{
		VR_MUTEX_AUTO;

		//// �Ƿ����༭״̬
		//if (!m_bEidt)
		//{
		//	// д����־
		//	IComManager::GetInstance().WriteLogMsg("��ǰ���ߴ��ڹرձ༭״̬", ERROR_NOT_EIDT);
		//	return;
		//}

		//// �ж��Ƿ񳬹�ֵ
		//if ((int)m_lstAirPoint.size() <= index)
		//{
		//	return;
		//}

		//// �Ƴ���
		//LstAirLinePoint::iterator itor = m_lstAirPoint.begin();
		//int i = 0;
		//for (; m_lstAirPoint.end() != itor, i < index; ++i, ++itor);

		//if (i == index)
		//{
		//	m_lstAirPoint.erase(itor);
		//}
	}

	//����㵽�ļ���
	void CTrajectLine::Save(const VRString& strFile) const
	{
		//std::ofstream of(strFile, )
	}

	// �༭״̬����
	void CTrajectLine::EnableEidt(bool bEidt)
	{
		m_bEidt = bEidt;
	}

	// ��ñ༭״̬
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
