/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����ͽ���ӿ�		                                        */
/* ʱ�䣺 2016-06-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENTITYTYPEUI_H_
#define _PUBLIC_IENTITYTYPEUI_H_

namespace VR_Soft
{
	class VRSOFT_DLL IEntityTypeUI 
	{
	public:
		// ��������
		virtual ~IEntityTypeUI(void) { }
		// ��ʼ��
		virtual void Init(IEntityFactoryManager* pIEntityFactoryManager) = 0;
		// ���һ��ʵ��
		virtual void UpdateNewItem(IEntityBaseFactory* pEntity) = 0;
		// �Ƴ�ʵ��
		virtual void UpdateDelItem(IEntityBaseFactory* pEntity) = 0;
	};
}

#endif // !_PUBLIC_IENTITYTYPEUI_H_