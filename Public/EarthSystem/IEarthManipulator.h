/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  osgEarth操作器	                                            */
/* 时间： 2015-11-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IEARTHMANIPULATOR_H_
#define _PUBLICE_IEARTHMANIPULATOR_H_

namespace VR_Soft
{
	class OSGEARTH_DLL IEarthManipulator
	{
	public:
		virtual ~IEarthManipulator() { }
		// 复位
		virtual void LookHome(void) = 0;
	};
}

#endif