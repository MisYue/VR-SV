/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  3d地球曹操器		                                            */
/* 时间： 2016-07-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _3DEARTHMANIPULATOR_H_
#define _3DEARTHMANIPULATOR_H_

#pragma once

#include <osgEarthUtil/EarthManipulator>
#include "SynchroManipulator.h"
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgearth/ElevationQuery>

namespace VR_Soft
{
	class CameraInfoCallback;

	class CEarthManipulator3D : public CSynchroManipulator
	{
	public:
		CEarthManipulator3D(void);
		virtual ~CEarthManipulator3D(void);

	public:
		void SetCameraInfoCallback(CameraInfoCallback* pCamCB);
		// 设置地图节点
		void SetEarthMapNode(osgEarth::MapNode* pMapNode);

	public: 
		// 设置跟踪实体
		virtual void SetTrackEntity( IEntityBase* pIEntity );

	public:
		// 事件处理器
		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	private:
		CameraInfoCallback *m_pCamCB;
		double m_distance, m_latitude, m_longtitude, m_height;
		const osgEarth::Map*       _map;
		const osgEarth::Terrain*   _terrain;
		osgEarth::ElevationQuery*   _query;
	};
}


#endif // !_3DEARTHMANIPULATOR_H_