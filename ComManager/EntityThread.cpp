
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


	// 运行线程
	void CEntityThread::Run(void)
	{
		// 调用消息
		IMessageManager::GetInstance().DispatchDelayedMessages();

		// 调用仿真时间
		((CSimManager*)(ISimManager::GetInstancePtr()))->Frame();
	}

}
