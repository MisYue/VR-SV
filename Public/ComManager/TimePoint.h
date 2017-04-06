/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ߵ�				                                        */
/* ʱ�䣺 2015-08-04                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _AIRLINEPOINT_H_
#define _AIRLINEPOINT_H_

#pragma once

#include <osg/Vec3d>

namespace VR_Soft
{
	class VRSOFT_DLL CTimePoint
	{
	public:
		// ���캯��
		explicit CTimePoint(void);
		explicit CTimePoint(const osg::Vec3d& v, double dt = 0.0);
		explicit CTimePoint(double x, double y, double z, double dt = 0.0);
		~CTimePoint(void);
		// ��ֵ
		CTimePoint &operator= (const CTimePoint& other);
		// ��ʱ����бȽ�
		bool operator< (double dt);
		bool operator== (double dt);
		bool operator== (const CTimePoint& other);
		
	public:
		// ��ö���
		osg::Vec3d GetPoint(void) const;

	private:
		osg::Vec3d m_point; // ��
		double m_dt; // ʱ��
	};
}

#endif // _AIRLINEPOINT_H_