/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨迹渲染管理基类		                                        */
/* 时间： 2016-03-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IDRAWTRAJECTORYATTRIBUTE_H_
#define _PUBLICE_IDRAWTRAJECTORYATTRIBUTE_H_

namespace VR_Soft
{
	class ITrajectory;

	class IDrawTrajectoryAttribute : public IDrawAttribute
	{
	public:
		// 析构函数
		virtual ~IDrawTrajectoryAttribute(void) { }
		// 设置轨迹
		virtual void SetTrajectory(ITrajectory* pITrajectory) = 0;
		// 获得轨迹
		virtual ITrajectory* GetTrajectory(void) const = 0;	
	};
}

#endif // ! _PUBLICE_IDRAWTRAJECTORYATTRIBUTE_H_