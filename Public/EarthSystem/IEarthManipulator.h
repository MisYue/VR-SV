/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  osgEarth������	                                            */
/* ʱ�䣺 2015-11-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IEARTHMANIPULATOR_H_
#define _PUBLICE_IEARTHMANIPULATOR_H_

namespace VR_Soft
{
	class OSGEARTH_DLL IEarthManipulator
	{
	public:
		virtual ~IEarthManipulator() { }
		// ��λ
		virtual void LookHome(void) = 0;
	};
}

#endif