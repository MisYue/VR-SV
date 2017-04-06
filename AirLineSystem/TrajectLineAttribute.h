/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨道线属性类			                                        */
/* 时间： 2016-05-24                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _TRAJECTLINEATTRIBUTE_H_
#define _TRAJECTLINEATTRIBUTE_H_

#pragma once

#include <osg/Geode>

namespace VR_Soft
{
/*	class CTrajectLineAttribute // : public CAttributeImp<IPathAttribute>
	{
	public:
		// 构造函数
		explicit CTrajectLineAttribute(IEntityBase* pIEntityBase);
		// 析构函数
		virtual ~CTrajectLineAttribute(void);
		
	public:
		// 初始化
		virtual void Init();
		// 是否移动
		virtual bool IsMove(void) const { return (false); }
		// 更新
		virtual void Update(void) ;
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

	protected:
		// 更新渲染体
		void UpdateDrawable(void);
		

	public:
		// 是否编辑
		void SetEnableEdit(bool bEdit);
		// 获得是否编辑
		bool GetEnableEdit(void) const;
		// 获取光照状态
		bool GetLight(void) const;
		// 设置光照状态
		void SetEnableLight(bool bLight);
		// 获取是否显示
		bool GetShowSate(void) const;
		// 设置是否显示
		void SetShowSate(bool bShow);

	public:
		// 声明属性
		DECLARE_PROPERTY(CTrajectLineAttribute, bool, Edit);
		DECLARE_PROPERTY(CTrajectLineAttribute, bool, Light);
		DECLARE_PROPERTY(CTrajectLineAttribute, bool, Show);

	protected:
		// 初始化渲染体
		void InitDrawable();

	private:
		bool m_bEdit; // 编辑
		bool m_bLight; // 光照
		bool m_bShow; // 是否隐藏
		osg::Geode* m_pGeode; // 渲染体

// 		ListPoints m_listPoints;
// 		ListPoints m_listDrawPoints; 

		osg::Geometry* m_pLineGeometry; // 绘制体
	};
*/
}

#endif //! _TRAJECTLINEATTRIBUTE_H_
