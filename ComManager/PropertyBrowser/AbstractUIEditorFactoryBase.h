/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������ع���			                                        */
/* ʱ�䣺 2016-09-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ABSTRACTUIEDITORFACORYBASE_H_
#define _ABSTRACTUIEDITORFACORYBASE_H_

namespace VR_Soft
{
	/////////////////////////////////CAbstractUIEditorFactoryBase/////////////////////////////////////////
	template <class Type>
	class CAbstractUIEditorFactoryBase
	{
	public:
		// �����༭��
		virtual Type* CreateEditor(CUIProperty* pProperty, Type* parent) = 0;

	protected:
		// ���캯��
		explicit CAbstractUIEditorFactoryBase() { }
	};

	template <class Type, class PropertyManager>
	class CAbstractUIEditorFactory : public CAbstractUIEditorFactoryBase<Type>
	{
	public:
		// ���캯��
		explicit CAbstractUIEditorFactory(void) { }
		// �����༭��
		virtual Type* CreateEditor(CUIProperty* pProperty, Type* parent)
		{
			std::set<PropertyManager *>::iterator itor = m_managers.begin();
			while (m_managers.end() != ++itor ) {
				PropertyManager *manager = itor;
				if (manager == pProperty->GetPropertyManager()) {
					return CreateEditor(manager, pProperty, parent);
				}
			}

			return (NULL);
		}
		// ������Թ���
		void AddPropertyManager(PropertyManager *manager);
		// �Ƴ����Թ���
		void RemovePropertyManager( PropertyManager *manager );
		std::set<PropertyManager *> propertyManagers() const
		{
			return m_managers;
		}
		// ������Թ���
		PropertyManager *GetPropertyManager( CUIProperty *pProperty ) const;

	protected:
		// ��������
		virtual Type *CreateEditor(PropertyManager *manager, CUIProperty *pProperty,
			Type *parent) = 0;
		virtual void DisconnectPropertyManager(PropertyManager *manager) = 0;

	private:
		std::set<PropertyManager *> m_managers;
		friend class QtAbstractPropertyEditor;
	}

	// ������Թ���
	template <class Type, class PropertyManager>
	void CAbstractUIEditorFactory<Type, PropertyManager>::AddPropertyManager( PropertyManager *manager )
	{
		if (m_managers.end() != m_managers.find(manager))
		{
			return;
		}

		m_managers.insert(manager);
	}

	// �Ƴ����Թ���
	template <class Type, class PropertyManager>
	void CAbstractUIEditorFactory<Type, PropertyManager>::RemovePropertyManager( PropertyManager *manager )
	{
		std::set<CUIProperty*>::iterator itor = m_managers.find(manager);
		if (m_managers.end() == itor)
		{
			return;
		}

		m_managers.erase(itor);
	/*	if (!m_managers.contains(manager))
			return;
		disconnect(manager, SIGNAL(destroyed(QObject *)),
			this, SLOT(managerDestroyed(QObject *)));
		disconnectPropertyManager(manager);
		m_managers.remove(manager);*/
	}

	// ������Թ���
	template <class Type, class PropertyManager>
	PropertyManager * CAbstractUIEditorFactory<Type, PropertyManager>::GetPropertyManager( CUIProperty *pProperty ) const
	{
		CAbstracUItPropertyManager* manager = pProperty->GetPropertyManager();
		set::set<PropertyManager*>::iterator itor = m_managers.begin();
		while (m_managers.end() != itor)
		{
			PropertyManager* m = *itor;
			if (m_managers == m)
			{
				return (m);
			}

			++itor;
		}

		return (NULL);
	}


}

#endif