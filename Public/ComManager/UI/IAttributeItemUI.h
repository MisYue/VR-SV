/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��������ؼ��ӿ�	                                        */
/* ʱ�䣺 2015-08-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLICE_IATTRIBUTEITEMUI_H_
#define _PUBLICE_IATTRIBUTEITEMUI_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAttributeItemUI
	{
	public:
		// ��������
		virtual ~IAttributeItemUI(void) { }
		// ������Ϣ
		virtual void SetInfor(void) = 0;
		// �ı���Ϣ��Ҫ����
		virtual void SaveInfo(void) = 0;
		// �������
		virtual Contrl GetContrlType(void) = 0;
		// ��ÿؼ�
		virtual void GetContrl(void* pContrl) = 0;
	};
}

#endif // _PUBLICE_IATTRIBUTEITEMUI_H_