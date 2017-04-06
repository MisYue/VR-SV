/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  osgEarth������	                                            */
/* ʱ�䣺 2016-09-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _EARTHUTIL_H_
#define _EARTHUTIL_H_

#pragma once

#include <osgEarthUtil/FeatureQueryTool>
#include <osgEarthUtil/MeasureTool>
#include <osgEarthUtil/Controls>

namespace VR_Soft
{
	class CFeatureQuery : public osgEarth::Util::FeatureQueryTool::Callback
	{
	public:
		// ���캯��
		explicit CFeatureQuery(osgEarth::Util::Controls::ControlCanvas* pContainver);
		// ������
		virtual void onHit(osgEarth::ObjectID id);
		// ����뿪
		virtual void onMiss(void);
		// ��������¼�����
		virtual bool accept(const osgGA::GUIEventAdapter& ea, const osgGA::GUIActionAdapter& aa);

	private:
		osgEarth::Util::Controls::Grid* m_pGrid;
		osgEarth::Features::FeatureID m_lastFID;
	};

	//////////////////////////////���ص�����////////////////////////////////////////////
	class CMeasureToolCallback : public osgEarth::Util::MeasureToolHandler::MeasureToolEventHandler
	{
	public:
		// ���캯��
		CMeasureToolCallback(osgEarth::Util::Controls::LabelControl* label);
		// ���ȸı�
		virtual void onDistanceChanged(osgEarth::Util::MeasureToolHandler* sender, double distance);

	private:
		 osgEarth::Util::Controls::LabelControl* m_pLabel;
	};

	//////////////////////////////��깤�߾��////////////////////////////////////////////
	class CMeasureToolHandler : public osgEarth::Util::MeasureToolHandler
	{
	public:
		// ���캯��
		CMeasureToolHandler(osg::Group* group, osgEarth::MapNode* mapNode);
		// ������
		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
	};

	class CEarthUtil
	{
	public:
		CEarthUtil(void);
		~CEarthUtil(void);
	};
}


#endif // !_EARTHUTIL_H_