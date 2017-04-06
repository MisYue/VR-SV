#include "../../Public/PlotSystem/PlotSystem.h"
#include "BaseContrl.h"
#include <algorithm>
#include <iterator>
#include "PlotStrategy.h"

namespace VR_Soft
{
	CBaseContrl::CBaseContrl(CPlotStrategy* pPlotStrategy)
		:m_pPlotStrategy(pPlotStrategy), m_bEndDraw(false),m_bPress(false)
	{
	}

	CBaseContrl::~CBaseContrl(void)
	{
	}

	// 从新计算
	void CBaseContrl::Rebuild( void )
	{
		m_keyContrlPoint.clear();
		std::copy(m_mouseContrlPoint.begin(), m_mouseContrlPoint.end(), std::back_inserter(m_keyContrlPoint));
	}

	void CBaseContrl::AddMousePoint( const osg::Vec3d& vMousePoint )
	{
		Rebuild();

		RebuildPlotStategy();

		m_bPress = true;
	}

	// 重新构建策略
	void CBaseContrl::RebuildPlotStategy( void )
	{

		if (NULL == m_pPlotStrategy)
		{
			return;
		}

		m_pPlotStrategy->Rebuild(m_keyContrlPoint);
	}

	// 是否结束绘制
	bool CBaseContrl::IsEndDraw( void )
	{
		return (m_bEndDraw);
	}

	// 鼠标滑动
	void CBaseContrl::AddMouseMovePoint( const osg::Vec3d& vMousePoint )
	{
		if (m_mouseContrlPoint.empty())
		{
			return;
		}

		if (m_bPress)
		{
			m_mouseContrlPoint.push_back(vMousePoint);
			m_bPress = false;
		}
		else
		{
			m_mouseContrlPoint[m_mouseContrlPoint.size() - 1] = vMousePoint;
		}
		

		Rebuild();

		RebuildPlotStategy();
	}
}
