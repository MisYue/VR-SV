/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ģ�͹������	                                                */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IENTITYMANAGER_H_
#define _IENTITYMANAGER_H_

namespace VR_Soft
{
	class IAttributeUIFactory;
	class IEntityManagerUI;
	class IStrategyManager;

	class VRSOFT_DLL IEntityManager : public CSingleton<IEntityManager>
	{
	public:
		// ��������
		virtual ~IEntityManager() { }
		// �����ͼģ��
		virtual void AddEntity(IEntityBase* pIEntity) = 0;
		// �Ƴ�����
		virtual void RemoveEntity(IEntityBase* pIEntity) = 0;
		// �Ƴ����� 
		virtual void RemoveEntity(const VRString& strName) = 0;
		// ɾ�����е���ʵ��
		virtual void RemoveAllEntity(void) = 0;
		// ��ȡ���е��Ӽ�
		virtual const std::vector<IEntityBase*>& GetAllEntities(void) const = 0;
		// ��������Ӽ�
		virtual std::vector<IEntityBase*> GetEntities(const VRString& strType) const = 0;
		// ͨ�����Ʋ�ѯʵ�� �ҵ���һ��ʵ�ֵ�ֱֵ�ӷ���
		virtual IEntityBase* GetEntity(const uint64_t uID) const = 0;
		// ���ʵ��ģ��
		virtual IEntityBase* GetEntity(const VRString& strEntityName) const = 0;
		// ���ģ�͸���
		virtual int GetCount(void) const  = 0;
		// ģ�͸��£�ÿһ����֡����)
		virtual void EntityUpdate(const CDateTime& dt) = 0;
		// ��ù�������
		virtual IEntityFactoryManager* GetEntityFactoryManager(void) = 0;
		// ͨ������������ѯ��Ӧ��ʵ��
		virtual IEntityBase* CreateEntity(const VRString& strName, const uint64_t ID) = 0;
		// �޸�ʵ������
		virtual void ChangeEntityName(IEntityBase* pIEntity, const VRString& strOld, const VRString& strNew) const = 0;
		// ��ӹ۲��� 
		virtual void Attach(IEntityManagerUI* pIEntityManagerUI) = 0;
		// �Ƴ��۲���
		virtual void Detach(IEntityManagerUI* pIEntityManagerUI) = 0;
	};
}

#endif // _IENTITYMANAGER_H_