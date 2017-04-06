/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����Ϲ�����		                                        */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IENTITYCOMPOSITE_H_
#define _IENTITYCOMPOSITE_H_

namespace VR_Soft
{
	class IEntityFactoryManager;

	class VRSOFT_DLL IEntityComposite : public IEntityComponent
	{
	public:
		typedef std::list<IEntityComponent*> LstEntitys;
	public:
		// ��������
		virtual ~IEntityComposite(void) {}
		// �ı�ʵ��ģ�����Ʒ�����в���
		virtual bool ChangeEntityName(IEntityComponent* pIEntity, const VRString& strNewName) { return (false); }
		// �Ƿ����Ӽ�
		virtual bool IsExport(void) { return (true); }
		// ��ù�������
		virtual IEntityFactoryManager* GetEntityFactoryManager(void) { return (NULL); }
		// ��Ӷ���
		virtual void AddEntity(IEntityComponent* pIEntity) { }
		// �Ƴ�����
		virtual void RemoveEntity(IEntityComponent* pIEntity) { }
		// �Ƴ����� ����ɾ��ʵ�ʶ��� �����޸����ƶ��ѣ�
		virtual void RemoveEntity(const VRString& strName) { }
		// ɾ�����ж���
		virtual void RemoveAllEntity(void) { }
		// ��ѯ��ö���
		virtual IEntityComponent* GetEntity(const VRString& strEntityID) { return (NULL); }
		// ��ȡ���е��Ӽ�
		virtual const LstEntitys GetLstEntitys(void) const { LstEntitys lstEntitys; return (lstEntitys);  }
		// ͨ������������ѯ��Ӧ��ʵ��
		virtual IEntityComponent* GetEntity(const VRString& strCompName, const VRString& strEntityID) { return (NULL); }
		// ͨ������������ѯ��Ӧ��ʵ��
		virtual IEntityComponent* GetEntity(IEntityComponent* pIComponent, const VRString& strEntityID) { return (NULL); }
		// ͨ����������������Ӧ��ʵ��
		virtual IEntityComponent* CreateEntity(const VRString& strCompName, const VRString& strType, const uint64_t ID) { return (NULL); }
		// ͨ������������ѯ��Ӧ��ʵ��
		virtual IEntityComponent* CreateEntity(IEntityComponent* pIComponent, const VRString& strType, const uint64_t ID) { return (NULL); }

	};
}

#endif // _IENTITYCOMPOSITE_H_