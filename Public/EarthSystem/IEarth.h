/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  osgEarth�ӿ�		                                            */
/* ʱ�䣺 2015-05-28                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IEARTH_H_
#define _IEARTH_H_

#pragma once

namespace VR_Soft
{

	class OSGEARTH_DLL IEarth
	{
	public:
		// ��������
		virtual ~IEarth() { }
		// ��õ�ͼ�ڵ�
		virtual EarthMap* GetEarthMap(void) const = 0;
	};
}

#endif