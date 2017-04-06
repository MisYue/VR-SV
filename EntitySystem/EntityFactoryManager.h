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
	class CEntityFactoryManager : public IEntityFactoryManager // CSingleton<CEntityFactoryManager>
	{
	public:
		// ���캯��
		explicit CEntityFactoryManager(void);
		// ��������
		virtual ~CEntityFactoryManager(void);

		// ע�Ṥ��
		void RegisterFactory(IEntityBaseFactory* pIEntityFactory);
		// ж�ع���
		void UnRegisterFactory(const VRString& strFactoryType);
		// ��ù���ʵ��
		IEntityBaseFactory* GetEntityFactory(const VRString& strType) const;
		// ��ù����б�
		virtual const LstFactroys& GetAllEntityFactory(void) const;

	protected:
		// �����Ƿ���ڵ�ǰ����
		bool IsHave(const VRString& strType) const;
		// ɾ�����й���
		void RemoveAll(void);

	protected:
		

	private:
		LstFactroys m_factorys;

		VR_AUTO_MUTEX
	};
}


#endif // _ENTITYFACTORYMANAGER_H_
