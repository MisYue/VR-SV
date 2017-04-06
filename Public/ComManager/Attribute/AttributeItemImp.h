/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����Ի���			                                        */
/* ʱ�䣺 2015-06-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_ATTRIBUTEITEMIMP_H_
#define _PUBLIC_ATTRIBUTEITEMIMP_H_

#include "IAttributeItem.h"

namespace VR_Soft
{
	template <class T>
	class CAttributeItemImp : public T // IAttributeItem
	{
	public:
		// ���캯��
		explicit CAttributeItemImp() ;
		// ���캯��
		explicit CAttributeItemImp(const VRString& strAttriName, const T& value, Contrl contrl = CTRL_EDIT) ;
		// ��������
		virtual ~CAttributeItemImp();

	public:
		// ��ȡ��������
		virtual VRString GetTypeName() const;
		// ��������
		virtual void SetTypeName(const VRString& strName) ;
		// ���������ʾ�ؼ�
		virtual Contrl GetCtrlType() const;
		// ����������ʾ�ؼ�
		virtual void SetCtrlType(Contrl ctrl = CTRL_EDIT);
		// 

	public:
		// ���Ա���������
		SET_GET_PROPERTY(Attribute, IAttribute*, pI);

	private:
		VRString m_strAttriName; // ��������
		Contrl m_contrlType; // �ؼ�����
		IAttribute* m_pIAttribute; // ��Ӧ����
	};

	template <class T>
	CAttributeItemImp<T>::CAttributeItemImp(): m_strAttriName(""), m_pIAttribute(NULL), m_contrlType(CTRL_EDIT)
	{

	}

	template <class T>
	CAttributeItemImp<T>::CAttributeItemImp(const VRString& strAttriName, const T& value, Contrl contrl /*= CTRL_EDIT*/) :
	m_strAttriName(strAttriName), m_pIAttribute(NULL),  m_contrlType(contrl)//,m_value(value)
	{

	}

	template <class T>
	CAttributeItemImp<T>::~CAttributeItemImp()
	{

	}

	template <class T>
	VRString CAttributeItemImp<T>::GetTypeName() const
	{
		return (m_strAttriName);
	}

	// ��������
	template <class T>
	void CAttributeItemImp<T>::SetTypeName(const VRString& strName) 
	{
		m_strAttriName = strName;
	}

	template <class T>
	Contrl CAttributeItemImp<T>::GetCtrlType() const
	{
		return (m_contrlType);
	}

	// ����������ʾ�ؼ�
	template <class T>
	void CAttributeItemImp<T>::SetCtrlType(Contrl ctrl)
	{
		m_contrlType = ctrl;
	}

}

#endif // _PUBLIC_ATTRIBUTEITEMIMP_H_