/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  仿真管理类                                                    */
/* 时间： 2016-04-08                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SIMMANAGER_H_
#define _SIMMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CSimManager : public ISimManager
	{
	public:
		// 构造函数
		CSimManager(void);
		// 析构函数
		virtual ~CSimManager(void);

		// 设置仿真开始时间
		virtual void SetBeginTime(const CDateTime& dtStart);
		// 设置结束时间
		virtual void SetEndTime(const CDateTime& dtStop) ;
		// 获得仿真开始时间
		virtual CDateTime GetStartTime(void) const ;
		// 获得结束时间
		virtual CDateTime GetEndTime( void) const;
		// 设置开始时间和结束时间
		virtual void SetSimTimRange(const CDateTime& dtStart, const CDateTime& dtStop);
		// 获得开始时间和结束时间
		virtual void GetSimTimRange(CDateTime& dtStart, CDateTime& dtStop) const ;
		// 设置时间指令
		virtual void SetSimCmd(SimCmd simCmd) ;
		// 获得仿真指令
		virtual SimCmd  GetSimCmd(void) const ;
		// 设置时间步长
		virtual void SetTimeStep(int nStep) ;
		// 获得时间步长
		virtual int GetTimeStep(void) const ;
		// 获取仿真时间
		virtual const CDateTime& GetSimTime(void) const ;
		// 仿真时间跳转
		virtual bool JumpSimTime(const CDateTime& dt) ;

	public:
		// 每一帧运行
		void Frame(void);

	protected:
		enum
		{
			RUN = 1,
			PUSE = 2
		};

	private:
		CDateTime m_dtBengin; // 开始时间
		CDateTime m_dtStop; // 结束时间
		CDateTime m_dtSim; // 仿真时间
		double m_dSimStep; // 步长
		double m_dSimMult; // 仿真倍数
		int m_nFlag; // 指令标志
		SimCmd m_simCmd;
		double m_dLoopStep; // 循环步长
		Timer_t m_dLastTicks; // 上一次的时间数
	};
}


#endif // ! _SIMMANAGER_H_