#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/ElectMagSystem/IRadar.h"
#include "../../Public/EntitySystem/EntitySystem.h"
#include "GroundRadarAttribute.h"

namespace VR_Soft
{
	CGroundRadarAttribute::CGroundRadarAttribute(IRadar* pIRadar, const VRString& strName)
		:CAttributeImp<IAttribute>(pIRadar, strName)
	{
	}


	CGroundRadarAttribute::~CGroundRadarAttribute(void)
	{
	}

	// 初始化
	void CGroundRadarAttribute::Init(void)
	{
		// 创建半径属性值
		int t = 20;
		IAttributeItem* pRadiusAttr = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem("radius", 20);
		AddAttrItem(pRadiusAttr);

		//t = 50;
		//pRadiusAttr = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem("size", &t, DT_INT);
		//AddAttrItem(pRadiusAttr);

		bool b = true;
		pRadiusAttr = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem("wire frame", true, CTRL_COMBOX);
		AddAttrItem(pRadiusAttr);

		b = false;
		IAttributeItem* pWaiteItem  =  IComManager::GetInstance().GetAttributeManager()->CreateWaiteAttributeItem("wire frame", false);
		pRadiusAttr->AddCandidatas(pWaiteItem);
	}
}

