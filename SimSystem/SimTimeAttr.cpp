#include "../../Public/VRSoft.h"
#include "SimTime.h"
#include "SimTimeAttr.h"

namespace VR_Soft
{
	/*
	CSimTimeAttr::CSimTimeAttr(CSimTime* pSimTime, const VRString& strName)
		:CAttributeImp<IAttribute>(pSimTime, strName)
	{
	}


	CSimTimeAttr::~CSimTimeAttr(void)
	{
	}

	// ��ʼ��
	void CSimTimeAttr::Init(void)
	{
		// �߼�ʱ�䲽��
		IAttributeItem* pILogicSimStep = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this,"LogicSimStep", "LogicSimStep", (double)200.0);
		AddAttrItem(pILogicSimStep);

		// ����ʱ�䱶��
		IAttributeItem* pISimMulti = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this,"SimMulti", "SimMulti", (double)1.0);
		AddAttrItem(pISimMulti);

		// �߼�ʱ��
		IAttributeItem* pISimLogicTime = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "SimLogicTime", "SimLogicTime", (double)0.0);
		AddAttrItem(pISimLogicTime);

		// ǽ�� �ӷ��濪ʼ��ʱ ��λ������
		IAttributeItem* pIWallTime = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "WallTime", "WallTime", (double)0.0);
		AddAttrItem(pIWallTime);

		// ֡�㷨
		IAttributeItem* pIFrame = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "Frame", "Frame", 0);
		AddAttrItem(pIFrame);

		// ǽ����ʼʱ��
		IAttributeItem* pIWllStartTime = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "WllStartTime", "WllStartTime", (long long)0);
		AddAttrItem(pIWllStartTime);

		// �����������
		IAttributeItem* pICmdAttrbute = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this,"SimCmd", "Start", ISimManager::Start, CTRL_COMBOX);
		AddAttrItem(pICmdAttrbute);
		// �����������
		pICmdAttrbute->AddCandidatas("Pause", ISimManager::Pause);
		pICmdAttrbute->AddCandidatas("Stop", ISimManager::Stop, true);
		pICmdAttrbute->AddCandidatas("Reset", ISimManager::Reset);
		pICmdAttrbute->AddCandidatas("Close", ISimManager::Close);
	}
	*/
}

