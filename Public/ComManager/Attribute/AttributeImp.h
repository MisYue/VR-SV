/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性基类			                                        */
/* 时间： 2015-06-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_ATTRIBUTEIMP_H_
#define _PUBLIC_ATTRIBUTEIMP_H_

#include <boost/unordered_map.hpp>
#include "AttributeItemImp.h"

namespace VR_Soft
{
	template <class T>
	class CAttributeImp : public T
	{
	public:
		// 构造函数
		explicit CAttributeImp(IEntityBase* pIEntityComponent, const VRString& strName);
		// 析构函数
		virtual ~CAttributeImp();
		// 获得实体对象
		virtual IEntityBase* GetEntity(void) const;
		// 获得名称
		virtual const VRString& GetName(void) const;
		// 设置名称
		virtual void SetName(const VRString& strName);
		// 获得属性列表
		virtual IAttribute::ListAttrItems GetAttrItems(void) const;
		// 通过属性的名称获取属性项
		virtual IAttributeItem* GetItem(const VRString& strName) const;
		// 设置属性
		virtual void AddAttrItem(IAttributeItem* pIItem) ;
		// 初始化
		virtual void Init(void);
		// 保存到内存中
		virtual void WriteMemory(void);
		// 是否随着移动
		virtual bool IsMove(void) const { return (true) ; }
		// 更新
		virtual void Update(void) { }
		// 读取XML文件
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement) { }
		// 保存XML节点
		virtual void SaveXmlNode(TiXmlElement* pTiXmlElement) const { }
	public:
		typedef std::vector<IAttributeItem*> ListAttributeItes;
		typedef boost::unordered_map<VRString, IAttributeItem*> ListStrAttributeItems;

	private:
		IEntityBase* m_pIEntityBase; // 指定实体
		ListAttributeItes m_listAttributeItems; // 属性项集合
		ListStrAttributeItems m_listStrAttrItems; // 属性项集合
		VRString m_strName; // 名称属性
		mutable bool m_bUpdate; // 是否需要更新
	};

	// 设置名称
	template <class T>
	void VR_Soft::CAttributeImp<T>::SetName( const VRString& strName )
	{
		m_strName = strName;
	}

	template <class T>
	const VRString& VR_Soft::CAttributeImp<T>::GetName( void ) const
	{
		return (m_strName);
	}

	
	// 构造函数
	template <class T>
	CAttributeImp<T>::CAttributeImp(IEntityBase* pIEntityBase, const VRString& strName)
		:m_pIEntityBase(pIEntityBase),m_strName(strName), m_bUpdate(false)
	{
		
	}

	// 析构函数
	template <class T>
	CAttributeImp<T>::~CAttributeImp()
	{
		// 移除属性项
		for (ListStrAttributeItems::iterator itor = m_listStrAttrItems.begin(); m_listStrAttrItems.end() != itor; ++itor)
		{
			VRSOFT_DELETE(itor->second);
		}

		m_listStrAttrItems.clear();
		m_listAttributeItems.clear();
	}

	// 获得实体对象
	template <class T>
	IEntityBase* CAttributeImp<T>::GetEntity(void) const
	{
		return (m_pIEntityBase);
	}
	
	// 获得属性列表
	template <class T>
	IAttribute::ListAttrItems CAttributeImp<T>::GetAttrItems(void) const
	{
		return (m_listAttributeItems);
	}

	// 通过属性的名称获取属性项
	template <class T>
	IAttributeItem* CAttributeImp<T>::GetItem(const VRString& strName) const
	{
		ListStrAttributeItems::const_iterator cstItor = m_listStrAttrItems.find(strName);
		if (m_listStrAttrItems.end() == cstItor)
		{
			return (NULL);
		}

		// 返回对象
		return (cstItor->second);
	}

	// 设置属性
	template <class T>
	void CAttributeImp<T>::AddAttrItem(IAttributeItem* pIItem) 
	{
		if (NULL == pIItem)
		{
			return;
		}

		// 查找是否含有当前的属性值
		const VRString strName = pIItem->GetTypeName();
		ListStrAttributeItems::const_iterator cstItor = m_listStrAttrItems.find(strName);
		if (m_listStrAttrItems.end() == cstItor)
		{
			// 没有当前属性 直接添加进去
		//	((CAttributeItemImp<IAttributeItem>*)pIItem)->SetAttribute(this);
			m_listStrAttrItems.insert(ListStrAttributeItems::value_type(strName, pIItem));
			m_listAttributeItems.push_back(pIItem);
			return;
		}

	}

	// 初始化
	template <class T>
	void CAttributeImp<T>::Init(void)
	{

	}

	// 保存到内存中
	template <class T>
	void CAttributeImp<T>::WriteMemory( void )
	{
		// 遍历选项
		for (ListStrAttributeItems::const_iterator cstItor = m_listStrAttrItems.begin(); \
			cstItor != m_listStrAttrItems.end(); ++cstItor)
		{
//			(*cstItor)->WriteMemory();
		}
		
	}

}

#endif // _PUBLIC_ATTRIBUTEIMP_H_