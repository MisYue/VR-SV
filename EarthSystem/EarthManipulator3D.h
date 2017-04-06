/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  3d����ܲ���		                                            */
/* ʱ�䣺 2016-07-01                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���õ�ͼ�ڵ�
		void SetEarthMapNode(osgEarth::MapNode* pMapNode);

	public: 
		// ���ø���ʵ��
		virtual void SetTrackEntity( IEntityBase* pIEntity );

	public:
		// �¼�������
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