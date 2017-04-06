/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  雷达接口														*/
/* 时间： 2015-05-22                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IRADAR_H_
#define _IRADAR_H_

#pragma once

#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osgSim/SphereSegment>

namespace VR_Soft
{
	extern VRString RADARTYPE;	
	class VRSOFT_PLUGIN_DLL IRadar : public IEntityBase
	{
	public:
		enum DrawMode
		{
			LINE_MODE = 0x01, // 线模式
			FACE_MODE = 0x02, // 面模式
			ALL_MODE = 0x04 // 全部渲染
		};

	public:
		// 设置半径
		virtual void SetRadius(float fRaius) = 0;
		// 获得半径
		virtual float GetRadius(void) const = 0;
		// 设置扫描速度
		virtual void SetScanSpeed(float fSpeed) = 0;
		// 获得扫描速度
		virtual float GetScanSpeed(void) const = 0;
		// 设置颜色
		virtual void SetColor(const osg::Vec4& vFaceColor, const osg::Vec4& vScanColor) = 0;
		// 获得颜色
		virtual void GetColor(osg::Vec4& vFaceColor, osg::Vec4& vScanColor) = 0;
		// 设置渲染模式
		virtual void SetDrawMode(const DrawMode dm) = 0;
		// 获得渲染模式
		virtual DrawMode GetDrawMode(void) const = 0;
		// 设置网格数
		virtual void SetWireframeCount(int nCount) = 0;
		// 设置网格数
		virtual int GetWireframeCount(void) const = 0;
		// 设置扫描开关
		virtual void SetScanState(bool bOpen) = 0;
		// 获得扫描开关
		virtual bool GetScanState(void) const = 0;
	};
}

#endif