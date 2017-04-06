#include <sys/types.h>
#include <fcntl.h>
#include <windows.h>
#include <winbase.h>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "../../Public/VRSoft.h"
#include "../../Public/SimSystem/SimSystem.h"
#include "SimSingleThreadEngine.h"
#include "SimSystem.h"
#include "SimTime.h"
#include "SimState.h"


namespace VR_Soft
{
/*
	// 执行状态
	void CSimStateBase::Execute(IEntityBase* pEntityBase)
	{
		// 定义时间
		LARGE_INTEGER liFrequency,t1,t2;
		t2.QuadPart=0;
		// 计算每一帧运用了时间数
		double dCalAccumlateTime=0;

		QueryPerformanceFrequency(&liFrequency);
		QueryPerformanceCounter(&t1);//计算函数，从新开始计时

		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);
		// 获得属性
		IAttribute* pIAttribute = pSimTime->GetAttribute();
		
		// 获得状态
		//VRVariant var = pIAttribute->GetItem("SimCmd")->GetVariant();
		ISimManager::SimCmd simCmd ;
		CanvartType<ISimManager::SimCmd>(pIAttribute->GetItem("SimCmd"), simCmd);
		//	= boost::any_cast<ISimManager::SimCmd>(var);
		if (simCmd != m_curSimCmd)
		{
			switch(simCmd)
			{
			case ISimManager::Start:
				{
					pSimTime->SetState(new CSimRunState);
					m_curSimCmd = simCmd;
				}
				break;

			case ISimManager::Pause:
				{
					pSimTime->SetState(new CSimPauseState);
					m_curSimCmd = simCmd;
				}
				break;

			case ISimManager::Accelerate:
				{

				}
				break;
			}
			

		}
		
		// 更新墙钟时间

		// 获得逻辑时间
		double dSimLogicTime = pIAttribute->GetItem("SimLogicTime")->GetValueToDobule();
		// 墙钟时间
		double dWallTime = pIAttribute->GetItem("WallTime")->GetValueToDobule();
		// 获得墙钟起始时间
		long long dWllStartTime ;
		CanvartType<long long>(pIAttribute->GetItem("WllStartTime"), dWllStartTime);
		(0 == dSimLogicTime)?
			(dWallTime=0):(dWallTime=(double)(t2.QuadPart-dWllStartTime)*1000/liFrequency.QuadPart);
		pIAttribute->GetItem("WallTime")->SetValue(dWallTime, false);
		
	}

	CSimRunState::CSimRunState(void)
		:m_dOverheadTime(0),m_dLoopStep(1)
	{
	}


	CSimRunState::~CSimRunState(void)
	{
	}

	// 进入状态
	void CSimRunState::Enter(IEntityBase* pEntityBase)
	{
		// 获得实体
		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);

		IAttribute* pIAttribute = pSimTime->GetAttribute();
		// 获得仿真步长
		m_dLoopStep = pIAttribute->GetItem("LogicSimStep")->GetValueToDobule();


	}

	// 执行状态
	void CSimRunState::Execute(IEntityBase* pEntityBase)
	{
		// 定义时间
		LARGE_INTEGER liFrequency,t1,t2;
		// 计算每一帧运用了时间数
		double dCalAccumlateTime=0;

		QueryPerformanceFrequency(&liFrequency);
		QueryPerformanceCounter(&t1);//计算函数，从新开始计时

		t2.QuadPart = 0;

		// 获得属性对象
		IAttribute* pIAttribute = pEntityBase->GetAttribute();
		if (NULL == pIAttribute)
		{
			return;
		}

		// 获得逻辑时间
		double dSimLogicTime = pIAttribute->GetItem("SimLogicTime")->GetValueToDobule();

		// 计算逻辑时间
		0 != dSimLogicTime ? m_dOverheadTime = (double)(t1.QuadPart \
			- t2.QuadPart)*1000/(double)liFrequency.QuadPart : m_dOverheadTime = 0;

		// 获得仿真步长
		double dLogicSimStep = pIAttribute->GetItem("LogicSimStep")->GetValueToDobule();

		// 更新模型
		UpdateEntity(dSimLogicTime);

		// 时间推移到下一个步长
		dSimLogicTime += dLogicSimStep;

		// 获得帧数
		int nFrame = pIAttribute->GetItem("Frame")->GetValueToInt();
		++nFrame;
		// 设置回去
		pIAttribute->GetItem("Frame")->SetValue(nFrame);

		// 循环进行计算
		do 
		{
			QueryPerformanceCounter(&t2);
			dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	

			// 获得墙钟起始时间
			LONGLONG dWallStartTime;
			CanvartType<LONGLONG>( pIAttribute->GetItem("WllStartTime"), dWallStartTime);

			//2释放CPU优化1
			for (;m_dLoopStep - dCalAccumlateTime >= 100;)
			{
				// 获取墙钟时间
				double dWallTime = pIAttribute->GetItem("WallTime")->GetValueToDobule();
				
				(0==dSimLogicTime)?
					(dWallTime=0):(dWallTime=(double)(t2.QuadPart - dWallStartTime)*1000/liFrequency.QuadPart);
				pIAttribute->GetItem("WallTime")->SetValue(dWallTime);

				// 让线程休眠
				boost::this_thread::sleep(boost::posix_time::milliseconds(80));

				QueryPerformanceCounter(&t2);
				dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	
			}

			//3释放CPU优化2
			for (;m_dLoopStep - dCalAccumlateTime >= 25.5;)
			{
				// 获取墙钟时间
				double dWallTime = pIAttribute->GetItem("WallTime")->GetValueToDobule();

				(0 == dSimLogicTime)?
					(dWallTime=0):(dWallTime=(double)(t2.QuadPart-dWallStartTime)*1000/liFrequency.QuadPart);
				pIAttribute->GetItem("WallTime")->SetValue(dWallTime);

				// 让线程休眠
				boost::this_thread::sleep(boost::posix_time::milliseconds(15));

				QueryPerformanceCounter(&t2);
				dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	
			}

		} while (dCalAccumlateTime<=m_dLoopStep - m_dOverheadTime);

		// 更新逻辑时间
		pIAttribute->GetItem("SimLogicTime")->SetValue(dSimLogicTime);

		CSimStateBase::Execute(pEntityBase);

	}

	// 离开状态
	void CSimRunState::Exit(IEntityBase* pEntityBase)
	{

	}

	// 消息处理
	bool CSimRunState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (true);
	}

	// 更新模型
	void CSimRunState::UpdateEntity(double dSimLogicTime)
	{
		// 调用消息
		IMessageManager* pIMssageMgr = CComManagerImp::GetComponent<IMessageManager>(INSTANCE_NAME_MESSAGESYSTEM);
		if (NULL != pIMssageMgr)
		{
			pIMssageMgr->DispatchDelayedMessages();
		}

		// 调用模型循环
		IEntityComposite* pIEntityCmp = IComManager::GetInstance().GetEntityComposite();
		if (NULL != pIEntityCmp)
		{
			pIEntityCmp->EntityUpdate(dSimLogicTime);
		}
		
	}

	/////////////////////////////////end state/////////////////////////////////////////
	CSimEndState::CSimEndState(void)
	{
	}


	CSimEndState::~CSimEndState(void)
	{
	}

	// 进入状态
	void CSimEndState::Enter(IEntityBase* pEntityBase)
	{
		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);
		pSimTime->SetState(this);

	}

	// 执行状态
	void CSimEndState::Execute(IEntityBase* pEntityBase)
	{
		
		// 让线程休眠
		boost::this_thread::sleep(boost::posix_time::milliseconds(300));

		// 获得状态
		CSimStateBase::Execute(pEntityBase);
	}

	// 离开状态
	void CSimEndState::Exit(IEntityBase* pEntityBase)
	{

	}

	// 消息处理
	bool CSimEndState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (true);
	}

	/////////////////////////////////pause state/////////////////////////////////////////
	CSimPauseState::CSimPauseState(void)
	{
	}


	CSimPauseState::~CSimPauseState(void)
	{
	}

	// 进入状态
	void CSimPauseState::Enter(IEntityBase* pEntityBase)
	{
		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);
		pSimTime->SetState(this);

	}

	// 执行状态
	void CSimPauseState::Execute(IEntityBase* pEntityBase)
	{
	
		// 让线程休眠
		boost::this_thread::sleep(boost::posix_time::milliseconds(99));
		CSimStateBase::Execute(pEntityBase);
	}

	// 离开状态
	void CSimPauseState::Exit(IEntityBase* pEntityBase)
	{

	}

	// 消息处理
	bool CSimPauseState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (true);
	}

	//////////////////////////////exit state////////////////////////////////////////////
	CSimExitState::CSimExitState(void)
	{
	}


	CSimExitState::~CSimExitState(void)
	{
	}

	// 进入状态
	void CSimExitState::Enter(IEntityBase* pEntityBase)
	{
		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);
		pSimTime->SetState(this);

	}

	// 执行状态
	void CSimExitState::Execute(IEntityBase* pEntityBase)
	{
		CSimStateBase::Execute(pEntityBase);
		// 退出线程
		((CSimSystem*)ISimManager::GetInstancePtr())->GetSimThreadEngine()->Join();
	}

	// 离开状态
	void CSimExitState::Exit(IEntityBase* pEntityBase)
	{

	}

	// 消息处理
	bool CSimExitState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (true);
	}
	*/

}

