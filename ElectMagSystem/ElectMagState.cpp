#include "../../Public/VRSoft.h"
#include "../../Public/ElectMagSystem/ElectMagSystem.h"
#include "ElectMagState.h"

namespace VR_Soft
{
	/************************************************************************/
	/*                            ����״̬                                  */
	/************************************************************************/
	CElectMagOnState::CElectMagOnState(void):m_vRadius(1.0,1.0,1.0),m_vRadiusUp(0.1, 0.1, 0.1)
	{
	}


	CElectMagOnState::~CElectMagOnState(void)
	{
	}

	// ����״̬
	void CElectMagOnState::Enter(IEntityBase* pEntityBase)
	{
		// ����״�뾶
// 		IRadar* pIRadar = dynamic_cast<IRadar*>(pEntityBase);
// 		if (NULL == pIRadar)
// 		{
// 			return;
// 		}
// 
// 		m_vRadius = pIRadar->GetAttribute()->GetItem("����")->GetValueToVec3d();
	}

	// ִ��״̬
	void CElectMagOnState::Execute(IEntityBase* pEntityBase)
	{
		//// ����״�뾶
		//IRadar* pIRadar = dynamic_cast<IRadar*>(pEntityBase);
		//if (NULL == pIRadar)
		//{
		//	return;
		//}

		//if (m_vRadius < m_vRadiusUp)
		//{
		//	pIRadar->GetAttribute()->GetItem("����")->SetValue(m_vRadius);

		//	// �л�״̬��ɨ��״̬
		//	pIRadar->GetStateMachine()->ChangeState(new CElectMagScanState);
		//	
		//}

		//m_vRadiusUp += osg::Vec3(0.1f, 0.1f, 0.1f);
		//pIRadar->GetAttribute()->GetItem("����")->SetValue(m_vRadiusUp);
	}

	// �뿪״̬
	void CElectMagOnState::Exit(IEntityBase* pEntityBase)
	{

	}

	// ��Ϣ����
	bool CElectMagOnState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (false);
	}

	/************************************************************************/
	/*                            ɨ��״̬                                  */
	/************************************************************************/
	CElectMagScanState::CElectMagScanState(void)
	{
	}


	CElectMagScanState::~CElectMagScanState(void)
	{
	}

	// ����״̬
	void CElectMagScanState::Enter(IEntityBase* pEntityBase)
	{
		
	}

	// ִ��״̬
	void CElectMagScanState::Execute(IEntityBase* pEntityBase)
	{
		// ����״�뾶
		IRadar* pIRadar = dynamic_cast<IRadar*>(pEntityBase);
		if (NULL == pIRadar)
		{
			return;
		}

//		pIRadar->ScanRender();
	}

	// �뿪״̬
	void CElectMagScanState::Exit(IEntityBase* pEntityBase)
	{

	}

	// ��Ϣ����
	bool CElectMagScanState::OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage)
	{
		return (false);
	}
}

