

#include "../../Public/VRSoft.h"


namespace VR_Soft
{
	CTimePoint::CTimePoint(void):m_point(osg::Vec3d(0.0, 0.0, 0.0)), m_dt(0.0)
	{
	}

	CTimePoint::CTimePoint(const osg::Vec3d& v, double dt):m_point(v), m_dt(dt)
	{

	}

	CTimePoint::CTimePoint(double x, double y, double z, double dt ):m_point(x, y, z), m_dt(dt)
	{

	}

	CTimePoint::~CTimePoint(void)
	{
	}

	CTimePoint &CTimePoint::operator= (const CTimePoint& other)
	{
		m_point = other.m_point;
		m_dt = other.m_dt;
		return (*this);
	}

	// 和时间进行比较
	bool CTimePoint::operator< (double dt)
	{
		return (m_dt < dt);
	}

	bool CTimePoint::operator== (double dt)
	{
		return (dt == m_dt);
	}

	bool CTimePoint::operator== (const CTimePoint& other)
	{
		return (m_point == other.m_point);
	}

	// 获得顶点
	osg::Vec3d CTimePoint::GetPoint(void) const
	{
		return (m_point);
	}
}
