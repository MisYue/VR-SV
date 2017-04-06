/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  弹道导弹弹道属性类	                                        */
/* 时间： 2016-05-31                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _BALLMISSILEATTRIBUTE_H_
#define _BALLMISSILEATTRIBUTE_H_

#pragma once

#include <osg/Geode>
#include <osg/Geometry>

namespace VR_Soft
{
/*
	class CBallMissileAttribute // : public CAttributeImp<IPathAttribute>
	{
	public:
		CBallMissileAttribute(IEntityBase* pIEntityBase);
		virtual ~CBallMissileAttribute(void);

	public:
		// 初始化
		virtual void Init();
		// 更新函数
		virtual void Update();
		// 是否移动
		virtual bool IsMove(void) const { return (false); }
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void) ;

	public:
		// 添加一个点进入属性中
		virtual void AddKeyPoint(const osg::Vec3d& vPos);
		// 移除一个点
		virtual void RemoveKeyPoint(const int index);
		// 更改点
		virtual void ChangeKeyPoint(const int index, const osg::Vec3d& vPos);
		// 获得某一个关键点
		virtual osg::Vec3d GetKeyPoint(int index) const;
// 		// 获得路径关键点
// 		virtual const ListPoints& GetKeyPoints(void) const;
// 		// 获得路径点
// 		virtual const ListPoints& GetPathPoints(void) const ;
		// 获得指定路径点
		virtual osg::Vec3d GetPathPoint(const int index) const;

	public:
		// 是否编辑
		void SetEnableEdit(bool bEdit);
		// 获得是否编辑
		bool GetEnableEdit(void) const;
		// 设置开始点
		void SetStartPoint(const osg::Vec3d& vStart);
		// 获得开始点
		osg::Vec3d GetStartPoint(void) const;
		// 设置结束点
		void SetEndPoint(const osg::Vec3d& vEnd) ;
		// 获得结束点
		osg::Vec3d GetEndPoint(void) const;
		// 设置最高点
		void SetHeight(double dHeight);
		// 获得最高点
		double GetHeight(void) const;
		// 更新渲染体
		void UpdateDrawable( void );
	public:
		// 声明属性
		DECLARE_PROPERTY(CBallMissileAttribute, bool, Edit);
		DECLARE_PROPERTY(CBallMissileAttribute, osg::Vec3d, StartPoint);
		DECLARE_PROPERTY(CBallMissileAttribute, osg::Vec3d, EndPoint);
		DECLARE_PROPERTY(CBallMissileAttribute, double, Height);

	protected:
		// 初始化渲染体
		void InitDrawable();

	private:
		bool m_bEdit; // 编辑
		osg::Vec3d m_vStart; // 开始点
		osg::Vec3d m_vStop; // 结束点
		double m_dHeight; // 高度

		osg::Geode* m_pGeode; // 渲染体

		ListPoints m_listPoints;
		ListPoints m_listDrawPoints; 

		osg::Geometry* m_pLineGeometry; // 绘制体
	};
	*/
}

#endif //  _BALLMISSILEATTRIBUTE_H_