/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��������ӿ�		                                        */
/* ʱ�䣺 2016-06-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENTITYMANAGERUI_H_
#define _PUBLIC_IENTITYMANAGERUI_H_

namespace VR_Soft
{
	class VRSOFT_DLL IEntityManagerUI 
	{
	public:
		// ��������
		virtual ~IEntityManagerUI(void) { }
		// ��ʼ��
		virtual void Init(IEntityManager* pIEntityManager) = 0;
		// ���һ��ʵ��
		virtual void UpdateNewItem(IEntityBase* pEntity) = 0;
		// �Ƴ�ʵ��
		virtual void UpdateDelItem(IEntityBase* pEntity) = 0;
		// ����ʵ������
		virtual void UpdateItem(IEntityBase* pEntity, const VRString& strOldName, const VRString& strNemName ) = 0;
	};
}

#endif // !_PUBLIC_IENTITYMANAGERUI_H_