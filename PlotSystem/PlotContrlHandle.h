/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �����Ƶ��ͷ�ļ�	                                        */
/* ʱ�䣺 2016-08-10                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���캯��
		explicit CPlotContrlHandle(void);
		// ����
		virtual~CPlotContrlHandle(void);

	public:
		// ���ÿ�����
		void SetContrl(CBaseContrl* pBaseContrl);
		// ������Ⱦ����
		void SetFeartureGeomtry( IFeatureGeomtry* pFeatureGeomtry );
		// ��õ��µ�λ��
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
