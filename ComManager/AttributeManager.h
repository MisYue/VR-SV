/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����Թ���ʵ����	                                        */
/* ʱ�䣺 2015-06-02                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ATTRIBUTEMANAGER_H_
#define _ATTRIBUTEMANAGER_H_

#pragma once

#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	class IEntityBase;
	/*class IAttribute;*/

	class CAttributeManager : public IAttributeManager
	{
	public:
		// ���캯��
		explicit CAttributeManager(void);
		// ��������
		virtual ~CAttributeManager(void);

		// ���õ�ǰ������
		virtual void SetCurrentEntityBase(IEntityBase* pIEntityBase);
		// ��õ�ǰ�����ʵ��
		virtual IEntityBase* GetCurrentEntityBase(void) const ;
		// ��õ�ǰ�����ʵ��ID
		virtual uint64_t GetCurrentEntityBaseID(void) const ;
		// �༭��ǰ��ʵ��
		virtual void EidtCurrentEntityBase(void) ;
		// �������������
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
			const VRVariant& var, const Contrl ct =  CTRL_SPINBOX);
		// �������������
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
			IProperty* var, bool b , const Contrl ct =  CTRL_SPINBOX);
		// ����������
		virtual void UpdateAttributeItem(const IAttributeItem* pIAttributeItem);

	public:
		// ��ӹ���
		virtual void AddFactory(IAttributeFactory* pIAttributeFactory) ;
		// �Ƴ�����
		virtual void RemoveFactory(const VRString& strFactory) ;
		// ��ù���
		virtual IAttributeFactory* GetFactory(const VRString& strFactory) const;
		// ���ļ��м���ָ��dll�� 
		virtual void LoadAttributeDll(void);
		// ɾ�����еĿ�
		virtual void RemoveAllAttributeDll(void) ;
		// �Ƴ�dll��
		virtual void RemoveAttributeDll(const VRString& strDll) ;
		// ��ȡ���е�dllָ������
		virtual ListString GetAllAttributeDll(void) const ;
		// �����������
		virtual ListString GetAllAttribute(void)  const;
		// ��ʵ������
		virtual bool BindAttribute(IEntityBase* pIEntityBase, const VRString& strFactory);
		// ��ʵ������
		virtual bool BindAttribute(IEntityBase* pIEntityBase, IAttribute* pIAttribute) ;
		// �Ӵ���
		virtual bool UnBindAttribute(IEntityBase* pIEntityBase, const VRString& strFactory) ;
		// �����
		virtual bool UnBindAttribute(IEntityBase* pIEntityBase, IAttribute* pIAttribute) ;

	public:
		// ע����洰��
		virtual void Attach(IAttributeUI* pIAttributeUI);
		// �Ƴ��۲���
		virtual void Detach(IAttributeUI* pIAttributeUI);

	protected:
		// ����UI
		void UpdateAttributeUI(IEntityBase* pIEntityBase);
		// ����dll��
		void LoadDll(const VRString& strDllPath);
		// ��ʼ��
		void Init(void);
		// �Ƴ����е����Թ���
		void RemoveAllFactory(void);
	protected:
// 		typedef std::map<IEntityBase*, IAttribute*> MapEntityAttribute;
 		typedef boost::unordered_set<IAttributeUI*> VctAttributeUI;

		typedef boost::unordered_map<VRString, CDyLib*> ListAttributeDlls; // dll ��Ӧ����
		typedef boost::unordered_map<VRString, IAttributeFactory*> ListAttributeFactories;  // ��������
		typedef std::vector<uint64_t> ListEntities; // ����ID����
		typedef boost::unordered_map<IAttributeFactory*, ListEntities> ListAttributeFactoriesEntities; // ������Ӧ��ʵ��

	private:
//		MapEntityAttribute m_mapEntityAttribute; // ģ�������б�
		VctAttributeUI m_vecAttributeUI; // ���漯��
		uint64_t m_uCurrentID; // IEntityBase* m_pICurEntityBase; // ��ǰģ���б�

		ListAttributeDlls m_listAttributeDlls;
		ListAttributeFactories m_listAttributeFactories; // ��������
		ListAttributeFactoriesEntities m_listAttributeFactoriesEntities; // ������Ӧ��ʵ��

		VR_AUTO_MUTEX
	};
}


#endif // _ATTRIBUTEMANAGER_H_