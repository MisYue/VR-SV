/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  osgEarth接口		                                            */
/* 时间： 2015-05-28                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IEARTH_H_
#define _IEARTH_H_

#pragma once

namespace VR_Soft
{

	class OSGEARTH_DLL IEarth
	{
	public:
		// 析构函数
		virtual ~IEarth() { }
		// 获得地图节点
		virtual EarthMap* GetEarthMap(void) const = 0;
	};
}

#endif