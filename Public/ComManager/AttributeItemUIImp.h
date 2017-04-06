/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性项控件模板	                                        */
/* 时间： 2015-08-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLICE_ATTRIBUTEITEMUIIMP_H_
#define _PUBLICE_ATTRIBUTEITEMUIIMP_H_

namespace VR_Soft
{
	template <class T>
	class CAttributeItemUIImp : public T
	{
	public: 
		explicit CAttributeItemUIImp(void) : m_pIAttributeItem(NULL) { }
		virtual ~CAttributeItemUIImp() {}

		// 设置属性项
		SET_GET_PROPERTY(AttributeItem, IAttributeItem* , pI)

		// 克隆函数
		virtual T* Clone(void) {  return (NULL); }

	private:
		IAttributeItem* m_pIAttributeItem;
	};
}

#endif // _PUBLICE_ATTRIBUTEITEMUIIMP_H_