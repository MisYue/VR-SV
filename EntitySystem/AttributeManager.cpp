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

	// 注册界面窗口
	void CAttributeManager::RegisterUI(IAttributeUI* pIAttributeUI)
	{
		VR_MUTEX_AUTO;
		// 查询是否存在当前的界面
		VctAttributeUI::const_iterator cstItor = std::find(m_vecAttributeUI.begin(), m_vecAttributeUI.end(), pIAttributeUI);
		if (m_vecAttributeUI.end() != cstItor)
		{
			return;
		}

		m_vecAttributeUI.push_back(pIAttributeUI);
	}

	// 发注册界面窗口
	void CAttributeManager::UnRegisterUI(IAttributeUI* pIAttributeUI)
	{
		VR_MUTEX_AUTO;
		// 查询是否存在当前的界面
		VctAttributeUI::iterator itor = std::find(m_vecAttributeUI.begin(), m_vecAttributeUI.end(), pIAttributeUI);
		if (m_vecAttributeUI.end() != itor)
		{
			return;
		}

		(*itor) = NULL;
		// 删除当前对象
		m_vecAttributeUI.erase(itor);
	}

	// 设置当前的属性
	void CAttributeManager::SetCurrentEntityBase(IEntityBase* pIEntityBase)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		m_pICurEntityBase = pIEntityBase;

		// 查询当前的模型的属性
		MapEntityAttribute::const_iterator cstItor = m_mapEntityAttribute.find(pIEntityBase);
		if (m_mapEntityAttribute.end() == cstItor)
		{
			return;
		}

		// 更新到界面中
		UpdateAttributeUI(cstItor->second);
	}

	// 添加属性接口
	void CAttributeManager::AddAttribute(IAttribute* pIAttribute)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		IEntityBase* pIEntityBase = pIAttribute->GetEntity();
		if (NULL == pIEntityBase)
		{
			IComManager::GetInstance().WriteLogMsg("添加属性到管理失败");
			return;
		}

		// 查找
		MapEntityAttribute::const_iterator cstItor = m_mapEntityAttribute.find(pIEntityBase);
		if (m_mapEntityAttribute.end() != cstItor)
		{
			return;
		}

		m_mapEntityAttribute[pIEntityBase] = pIAttribute;
	}

	// 创建属性项对象
	IAttributeItem* CAttributeManager::CreateAttributeItem(IAttribute* pIAttribute, const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
		const VRVariant& var, const Contrl ct /*=  CTRL_EDIT*/)
	{
		// 确保线程安全
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

		// 返回有效值
		return (pItem);
	}

	// 更新属性项
	void CAttributeManager::UpdateAttributeItem(const IAttributeItem* pIAttributeItem)
	{
		VR_MUTEX_AUTO;

		IAttribute* pIAttribute = ((CAttributeItemImp<IAttributeItem>*)pIAttributeItem)->GetAttribute();
		if (NULL == pIAttribute)
		{
			return;
		}

		// 获得当前属性
		if (NULL == pIAttribute->GetEntity() || m_pICurEntityBase != pIAttribute->GetEntity())
		{
			return;
		}

		// 更新到界面UI
		//UpdateAttributeUI(pIAttribute);

	}

	// 更新UI
	void CAttributeManager::UpdateAttributeUI(const IAttribute* pIAttribute)
	{
		// 循环更新
		for (VctAttributeUI::const_iterator cstItor = m_vecAttributeUI.begin(); \
			m_vecAttributeUI.end() != cstItor; ++cstItor)
		{
			(*cstItor)->Update((void*)pIAttribute);
		}
	}
}

