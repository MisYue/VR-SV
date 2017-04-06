/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�������			                                        */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#pragma once

#include "EntityFactoryManager.h"

namespace VR_Soft
{
	class CEntityManager : public IEntityComposite
	{
	public:
		explicit CEntityManager(const VRString& strComponentName);
		virtual ~CEntityManager(void);

	public:
		// ���ʵ��ģ��
		virtual IEntityComponent* GetEntity(const VRString& strEntityID) const;
		// �����ͼģ��
		virtual void AddEntity(IEntityComponent* pIEntity);
		// �Ƴ�����
		virtual void RemoveEntity(IEntityComponent* pIEntity);
		// �Ƴ����� 
		virtual void RemoveEntity(const VRString& strName);
		// ɾ�����е���ʵ��
		virtual void RemoveAllEntity(void);
		// �ı�ʵ��ģ�����Ʒ�����в���
		virtual bool ChangeEntityName(IEntityComponent* pIEntity, const VRString& strNewName);
		// ��ȡ���е��Ӽ�
		virtual const LstEntitys GetLstEntitys(void) const;
		// ͨ�����Ʋ�ѯʵ�� �ҵ���һ��ʵ�ֵ�ֱֵ�ӷ���
		virtual IEntityComponent* GetEntity(const VRString& strName);
		// ͨ������������ѯ��Ӧ��ʵ��
		virtual IEntityComponent* GetEntity(const VRString& strCompName, const VRString& strEntityID);
		// ͨ�������ͻ�ö�Ӧ��ʵ��
		virtual IEntityComponent* GetEntity(IEntityComponent* pIComponent, const VRString& strEntityID);
		// ģ�͸��£�ÿһ����֡����)
		virtual void EntityUpdate(double dt);
		// ��ù�������
		virtual IEntityFactoryManager* GetEntityFactoryManager(void);
		// ͨ����������������Ӧ��ʵ��
		virtual IEntityComponent* CreateEntity(const VRString& strCompName, const VRString& strType, const uint64_t ID);
		// ͨ������������ѯ��Ӧ��ʵ��
		virtual IEntityComponent* CreateEntity(IEntityComponent* pIComponent, const VRString& strType, const uint64_t ID);

	private:

	protected:
		typedef std::map<VRString, IEntityComponent*> MapStrEntity;

	private:
		MapStrEntity m_mapStrEntity; // ʵ������б�

		CEntityFactoryManager m_entityFactoryManager; // ʵ�幤������

		VR_AUTO_MUTEX
	};
}

#endif // _ENTITYMANAGER_H_