#include "../../Public/VRSoft.h"
#include "AttributeUIFactory.h"

namespace VR_Soft
{
	CAttributeUIFactory::CAttributeUIFactory(void)
	{
	}


	CAttributeUIFactory::~CAttributeUIFactory(void)
	{
	}

	// 注册界面
	void CAttributeUIFactory::Register(IAttributeItemUI* pIAttributeItemUI)
	{
		// 线程安全 
		VR_MUTEX_AUTO;

		// 查找是否存在
		Contrl ct = pIAttributeItemUI->GetContrlType();
		AttributItemUIs::const_iterator cstItor = m_attributeItemUis.find(ct);
		if (m_attributeItemUis.end() == cstItor)
		{
			m_attributeItemUis[ct] = pIAttributeItemUI;
		}

	}

	// 反注册界面
	void CAttributeUIFactory::UnRegister(IAttributeItemUI* pIAttributeItemUI)
	{
		// 线程安全 
		VR_MUTEX_AUTO;

		// 查找是否存在
		Contrl ct = pIAttributeItemUI->GetContrlType();
		AttributItemUIs::iterator itor = m_attributeItemUis.find(ct);
		if (m_attributeItemUis.end() != itor)
		{
			m_attributeItemUis.erase(itor);
		}
	}

	// 获得控件
	IAttributeItemUI* CAttributeUIFactory::GetContrl(IAttributeItem* pIAttributeItem)
	{
		// 线程安全 
		VR_MUTEX_AUTO;

		// 查找是否存在
		Contrl ct = pIAttributeItem->GetCtrlType();
		AttributItemUIs::iterator itor = m_attributeItemUis.find(ct);
		if (m_attributeItemUis.end() == itor)
		{
			IComManager::GetInstance().WriteLogMsg(pIAttributeItem->GetTypeName() + "没有找到属性对应的控件", ERROR_NOT_FIND);
			return (NULL);
		}

		// 设置属性
		CAttributeItemUIImp<IAttributeItemUI>* pIAttributeItemUI = dynamic_cast<CAttributeItemUIImp<IAttributeItemUI> * >(\
			itor->second);
		if (NULL == pIAttributeItemUI)
		{
			IComManager::GetInstance().WriteLogMsg(pIAttributeItem->GetTypeName() + "控件转换失败", ERROR_FAILE_CONVERT);
			return (NULL);
		}

		IAttributeItemUI* pCloneObj = pIAttributeItemUI->Clone();

		((CAttributeItemUIImp<IAttributeItemUI>*)pCloneObj)->SetAttributeItem(pIAttributeItem);
		pCloneObj->SetInfor();
		return (pCloneObj);
	}
}
