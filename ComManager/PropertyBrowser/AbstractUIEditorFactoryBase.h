/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  属性相关工厂			                                        */
/* 时间： 2016-09-13                                                    */
/* 修改时间:                                                            */
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
		// 创建编辑器
		virtual Type* CreateEditor(CUIProperty* pProperty, Type* parent) = 0;

	protected:
		// 构造函数
		explicit CAbstractUIEditorFactoryBase() { }
	};

	template <class Type, class PropertyManager>
	class CAbstractUIEditorFactory : public CAbstractUIEditorFactoryBase<Type>
	{
	public:
		// 构造函数
		explicit CAbstractUIEditorFactory(void) { }
		// 创建编辑器
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
		// 添加属性管理
		void AddPropertyManager(PropertyManager *manager);
		// 移除属性管理
		void RemovePropertyManager( PropertyManager *manager );
		std::set<PropertyManager *> propertyManagers() const
		{
			return m_managers;
		}
		// 获得属性管理
		PropertyManager *GetPropertyManager( CUIProperty *pProperty ) const;

	protected:
		// 创建窗口
		virtual Type *CreateEditor(PropertyManager *manager, CUIProperty *pProperty,
			Type *parent) = 0;
		virtual void DisconnectPropertyManager(PropertyManager *manager) = 0;

	private:
		std::set<PropertyManager *> m_managers;
		friend class QtAbstractPropertyEditor;
	}

	// 添加属性管理
	template <class Type, class PropertyManager>
	void CAbstractUIEditorFactory<Type, PropertyManager>::AddPropertyManager( PropertyManager *manager )
	{
		if (m_managers.end() != m_managers.find(manager))
		{
			return;
		}

		m_managers.insert(manager);
	}

	// 移除属性管理
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

	// 获得属性管理
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