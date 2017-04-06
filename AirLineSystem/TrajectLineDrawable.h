/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨道线														*/
/* 时间： 2016-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _TRAJECTLINEDRAWABLE_H_
#define _TRAJECTLINEDRAWABLE_H_

#pragma once

#include <osg/Geode>

namespace VR_Soft
{
	class CTrajectLineDrawable : public CAttributeImp<IDrawAttribute>
	{
	public:
		// 构造函数
		CTrajectLineDrawable(void);
		// 析构函数
		virtual ~CTrajectLineDrawable(void);

	public:
		// 更新
		virtual void Update(void);
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void);
		// 设置算法对象
		virtual void SetTrajectory(ITrajectory* pITrajectory) ;

	protected:
		// 初始化渲染体
		bool InitDrawabel(void);

		// 获得顶点
		osg::Vec3Array* GetVertexArrays(ITrajectory* pITrajectory) const;

	private:
		osg::Geode* m_pGeode;
		bool m_bUpdate;

		ITrajectory* m_pITrajectory;
	};
}


#endif // !_TRAJECTLINEDRAWABLE_H_