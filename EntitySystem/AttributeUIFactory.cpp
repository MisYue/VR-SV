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

	// ע�����
	void CAttributeUIFactory::Register(IAttributeItemUI* pIAttributeItemUI)
	{
		// �̰߳�ȫ 
		VR_MUTEX_AUTO;

		// �����Ƿ����
		Contrl ct = pIAttributeItemUI->GetContrlType();
		AttributItemUIs::const_iterator cstItor = m_attributeItemUis.find(ct);
		if (m_attributeItemUis.end() == cstItor)
		{
			m_attributeItemUis[ct] = pIAttributeItemUI;
		}

	}

	// ��ע�����
	void CAttributeUIFactory::UnRegister(IAttributeItemUI* pIAttributeItemUI)
	{
		// �̰߳�ȫ 
		VR_MUTEX_AUTO;

		// �����Ƿ����
		Contrl ct = pIAttributeItemUI->GetContrlType();
		AttributItemUIs::iterator itor = m_attributeItemUis.find(ct);
		if (m_attributeItemUis.end() != itor)
		{
			m_attributeItemUis.erase(itor);
		}
	}

	// ��ÿؼ�
	IAttributeItemUI* CAttributeUIFactory::GetContrl(IAttributeItem* pIAttributeItem)
	{
		// �̰߳�ȫ 
		VR_MUTEX_AUTO;

		// �����Ƿ����
		Contrl ct = pIAttributeItem->GetCtrlType();
		AttributItemUIs::iterator itor = m_attributeItemUis.find(ct);
		if (m_attributeItemUis.end() == itor)
		{
			IComManager::GetInstance().WriteLogMsg(pIAttributeItem->GetTypeName() + "û���ҵ����Զ�Ӧ�Ŀؼ�", ERROR_NOT_FIND);
			return (NULL);
		}

		// ��������
		CAttributeItemUIImp<IAttributeItemUI>* pIAttributeItemUI = dynamic_cast<CAttributeItemUIImp<IAttributeItemUI> * >(\
			itor->second);
		if (NULL == pIAttributeItemUI)
		{
			IComManager::GetInstance().WriteLogMsg(pIAttributeItem->GetTypeName() + "�ؼ�ת��ʧ��", ERROR_FAILE_CONVERT);
			return (NULL);
		}

		IAttributeItemUI* pCloneObj = pIAttributeItemUI->Clone();

		((CAttributeItemUIImp<IAttributeItemUI>*)pCloneObj)->SetAttributeItem(pIAttributeItem);
		pCloneObj->SetInfor();
		return (pCloneObj);
	}
}
