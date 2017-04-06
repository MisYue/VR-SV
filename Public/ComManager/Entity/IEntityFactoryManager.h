/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����๤������ӿ�	                                        */
/* ʱ�䣺 2015-07-29                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IENTITYFACTORYMANAGER_H_
#define _IENTITYFACTORYMANAGER_H_

namespace VR_Soft
{
	class IEntityTypeUI;

	class VRSOFT_DLL IEntityFactoryManager : public CSingleton<IEntityFactoryManager>
	{
	public:
		// ��������
		virtual ~IEntityFactoryManager() { }
		// ע�Ṥ��
		virtual void RegisterFactory(IEntityBaseFactory* pIEntityFactory) = 0;
		// ж�ع���
		virtual void UnRegisterFactory(const VRString& strFactoryType) = 0;
		// ��ù���ʵ��
		virtual IEntityBaseFactory* GetEntityFactory(const VRString& strType) const = 0;
		// ��ù����б�
		virtual const ListString GetAllEntityFactory(void) const = 0;
		// ��ӹ۲���
		virtual void Attach(IEntityTypeUI* pIEntityTypeUI) = 0;
		// �Ƴ��۲���
		virtual void Detach(IEntityTypeUI* pIEntityTypeUI) = 0;
	};
}

#endif // _IENTITYFACTORYMANAGER_H_