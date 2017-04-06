#define VRSOFT_PLUGIN_EXPORT
#include <algorithm>
#include <vector>
#include "../../Public/VRSoft.h"
#include "../../Public/EntitySystem/EntitySystem.h"
#include "AttributeItem.h"
#include "AttributeManager.h"

namespace VR_Soft
{
	CAttributeManager::CAttributeManager(void):
		m_pICurEntityBase(NULL)
	{
		
	}


	CAttributeManager::~CAttributeManager(void)
	{
	}

	// ע����洰��
	void CAttributeManager::RegisterUI(IAttributeUI* pIAttributeUI)
	{
		VR_MUTEX_AUTO;
		// ��ѯ�Ƿ���ڵ�ǰ�Ľ���
		VctAttributeUI::const_iterator cstItor = std::find(m_vecAttributeUI.begin(), m_vecAttributeUI.end(), pIAttributeUI);
		if (m_vecAttributeUI.end() != cstItor)
		{
			return;
		}

		m_vecAttributeUI.push_back(pIAttributeUI);
	}

	// ��ע����洰��
	void CAttributeManager::UnRegisterUI(IAttributeUI* pIAttributeUI)
	{
		VR_MUTEX_AUTO;
		// ��ѯ�Ƿ���ڵ�ǰ�Ľ���
		VctAttributeUI::iterator itor = std::find(m_vecAttributeUI.begin(), m_vecAttributeUI.end(), pIAttributeUI);
		if (m_vecAttributeUI.end() != itor)
		{
			return;
		}

		(*itor) = NULL;
		// ɾ����ǰ����
		m_vecAttributeUI.erase(itor);
	}

	// ���õ�ǰ������
	void CAttributeManager::SetCurrentEntityBase(IEntityBase* pIEntityBase)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		m_pICurEntityBase = pIEntityBase;

		// ��ѯ��ǰ��ģ�͵�����
		MapEntityAttribute::const_iterator cstItor = m_mapEntityAttribute.find(pIEntityBase);
		if (m_mapEntityAttribute.end() == cstItor)
		{
			return;
		}

		// ���µ�������
		UpdateAttributeUI(cstItor->second);
	}

	// ������Խӿ�
	void CAttributeManager::AddAttribute(IAttribute* pIAttribute)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		IEntityBase* pIEntityBase = pIAttribute->GetEntity();
		if (NULL == pIEntityBase)
		{
			IComManager::GetInstance().WriteLogMsg("������Ե�����ʧ��");
			return;
		}

		// ����
		MapEntityAttribute::const_iterator cstItor = m_mapEntityAttribute.find(pIEntityBase);
		if (m_mapEntityAttribute.end() != cstItor)
		{
			return;
		}

		m_mapEntityAttribute[pIEntityBase] = pIAttribute;
	}

	// �������������
	IAttributeItem* CAttributeManager::CreateAttributeItem(IAttribute* pIAttribute, const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
		const VRVariant& var, const Contrl ct /*=  CTRL_EDIT*/)
	{
		// ȷ���̰߳�ȫ
		VR_MUTEX_AUTO;

		IAttributeItem* pItem = new CAttributeItem(pIAttribute, strText, strUntil, var);
		if (NULL != pItem)
		{
			CAttributeItemImp<IAttributeItem>* pItemImp = dynamic_cast<CAttributeItemImp<IAttributeItem>*>(pItem);
			if (NULL != pItemImp)
			{
				pItemImp->SetTypeName(strItemName);
				pItemImp->SetCtrlType(ct);
			}
		}

		// ������Чֵ
		return (pItem);
	}

	// ����������
	void CAttributeManager::UpdateAttributeItem(const IAttributeItem* pIAttributeItem)
	{
		VR_MUTEX_AUTO;

		IAttribute* pIAttribute = ((CAttributeItemImp<IAttributeItem>*)pIAttributeItem)->GetAttribute();
		if (NULL == pIAttribute)
		{
			return;
		}

		// ��õ�ǰ����
		if (NULL == pIAttribute->GetEntity() || m_pICurEntityBase != pIAttribute->GetEntity())
		{
			return;
		}

		// ���µ�����UI
		//UpdateAttributeUI(pIAttribute);

	}

	// ����UI
	void CAttributeManager::UpdateAttributeUI(const IAttribute* pIAttribute)
	{
		// ѭ������
		for (VctAttributeUI::const_iterator cstItor = m_vecAttributeUI.begin(); \
			m_vecAttributeUI.end() != cstItor; ++cstItor)
		{
			(*cstItor)->Update((void*)pIAttribute);
		}
	}
}

