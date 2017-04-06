/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����������湤��	                                        */
/* ʱ�䣺 2015-08-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ATTRIBUTEUIFACTORY_H_
#define _ATTRIBUTEUIFACTORY_H_
#pragma once

namespace VR_Soft
{
	class CAttributeUIFactory : public IAttributeUIFactory
	{
	public:
		explicit CAttributeUIFactory(void);
		virtual ~CAttributeUIFactory(void);

		// ע�����
		virtual void Register(IAttributeItemUI* pIAttributeItemUI);
		// ��ע�����
		virtual void UnRegister(IAttributeItemUI* pIAttributeItemUI);
		// ��ÿؼ�
		virtual IAttributeItemUI* GetContrl(IAttributeItem* pIAttributeItem);

	protected: 
		typedef boost::unordered_map<int, IAttributeItemUI*> AttributItemUIs;

	private:
		AttributItemUIs m_attributeItemUis;

		VR_AUTO_MUTEX
	};
}


#endif // _ATTRIBUTEUIFACTORY_H_