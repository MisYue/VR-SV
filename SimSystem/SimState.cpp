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
	// ִ��״̬
	void CSimStateBase::Execute(IEntityBase* pEntityBase)
	{
		// ����ʱ��
		LARGE_INTEGER liFrequency,t1,t2;
		t2.QuadPart=0;
		// ����ÿһ֡������ʱ����
		double dCalAccumlateTime=0;

		QueryPerformanceFrequency(&liFrequency);
		QueryPerformanceCounter(&t1);//���㺯�������¿�ʼ��ʱ

		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);
		// �������
		IAttribute* pIAttribute = pSimTime->GetAttribute();
		
		// ���״̬
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
		
		// ����ǽ��ʱ��

		// ����߼�ʱ��
		double dSimLogicTime = pIAttribute->GetItem("SimLogicTime")->GetValueToDobule();
		// ǽ��ʱ��
		double dWallTime = pIAttribute->GetItem("WallTime")->GetValueToDobule();
		// ���ǽ����ʼʱ��
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

	// ����״̬
	void CSimRunState::Enter(IEntityBase* pEntityBase)
	{
		// ���ʵ��
		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);

		IAttribute* pIAttribute = pSimTime->GetAttribute();
		// ��÷��沽��
		m_dLoopStep = pIAttribute->GetItem("LogicSimStep")->GetValueToDobule();


	}

	// ִ��״̬
	void CSimRunState::Execute(IEntityBase* pEntityBase)
	{
		// ����ʱ��
		LARGE_INTEGER liFrequency,t1,t2;
		// ����ÿһ֡������ʱ����
		double dCalAccumlateTime=0;

		QueryPerformanceFrequency(&liFrequency);
		QueryPerformanceCounter(&t1);//���㺯�������¿�ʼ��ʱ

		t2.QuadPart = 0;

		// ������Զ���
		IAttribute* pIAttribute = pEntityBase->GetAttribute();
		if (NULL == pIAttribute)
		{
			return;
		}

		// ����߼�ʱ��
		double dSimLogicTime = pIAttribute->GetItem("SimLogicTime")->GetValueToDobule();

		// �����߼�ʱ��
		0 != dSimLogicTime ? m_dOverheadTime = (double)(t1.QuadPart \
			- t2.QuadPart)*1000/(double)liFrequency.QuadPart : m_dOverheadTime = 0;

		// ��÷��沽��
		double dLogicSimStep = pIAttribute->GetItem("LogicSimStep")->GetValueToDobule();

		// ����ģ��
		UpdateEntity(dSimLogicTime);

		// ʱ�����Ƶ���һ������
		dSimLogicTime += dLogicSimStep;

		// ���֡��
		int nFrame = pIAttribute->GetItem("Frame")->GetValueToInt();
		++nFrame;
		// ���û�ȥ
		pIAttribute->GetItem("Frame")->SetValue(nFrame);

		// ѭ�����м���
		do 
		{
			QueryPerformanceCounter(&t2);
			dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	

			// ���ǽ����ʼʱ��
			LONGLONG dWallStartTime;
			CanvartType<LONGLONG>( pIAttribute->GetItem("WllStartTime"), dWallStartTime);

			//2�ͷ�CPU�Ż�1
			for (;m_dLoopStep - dCalAccumlateTime >= 100;)
			{
				// ��ȡǽ��ʱ��
				double dWallTime = pIAttribute->GetItem("WallTime")->GetValueToDobule();
				
				(0==dSimLogicTime)?
					(dWallTime=0):(dWallTime=(double)(t2.QuadPart - dWallStartTime)*1000/liFrequency.QuadPart);
				pIAttribute->GetItem("WallTime")->SetValue(dWallTime);

				// ���߳�����
				boost::this_thread::sleep(boost::posix_time::milliseconds(80));

				QueryPerformanceCounter(&t2);
				dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	
			}

			//3�ͷ�CPU�Ż�2
			for (;m_dLoopStep - dCalAccumlateTime >= 25.5;)
			{
				// ��ȡǽ��ʱ��
				double dWallTime = pIAttribute->GetItem("WallTime")->GetValueToDobule();

				(0 == dSimLogicTime)?
					(dWallTime=0):(dWallTime=(double)(t2.QuadPart-dWallStartTime)*1000/liFrequency.QuadPart);
				pIAttribute->GetItem("WallTime")->SetValue(dWallTime);

				// ���߳�����
				boost::this_thread::sleep(boost::posix_time::milliseconds(15));

				QueryPerformanceCounter(&t2);
				dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	
			}

		} while (dCalAccumlateTime<=m_dLoopStep - m_dOverheadTime);

		// �����߼�ʱ��
		pIAttribute->GetItem("SimLogicTime")->SetValue(dSimLogicTime);

		CSimStateBase::Execute(pEntityBase);

	}

	// �뿪״̬
	void CSimRunState::Exit(IEntityBase* pEntityBase)
	{

	}

	// ��Ϣ����
	bool CSimRunState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (true);
	}

	// ����ģ��
	void CSimRunState::UpdateEntity(double dSimLogicTime)
	{
		// ������Ϣ
		IMessageManager* pIMssageMgr = CComManagerImp::GetComponent<IMessageManager>(INSTANCE_NAME_MESSAGESYSTEM);
		if (NULL != pIMssageMgr)
		{
			pIMssageMgr->DispatchDelayedMessages();
		}

		// ����ģ��ѭ��
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

	// ����״̬
	void CSimEndState::Enter(IEntityBase* pEntityBase)
	{
		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);
		pSimTime->SetState(this);

	}

	// ִ��״̬
	void CSimEndState::Execute(IEntityBase* pEntityBase)
	{
		
		// ���߳�����
		boost::this_thread::sleep(boost::posix_time::milliseconds(300));

		// ���״̬
		CSimStateBase::Execute(pEntityBase);
	}

	// �뿪״̬
	void CSimEndState::Exit(IEntityBase* pEntityBase)
	{

	}

	// ��Ϣ����
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

	// ����״̬
	void CSimPauseState::Enter(IEntityBase* pEntityBase)
	{
		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);
		pSimTime->SetState(this);

	}

	// ִ��״̬
	void CSimPauseState::Execute(IEntityBase* pEntityBase)
	{
	
		// ���߳�����
		boost::this_thread::sleep(boost::posix_time::milliseconds(99));
		CSimStateBase::Execute(pEntityBase);
	}

	// �뿪״̬
	void CSimPauseState::Exit(IEntityBase* pEntityBase)
	{

	}

	// ��Ϣ����
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

	// ����״̬
	void CSimExitState::Enter(IEntityBase* pEntityBase)
	{
		CSimTime* pSimTime = dynamic_cast<CSimTime*>(pEntityBase);
		pSimTime->SetState(this);

	}

	// ִ��״̬
	void CSimExitState::Execute(IEntityBase* pEntityBase)
	{
		CSimStateBase::Execute(pEntityBase);
		// �˳��߳�
		((CSimSystem*)ISimManager::GetInstancePtr())->GetSimThreadEngine()->Join();
	}

	// �뿪״̬
	void CSimExitState::Exit(IEntityBase* pEntityBase)
	{

	}

	// ��Ϣ����
	bool CSimExitState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (true);
	}
	*/

}

