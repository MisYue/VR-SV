/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����๤��������	                                        */
/* ʱ�䣺 2015-06-09                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ENTITYFACTORYMANAGER_H_
#define _ENTITYFACTORYMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CEntityFileManager;

	class CEntityFactoryManager : public IEntityFactoryManager // CSingleton<CEntityFactoryManager>
	{
	public:
		// ���캯��
		explicit CEntityFactoryManager(void);
		// ��������
		virtual ~CEntityFactoryManager(void);

		// ע�Ṥ��
		virtual void RegisterFactory(IEntityBaseFactory* pIEntityFactory);
		// ж�ع���
		virtual void UnRegisterFactory(const VRString& strFactoryType);
		// ��ù���ʵ��
		virtual IEntityBaseFactory* GetEntityFactory(const VRString& strType) const;
		// ��ù����б�
		virtual const ListString GetAllEntityFactory(void) const;

	public:
		// ��ӹ۲���
		virtual void Attach(IEntityTypeUI* pIEntityTypeUI);
		// �Ƴ��۲���
		virtual void Detach(IEntityTypeUI* pIEntityTypeUI);

	protected:
		// �����Ƿ���ڵ�ǰ����
		bool IsHave(const VRString& strType) const;
		// ɾ�����й���
		void RemoveAll(void);

	protected:
		typedef boost::unordered_map<VRString, IEntityBaseFactory*> ListStrEntityBaseFactories;
		typedef boost::unordered_set<IEntityTypeUI*> ListEntityTypeUIs;
		

	private:
		ListStrEntityBaseFactories m_factorys;
		ListEntityTypeUIs m_listEntityTypeUIs;
		CEntityFileManager* m_pEntityFileManager; // �ļ�ʵ����
		VR_AUTO_MUTEX
	};
}


#endif // _ENTITYFACTORYMANAGER_H_
