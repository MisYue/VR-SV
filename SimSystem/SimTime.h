/************************************************************************
 作者： LJ                                                            
 用途:  仿真时间属性控制类                   
 时间： 2015-10-21                                                    
 修改时间:                                                            
************************************************************************/

#ifndef _SIMTIME_H_
#define  _SIMTIME_H_

#pragma once

const int PROCESSNAMELEN = 256;

namespace VR_Soft
{
	class CSimTime : public CSingleton<CSimTime>
	{
	public:
		enum SimState
		{
			SimStateRun = 0, // 仿真运行
			SimStatePause = 1, // 暂停仿真
			SimStateStop = 2 // 结束仿真
		};

	public:
		// 构造函数
		CSimTime(void);
		// 析构函数
		virtual ~CSimTime(void);

	public:
		// 开始仿真
		void Start(void);
		// 仿真暂停
		void Pause(void);
		// 加速
		void Acclerate(void);
		// 减速
		void Decelerate(void);
		// 停止
		void Stop(void);
		// 设置开始时间
		void SetStartTime(double dStartTime);
		// 设置开始时间
		void SetStartTime(int nYear, int nMonth, int nDay, \
				int nHour, int nMin, double dSec);
		// 设置结束时间
		void SetEndTime(double )
		// 设置结束时间
		void SetEndTime(int nYear, int nMonth, int nDay, \
			int nHour, int nMin, double dSec);
		// 获得仿真时间
		TIME_T GetSimulationTime(void) const ;
		// 返回tm系统时间
		struct tm* GetSimulationTimeTm(void) const ;
		// 系统运行时间
		TIME_T GetTick() const ;
		// 操作系统运行时间
		TIME_T GetSystemTick() const =;
		// 获得时分秒 格式（yyyy-MM-dd h:m:s.sss）
		VRString GetSimulationString(void) const ;
		// 操作系统运行时间 获得时分秒 格式（yyyy-MM-dd h:m:s.sss）
		VRString GetSystemTickString() const ;

	private:
		TIME_T m_dStartTime; // 开始时间
		TIME_T m_dEndTimer; // 结束时间		
	};
}
#endif // ! _SIMTIME_H_