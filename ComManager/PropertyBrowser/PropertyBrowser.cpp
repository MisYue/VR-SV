#include "../../../Public/VRSoft.h"
#include "PropertyBrowser.h"
#include <set>

namespace VR_Soft
{
	// CUIProperty ����˽������
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

	///////////////////////////////////�������˽������///////////////////////////////////////
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
	
	// ���캯��
	CUIProperty::CUIProperty(CAbstracUItPropertyManager *manager)
	{
		m_pPtr = new CUIPropertyPrivate(manager);
		m_pPtr->m_pPtr = this;
	}

	// ��������
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

	// ������������
	CUIProperty::ListUIProperty CUIProperty::GetSubProperties() const
	{
		return m_pPtr->m_subItems;
	}

	// ������Թ���
	CAbstracUItPropertyManager *CUIProperty::GetPropertyManager() const
	{
		return m_pPtr->m_manager;
	}

	// �����Ϣ��ʾ
	VRString CUIProperty::GetToolTip() const
	{
		return m_pPtr->m_strToolTip;
	}

	// ���״̬��ʾ��Ϣ
	VRString CUIProperty::GetStatusTip() const
	{
		return m_pPtr->m_strStatusTip;
	}

	// ��ý�����Ϣ
	VRString CUIProperty::GetWhatsThis() const
	{
	return m_pPtr->m_strWhatsThis;
	}

	//�����������
	VRString CUIProperty::PropertyName(void) const
	{
		return m_pPtr->m_strName;
	}

	// ��ȡ�Ƿ񱻽���
	bool CUIProperty::IsEnabled() const
	{
		return m_pPtr->m_enabled;
	}

	// ��ȡ�Ƿ�Ľ�
	bool CUIProperty::IsModified() const
	{
		return m_pPtr->m_modified;
	}

	// ��ȡ�Ƿ���ֵ
	bool CUIProperty::HasValue() const
	{
		return m_pPtr->m_manager->HasValue(this);
	}

	// �������������ı�
	VRString CUIProperty::GetValueText() const
	{
		return m_pPtr->m_manager->GetValueText(this);
	}

	// ���Աȶ�
	bool CUIProperty::Compare(const CUIProperty& other)const
	{
	  return (PropertyName() == other.PropertyName()
			  && GetToolTip() == other.GetToolTip()
			  && GetStatusTip() == other.GetStatusTip()
			  && GetWhatsThis() == other.GetWhatsThis()
			  && IsEnabled() == other.IsEnabled()
			  && IsModified() == other.IsModified());
	}

	// ���ù�������ʾ��Ϣ
	void CUIProperty::SetToolTip(const VRString &text)
	{
		if (m_pPtr->m_strToolTip == text)
			return;

		m_pPtr->m_strToolTip = text;
		PropertyChanged();
	}

	// ����״̬����Ϣ
	void CUIProperty::SetStatusTip(const VRString &text)
	{
		if (m_pPtr->m_strStatusTip == text)
			return;

		m_pPtr->m_strStatusTip = text;
		PropertyChanged();
	}

	// ���ý�����Ϣ
	void CUIProperty::SetWhatsThis(const VRString &text)
	{
		if (m_pPtr->m_strWhatsThis == text)
			return;

		m_pPtr->m_strWhatsThis = text;
		PropertyChanged();
	}

	// ������������
	void CUIProperty::SetPropertyName(const VRString &text)
	{
		if (m_pPtr->m_strName == text)
			return;

		m_pPtr->m_strName = text;
		PropertyChanged();
	}

	// �����Ƿ����
	void CUIProperty::SetEnabled(bool enable)
	{
		if (m_pPtr->m_enabled == enable)
			return;

		m_pPtr->m_enabled = enable;
		PropertyChanged();
	}

	// �����Ƿ�Ľ�
	void CUIProperty::SetModified(bool modified)
	{
		if (m_pPtr->m_modified == modified)
			return;

		m_pPtr->m_modified = modified;
		PropertyChanged();
	}

	// �Ƿ���������
	bool CUIProperty::IsSubProperty(void) const
	{
	  return (m_pPtr->m_parentItems.size() != 0);
	}

	// ���������
	void CUIProperty::AddSubProperty(CUIProperty *pProperty)
	{
		m_pPtr->m_subItems.push_back(pProperty);
	}

	// ����
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
				return; // �Ѿ���ӹ�ֱ�ӷ���
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

	// �Ƴ�������
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

	// ���Ը���
	void CUIProperty::PropertyChanged()
	{
		m_pPtr->m_manager->m_pPtr->PropertyChanged(this);
	}

	///////////////////////////////////CAbstracUItPropertyManager///////////////////////////////////////
	// ���캯��
	CAbstracUItPropertyManager::CAbstracUItPropertyManager(void)
	{
		m_pPtr = new CAbstracUItPropertyManagerPrivate;
		m_pPtr->m_pPtr = this;
	}
	
	// ��������
	CAbstracUItPropertyManager::~CAbstracUItPropertyManager(void)
	{
		Clear();
		VRSOFT_DELETE(m_pPtr);
	}

	// �����������
	std::set<CUIProperty *> CAbstracUItPropertyManager::GetProperties() const
	{
		return (m_pPtr->m_properties);
	}

	// �������ֵ
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

	// �������
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

	// �Ƿ�������
	bool CAbstracUItPropertyManager::HasValue( const CUIProperty *pProperty ) const
	{
		(void)pProperty;
		return true;
	}

	// �������ֵ�ı�
	VRString CAbstracUItPropertyManager::GetValueText( const CUIProperty *pProperty ) const
	{
		(void)pProperty;
		return (VRString(""));
	}

	// ж�س�ʼ��
	void CAbstracUItPropertyManager::UninitializeProperty( CUIProperty *pProperty )
	{
		(void) pProperty;
	}

	// ��������
	CUIProperty* CAbstracUItPropertyManager::CreateProperty(void)
	{
		return (new CUIProperty(this));
	}

	//////////////////////////////CBrowserItemPrivate////////////////////////////////////////////
	class CBrowserItemPrivate
	{
	public:
		// ���캯��
		CBrowserItemPrivate(CAbstractUIPropertyBrowser *pBrowser, CUIProperty *pProperty, CBrowserItem *parent)
			:m_pBrowser(pBrowser), m_pProperty(pProperty), m_pParent(parent), m_pPtr(NULL) { }
		
		// �������
		void AddChild(CBrowserItem *index, CBrowserItem *after);
		// �Ƴ�����
		void RemoveChild(CBrowserItem *index);

		CAbstractUIPropertyBrowser * const m_pBrowser;
		CUIProperty *m_pProperty;
		CBrowserItem *m_pParent;

		CBrowserItem *m_pPtr;

		std::list<CBrowserItem *> m_children;
	};

	// �������
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

	// �Ƴ�����
	void CBrowserItemPrivate::RemoveChild( CBrowserItem *index )
	{
		m_children.remove(index);
	}

	// �������
	CUIProperty * CBrowserItem::GetProperty() const
	{
		return (m_pPtr->m_pProperty);
	}

	// ��ø���
	CBrowserItem * CBrowserItem::GetParent() const
	{
		return (m_pPtr->m_pParent);
	}

	// �������
	std::list<CBrowserItem *> CBrowserItem::GetChildren() const
	{
		return (m_pPtr->m_children);
	}

	// ��������
	CAbstractUIPropertyBrowser * CBrowserItem::GetBowser() const
	{
		return (m_pPtr->m_pBrowser);
	}

	// ���캯��
	CBrowserItem::CBrowserItem( CAbstractUIPropertyBrowser *pBrowser, CUIProperty *pProperty, CBrowserItem *parent )
	{
		m_pPtr = new CBrowserItemPrivate(pBrowser, pProperty, parent);
		m_pPtr->m_pPtr = this;
	}

	// ��������
	CBrowserItem::~CBrowserItem()
	{
		VRSOFT_DELETE(m_pPtr);
	}

}

