/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��������ؼ�ģ��	                                        */
/* ʱ�䣺 2015-08-12                                                    */
/* �޸�ʱ��:                                                            */
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

		// ����������
		SET_GET_PROPERTY(AttributeItem, IAttributeItem* , pI)

		// ��¡����
		virtual T* Clone(void) {  return (NULL); }

	private:
		IAttributeItem* m_pIAttributeItem;
	};
}

#endif // _PUBLICE_ATTRIBUTEITEMUIIMP_H_