#include "../../Public/VRSoft.h"
#include "SimManager.h"

namespace VR_Soft
{
	// ���캯��
	CSimManager::CSimManager(void)
		:m_dLoopStep(1), m_dSimStep(1), m_dSimMult(1.0),m_simCmd(ISimManager::Stop)
	{
	}

	// ��������
	CSimManager::~CSimManager(void)
	{
	}

	// ���÷��濪ʼʱ��
	void CSimManager::SetBeginTime(const CDateTime& dtStart)
	{
		m_dtBengin = dtStart;
		m_dtSim = m_dtBengin;
	}

	// ���ý���ʱ��
	void CSimManager::SetEndTime(const CDateTime& dtStart)
	{
		m_dtStop = dtStart;
	}

	// ��÷��濪ʼʱ��
	CDateTime CSimManager::GetStartTime(void) const
	{
		return (m_dtBengin);
	}

	// ��ý���ʱ��
	CDateTime CSimManager::GetEndTime(void) const
	{
		return (m_dtStop);
	}

	// ���ÿ�ʼʱ��ͽ���ʱ��
	void CSimManager::SetSimTimRange(const CDateTime& dtStart, const CDateTime& dtStop)
	{
		SetBeginTime(dtStart);
		SetEndTime(dtStop);
	}

	// ��ÿ�ʼʱ��ͽ���ʱ��
	void CSimManager::GetSimTimRange(CDateTime& dtStart, CDateTime& dtStop) const
	{
		dtStart = m_dtBengin;
		dtStop = m_dtStop;
	}

	// ����ʱ��ָ��
	void CSimManager::SetSimCmd(SimCmd simCmd)
	{
		m_simCmd = simCmd;

		switch(simCmd)
		{
		case ISimManager::Start:
			{
				m_nFlag = RUN;
				m_dLastTicks = ITimer::GetInstance().Tick();

				// ����ָ��
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

	// ��÷���ָ��
	ISimManager::SimCmd CSimManager::GetSimCmd(void) const
	{
		return (m_simCmd);
	}

	// ����ʱ�䲽��
	void CSimManager::SetTimeStep(int nStep)
	{

	}

	// ���ʱ�䲽��
	int CSimManager::GetTimeStep(void) const
	{
		return (m_dSimMult);
	}

	// ��ȡ����ʱ��
	const CDateTime& CSimManager::GetSimTime(void) const
	{
		return (m_dtSim);
	}

	// ����ʱ����ת
	bool CSimManager::JumpSimTime(const CDateTime& dt)
	{
		// �ж�ʱ���Ƿ�����Ч��Χ��
		if (dt < m_dtBengin || dt > m_dtStop)
		{
			ILogManager::GetInstance().SetLogMessage("ʱ�䷶Χ����ȷ", ERROR_NOT_FIND);
			
			return (false);
		}

		m_dtSim = dt;
		return (true);
	}

	// ÿһ֡����
	void CSimManager::Frame(void)
	{
		if ((m_nFlag != RUN) /*|| (m_dtSim >= m_dtStop)*/ )
		{
			// �߳����� 
			boost::this_thread::sleep(boost::posix_time::milliseconds(600));

			// ��ѯ��ǰ��ʵ��
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
		
		// ����ģ��ѭ��
		IEntityManager::GetInstance().EntityUpdate(m_dtSim);

		// ��������
		IActionManager::GetInstance().Execute(m_dtSim);

		// ���Ʒ��沽��
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


		// ���·���ʱ��
		m_dtSim = m_dtSim.AddMillisecond(m_dSimStep);
		// ת����������ʱ��
		m_dtSim.ToJulian();
	}
}
