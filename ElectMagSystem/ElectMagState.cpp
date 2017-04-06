#include "../../Public/VRSoft.h"
#include "../../Public/ElectMagSystem/ElectMagSystem.h"
#include "ElectMagState.h"

namespace VR_Soft
{
	/************************************************************************/
	/*                            开机状态                                  */
	/************************************************************************/
	CElectMagOnState::CElectMagOnState(void):m_vRadius(1.0,1.0,1.0),m_vRadiusUp(0.1, 0.1, 0.1)
	{
	}


	CElectMagOnState::~CElectMagOnState(void)
	{
	}

	// 进入状态
	void CElectMagOnState::Enter(IEntityBase* pEntityBase)
	{
		// 获得雷达半径
// 		IRadar* pIRadar = dynamic_cast<IRadar*>(pEntityBase);
// 		if (NULL == pIRadar)
// 		{
// 			return;
// 		}
// 
// 		m_vRadius = pIRadar->GetAttribute()->GetItem("缩放")->GetValueToVec3d();
	}

	// 执行状态
	void CElectMagOnState::Execute(IEntityBase* pEntityBase)
	{
		//// 获得雷达半径
		//IRadar* pIRadar = dynamic_cast<IRadar*>(pEntityBase);
		//if (NULL == pIRadar)
		//{
		//	return;
		//}

		//if (m_vRadius < m_vRadiusUp)
		//{
		//	pIRadar->GetAttribute()->GetItem("缩放")->SetValue(m_vRadius);

		//	// 切换状态到扫描状态
		//	pIRadar->GetStateMachine()->ChangeState(new CElectMagScanState);
		//	
		//}

		//m_vRadiusUp += osg::Vec3(0.1f, 0.1f, 0.1f);
		//pIRadar->GetAttribute()->GetItem("缩放")->SetValue(m_vRadiusUp);
	}

	// 离开状态
	void CElectMagOnState::Exit(IEntityBase* pEntityBase)
	{

	}

	// 消息处理
	bool CElectMagOnState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (false);
	}

	/************************************************************************/
	/*                            扫描状态                                  */
	/************************************************************************/
	CElectMagScanState::CElectMagScanState(void)
	{
	}


	CElectMagScanState::~CElectMagScanState(void)
	{
	}

	// 进入状态
	void CElectMagScanState::Enter(IEntityBase* pEntityBase)
	{
		
	}

	// 执行状态
	void CElectMagScanState::Execute(IEntityBase* pEntityBase)
	{
		// 获得雷达半径
		IRadar* pIRadar = dynamic_cast<IRadar*>(pEntityBase);
		if (NULL == pIRadar)
		{
			return;
		}

//		pIRadar->ScanRender();
	}

	// 离开状态
	void CElectMagScanState::Exit(IEntityBase* pEntityBase)
	{

	}

	// 消息处理
	bool CElectMagScanState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (false);
	}
}

