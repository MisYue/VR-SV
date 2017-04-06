/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线类				                                        */
/* 时间： 2015-08-04                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _AIRLINE_H_
#define _AIRLINE_H_

#pragma once

#include <osgEarthSymbology/Style>

namespace osgEarth
{
	namespace Annotation
	{
		class FeatureNode;
	}

	namespace Symbology
	{
		class LineString;
	}

	namespace Features
	{
		class Feature;
	}
}

namespace VR_Soft
{
	class CTrajectLine : public ITrajectory
	{

	public:
		explicit CTrajectLine(void);
		virtual ~CTrajectLine(void);

	public:
		// 初始化
		virtual void Init(void);
		// 获得弹道数据
		virtual const ListTrajectoryInfo& GetTrajectoryPoint(void) const ;
		// 弹道算法
		virtual void AlgorithmTrajectoryPoint(void);
		// 设置弹道对象
		virtual void SetTrajectoryEntity(IEntityBase* pITrajectoryEntity) ;

	public: 
		// 添加点
		virtual void AddAirLinePoint(const TrajectoryInfo& airLinePoint);
		// 移除点
		virtual void RemoveAirLinePoint(const int index);
		//保存点到文件中
		virtual void Save(const VRString& strFile) const ;
		// 从文件加载
		virtual void Load(const VRString& strFile) { }
		// 编辑状态开关
		virtual void EnableEidt(bool bEidt);
		// 获得编辑状态
		virtual bool EidtState(void) const ;

	public:
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine);

	protected:
		// 获得依赖地球最终矩阵
		virtual void GetMatrixInEarth(const osg::Vec3& vPositon) { }
		osgEarth::Symbology::Style BuildStyle(void);


	private: 
		bool m_bEidt; // 编辑状态
//		LstAirLinePoint m_lstAirPoint; // 航线关键点
		osgEarth::Annotation::FeatureNode* m_pFeatureNode; // 线的节点
		osgEarth::Features::Feature* m_pFeature; // 样式
		osgEarth::Symbology::LineString* m_pLineString; // 线对象

		ITrajectory::ListTrajectoryInfo m_listTrajectroryPoint; // 轨迹数据顶点
		IEntityBase* m_pIEntityBase;

		VR_AUTO_MUTEX;

	};

}

#endif // _AIRLINE_H_