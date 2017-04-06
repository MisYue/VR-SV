/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ̧ͷHUD��Ļ�ӿ�
 ʱ�䣺 2015-11-28                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _PUBLIC_ISCREENHUD_H_
#define _PUBLIC_ISCREENHUD_H_

namespace VR_Soft
{
	class OSGRENDER_DLL IScreenHUD
	{
	public: 
		// ��������
		virtual ~IScreenHUD() { }
		// ���ô�������
		virtual void SetHUDName(const VRString& strName) = 0;
		// ��ô�������
		virtual const VRString& GetHUDName(void) const = 0;
		// �ƶ�λ��
		virtual void Move(int x, int y, int width, int height)  = 0;
		// ��������
		virtual void SetText(const VRString& strText) = 0;
		// ���ñ�����ɫ
		virtual void SetBgColor(const float r, const float g, const float b, const float a = 1.0f) = 0;
		// ��ʾ
		virtual void Show(void) = 0;
		// ����
		virtual void Hide(void) = 0;
		// ��ʾ����״̬
		virtual bool ShowState(void)const = 0;
	};
}

#endif