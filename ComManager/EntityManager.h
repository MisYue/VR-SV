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

#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	class CEntityManager : public IEntityManager
	{
	public:
		explicit CEntityManager(void);
		virtual ~CEntityManager(void);

	public:
		// �����ͼģ��
		virtual void AddEntity(IEntityBase* pIEntity);
		// �Ƴ�����
		virtual void RemoveEntity(IEntityBase* pIEntity);
		// �Ƴ����� 
		virtual void RemoveEntity(const VRString& strName);
		// �Ƴ�����
		virtual void RemoveEntity(const uint64_t ID);
		// ɾ�����е���ʵ��
		virtual void RemoveAllEntity(void);
		// ��ȡ���е��Ӽ�
		virtual const std::vector<IEntityBase*>& GetAllEntities(void) const;
		// ��������Ӽ�
		virtual std::vector<IEntityBase*> GetEntities(const VRString& strType) const ;
		// ���ģ�͸���
		virtual int GetCount(void) const;
		// ͨ�����Ʋ�ѯʵ�� �ҵ���һ��ʵ�ֵ�ֱֵ�ӷ���
		virtual IEntityBase* GetEntity(const uint64_t uID) const;
		// ���ʵ��ģ��
		virtual IEntityBase* GetEntity(const VRString& strEntityName) const;
		// ģ�͸��£�ÿһ����֡����)
		virtual void EntityUpdate(const CDateTime& dt);
		// ��ù�������
		virtual IEntityFactoryManager* GetEntityFactoryManager(void);
		// ͨ������������ѯ��Ӧ��ʵ��
		virtual IEntityBase* CreateEntity(const VRString& strName, const uint64_t ID);
		// �޸�ʵ������
		virtual void ChangeEntityName(IEntityBase* pIEntity, const VRString& strOld, const VRString& strNew) const ;


	public:
		// ��ӹ۲���
		virtual void Attach(IEntityManagerUI* pIEntityManagerUI) ;
		// �Ƴ��۲���
		virtual void Detach(IEntityManagerUI* pIEntityManagerUI) ;

	public:
		// ��ʼ��
		void Init(void);
		// �Ƴ�����
		void RemoveFactory(IEntityBaseFactory* pIEntityBaseFactory);
		// ͨ����������ϵͳʵ����ļ�ʵ��
		IEntityBase* CreateEntityByFactory(const VRString& strName, const uint64_t ID);
		// �Ƴ����еĹ���
		void RemoveAllFactroy(void);

	protected:
		typedef boost::unordered_map<uint64_t, IEntityBase*> ListIDEntities; // ʵ������
		typedef std::vector<IEntityBase*> VectEntities; // ����ʵ�弯��
		typedef std::vector<uint64_t> VectEntityIDs;
		typedef boost::unordered_map<IEntityBaseFactory*, VectEntityIDs> ListFactoryEntities; // ʵ�幤����Ӧ

		typedef boost::unordered_set<IEntityManagerUI*> ListEntityManagerUI;

	private:
		ListIDEntities m_listIDEntities; // ID��ģ���б�
		VectEntities m_vecEntities; // ����ʵ�弯��

		CEntityFactoryManager m_entityFactoryManager; // ʵ�幤������
		ListFactoryEntities m_listFactoryEntities; // ʵ�幤����Ӧ

		ListEntityManagerUI m_listEntityManagerUI; // ���湤��

		VR_AUTO_MUTEX
	};
}

#endif // _ENTITYMANAGER_H_