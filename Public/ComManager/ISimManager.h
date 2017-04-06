/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  仿真管理接口			                                        */
/* 时间： 2015-08-31                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ISIMMANAGER_H_
#define _PUBLICE_ISIMMANAGER_H_

namespace VR_Soft
{
	class VRSOFT_DLL ISimManager : public CSingleton<ISimManager>
	{
	public:
		// 枚举命令
		enum SimCmd
		{
			Start, // 引擎启动
			Pause, // 引擎暂停
			Accelerate, // 加速
			Decelerate, // 减速
			Stop, // 停止
			Reset // 重置
		};

	public:
		virtual ~ISimManager() { }
		// 设置仿真开始时间
		virtual void SetBeginTime(const CDateTime& dtStart) = 0;
		// 设置结束时间
		virtual void SetEndTime(const CDateTime& dtStop) = 0;
		// 获得仿真开始时间
		virtual CDateTime GetStartTime(void) const = 0 ;
		// 获得结束时间
		virtual CDateTime GetEndTime(void) const = 0;
		// 设置开始时间和结束时间
		virtual void SetSimTimRange(const CDateTime& dtStart, const CDateTime& dtStop) = 0;
		// 获得开始时间和结束时间
		virtual void GetSimTimRange(CDateTime& dtStart, CDateTime& dtStop) const = 0;
		// 设置时间指令
		virtual void SetSimCmd(SimCmd simCmd) = 0 ;
		// 获得仿真指令
		virtual SimCmd  GetSimCmd(void) const = 0 ;
		// 设置时间步长
		virtual void SetTimeStep(int nStep) = 0 ;
		// 获得时间步长
		virtual int GetTimeStep(void) const = 0 ;
		// 获取仿真时间
		virtual const CDateTime& GetSimTime(void) const = 0 ;
		// 仿真时间跳转
		virtual bool JumpSimTime(const CDateTime& dt) = 0;
	};
}

#endif // _PUBLICE_ISIMMANAGER_H_