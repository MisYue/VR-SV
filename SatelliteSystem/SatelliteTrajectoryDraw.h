/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  卫星实体														*/
/* 时间： 2016-04-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SATELLITETRAJECTORYDRAW_H_
#define _SATELLITETRAJECTORYDRAW_H_

#pragma once

#include <osg/Geode>
#include <osg/MatrixTransform>

namespace VR_Soft
{
	class CSatalliteTrajectoryDraw : public IDrawTrajectory
	{
	public:
		// 构造函数
		explicit CSatalliteTrajectoryDraw();
		// 析构函数
		~CSatalliteTrajectoryDraw(void);

	public:
		// 更新
		virtual void Update(void);
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void);
		// 设置算法对象
		virtual void SetTrajectory(ITrajectory* pITrajectory) ;

	public:
		// 更新旋转矩阵
		void UpdateMatrix(double dt);
	protected:
		// 初始化渲染体
		bool InitDrawabel(void);

		// 获得顶点
		osg::Vec3Array* GetVertexArrays(ITrajectory* pITrajectory) const;


	private:
		osg::Geode* m_pGeode;
		bool m_bUpdate;
		osg::MatrixTransform* m_pMt;

		ITrajectory* m_pITrajectory;
	};

}

#endif // !_SATELLITETRAJECTORYDRAW_H_