/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨道线														*/
/* 时间： 2016-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _BALLMISSILTRAJECTDRAWABLE_H_
#define _BALLMISSILTRAJECTDRAWABLE_H_


#pragma once

#include "BallMissileTraject.h"

#include <osg/Geode>

namespace VR_Soft
{
/*	class CBallMissileTrajectEntity;

	class CBallMissileTrajectDrawable : public CAttributeImp<IDrawAttribute>
	{
	public:
		CBallMissileTrajectDrawable(IEntityBase* pIEntityBase);
		~CBallMissileTrajectDrawable(void);

	public:
		// 更新
		virtual void Update(void);
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void) ;
		// 是否随着移动
		virtual bool IsMove(void) const ;
		// 初始化
		virtual void Init(void);

	public:
		//// 获得渲染点对象
		//virtual ITrajectory* GetTrajectory(void);

	protected:
		// 绘制直线
		void DrawLine(void);
		// 更新渲染体
		void UpdateDrawable(void);
		void InitDrawable( void );
	private:
		osg::Geode* m_pGeode; // 渲染体
		osg::Geometry* m_pLineGeometry; // 线渲染体

// 		ListPoints m_listPoints;
// 		ListPoints m_listDrawPoints;

		CBallMissileTrajectEntity* m_pBallMissileTrajectEntity;
	};
	*/
}

#endif // !_BALLMISSILTRAJECTDRAWABLE_H_