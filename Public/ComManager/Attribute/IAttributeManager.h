/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����Թ���ӿ�		                                        */
/* ʱ�䣺 2015-06-02                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IATTRIBUTEMANAGER_H_
#define _IATTRIBUTEMANAGER_H_

#include "IAttributeItem.h"

namespace VR_Soft
{
	class IAttributeUI;

	class VRSOFT_DLL IAttributeManager : public CSingleton<IAttributeManager>
	{
	public:
		// ��������
		virtual ~IAttributeManager() { }
		// ���õ�ǰ������
		virtual void SetCurrentEntityBase(IEntityBase* pIEntityBase) = 0;
		// ��õ�ǰ�����ʵ��
		virtual IEntityBase* GetCurrentEntityBase(void) const = 0;
		// ��õ�ǰ�����ʵ��ID
		virtual uint64_t GetCurrentEntityBaseID(void) const  = 0;
		// �༭��ǰ��ʵ��
		virtual void EidtCurrentEntityBase(void) = 0;
		// �������������
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute, const VRString& strItemName, const VRString& strText, const VRString& strUntil, \
			const VRVariant& var, const Contrl ct =  CTRL_SPINBOX) = 0;
		// �������������
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
			IProperty* var, bool b , const Contrl ct =  CTRL_SPINBOX) = 0;
		// ����������
		virtual void UpdateAttributeItem(const IAttributeItem* pIAttributeItem) = 0;

	public:
		// ��ӹ���
		virtual void AddFactory(IAttributeFactory* pIAttributeFactory) = 0;
		// �Ƴ�����
		virtual void RemoveFactory(const VRString& strFactory) = 0;
		// ��ù���
		virtual IAttributeFactory* GetFactory(const VRString& strFactory) const = 0;
		// ���ļ��м���ָ��dll�� 
		virtual void LoadAttributeDll(void) = 0;
		// ɾ�����еĿ�
		virtual void RemoveAllAttributeDll(void) = 0;
		// �Ƴ�dll��
		virtual void RemoveAttributeDll(const VRString& strDll) = 0;
		// ��ȡ���е�dllָ������
		virtual ListString GetAllAttributeDll(void) const = 0;
		// �����������
		virtual ListString GetAllAttribute(void) const = 0;
		// ��ʵ������
		virtual bool BindAttribute(IEntityBase* pIEntityBase, const VRString& strFactory) = 0;
		// ��ʵ������
		virtual bool BindAttribute(IEntityBase* pIEntityBase, IAttribute* pIAttribute) = 0;
		// �����
		virtual bool UnBindAttribute(IEntityBase* pIEntityBase, const VRString& strFactory) = 0;
		// �����
		virtual bool UnBindAttribute(IEntityBase* pIEntityBase, IAttribute* pIAttribute) = 0;

	public:
		// ע����洰��
		virtual void Attach(IAttributeUI* pIAttributeUI) = 0;
		// �Ƴ��۲���
		virtual void Detach(IAttributeUI* pIAttributeUI) = 0;

	};
}

#endif // _IATTRIBUTEMANAGER_H_