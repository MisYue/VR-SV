/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ̧ͷHUD��Ļ����ӿ�
 ʱ�䣺 2015-11-29                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _PUBLIC_SCREENHUDMANAGER_H_
#define _PUBLIC_SCREENHUDMANAGER_H_

namespace VR_Soft
{
	class OSGRENDER_DLL IScreenHUDManager
	{
	public:
		// ��������
		virtual ~IScreenHUDManager(void) { }
		// ���HUD����
		virtual IScreenHUD* GetScreenHUD(const VRString& strHUDName, const VRString& strViewName = "mainView") const = 0;
		// ���HUD����
		virtual void AddScreenHUD(const IScreenHUD* pIScreenHUD, const VRString& strViewName = "mainView") = 0;
	};

}

#endif // !_PUBLIC_SCREENHUDMANAGER_H_