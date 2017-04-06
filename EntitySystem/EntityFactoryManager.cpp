#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "EntityFactoryManager.h"

namespace VR_Soft
{
	CEntityFactoryManager::CEntityFactoryManager(void)
	{
	}


	CEntityFactoryManager::~CEntityFactoryManager(void)
	{
		RemoveAll();
	}

	// 注册工厂
	void CEntityFactoryManager::RegisterFactory(IEntityBaseFactory* pIEntityFactory)
	{
		VR_MUTEX_AUTO;

		// 获取工厂类型
		const VRString strType = pIEntityFactory->GetEntiryBaseType();
		bool bHave = IsHave(strType);
		if (bHave)
		{
			return;
		}

		m_factorys.push_back(pIEntityFactory);

		// 更新界面
		IEntityManager::GetInstance().UpdateUI();
	}

	// 卸载工厂
	void CEntityFactoryManager::UnRegisterFactory(const VRString& strFactoryType)
	{
		VR_MUTEX_AUTO;

		// 获取工厂类型
		bool bHave = IsHave(strFactoryType);
		if (!bHave)
		{
			return;
		}

		// 遍历所有的工厂
		LstFactroys::iterator itor = m_factorys.begin();
		for (; m_factorys.end() != itor; ++itor)
		{
			// 转换实例
			const VRString strFactoryType = (*itor)->GetEntiryBaseType();
			if (0 == strFactoryType.compare(strFactoryType))
			{
				// 找到工厂对应实例, 直接删除
				VRSOFT_DELETE(*itor);
				m_factorys.erase(itor);
				break;
			}
		}

		// 更新界面
		IEntityManager::GetInstance().UpdateUI();
	}

	// 查找是否存在当前工厂
	bool CEntityFactoryManager::IsHave(const VRString& strType) const
	{
		// 遍历所有的工厂
		LstFactroys::const_iterator cstItor = m_factorys.begin();
		for (; m_factorys.end() != cstItor; ++cstItor)
		{
			// 转换实例
			const VRString strFactoryType = (*cstItor)->GetEntiryBaseType();
			if (0 == strFactoryType.compare(strType))
			{
				// 找到工厂对应实例，直接返回
				return (true);
			}
		}

		return (false);
	}

	// 获得工厂实例
	IEntityBaseFactory* CEntityFactoryManager::GetEntityFactory(const VRString& strType) const
	{
		VR_MUTEX_AUTO;

		// 遍历所有的工厂
		LstFactroys::const_iterator cstItor = m_factorys.begin();
		for (; m_factorys.end() != cstItor; ++cstItor)
		{
			// 转换实例
			const VRString strFactoryType = (*cstItor)->GetEntiryBaseType();
			if (0 == strFactoryType.compare(strType))
			{
				// 找到工厂对应实例，直接返回
				return (*cstItor);
			}
		}

		// 返回空值
		return (NULL);
	}

	// 删除所有工厂
	void CEntityFactoryManager::RemoveAll(void)
	{
		VR_MUTEX_AUTO;

		LstFactroys::iterator itor = m_factorys.begin();
		while (itor != m_factorys.end())
		{
			VRSOFT_DELETE(*itor);
			++itor;
		}

		m_factorys.clear();

		// 更新界面
		IEntityManager::GetInstance().UpdateUI();
	}

	// 获得工厂列表
	const CEntityFactoryManager::LstFactroys& CEntityFactoryManager::GetAllEntityFactory(void) const
	{
		return (m_factorys);
	}
}

