/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  2Dͬ����������	                                            */
/* ʱ�䣺 2016-07-01                                                    */
/* �޸�ʱ��:                                                            */
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
		// �����ӵ�
		virtual void SetViewPoint(const osgEarth::Viewpoint& vp, double duration_s  = 0.0 );
		// �����㷨
		virtual void rotate( double dx, double dy );

		// ���ø���ʵ��
		virtual void SetTrackEntity( IEntityBase* pIEntity );
		
	protected:
		// ����ͬ��
		virtual void SendSynchro( double duration_s =0.0 );
		// ����ͬ��ָ��
		virtual void SendSynchro(const osgEarth::Viewpoint& vp, double duration_s = 0);

	private:
		double m_dPitch;
		double m_dHeading;
	};

}

#endif // !_SYNCHROMAINPULATOR2D_H_