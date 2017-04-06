#pragma once
#include<osg/MatrixTransform>
#include <osg/NodeCallback>
#include <QtGui/QTableWidget>
#include <QtGui/QTableWidgetItem>
#include "InitParameterDialog.h"
//说明：conType ： 0：不绘制单片线 1：开始绘制,单次循环 2：暂停绘制 3：重新绘制
//
class LineUpDataCallBack : public osg::Drawable::UpdateCallback
{
private:
	std::vector<FragMentLine> p_AimFragmeList;
	CoordinatesPosition p_HitPostion;
	osg::Vec4 Vec_color;
	int LoopTimes;
	int conType;
public:
	LineUpDataCallBack(std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion,osg::Vec4 _Pvec)
	{
		p_AimFragmeList = AimFragmeList;
		p_HitPostion = HitPostion;
		LoopTimes = 0.0;
		Vec_color = _Pvec;
		conType = 0;
	};
	virtual void update(osg::NodeVisitor* nv, osg::Drawable* drawable);
	void ControlCall(int i_conType);
};
//
class ShockWaveCallBack : public osg::NodeCallback
{
private:
	CoordinatesPosition p_HitPostion;
	int LoopTimes;
	int conType;
public:
	ShockWaveCallBack(CoordinatesPosition HitPostion)
	{
		p_HitPostion = HitPostion;
		LoopTimes = 0.0;
		conType = 0;
	};
	virtual void operator()(osg::Node* node,osg::NodeVisitor *nv);
	void ControlCall(int i_conType);
};