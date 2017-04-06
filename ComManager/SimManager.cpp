#include "../../Public/VRSoft.h"
#include "SimManager.h"

namespace VR_Soft
{
	// 构造函数
	CSimManager::CSimManager(void)
		:m_dLoopStep(1), m_dSimStep(1), m_dSimMult(1.0),m_simCmd(ISimManager::Stop)
	{
	}

	// 析构函数
	CSimManager::~CSimManager(void)
	{
	}

	// 设置仿真开始时间
	void CSimManager::SetBeginTime(const CDateTime& dtStart)
	{
		m_dtBengin = dtStart;
		m_dtSim = m_dtBengin;
	}

	// 设置结束时间
	void CSimManager::SetEndTime(const CDateTime& dtStart)
	{
		m_dtStop = dtStart;
	}

	// 获得仿真开始时间
	CDateTime CSimManager::GetStartTime(void) const
	{
		return (m_dtBengin);
	}

	// 获得结束时间
	CDateTime CSimManager::GetEndTime(void) const
	{
		return (m_dtStop);
	}

	// 设置开始时间和结束时间
	void CSimManager::SetSimTimRange(const CDateTime& dtStart, const CDateTime& dtStop)
	{
		SetBeginTime(dtStart);
		SetEndTime(dtStop);
	}

	// 获得开始时间和结束时间
	void CSimManager::GetSimTimRange(CDateTime& dtStart, CDateTime& dtStop) const
	{
		dtStart = m_dtBengin;
		dtStop = m_dtStop;
	}

	// 设置时间指令
	void CSimManager::SetSimCmd(SimCmd simCmd)
	{
		m_simCmd = simCmd;

		switch(simCmd)
		{
		case ISimManager::Start:
			{
				m_nFlag = RUN;
				m_dLastTicks = ITimer::GetInstance().Tick();

				// 设置指令
				IActionManager::GetInstance().Init();
			}
			break;

		case ISimManager::Pause:
			{
				m_nFlag = PUSE;
			}
			break;

		case ISimManager::Stop:
			{
				m_nFlag = PUSE;
				m_dtSim = m_dtBengin;
			}
			break;

		case ISimManager::Accelerate:
			{
				//m_dStep *= 2;
				if (m_dSimMult >= 8)
				{
					m_dSimStep *= 2;
				}
				else
				{
					m_dSimMult *= 2;
					m_dLoopStep = m_dSimStep / m_dSimMult;
				}
				
			}
			break;

		case ISimManager::Decelerate:
			{
				if (m_dSimMult >= 8)
				{
					m_dSimStep *= 0.5;
				}
				else
				{
					m_dSimMult *= 0.5;
					m_dLoopStep = m_dSimStep * m_dSimMult;
				}
				
			}
			break;

		case  ISimManager::Reset:
			{
				m_dtSim = m_dtBengin;
			}

		default:
			break;
		}
	}

	// 获得仿真指令
	ISimManager::SimCmd CSimManager::GetSimCmd(void) const
	{
		return (m_simCmd);
	}

	// 设置时间步长
	void CSimManager::SetTimeStep(int nStep)
	{

	}

	// 获得时间步长
	int CSimManager::GetTimeStep(void) const
	{
		return (m_dSimMult);
	}

	// 获取仿真时间
	const CDateTime& CSimManager::GetSimTime(void) const
	{
		return (m_dtSim);
	}

	// 仿真时间跳转
	bool CSimManager::JumpSimTime(const CDateTime& dt)
	{
		// 判断时间是否在有效范围内
		if (dt < m_dtBengin || dt > m_dtStop)
		{
			ILogManager::GetInstance().SetLogMessage("时间范围不正确", ERROR_NOT_FIND);
			
			return (false);
		}

		m_dtSim = dt;
		return (true);
	}

	// 每一帧运行
	void CSimManager::Frame(void)
	{
		if ((m_nFlag != RUN) /*|| (m_dtSim >= m_dtStop)*/ )
		{
			// 线程休眠 
			boost::this_thread::sleep(boost::posix_time::milliseconds(600));

			// 查询当前的实体
// 			IEntityBase* pIEntityBase = IAttributeManager::GetInstance().GetCurrentEntityBase();
// 			if (NULL == pIEntityBase)
// 			{
// 				return;
// 			}
// 
// 			pIEntityBase->EntityUpdate(m_dtSim);
// 
			return; 
		}

		m_dLastTicks = ITimer::GetInstance().Tick();
		
		// 调用模型循环
		IEntityManager::GetInstance().EntityUpdate(m_dtSim);

		// 更新命令
		IActionManager::GetInstance().Execute(m_dtSim);

		// 控制仿真步长
		Timer_t dLastTick = ITimer::GetInstance().Tick();
		double dCalAccumlateTime = ITimer::GetInstance().DeltaMil(m_dLastTicks, dLastTick);

		while (m_dLoopStep > dCalAccumlateTime)
		{
			if (m_dSimStep - dCalAccumlateTime > 15)
			{
				boost::this_thread::sleep(boost::posix_time::milliseconds(15));
			}
			
			dLastTick = ITimer::GetInstance().Tick();
			dCalAccumlateTime = ITimer::GetInstance().DeltaMil(m_dLastTicks, dLastTick);
		}


		// 更新仿真时间
		m_dtSim = m_dtSim.AddMillisecond(m_dSimStep);
		// 转换到儒略日时间
		m_dtSim.ToJulian();
	}
}
