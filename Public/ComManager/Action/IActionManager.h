/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ָ�����ӿ�			                                        */
/* ʱ�䣺 2016-06-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IACTIONMANAGER_H_
#define _PUBLIC_IACTIONMANAGER_H_

namespace VR_Soft
{
	class VRSOFT_DLL IActionManager : public CSingleton<IActionManager>
	{
	public: 
		// ��������
		virtual ~IActionManager(void) { }
		// ���ָ��
		virtual void AddAction(IEntityBase* pIEnity, const VRString& strAciton) = 0;
		// �Ƴ�ָ��
		virtual void RemoveAction(IEntityBase* pIEnity, const int index) = 0;
		// ��ӹ���
		virtual void AddFactory(IActionFactory* pIActionFactory) = 0;
		// �Ƴ�����
		virtual void RemoveFactory(const VRString& strFactory) = 0;
		// ���ļ��м���ָ��dll�� 
		virtual void LoadAction(void) = 0;
		// ��ȡ���е�dllָ������
		virtual ListString GetAllActionDll(void) const = 0;
		// ��õ�ǰʵ���ָ��
		virtual ListString GetAllActionDll(IEntityBase* pIEntity) const = 0;
		// ���ָ��
		virtual IAction* GetAction(IEntityBase* pIEntity, const int index) const = 0;
		// �Ƴ�dll��
		virtual void RemoveActionDll(const VRString& strDll) = 0;
		// ִ��ָ��
		virtual void Execute(const CDateTime& dt) = 0;
		// ��ʼ��
		virtual void Init( void ) = 0;
	};
}

#endif // !_PUBLIC_IACTIONMANAGER_H_