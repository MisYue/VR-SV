/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ͬ������������	                                            */
/* ʱ�䣺 2016-07-01                                                    */
/* �޸�ʱ��:                                                            */
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
		// ����
		virtual void zoom( double dx, double dy );
		// ��ת
		virtual void rotate( double dx, double dy );
		//virtual bool handleScrollAction( const osgEarth::Util::EarthManipulator::Action& action, double duration_s  = DBL_MAX  );

	public:
		// �����ӵ�
		virtual void SetViewPoint(const osgEarth::Viewpoint& vp, double duration_s =0.0);
		// ���ø���ʵ��
		virtual void SetTrackEntity( IEntityBase* pIEntity );

	public:
		void SlotZoom( double value );
		void SlotTraval( const osg::Vec2& _direction );
		void SetCompass( Compass* pCompass );
		void SlotPitch(const osg::Vec2& _direction );

	protected:
		// ����ͬ��
		virtual void SendSynchro( double duration_s =0.0 );
		// ����ͬ��ָ��
		virtual void SendSynchro(const osgEarth::Viewpoint& vp, double duration_s = 0);
		// ���ָ��ֵ
		double GetDoubleOption(const osgEarth::Util::EarthManipulator::Action& action, int option, double defaultValue);

	protected:
		// ˫��
		virtual bool handlePointAction( const osgEarth::Util::EarthManipulator::Action& action, float mx, float my, osg::View* view );
		// �¼�������
		virtual bool handleKeyboardAction( const osgEarth::Util::EarthManipulator::Action& action, double duration_s = DBL_MAX );
		

	protected:
		Compass* m_pCompass;
	};

}

#endif // !_SYSNCHROMANIPULATOR_H_