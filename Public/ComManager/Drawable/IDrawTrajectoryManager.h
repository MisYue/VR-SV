/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨迹渲染类基类		                                        */
/* 时间： 2016-03-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IDRAWTRAJECTORY_H_
#define _PUBLICE_IDRAWTRAJECTORY_H_

namespace VR_Soft
{
	class ITrajectory;

	class IDrawTrajectory 
	{
	public:
		// 析构函数
		virtual ~IDrawTrajectory(void) { }
		// 需要重新绘制
		virtual void Update(void) = 0;
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void) = 0;
		// 设置算法对象
		virtual void SetTrajectory(ITrajectory* pITrajectory) = 0;
		
	};
}

#endif // ! _PUBLICE_IDRAWTRAJECTORY_H_