/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨迹渲染管理			                                        */
/* 时间： 2015-08-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _DRAWTRAJECOTORYMANAGER_H_
#define _DRAWTRAJECOTORYMANAGER_H_ 

#pragma once

#include <vector>
#include <osg/Group>

namespace VR_Soft
{
	class CDrawTrajectoryManager : public IDrawTrajectoryManager
	{
	public:
		// 构造函数
		CDrawTrajectoryManager(void);
		// 析构函数
		virtual ~CDrawTrajectoryManager(void);

	public:
		// 添加轨迹
		virtual void AddTrajectory(IDrawTrajectory* pIDrawTrajectory) ;
		// 移除轨迹
		virtual void RemoveTrajectory(IDrawTrajectory* pIDrawTrajectory) ;
		// 需要重新绘制
		virtual void Update(void) ;
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void);

	protected:
		// 清空
		void Clear(void);

	protected:
		typedef std::vector<IDrawTrajectory*> ListDrawTrajectorys;

	private:
		osg::Group* m_pRoot;

		ListDrawTrajectorys m_listDrawTrajectorys;


	};

}

#endif // !_DRAWTRAJECOTORYMANAGER_H_