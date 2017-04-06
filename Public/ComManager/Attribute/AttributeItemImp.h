/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性基类			                                        */
/* 时间： 2015-06-12                                                    */
/* 修改时间:                                                            */
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
		// 构造函数
		explicit CAttributeItemImp() ;
		// 构造函数
		explicit CAttributeItemImp(const VRString& strAttriName, const T& value, Contrl contrl = CTRL_EDIT) ;
		// 析构函数
		virtual ~CAttributeItemImp();

	public:
		// 获取属性名称
		virtual VRString GetTypeName() const;
		// 设置名称
		virtual void SetTypeName(const VRString& strName) ;
		// 获得属性显示控件
		virtual Contrl GetCtrlType() const;
		// 设置属性显示控件
		virtual void SetCtrlType(Contrl ctrl = CTRL_EDIT);
		// 

	public:
		// 属性变量访问器
		SET_GET_PROPERTY(Attribute, IAttribute*, pI);

	private:
		VRString m_strAttriName; // 属性名称
		Contrl m_contrlType; // 控件属性
		IAttribute* m_pIAttribute; // 对应属性
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

	// 设置名称
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

	// 设置属性显示控件
	template <class T>
	void CAttributeItemImp<T>::SetCtrlType(Contrl ctrl)
	{
		m_contrlType = ctrl;
	}

}

#endif // _PUBLIC_ATTRIBUTEITEMIMP_H_