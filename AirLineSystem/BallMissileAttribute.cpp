#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "BallMissileAttribute.h"

namespace VR_Soft
{
/*	CBallMissileAttribute::CBallMissileAttribute(IEntityBase* pIEntityBase)
		:CAttributeImp<IPathAttribute>(pIEntityBase, "������������������"),m_bEdit(true),
		m_vStart(0, 0, 0), m_vStop(0, 0, 0),m_dHeight(1000000.0)
	{
	}


	CBallMissileAttribute::~CBallMissileAttribute(void)
	{
	}

	// ��ʼ��
	void CBallMissileAttribute::Init()
	{
		m_listPoints.resize(3);
		InitDrawable();

		DEFINITION_PROPERTY(Edit, &CBallMissileAttribute::SetEnableEdit, &CBallMissileAttribute::GetEnableEdit, "�༭", "", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(Edit, "TRUE", true);
		ADDENUM_PROPERTY(Edit, "FALSE", false);

		DEFINITION_PROPERTY(StartPoint, &CBallMissileAttribute::SetStartPoint, &CBallMissileAttribute::GetStartPoint, "��ʼλ��", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(EndPoint, &CBallMissileAttribute::SetEndPoint, &CBallMissileAttribute::GetEndPoint, "����λ��", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(Height, &CBallMissileAttribute::SetHeight, &CBallMissileAttribute::GetHeight, "�߶�", "", "��", CTRL_SPINBOX);
	}

	// �Ƿ�༭
	void CBallMissileAttribute::SetEnableEdit(const bool bEdit)
	{
		m_bEdit = bEdit;
	}

	// ����Ƿ�༭
	bool CBallMissileAttribute::GetEnableEdit(void) const
	{
		return (m_bEdit);
	}

	// ���ÿ�ʼ��
	void CBallMissileAttribute::SetStartPoint(const osg::Vec3d& vStart)
	{
		m_vStart = vStart;
		m_listPoints[0] = vStart;

		// ��Ҫ���µ�ǰʵ��
		//GetEntity()->NeedUpdate();
	}

	// ��ÿ�ʼ��
	osg::Vec3d CBallMissileAttribute::GetStartPoint(void) const
	{
		return (m_vStart);
	}

	// ���ý�����
	void CBallMissileAttribute::SetEndPoint(const osg::Vec3d& vEnd)
	{
		m_vStop = vEnd;
		m_listPoints[2] = vEnd;

		// ��Ҫ���µ�ǰʵ��
		//GetEntity()->NeedUpdate();
	}

	// ��ý�����
	osg::Vec3d CBallMissileAttribute::GetEndPoint(void) const
	{
		return (m_vStop);
	}

	// ������ߵ�
	void CBallMissileAttribute::SetHeight(double dHeight)
	{
		m_dHeight = dHeight;

		// ��Ҫ���µ�ǰʵ��
		//GetEntity()->NeedUpdate();
	}

	// �����ߵ�
	double CBallMissileAttribute::GetHeight(void) const
	{
		return (m_dHeight);
	}

	// ���º���
	void CBallMissileAttribute::Update()
	{
// 		ISimManager::SimCmd simCmd = ISimManager::GetInstance().GetSimCmd();
// 		if (ISimManager::Pause !=  simCmd && ISimManager::Stop != simCmd )
// 		{
// 			//			SimRun(dt);
// 			return;
// 		}
// 
// 		// �ж��Ƿ�������Ҽ�
// 		if (IEvent::GetInstance().GetMouseButton(MS_RIGHT) && m_bEdit)
// 		{
// 			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
// 			// ��õ�
// 			IEarthManager*  pIEarthManager = CComManagerImp::GetComponent<IEarthManager>(INSTANCE_NAME_EARTHSYSTEM);
// 			if (NULL == pIEarthManager)
// 			{
// 				return;
// 			}
// 
// 			double dLat = 0.0, dLon = 0.0, dHeight = 0.0;
// 			pIEarthManager->GetEarth()->GetLongLatHightByPoint(v.x(), v.y(), dLat, dLon, dHeight);
// 			
// 			SetEndPoint(osg::Vec3d(dLat, dLon, dHeight));
// 			//AddKeyPoint(osg::Vec3d(dLat, dLon, dHeight));
// 		}
// 		else if (IEvent::GetInstance().GetMouseButton(MS_LEFT)  && m_bEdit)
// 		{
// 			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
// 			// ��õ�
// 			IEarthManager*  pIEarthManager = CComManagerImp::GetComponent<IEarthManager>(INSTANCE_NAME_EARTHSYSTEM);
// 			if (NULL == pIEarthManager)
// 			{
// 				return;
// 			}
// 
// 			double dLat = 0.0, dLon = 0.0, dHeight = 0.0;
// 			pIEarthManager->GetEarth()->GetLongLatHightByPoint(v.x(), v.y(), dLat, dLon, dHeight);
// 			SetStartPoint(osg::Vec3d(dLat, dLon, dHeight));
// 			//AddKeyPoint(osg::Vec3d(dLat, dLon, dHeight));
// 
// 		}
// 		else if (IEvent::GetInstance().GetMouseButton(MS_MIDDILE))
// 		{
// 			m_bEdit = false;
// 
// 			UpdateDrawable();
// 		}
	}

	// ���һ�������������
	void CBallMissileAttribute::AddKeyPoint( const osg::Vec3d& vPos )
	{
		m_listPoints.push_back(vPos);

		// ת������������
		osg::Vec3d vWord;
		CConvert::LatLongHeightToWord(vPos, vWord);
		m_listDrawPoints.push_back(vWord);
	}

	// �Ƴ�һ����
	void CBallMissileAttribute::RemoveKeyPoint( const int index )
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
	void CBallMissileAttribute::ChangeKeyPoint( const int index, const osg::Vec3d& vPos )
	{
		if (index < 0 || index > (int)m_listPoints.size())
		{
			ILogManager::GetInstance().SetLogMessage("�Ƴ���λ����Ч", ERROR_NOT_FIND);
			return;
		}

		m_listPoints[index] = vPos;
	}

	// ���·���ؼ���
// 	const IPathAttribute::ListPoints& CBallMissileAttribute::GetKeyPoints( void ) const
// 	{
// 		return (m_listPoints);
// 	}
// 
// 	// ���·����
// 	const IPathAttribute::ListPoints& CBallMissileAttribute::GetPathPoints( void ) const
// 	{
// 		return (m_listDrawPoints);
// 	}

	// ���ָ��·����
	osg::Vec3d CBallMissileAttribute::GetPathPoint( const int index ) const
	{
		if (index < 0 || index >= (int)m_listDrawPoints.size())
		{
			return (osg::Vec3(-1,-1,-1));
		}

		return m_listDrawPoints[index];
	}

	// �����Ⱦ��
	DrawObj* CBallMissileAttribute::GetDrawObj( void )
	{
		return (m_pGeode);
	}

	// ������Ⱦ��
	void CBallMissileAttribute::UpdateDrawable( void )
	{
		// �����е��λ��
		// ת����������
		osg::Vec3d vStart;
		osg::Vec3d vStop;

		CConvert::LatLongHeightToWord(m_vStart, vStart);
		CConvert::LatLongHeightToWord(m_vStop, vStop);

		osg::Vec3d vMidGeo = (m_vStop + m_vStart) * 0.5;
		vMidGeo.z() = m_dHeight;

		osg::Vec3d vMid;
		CConvert::LatLongHeightToWord(vMidGeo, vMid);

		m_listPoints[1] = vMidGeo;

		m_listDrawPoints.clear();
		m_listDrawPoints.push_back(vStart);
		m_listDrawPoints.push_back(vMid);
		m_listDrawPoints.push_back(vStop);


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

	// ��ʼ����Ⱦ��
	void CBallMissileAttribute::InitDrawable()
	{
		m_pGeode = new osg::Geode;

		m_pLineGeometry = new osg::Geometry;
		m_pGeode->addDrawable(m_pLineGeometry);

		osg::Vec4Array* pColorArray = new osg::Vec4Array;
		pColorArray->push_back(osg::Vec4(1, 0, 0, 1));

		m_pLineGeometry->setColorArray(pColorArray);

		m_pLineGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP));
	}

	// ���ĳһ���ؼ���
	osg::Vec3d CBallMissileAttribute::GetKeyPoint( int index ) const
	{
		if (index < 0 || index >= (int)m_listPoints.size())
		{
			return (osg::Vec3(-1,-1,-1));
		}

		return m_listPoints[index];
	}
	*/
}