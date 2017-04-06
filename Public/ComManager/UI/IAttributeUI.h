/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ������UI�ӿ�		                                        */
/* ʱ�䣺 2015-06-02                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IATTRIBUTEUI_H_
#define _IATTRIBUTEUI_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAttributeUI // : public IPluginUI
	{
	public:
		// ��������
		virtual ~IAttributeUI() { }
		// ����������Խ���
		virtual void Clear(void) = 0;
		// ����ʵ��
		virtual void ChangeEntity(IEntityBase* pIEntity) = 0;
		// ���һ��ʵ��
		virtual void UpdateNewItem(IAttribute* pIAttribute) = 0;
		// �Ƴ�ʵ��
		virtual void UpdateDelItem(IAttribute* pIAttribute) = 0;

	};
}

#endif // _IATTRIBUTEUI_H_