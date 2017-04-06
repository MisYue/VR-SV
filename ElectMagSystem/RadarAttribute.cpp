#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/ElectMagSystem/IRadar.h"
#include "../../Public/EntitySystem/AttributeImp.h"
#include "RadarAttribute.h"

namespace VR_Soft
{
	CRadarAttribute::CRadarAttribute(IRadar* pIRadar, const VRString& strName):CAttributeImp<IAttribute>(pIRadar, strName)
	{
	}

	CRadarAttribute::~CRadarAttribute(void)
	{
		IAttributeManager* pIAttributeManager = IComManager::GetInstance().GetAttributeManager();
		if (NULL == pIAttributeManager)
		{
			return;
		}
	}

	// 初始化
	void CRadarAttribute::Init(void)
	{
		//// 创建名称
		//IAttributeItem* pIAttribute = new CAttributeItemImp<VRString>("Object Name", m_strName);
		//m_lstAttributeItems.push_back(pIAttribute);
	}

	 //// 通过属性名称查询属性值
	 //IAttributeItem* CRadarAttribute::GetAttrItemByName(const VRString& strAttrName) const
	 //{
		// // 回收内存
		// VR_MUTEX_AUTO;

		// // 遍历名称
		// LstAttrItems::const_iterator cstItor = m_lstAttributeItems.begin();
		// for (; cstItor != m_lstAttributeItems.end(); ++cstItor)
		// {
		//	 IAttributeItem* pIAttributeItem = *cstItor;
		//	 if (0 == strAttrName.compare(pIAttributeItem->GetTypeName()))
		//	 {
		//		 return pIAttributeItem;
		//	 }
		// }

		// return (NULL);
	 //}
}

