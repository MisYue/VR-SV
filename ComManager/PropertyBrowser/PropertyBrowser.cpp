#include "../../../Public/VRSoft.h"
#include "PropertyBrowser.h"
#include <set>

namespace VR_Soft
{
	// CUIProperty 属性私有数据
	class CUIPropertyPrivate
	{
	public:
		CUIPropertyPrivate(CAbstracUItPropertyManager *manager) : m_enabled(true), m_modified(false), m_manager(manager) {}
		CUIProperty *m_pPtr;

		std::set<CUIProperty *> m_parentItems;
		CUIProperty::ListUIProperty m_subItems;

		VRString m_strToolTip;
		VRString m_strStatusTip;
		VRString m_strWhatsThis;
		VRString m_strName;
		bool m_enabled;
		bool m_modified;

		CAbstracUItPropertyManager * const m_manager;
	};

	///////////////////////////////////抽象管理私有属性///////////////////////////////////////
	class CAbstracUItPropertyManagerPrivate
	{
		CAbstracUItPropertyManager *m_pPtr;
		DECLARE_PUBLIC(CAbstracUItPropertyManager)
	public:
		void PropertyDestroyed(CUIProperty *pProperty);
		void PropertyChanged(CUIProperty *pProperty) const;
		void PropertyRemoved(CUIProperty *pProperty,
			CUIProperty *pParentProperty) const;
		void PropertyInserted(CUIProperty *pProperty, CUIProperty *pParentProperty,
			CUIProperty *pAfterProperty) const;

		std::set<CUIProperty *> m_properties;
	};


	void CAbstracUItPropertyManagerPrivate::PropertyDestroyed(CUIProperty *pProperty)
	{
		if (m_properties.end() != m_properties.find(pProperty)) {
		//	emit q_ptr->propertyDestroyed(property);
			m_pPtr->UninitializeProperty(pProperty);
			std::set<CUIProperty *>::iterator itor = std::find(m_properties.begin(), m_properties.end(), pProperty);
			if (m_properties.end() != itor)
			{
				m_properties.erase(itor);
			}
			
			//m_properties.remove(pProperty);
		}
	}

	void CAbstracUItPropertyManagerPrivate::PropertyChanged(CUIProperty *pProperty) const
	{
		// emit q_ptr->propertyChanged(property);
	}

	void CAbstracUItPropertyManagerPrivate:: PropertyRemoved(CUIProperty *pProperty,
		CUIProperty *pParentProperty) const
	{
		// emit q_ptr->propertyRemoved(property, parentProperty);
	}

	void CAbstracUItPropertyManagerPrivate::PropertyInserted(CUIProperty *pProperty, CUIProperty *pParentProperty,
		CUIProperty *pAfterProperty) const
	{
		// emit q_ptr->propertyInserted(property, parentProperty, afterProperty);
	}
	
	//////////////////////////////////////////////////////////////////////////
	
	// 构造函数
	CUIProperty::CUIProperty(CAbstracUItPropertyManager *manager)
	{
		m_pPtr = new CUIPropertyPrivate(manager);
		m_pPtr->m_pPtr = this;
	}

	// 析构函数
	CUIProperty::~CUIProperty()
	{
		std::set<CUIProperty *>::iterator itParent = m_pPtr->m_parentItems.begin();
		while (m_pPtr->m_parentItems.end() != ++itParent) {
			CUIProperty *property = *itParent;
			property->m_pPtr->m_manager->m_pPtr->PropertyRemoved(this, property);
		}

		m_pPtr->m_manager->m_pPtr->PropertyDestroyed(this);

		ListUIProperty::iterator itChild = m_pPtr->m_subItems.begin();
		while ( m_pPtr->m_subItems.end() != itChild) {
			CUIProperty *property = (*itChild)++;
			std::set<CUIProperty *>& parentItems = property->m_pPtr->m_parentItems;
			std::set<CUIProperty *>::iterator itor = std::find(parentItems.begin(), parentItems.end(), this);
			if (parentItems.end() != itor)
			{
				parentItems.erase(itor);
			}
			

		}

		itParent = m_pPtr->m_parentItems.begin();
		while (m_pPtr->m_parentItems.end() != ++itParent) {
			CUIProperty *property = *itParent;
			ListUIProperty::iterator itor = std::remove(property->m_pPtr->m_subItems.begin(), property->m_pPtr->m_subItems.end(), this) ;
			property->m_pPtr->m_subItems.erase(itor);
		}
		delete m_pPtr;
	}

	// 返回所有属性
	CUIProperty::ListUIProperty CUIProperty::GetSubProperties() const
	{
		return m_pPtr->m_subItems;
	}

	// 获得属性管理
	CAbstracUItPropertyManager *CUIProperty::GetPropertyManager() const
	{
		return m_pPtr->m_manager;
	}

	// 获得信息提示
	VRString CUIProperty::GetToolTip() const
	{
		return m_pPtr->m_strToolTip;
	}

	// 获得状态提示信息
	VRString CUIProperty::GetStatusTip() const
	{
		return m_pPtr->m_strStatusTip;
	}

	// 获得介绍信息
	VRString CUIProperty::GetWhatsThis() const
	{
	return m_pPtr->m_strWhatsThis;
	}

	//获得属性名称
	VRString CUIProperty::PropertyName(void) const
	{
		return m_pPtr->m_strName;
	}

	// 获取是否被禁用
	bool CUIProperty::IsEnabled() const
	{
		return m_pPtr->m_enabled;
	}

	// 获取是否改进
	bool CUIProperty::IsModified() const
	{
		return m_pPtr->m_modified;
	}

	// 获取是否有值
	bool CUIProperty::HasValue() const
	{
		return m_pPtr->m_manager->HasValue(this);
	}

	// 返回属性内容文本
	VRString CUIProperty::GetValueText() const
	{
		return m_pPtr->m_manager->GetValueText(this);
	}

	// 属性比对
	bool CUIProperty::Compare(const CUIProperty& other)const
	{
	  return (PropertyName() == other.PropertyName()
			  && GetToolTip() == other.GetToolTip()
			  && GetStatusTip() == other.GetStatusTip()
			  && GetWhatsThis() == other.GetWhatsThis()
			  && IsEnabled() == other.IsEnabled()
			  && IsModified() == other.IsModified());
	}

	// 设置工具栏提示信息
	void CUIProperty::SetToolTip(const VRString &text)
	{
		if (m_pPtr->m_strToolTip == text)
			return;

		m_pPtr->m_strToolTip = text;
		PropertyChanged();
	}

	// 设置状态栏信息
	void CUIProperty::SetStatusTip(const VRString &text)
	{
		if (m_pPtr->m_strStatusTip == text)
			return;

		m_pPtr->m_strStatusTip = text;
		PropertyChanged();
	}

	// 设置介绍信息
	void CUIProperty::SetWhatsThis(const VRString &text)
	{
		if (m_pPtr->m_strWhatsThis == text)
			return;

		m_pPtr->m_strWhatsThis = text;
		PropertyChanged();
	}

	// 设置属性名称
	void CUIProperty::SetPropertyName(const VRString &text)
	{
		if (m_pPtr->m_strName == text)
			return;

		m_pPtr->m_strName = text;
		PropertyChanged();
	}

	// 设置是否禁用
	void CUIProperty::SetEnabled(bool enable)
	{
		if (m_pPtr->m_enabled == enable)
			return;

		m_pPtr->m_enabled = enable;
		PropertyChanged();
	}

	// 设置是否改进
	void CUIProperty::SetModified(bool modified)
	{
		if (m_pPtr->m_modified == modified)
			return;

		m_pPtr->m_modified = modified;
		PropertyChanged();
	}

	// 是否有子属性
	bool CUIProperty::IsSubProperty(void) const
	{
	  return (m_pPtr->m_parentItems.size() != 0);
	}

	// 添加子属性
	void CUIProperty::AddSubProperty(CUIProperty *pProperty)
	{
		m_pPtr->m_subItems.push_back(pProperty);
	}

	// 插入
	void CUIProperty::InsertSubProperty(CUIProperty *pProperty,
				CUIProperty *pAfterProperty)
	{
		if (!pProperty)
			return;

		if (pProperty == this)
			return;

		// traverse all children of item. if this item is a child of item then cannot add.
		ListUIProperty pendingList = pProperty->GetSubProperties();
		std::map<CUIProperty *, bool> visited;
		while (!pendingList.empty()) {
			CUIProperty *i = *pendingList.begin();
			if (i == this)
				return;
			std::find(pendingList.begin(), pendingList.end(), i);
			if (visited.end() != visited.find(i))
				continue;
			visited[i] = true;

			ListUIProperty subPendingList = i->GetSubProperties();
			std::copy(subPendingList.begin(), subPendingList.end(), std::back_inserter(pendingList) );
		}

		pendingList = GetSubProperties();
		int pos = 0;
		int newPos = 0;
	
		CUIProperty *properAfterProperty = 0;
		while (pos < (int)pendingList.size()) {
			CUIProperty *i = pendingList.at(pos);
			if (i == pProperty)
				return; // 已经添加过直接返回
			if (i == pAfterProperty) {
				newPos = pos + 1;
				properAfterProperty = pAfterProperty;
			}
			pos++;
		}

		ListUIProperty::iterator newItor = m_pPtr->m_subItems.begin();
		for (int index = 0; index < newPos; ++index)
		{
			++newItor;
		}
		
		m_pPtr->m_subItems.insert(newItor, pProperty);
		pProperty->m_pPtr->m_parentItems.insert(this);

		m_pPtr->m_manager->m_pPtr->PropertyInserted(pProperty, this, properAfterProperty);
	}

	// 移除子属性
	void CUIProperty::RemoveSubProperty(CUIProperty *pProperty)
	{
		if (!pProperty)
			return;

		m_pPtr->m_manager->m_pPtr->PropertyRemoved(pProperty, this);

		ListUIProperty pendingList = GetSubProperties();
		int pos = 0;
		while (pos < (int)pendingList.size()) {
			if (pendingList.at(pos) == pProperty) {
				//m_pPtr->m_subItems.(pos);
				ListUIProperty::iterator itor = std::find(m_pPtr->m_subItems.begin(),m_pPtr->m_subItems.end(), m_pPtr->m_subItems[pos]);
				if (m_pPtr->m_subItems.end() != itor)
				{
					m_pPtr->m_subItems.erase(itor);
				}
				
			//	std::remove(pProperty->m_pPtr->m_parentItems.begin(),pProperty->m_pPtr->m_parentItems.end(), this);
				std::set<CUIProperty *>::iterator parentItor = pProperty->m_pPtr->m_parentItems.find(this);
				if (pProperty->m_pPtr->m_parentItems.end() != parentItor)
				{
					pProperty->m_pPtr->m_parentItems.erase(parentItor);
				}
				

					//pProperty->m_pPtr->m_parentItems.remove(this);

				return;
			}
			pos++;
		}
	}

	// 属性更改
	void CUIProperty::PropertyChanged()
	{
		m_pPtr->m_manager->m_pPtr->PropertyChanged(this);
	}

	///////////////////////////////////CAbstracUItPropertyManager///////////////////////////////////////
	// 构造函数
	CAbstracUItPropertyManager::CAbstracUItPropertyManager(void)
	{
		m_pPtr = new CAbstracUItPropertyManagerPrivate;
		m_pPtr->m_pPtr = this;
	}
	
	// 析构函数
	CAbstracUItPropertyManager::~CAbstracUItPropertyManager(void)
	{
		Clear();
		VRSOFT_DELETE(m_pPtr);
	}

	// 获得所有属性
	std::set<CUIProperty *> CAbstracUItPropertyManager::GetProperties() const
	{
		return (m_pPtr->m_properties);
	}

	// 清空属性值
	void CAbstracUItPropertyManager::Clear() const
	{
		std::set<CUIProperty *>::iterator itor = m_pPtr->m_properties.begin();
		for (; m_pPtr->m_properties.end() != itor; ++itor)
		{
			CUIProperty* pUIProperty = *itor;
			VRSOFT_DELETE(pUIProperty);
		}
		
		m_pPtr->m_properties.clear();
	}

	// 添加属性
	CUIProperty * CAbstracUItPropertyManager::AddProperty( const VRString &strName /*= VRString()*/ )
	{
		CUIProperty *pProperty = CreateProperty();
		if (NULL != pProperty) {
			pProperty->SetPropertyName(strName);
			m_pPtr->m_properties.insert(pProperty);
			InitializeProperty(pProperty);
		}
		return pProperty;
	}

	// 是否有属性
	bool CAbstracUItPropertyManager::HasValue( const CUIProperty *pProperty ) const
	{
		(void)pProperty;
		return true;
	}

	// 获得属性值文本
	VRString CAbstracUItPropertyManager::GetValueText( const CUIProperty *pProperty ) const
	{
		(void)pProperty;
		return (VRString(""));
	}

	// 卸载初始化
	void CAbstracUItPropertyManager::UninitializeProperty( CUIProperty *pProperty )
	{
		(void) pProperty;
	}

	// 创建属性
	CUIProperty* CAbstracUItPropertyManager::CreateProperty(void)
	{
		return (new CUIProperty(this));
	}

	//////////////////////////////CBrowserItemPrivate////////////////////////////////////////////
	class CBrowserItemPrivate
	{
	public:
		// 构造函数
		CBrowserItemPrivate(CAbstractUIPropertyBrowser *pBrowser, CUIProperty *pProperty, CBrowserItem *parent)
			:m_pBrowser(pBrowser), m_pProperty(pProperty), m_pParent(parent), m_pPtr(NULL) { }
		
		// 添加子项
		void AddChild(CBrowserItem *index, CBrowserItem *after);
		// 移除子项
		void RemoveChild(CBrowserItem *index);

		CAbstractUIPropertyBrowser * const m_pBrowser;
		CUIProperty *m_pProperty;
		CBrowserItem *m_pParent;

		CBrowserItem *m_pPtr;

		std::list<CBrowserItem *> m_children;
	};

	// 添加子项
	void CBrowserItemPrivate::AddChild( CBrowserItem *index, CBrowserItem *after )
	{
		std::list<CBrowserItem* >::const_iterator cstItor = std::find(m_children.begin(), m_children.end(), index);
		if (m_children.end() != cstItor)
		{
			return;
		}

		std::list<CBrowserItem* >::iterator findItor = std::find(m_children.begin(), m_children.end(), after);
		m_children.insert(findItor, index);
	}

	// 移除子项
	void CBrowserItemPrivate::RemoveChild( CBrowserItem *index )
	{
		m_children.remove(index);
	}

	// 获得属性
	CUIProperty * CBrowserItem::GetProperty() const
	{
		return (m_pPtr->m_pProperty);
	}

	// 获得父项
	CBrowserItem * CBrowserItem::GetParent() const
	{
		return (m_pPtr->m_pParent);
	}

	// 获得子项
	std::list<CBrowserItem *> CBrowserItem::GetChildren() const
	{
		return (m_pPtr->m_children);
	}

	// 获得浏览项
	CAbstractUIPropertyBrowser * CBrowserItem::GetBowser() const
	{
		return (m_pPtr->m_pBrowser);
	}

	// 构造函数
	CBrowserItem::CBrowserItem( CAbstractUIPropertyBrowser *pBrowser, CUIProperty *pProperty, CBrowserItem *parent )
	{
		m_pPtr = new CBrowserItemPrivate(pBrowser, pProperty, parent);
		m_pPtr->m_pPtr = this;
	}

	// 析构函数
	CBrowserItem::~CBrowserItem()
	{
		VRSOFT_DELETE(m_pPtr);
	}

}

