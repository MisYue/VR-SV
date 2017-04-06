/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����������湤���ӿ�                                        */
/* ʱ�䣺 2015-08-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IATTRIBUTEUIFACTORY_H_
#define _IATTRIBUTEUIFACTORY_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAttributeUIFactory : public CSingleton<IAttributeUIFactory>
	{
	public:
		virtual ~IAttributeUIFactory() { }

		// ע�����
		virtual void Register(IAttributeItemUI* pIAttributeItemUI) = 0;
		// ��ע�����
		virtual void UnRegister(IAttributeItemUI* pIAttributeItemUI) = 0;
		// ��ÿؼ�
		virtual IAttributeItemUI* GetContrl(IAttributeItem* pIAttributeItem) = 0;
	};
}

#endif // _IATTRIBUTEUIFACTORY_H_