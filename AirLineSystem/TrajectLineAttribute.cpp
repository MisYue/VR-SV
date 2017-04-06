#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "TrajectLineAttribute.h"
#include <osg/Geode>
#include <osg/Geometry>

namespace VR_Soft
{
	// ���캯��
/*	CTrajectLineAttribute::CTrajectLineAttribute(IEntityBase* pIEntityBase)
		:CAttributeImp<IPathAttribute>(pIEntityBase, "·������"),m_bEdit(true), m_bLight(false),m_bShow(true)
	{
		//m_pGeode = new osg::Geode;
	}

	// ��������
	CTrajectLineAttribute::~CTrajectLineAttribute(void)
	{
	}

	// ��ʼ��
	void CTrajectLineAttribute::Init()
	{
// 		DEFINITION_PROPERTY(Edit, &CTrajectLineAttribute::SetEnableEdit, &CTrajectLineAttribute::GetEnableEdit, "�༭", "", "", CTRL_COMBOX);
// 		ADDENUM_PROPERTY(Edit, "TRUE", true);
// 		ADDENUM_PROPERTY(Edit, "FALSE", false);
// 
// 		DEFINITION_PROPERTY(Light, &CTrajectLineAttribute::SetEnableLight, &CTrajectLineAttribute::GetLight, "����", "", "", CTRL_COMBOX);
// 		ADDENUM_PROPERTY(Light, "TRUE", true);
// 		ADDENUM_PROPERTY(Light, "FALSE", false);
// 
// 		DEFINITION_PROPERTY(Show, &CTrajectLineAttribute::SetShowSate, &CTrajectLineAttribute::GetShowSate, "����", "", "", CTRL_COMBOX);
// 		ADDENUM_PROPERTY(Show, "��ʾ", true);
// 		ADDENUM_PROPERTY(Show, "����", false);

		m_listPoints.clear();
		InitDrawable();
	}

	// �Ƿ�༭
	void CTrajectLineAttribute::SetEnableEdit(const bool bEdit)
	{
		m_bEdit = bEdit;
	}

	// ����Ƿ�༭
	bool CTrajectLineAttribute::GetEnableEdit(void) const
	{
		return (m_bEdit);
	}

	// ����
	void CTrajectLineAttribute::Update( void )
	{
		// ��ø��¶���

		ISimManager::SimCmd simCmd = ISimManager::GetInstance().GetSimCmd();
		if (ISimManager::Pause !=  simCmd && ISimManager::Stop != simCmd )
		{
			//			SimRun(dt);
			return;
		}

		if (IEvent::GetInstance().GetMouseButton(MS_RIGHT))
		{
			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
			// ��õ�
			IEarthManager*  pIEarthManager = CComManagerImp::GetComponent<IEarthManager>(INSTANCE_NAME_EARTHSYSTEM);
			if (NULL == pIEarthManager)
			{
				return;
			}

			double dLat = 0.0, dLon = 0.0, dHeight = 0.0;
			pIEarthManager->GetEarth()->GetLongLatHightByPoint(v.x(), v.y(), dLat, dLon, dHeight);
			dHeight += 10000;

			// ��ӵ���
			AddKeyPoint(osg::Vec3d(dLat, dLon, dHeight));

			UpdateDrawable();
		}
	}

	// �����Ⱦ��
	DrawObj* CTrajectLineAttribute::GetDrawObj( void )
	{
		return (m_pGeode);
	}

	// ��ȡ����״̬
	bool CTrajectLineAttribute::GetLight( void ) const
	{
		return (m_bLight);
	}

	// ���ù���״̬
	void CTrajectLineAttribute::SetEnableLight( bool bLight )
	{
		m_bLight = bLight;
		if (m_bLight)
		{
			m_pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		}
		else
		{
			m_pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		}
	}
	// ���һ�������������
	void CTrajectLineAttribute::AddKeyPoint( const osg::Vec3d& vPos )
	{
		m_listPoints.push_back(vPos);

		// ת������������
		osg::Vec3d vWord;
		CConvert::LatLongHeightToWord(vPos, vWord);
		m_listDrawPoints.push_back(vWord);
	}

	// �Ƴ�һ����
	void CTrajectLineAttribute::RemoveKeyPoint( const int index )
	{
		if (index < 0 || index > (int)m_listPoints.size())
		{
			ILogManager::GetInstance().SetLogMessage("�Ƴ���λ����Ч", ERROR_NOT_FIND);
			return;
		}

// 		ListPoints::iterator itor = m_listPoints.begin();
// 		for (int i = 0; i < index; ++i)
// 		{
// 			++itor;
// 		}
// 
// 		m_listPoints.erase(itor);

	}

	// ���ĵ�
	void CTrajectLineAttribute::ChangeKeyPoint( const int index, const osg::Vec3d& vPos )
	{
		if (index < 0 || index > (int)m_listPoints.size())
		{
			ILogManager::GetInstance().SetLogMessage("�Ƴ���λ����Ч", ERROR_NOT_FIND);
			return;
		}

		m_listPoints[index] = vPos;
	}

	// ��ʼ��������
	void CTrajectLineAttribute::InitDrawable( void )
	{
		m_pGeode = new osg::Geode;

		m_pLineGeometry = new osg::Geometry;
		m_pGeode->addDrawable(m_pLineGeometry);

		osg::Vec4Array* pColorArray = new osg::Vec4Array;
		pColorArray->push_back(osg::Vec4(1, 0, 0, 1));

		m_pLineGeometry->setColorArray(pColorArray);

		m_pLineGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP));
	}

	// ������Ⱦ��
	void CTrajectLineAttribute::UpdateDrawable( void )
	{
		osg::Vec3Array* pVertexArray = new osg::Vec3Array;
		int nCount = (int)m_listDrawPoints.size();
		for (int index = 0; index < nCount; ++index)
		{
			pVertexArray->push_back(m_listDrawPoints[index]);
		}

		osg::Geometry* pGeomerty = m_pLineGeometry;
		pGeomerty->setVertexArray(pVertexArray);

		osg::Vec4Array* pColorArray = (osg::Vec4Array*)pGeomerty->getColorArray();
		pGeomerty->setColorArray(pColorArray);
		pGeomerty->setColorBinding(osg::Geometry::BIND_OVERALL);

		osg::DrawArrays* pDrawArrays = (osg::DrawArrays*)pGeomerty->getPrimitiveSet(0);
		pDrawArrays->set(GL_LINE_STRIP, 0, pVertexArray->size());
	}

	// ���ĳһ���ؼ���
	osg::Vec3d CTrajectLineAttribute::GetKeyPoint( int index ) const
	{
		if (index < 0 || index >= (int)m_listPoints.size())
		{
			return (osg::Vec3(-1,-1,-1));
		}

		return m_listPoints[index];
	}

// 	// ���·���ؼ���
// 	const IPathAttribute::ListPoints& CTrajectLineAttribute::GetKeyPoints( void ) const
// 	{
// 		return (m_listPoints);
// 	}
// 
// 	// ���·����
// 	const IPathAttribute::ListPoints& CTrajectLineAttribute::GetPathPoints( void ) const
// 	{
// 		return (m_listDrawPoints);
// 	}

	// ���ָ��·����
	osg::Vec3d CTrajectLineAttribute::GetPathPoint( const int index ) const
	{
		if (index < 0 || index >= (int)m_listDrawPoints.size())
		{
			return (osg::Vec3(-1,-1,-1));
		}

		return m_listDrawPoints[index];
	}

	// ��ȡ�Ƿ���ʾ
	bool CTrajectLineAttribute::GetShowSate( void ) const
	{
		return (m_bShow);
	}

	void CTrajectLineAttribute::SetShowSate( bool bShow )
	{
		if (bShow)
		{
			m_pGeode->setNodeMask(0x01);
		}
		else
		{
			m_pGeode->setNodeMask(0x00);
		}

		m_bShow = bShow;
	}
*/
}
