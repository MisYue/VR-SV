#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "BallMissileAttribute.h"

namespace VR_Soft
{
/*	CBallMissileAttribute::CBallMissileAttribute(IEntityBase* pIEntityBase)
		:CAttributeImp<IPathAttribute>(pIEntityBase, "弹道导弹弹道线属性"),m_bEdit(true),
		m_vStart(0, 0, 0), m_vStop(0, 0, 0),m_dHeight(1000000.0)
	{
	}


	CBallMissileAttribute::~CBallMissileAttribute(void)
	{
	}

	// 初始化
	void CBallMissileAttribute::Init()
	{
		m_listPoints.resize(3);
		InitDrawable();

		DEFINITION_PROPERTY(Edit, &CBallMissileAttribute::SetEnableEdit, &CBallMissileAttribute::GetEnableEdit, "编辑", "", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(Edit, "TRUE", true);
		ADDENUM_PROPERTY(Edit, "FALSE", false);

		DEFINITION_PROPERTY(StartPoint, &CBallMissileAttribute::SetStartPoint, &CBallMissileAttribute::GetStartPoint, "开始位置", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(EndPoint, &CBallMissileAttribute::SetEndPoint, &CBallMissileAttribute::GetEndPoint, "结束位置", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(Height, &CBallMissileAttribute::SetHeight, &CBallMissileAttribute::GetHeight, "高度", "", "米", CTRL_SPINBOX);
	}

	// 是否编辑
	void CBallMissileAttribute::SetEnableEdit(const bool bEdit)
	{
		m_bEdit = bEdit;
	}

	// 获得是否编辑
	bool CBallMissileAttribute::GetEnableEdit(void) const
	{
		return (m_bEdit);
	}

	// 设置开始点
	void CBallMissileAttribute::SetStartPoint(const osg::Vec3d& vStart)
	{
		m_vStart = vStart;
		m_listPoints[0] = vStart;

		// 需要更新当前实体
		//GetEntity()->NeedUpdate();
	}

	// 获得开始点
	osg::Vec3d CBallMissileAttribute::GetStartPoint(void) const
	{
		return (m_vStart);
	}

	// 设置结束点
	void CBallMissileAttribute::SetEndPoint(const osg::Vec3d& vEnd)
	{
		m_vStop = vEnd;
		m_listPoints[2] = vEnd;

		// 需要更新当前实体
		//GetEntity()->NeedUpdate();
	}

	// 获得结束点
	osg::Vec3d CBallMissileAttribute::GetEndPoint(void) const
	{
		return (m_vStop);
	}

	// 设置最高点
	void CBallMissileAttribute::SetHeight(double dHeight)
	{
		m_dHeight = dHeight;

		// 需要更新当前实体
		//GetEntity()->NeedUpdate();
	}

	// 获得最高点
	double CBallMissileAttribute::GetHeight(void) const
	{
		return (m_dHeight);
	}

	// 更新函数
	void CBallMissileAttribute::Update()
	{
// 		ISimManager::SimCmd simCmd = ISimManager::GetInstance().GetSimCmd();
// 		if (ISimManager::Pause !=  simCmd && ISimManager::Stop != simCmd )
// 		{
// 			//			SimRun(dt);
// 			return;
// 		}
// 
// 		// 判断是否按下鼠标右键
// 		if (IEvent::GetInstance().GetMouseButton(MS_RIGHT) && m_bEdit)
// 		{
// 			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
// 			// 获得点
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
// 			// 获得点
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

	// 添加一个点进入属性中
	void CBallMissileAttribute::AddKeyPoint( const osg::Vec3d& vPos )
	{
		m_listPoints.push_back(vPos);

		// 转换成世界坐标
		osg::Vec3d vWord;
		CConvert::LatLongHeightToWord(vPos, vWord);
		m_listDrawPoints.push_back(vWord);
	}

	// 移除一个点
	void CBallMissileAttribute::RemoveKeyPoint( const int index )
	{
		if (index < 0 || index > (int)m_listPoints.size())
		{
			ILogManager::GetInstance().SetLogMessage("移除点位置无效", ERROR_NOT_FIND);
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

	// 更改点
	void CBallMissileAttribute::ChangeKeyPoint( const int index, const osg::Vec3d& vPos )
	{
		if (index < 0 || index > (int)m_listPoints.size())
		{
			ILogManager::GetInstance().SetLogMessage("移除点位置无效", ERROR_NOT_FIND);
			return;
		}

		m_listPoints[index] = vPos;
	}

	// 获得路径关键点
// 	const IPathAttribute::ListPoints& CBallMissileAttribute::GetKeyPoints( void ) const
// 	{
// 		return (m_listPoints);
// 	}
// 
// 	// 获得路径点
// 	const IPathAttribute::ListPoints& CBallMissileAttribute::GetPathPoints( void ) const
// 	{
// 		return (m_listDrawPoints);
// 	}

	// 获得指定路径点
	osg::Vec3d CBallMissileAttribute::GetPathPoint( const int index ) const
	{
		if (index < 0 || index >= (int)m_listDrawPoints.size())
		{
			return (osg::Vec3(-1,-1,-1));
		}

		return m_listDrawPoints[index];
	}

	// 获得渲染体
	DrawObj* CBallMissileAttribute::GetDrawObj( void )
	{
		return (m_pGeode);
	}

	// 更新渲染体
	void CBallMissileAttribute::UpdateDrawable( void )
	{
		// 计算中点的位置
		// 转换世界坐标
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

	// 初始化渲染体
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

	// 获得某一个关键点
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