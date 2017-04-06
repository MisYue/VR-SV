/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  标绘控制点的头文件	                                        */
/* 时间： 2016-08-10                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PLOTCONTRLHANDEL_H_
#define _PLOTCONTRLHANDEL_H_

#pragma once

#include <osgGA/GUIEventHandler>
#include <osgViewer/View>

namespace VR_Soft
{
	class CBaseContrl;
	class CFeatureGeomtry;

	class CPlotContrlHandle : public osgGA::GUIEventHandler, public IPlotContrlHandle
	{
	public:
		// 构造函数
		explicit CPlotContrlHandle(void);
		// 函数
		virtual~CPlotContrlHandle(void);

	public:
		// 设置控制器
		void SetContrl(CBaseContrl* pBaseContrl);
		// 设置渲染对象
		void SetFeartureGeomtry( IFeatureGeomtry* pFeatureGeomtry );
		// 获得点下的位置
		bool GetLocationAt( osgViewer::View* view, double x, double y, double &lon, double &lat );

	public:
		 virtual bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&);
		 
		 
	private:
		CBaseContrl* m_pBaseContrl;
		CFeatureGeomtry* m_pFeatureGeomtry;
		bool _finished;
		bool _mouseDown;
		float _mouseDownX, _mouseDownY;
		int _mouseButton;
		osg::Node::NodeMask m_intersectionMask;
		bool m_gotFirstLocation;
		bool _lastPointTemporary;
	};
}


#endif // !_PLOTCONTRLHANDEL_H_
