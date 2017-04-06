/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  同步操作器基类	                                            */
/* 时间： 2016-07-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SYSNCHROMANIPULATOR_H_
#define _SYSNCHROMANIPULATOR_H_

#pragma once

#include <osgEarth/Viewpoint>
#include <osgEarthUtil/EarthManipulator>

namespace VR_Soft
{
	class Compass;

	class CSynchroManipulator : public osgEarth::Util::EarthManipulator
	{
	public:
		CSynchroManipulator(void);
		virtual ~CSynchroManipulator(void);

	public:
		virtual void pan( double dx, double dy );
		// 缩放
		virtual void zoom( double dx, double dy );
		// 旋转
		virtual void rotate( double dx, double dy );
		//virtual bool handleScrollAction( const osgEarth::Util::EarthManipulator::Action& action, double duration_s  = DBL_MAX  );

	public:
		// 设置视点
		virtual void SetViewPoint(const osgEarth::Viewpoint& vp, double duration_s =0.0);
		// 设置跟踪实体
		virtual void SetTrackEntity( IEntityBase* pIEntity );

	public:
		void SlotZoom( double value );
		void SlotTraval( const osg::Vec2& _direction );
		void SetCompass( Compass* pCompass );
		void SlotPitch(const osg::Vec2& _direction );

	protected:
		// 发送同步
		virtual void SendSynchro( double duration_s =0.0 );
		// 发送同步指令
		virtual void SendSynchro(const osgEarth::Viewpoint& vp, double duration_s = 0);
		// 获得指令值
		double GetDoubleOption(const osgEarth::Util::EarthManipulator::Action& action, int option, double defaultValue);

	protected:
		// 双击
		virtual bool handlePointAction( const osgEarth::Util::EarthManipulator::Action& action, float mx, float my, osg::View* view );
		// 事件处理器
		virtual bool handleKeyboardAction( const osgEarth::Util::EarthManipulator::Action& action, double duration_s = DBL_MAX );
		

	protected:
		Compass* m_pCompass;
	};

}

#endif // !_SYSNCHROMANIPULATOR_H_