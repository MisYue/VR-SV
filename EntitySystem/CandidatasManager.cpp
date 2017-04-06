#include "../../Public/VRSoft.h"
#include "CandidatasManager.h"

namespace VR_Soft
{
	CCandidatasManager::CCandidatasManager(void)
	{
	}


	CCandidatasManager::~CCandidatasManager(void)
	{
	}

	void CCandidatasManager::Add(const Candidatas& candidata)
	{
		if (!IsHave(candidata))
		{
			IComManager::GetInstance().WriteLogMsg("当前属性已经存在", ERRROR_HAVEED);
			return;
		}

		m_lstCandidatas.push_back(candidata);
	}

	void CCandidatasManager::Remove(VRString& strName)
	{
		IAttributeItem::LstCandidatas::iterator cstItro = std::find(m_lstCandidatas.begin(), m_lstCandidatas.end(), strName);
		if (cstItro == m_lstCandidatas.end())
		{
			return;
		}

		m_lstCandidatas.erase(cstItro);
	}

	bool CCandidatasManager::Empty(void) const
	{
		return m_lstCandidatas.empty();
	}

	Candidatas CCandidatasManager::GetCandidata(const VRString& strName, bool& b)
	{
		IAttributeItem::LstCandidatas::iterator cstItro = std::find(m_lstCandidatas.begin(), m_lstCandidatas.end(), strName);
		if (cstItro == m_lstCandidatas.end())
		{
			b = false;
			return Candidatas("", "");
		}

		b = true;
		return *cstItro;

	}

	const IAttributeItem::LstCandidatas& CCandidatasManager::GetCandidatas(void) const
	{
		return m_lstCandidatas;
	}

	int CCandidatasManager::SelectCandidata(void) const
	{
		// 遍历所有的值
		int index = 0;
		IAttributeItem::LstCandidatas::const_iterator cstItro = m_lstCandidatas.begin();
		for (; m_lstCandidatas.end() != cstItro; ++cstItro, ++index)
		{
			if (cstItro->bSelect)
			{
				return (index);
			}
		}

		// 判断当前没有选中者直接返回第一个
		return (0);
	}

	void CCandidatasManager::SetSelect(const int index)
	{
		// 判断如果当前的索引项不存在 则之间返回
		if (index >= (int)m_lstCandidatas.size())
		{
			return;
		}

		// 遍历所有的值 处理选择项
		IAttributeItem::LstCandidatas::iterator itor = m_lstCandidatas.begin();
		for (int i = 0; m_lstCandidatas.end() != itor; ++itor, ++i)
		{
			itor->bSelect = index == i ? true : false;
		}
	}

	VR_Soft::VRVariant CCandidatasManager::GetVariant(void) const
	{
		// 遍历所有的值 处理选择项
		IAttributeItem::LstCandidatas::const_iterator itor = m_lstCandidatas.begin();
		for (int i = 0; m_lstCandidatas.end() != itor; ++itor, ++i)
		{
			if (itor->bSelect)
			{
				return (itor->value);
			}
		
		}

		return (m_lstCandidatas.begin()->value);
	}

	bool CCandidatasManager::IsHave(const VRString& strName)
	{
		IAttributeItem::LstCandidatas::const_iterator cstItro = std::find(m_lstCandidatas.begin(), m_lstCandidatas.end(), strName);
		return (cstItro == m_lstCandidatas.end());
	}

	bool CCandidatasManager::IsHave(const Candidatas& candidata)
	{
		IAttributeItem::LstCandidatas::const_iterator cstItro = std::find(m_lstCandidatas.begin(), m_lstCandidatas.end(), candidata);
		return (cstItro == m_lstCandidatas.end());
	}

}

