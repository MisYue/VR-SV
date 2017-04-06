/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨迹实体接口			                                        */
/* 时间： 2015-08-04                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ITRAJECTORYENTITY_H_
#define _PUBLIC_ITRAJECTORYENTITY_H_

#include <vector>

namespace VR_Soft
{
	class ITrajectoryEntity : public CEntityBaseImp<IEntityBase>
	{
	public: 
		// 析构函数
		virtual ~ITrajectoryEntity(void) { }
		// 设置算法策略
		virtual void SetTrajectory(ITrajectory* pITrajectory) = 0;
		// 获得算法策略
		virtual ITrajectory* GetTrajectory(void) = 0;
		// 生成轨道
		virtual void Generate(void) = 0;
	};
	
}

#endif // _PUBLIC_ITRAJECTORYENTITY_H_