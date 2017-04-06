/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����Ի���			                                        */
/* ʱ�䣺 2015-06-13                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���캯��
		explicit CAttributeImp(IEntityBase* pIEntityComponent, const VRString& strName);
		// ��������
		virtual ~CAttributeImp();
		// ���ʵ�����
		virtual IEntityBase* GetEntity(void) const;
		// �������
		virtual const VRString& GetName(void) const;
		// ��������
		virtual void SetName(const VRString& strName);
		// ��������б�
		virtual IAttribute::ListAttrItems GetAttrItems(void) const;
		// ͨ�����Ե����ƻ�ȡ������
		virtual IAttributeItem* GetItem(const VRString& strName) const;
		// ��������
		virtual void AddAttrItem(IAttributeItem* pIItem) ;
		// ��ʼ��
		virtual void Init(void);
		// ���浽�ڴ���
		virtual void WriteMemory(void);
		// �Ƿ������ƶ�
		virtual bool IsMove(void) const { return (true) ; }
		// ����
		virtual void Update(void) { }
		// ��ȡXML�ļ�
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement) { }
		// ����XML�ڵ�
		virtual void SaveXmlNode(TiXmlElement* pTiXmlElement) const { }
	public:
		typedef std::vector<IAttributeItem*> ListAttributeItes;
		typedef boost::unordered_map<VRString, IAttributeItem*> ListStrAttributeItems;

	private:
		IEntityBase* m_pIEntityBase; // ָ��ʵ��
		ListAttributeItes m_listAttributeItems; // �������
		ListStrAttributeItems m_listStrAttrItems; // �������
		VRString m_strName; // ��������
		mutable bool m_bUpdate; // �Ƿ���Ҫ����
	};

	// ��������
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

	
	// ���캯��
	template <class T>
	CAttributeImp<T>::CAttributeImp(IEntityBase* pIEntityBase, const VRString& strName)
		:m_pIEntityBase(pIEntityBase),m_strName(strName), m_bUpdate(false)
	{
		
	}

	// ��������
	template <class T>
	CAttributeImp<T>::~CAttributeImp()
	{
		// �Ƴ�������
		for (ListStrAttributeItems::iterator itor = m_listStrAttrItems.begin(); m_listStrAttrItems.end() != itor; ++itor)
		{
			VRSOFT_DELETE(itor->second);
		}

		m_listStrAttrItems.clear();
		m_listAttributeItems.clear();
	}

	// ���ʵ�����
	template <class T>
	IEntityBase* CAttributeImp<T>::GetEntity(void) const
	{
		return (m_pIEntityBase);
	}
	
	// ��������б�
	template <class T>
	IAttribute::ListAttrItems CAttributeImp<T>::GetAttrItems(void) const
	{
		return (m_listAttributeItems);
	}

	// ͨ�����Ե����ƻ�ȡ������
	template <class T>
	IAttributeItem* CAttributeImp<T>::GetItem(const VRString& strName) const
	{
		ListStrAttributeItems::const_iterator cstItor = m_listStrAttrItems.find(strName);
		if (m_listStrAttrItems.end() == cstItor)
		{
			return (NULL);
		}

		// ���ض���
		return (cstItor->second);
	}

	// ��������
	template <class T>
	void CAttributeImp<T>::AddAttrItem(IAttributeItem* pIItem) 
	{
		if (NULL == pIItem)
		{
			return;
		}

		// �����Ƿ��е�ǰ������ֵ
		const VRString strName = pIItem->GetTypeName();
		ListStrAttributeItems::const_iterator cstItor = m_listStrAttrItems.find(strName);
		if (m_listStrAttrItems.end() == cstItor)
		{
			// û�е�ǰ���� ֱ����ӽ�ȥ
		//	((CAttributeItemImp<IAttributeItem>*)pIItem)->SetAttribute(this);
			m_listStrAttrItems.insert(ListStrAttributeItems::value_type(strName, pIItem));
			m_listAttributeItems.push_back(pIItem);
			return;
		}

	}

	// ��ʼ��
	template <class T>
	void CAttributeImp<T>::Init(void)
	{

	}

	// ���浽�ڴ���
	template <class T>
	void CAttributeImp<T>::WriteMemory( void )
	{
		// ����ѡ��
		for (ListStrAttributeItems::const_iterator cstItor = m_listStrAttrItems.begin(); \
			cstItor != m_listStrAttrItems.end(); ++cstItor)
		{
//			(*cstItor)->WriteMemory();
		}
		
	}

}

#endif // _PUBLIC_ATTRIBUTEIMP_H_