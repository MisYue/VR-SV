/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  osgEarth操作类	                                            */
/* 时间： 2016-09-12                                                    */
/* 修改时间:                                                            */
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
		// 构造函数
		explicit CFeatureQuery(osgEarth::Util::Controls::ControlCanvas* pContainver);
		// 鼠标点中
		virtual void onHit(osgEarth::ObjectID id);
		// 鼠标离开
		virtual void onMiss(void);
		// 接收鼠标事件类型
		virtual bool accept(const osgGA::GUIEventAdapter& ea, const osgGA::GUIActionAdapter& aa);

	private:
		osgEarth::Util::Controls::Grid* m_pGrid;
		osgEarth::Features::FeatureID m_lastFID;
	};

	//////////////////////////////鼠标回调工具////////////////////////////////////////////
	class CMeasureToolCallback : public osgEarth::Util::MeasureToolHandler::MeasureToolEventHandler
	{
	public:
		// 构造函数
		CMeasureToolCallback(osgEarth::Util::Controls::LabelControl* label);
		// 长度改变
		virtual void onDistanceChanged(osgEarth::Util::MeasureToolHandler* sender, double distance);

	private:
		 osgEarth::Util::Controls::LabelControl* m_pLabel;
	};

	//////////////////////////////鼠标工具句柄////////////////////////////////////////////
	class CMeasureToolHandler : public osgEarth::Util::MeasureToolHandler
	{
	public:
		// 构造函数
		CMeasureToolHandler(osg::Group* group, osgEarth::MapNode* mapNode);
		// 处理句柄
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