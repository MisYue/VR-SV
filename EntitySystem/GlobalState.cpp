#include "../../Public/VRSoft.h"
#include "GlobalState.h"

namespace VR_Soft
{
	CGlobalState::CGlobalState(void)
	{
	}


	CGlobalState::~CGlobalState(void)
	{
	}

	// 进入状态
	void VR_Soft::CGlobalState::Enter(IEntityBase* pEntityBase)
	{

	}

	// 执行状态
	void CGlobalState::Execute(IEntityBase* pEntityBase)
	{

	}
	
	// 离开状态
	void CGlobalState::Exit(IEntityBase* pEntityBase)
	{

	}

	// 消息处理
	bool CGlobalState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{

		return (true);
	}

}
