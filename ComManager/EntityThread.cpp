
#include "../../Public/VRSoft.h"
#include "EntityThread.h"
#include "SimManager.h"

namespace VR_Soft
{
	CEntityThread::CEntityThread(void)
	{
	}


	CEntityThread::~CEntityThread(void)
	{
	}


	// �����߳�
	void CEntityThread::Run(void)
	{
		// ������Ϣ
		IMessageManager::GetInstance().DispatchDelayedMessages();

		// ���÷���ʱ��
		((CSimManager*)(ISimManager::GetInstancePtr()))->Frame();
	}

}
