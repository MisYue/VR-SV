/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  控制点头文件			                                        */
/* 时间： 2016-08-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _BASECONTRL_H_
#define _BASECONTRL_H_

#pragma once

#include <vector>
#include <osg/Vec3d>


namespace VR_Soft
{
	class CPlotStrategy;

	class CBaseContrl
	{
	public:
		typedef std::vector<osg::Vec3d> ListContrlPoint;

	public:
		CBaseContrl(CPlotStrategy* pPlotStrategy);
		~CBaseContrl(void);

		// 重新构建策略
		void RebuildPlotStategy(void);
		// 判断是否结束绘制
		bool IsEndDraw( void );
		// 设置是否结束绘制
		inline void SetEndDraw(bool bEndDraw) { m_bEndDraw = bEndDraw; }
		// 鼠标滑动
		void AddMouseMovePoint(const osg::Vec3d& vMousePoint);
	public:
		// 添加鼠标点
		virtual void AddMousePoint(const osg::Vec3d& vMousePoint);

		// 从新计算
		virtual void Rebuild(void);
		
	protected:
		ListContrlPoint m_mouseContrlPoint;
		ListContrlPoint m_keyContrlPoint;

		CPlotStrategy* m_pPlotStrategy;
		bool m_bEndDraw;
		bool m_bPress;
	};
}


#endif // !_BASECONTRL_H_