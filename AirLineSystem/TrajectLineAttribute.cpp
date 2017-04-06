#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "TrajectLineAttribute.h"
#include <osg/Geode>
#include <osg/Geometry>

namespace VR_Soft
{
	// 构造函数
/*	CTrajectLineAttribute::CTrajectLineAttribute(IEntityBase* pIEntityBase)
		:CAttributeImp<IPathAttribute>(pIEntityBase, "路径属性"),m_bEdit(true), m_bLight(false),m_bShow(true)
	{
		//m_pGeode = new osg::Geode;
	}

	// 析构函数
	CTrajectLineAttribute::~CTrajectLineAttribute(void)
	{
	}

	// 初始化
	void CTrajectLineAttribute::Init()
	{
// 		DEFINITION_PROPERTY(Edit, &CTrajectLineAttribute::SetEnableEdit, &CTrajectLineAttribute::GetEnableEdit, "编辑", "", "", CTRL_COMBOX);
// 		ADDENUM_PROPERTY(Edit, "TRUE", true);
// 		ADDENUM_PROPERTY(Edit, "FALSE", false);
// 
// 		DEFINITION_PROPERTY(Light, &CTrajectLineAttribute::SetEnableLight, &CTrajectLineAttribute::GetLight, "光照", "", "", CTRL_COMBOX);
// 		ADDENUM_PROPERTY(Light, "TRUE", true);
// 		ADDENUM_PROPERTY(Light, "FALSE", false);
// 
// 		DEFINITION_PROPERTY(Show, &CTrajectLineAttribute::SetShowSate, &CTrajectLineAttribute::GetShowSate, "显隐", "", "", CTRL_COMBOX);
// 		ADDENUM_PROPERTY(Show, "显示", true);
// 		ADDENUM_PROPERTY(Show, "隐藏", false);

		m_listPoints.clear();
		InitDrawable();
	}

	// 是否编辑
	void CTrajectLineAttribute::SetEnableEdit(const bool bEdit)
	{
		m_bEdit = bEdit;
	}

	// 获得是否编辑
	bool CTrajectLineAttribute::GetEnableEdit(void) const
	{
		return (m_bEdit);
	}

	// 更新
	void CTrajectLineAttribute::Update( void )
	{
		// 获得更新顶点

		ISimManager::SimCmd simCmd = ISimManager::GetInstance().GetSimCmd();
		if (ISimManager::Pause !=  simCmd && ISimManager::Stop != simCmd )
		{
			//			SimRun(dt);
			return;
		}

		if (IEvent::GetInstance().GetMouseButton(MS_RIGHT))
		{
			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
			// 获得点
			IEarthManager*  pIEarthManager = CComManagerImp::GetComponent<IEarthManager>(INSTANCE_NAME_EARTHSYSTEM);
			if (NULL == pIEarthManager)
			{
				return;
			}

			double dLat = 0.0, dLon = 0.0, dHeight = 0.0;
			pIEarthManager->GetEarth()->GetLongLatHightByPoint(v.x(), v.y(), dLat, dLon, dHeight);
			dHeight += 10000;

			// 添加到点
			AddKeyPoint(osg::Vec3d(dLat, dLon, dHeight));

			UpdateDrawable();
		}
	}

	// 获得渲染体
	DrawObj* CTrajectLineAttribute::GetDrawObj( void )
	{
		return (m_pGeode);
	}

	// 获取光照状态
	bool CTrajectLineAttribute::GetLight( void ) const
	{
		return (m_bLight);
	}

	// 设置光照状态
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
	// 添加一个点进入属性中
	void CTrajectLineAttribute::AddKeyPoint( const osg::Vec3d& vPos )
	{
		m_listPoints.push_back(vPos);

		// 转换成世界坐标
		osg::Vec3d vWord;
		CConvert::LatLongHeightToWord(vPos, vWord);
		m_listDrawPoints.push_back(vWord);
	}

	// 移除一个点
	void CTrajectLineAttribute::RemoveKeyPoint( const int index )
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
	void CTrajectLineAttribute::ChangeKeyPoint( const int index, const osg::Vec3d& vPos )
	{
		if (index < 0 || index > (int)m_listPoints.size())
		{
			ILogManager::GetInstance().SetLogMessage("移除点位置无效", ERROR_NOT_FIND);
			return;
		}

		m_listPoints[index] = vPos;
	}

	// 初始化绘制体
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

	// 更新渲染体
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

	// 获得某一个关键点
	osg::Vec3d CTrajectLineAttribute::GetKeyPoint( int index ) const
	{
		if (index < 0 || index >= (int)m_listPoints.size())
		{
			return (osg::Vec3(-1,-1,-1));
		}

		return m_listPoints[index];
	}

// 	// 获得路径关键点
// 	const IPathAttribute::ListPoints& CTrajectLineAttribute::GetKeyPoints( void ) const
// 	{
// 		return (m_listPoints);
// 	}
// 
// 	// 获得路径点
// 	const IPathAttribute::ListPoints& CTrajectLineAttribute::GetPathPoints( void ) const
// 	{
// 		return (m_listDrawPoints);
// 	}

	// 获得指定路径点
	osg::Vec3d CTrajectLineAttribute::GetPathPoint( const int index ) const
	{
		if (index < 0 || index >= (int)m_listDrawPoints.size())
		{
			return (osg::Vec3(-1,-1,-1));
		}

		return m_listDrawPoints[index];
	}

	// 获取是否显示
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
