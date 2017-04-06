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

	// 初始化
	void CSimTimeAttr::Init(void)
	{
		// 逻辑时间步长
		IAttributeItem* pILogicSimStep = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this,"LogicSimStep", "LogicSimStep", (double)200.0);
		AddAttrItem(pILogicSimStep);

		// 缩放时间倍数
		IAttributeItem* pISimMulti = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this,"SimMulti", "SimMulti", (double)1.0);
		AddAttrItem(pISimMulti);

		// 逻辑时间
		IAttributeItem* pISimLogicTime = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "SimLogicTime", "SimLogicTime", (double)0.0);
		AddAttrItem(pISimLogicTime);

		// 墙钟 从仿真开始计时 单位：毫秒
		IAttributeItem* pIWallTime = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "WallTime", "WallTime", (double)0.0);
		AddAttrItem(pIWallTime);

		// 帧算法
		IAttributeItem* pIFrame = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "Frame", "Frame", 0);
		AddAttrItem(pIFrame);

		// 墙钟起始时间
		IAttributeItem* pIWllStartTime = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "WllStartTime", "WllStartTime", (long long)0);
		AddAttrItem(pIWllStartTime);

		// 添加命令属性
		IAttributeItem* pICmdAttrbute = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this,"SimCmd", "Start", ISimManager::Start, CTRL_COMBOX);
		AddAttrItem(pICmdAttrbute);
		// 添加其他命令
		pICmdAttrbute->AddCandidatas("Pause", ISimManager::Pause);
		pICmdAttrbute->AddCandidatas("Stop", ISimManager::Stop, true);
		pICmdAttrbute->AddCandidatas("Reset", ISimManager::Reset);
		pICmdAttrbute->AddCandidatas("Close", ISimManager::Close);
	}
	*/
}

