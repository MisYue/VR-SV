/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨迹渲染管理基类		                                        */
/* 时间： 2016-03-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IDRAWTRAJECTORYMANAGER_H_
#define _PUBLICE_IDRAWTRAJECTORYMANAGER_H_

namespace VR_Soft
{
	class IDrawTrajectory;

	class IDrawTrajectoryManager
	{
	public:
		// 析构函数
		virtual ~IDrawTrajectoryManager(void) { }
		// 添加轨迹
		virtual void AddTrajectory(IDrawTrajectory* pIDrawTrajectory) = 0;
		// 移除轨迹
		// 添加轨迹
		virtual void RemoveTrajectory(IDrawTrajectory* pIDrawTrajectory) = 0;
		// 需要重新绘制
		virtual void Update(void) = 0;
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void) = 0;
		
	};
}

#endif // ! _PUBLICE_IDRAWTRAJECTORYMANAGER_H_