/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  2D同步操作器类	                                            */
/* 时间： 2016-07-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SYNCHROMAINPULATOR2D_H_
#define _SYNCHROMAINPULATOR2D_H_

#pragma once

#include <osgEarthUtil/EarthManipulator>
#include "SynchroManipulator.h"

namespace VR_Soft
{
	class CSynchroMainpultor2D : public CSynchroManipulator
	{
	public:
		CSynchroMainpultor2D(void);
		virtual ~CSynchroMainpultor2D(void);

	public:
		// 设置视点
		virtual void SetViewPoint(const osgEarth::Viewpoint& vp, double duration_s  = 0.0 );
		// 重置算法
		virtual void rotate( double dx, double dy );

		// 设置跟踪实体
		virtual void SetTrackEntity( IEntityBase* pIEntity );
		
	protected:
		// 发送同步
		virtual void SendSynchro( double duration_s =0.0 );
		// 发送同步指令
		virtual void SendSynchro(const osgEarth::Viewpoint& vp, double duration_s = 0);

	private:
		double m_dPitch;
		double m_dHeading;
	};

}

#endif // !_SYNCHROMAINPULATOR2D_H_