/************************************************************************
 作者： LJ                                                            
 用途:  仿真时间运行器，进行实时的时间运行                     
 时间： 2015-10-21                                                    
 修改时间:                                                            
************************************************************************/

#ifndef _SIMSINGLETHREADENGINE_H_
#define _SIMSINGLETHREADENGINE_H_

#pragma once

namespace VR_Soft
{
	class CSimTime;

	class CSimSingleThreadEngine : public CVRSoftThread
	{
	public:
		// 构造函数
		explicit CSimSingleThreadEngine(CSimTime* pSimTime);
		// 析构函数
		virtual ~CSimSingleThreadEngine(void);
		// 直接运行
		virtual void RunSimple(void);

	protected:
		// 运行线程
		virtual void Run(void);

	protected:
		// 获得仿真指令
		void ProcessSimCmd(void);

	private:
		CSimTime* m_pSimTime; // 仿真时间
	};
}


#endif // _SIMSINGLETHREADENGINE_H_