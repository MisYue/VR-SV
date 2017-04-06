/************************************************************************
 作者： LJ                                                            
 用途:  抬头HUD屏幕管理接口
 时间： 2015-11-29                                                    
 修改时间:                                                            
************************************************************************/

#ifndef _PUBLIC_SCREENHUDMANAGER_H_
#define _PUBLIC_SCREENHUDMANAGER_H_

namespace VR_Soft
{
	class OSGRENDER_DLL IScreenHUDManager
	{
	public:
		// 析构函数
		virtual ~IScreenHUDManager(void) { }
		// 获得HUD窗口
		virtual IScreenHUD* GetScreenHUD(const VRString& strHUDName, const VRString& strViewName = "mainView") const = 0;
		// 添加HUD窗口
		virtual void AddScreenHUD(const IScreenHUD* pIScreenHUD, const VRString& strViewName = "mainView") = 0;
	};

}

#endif // !_PUBLIC_SCREENHUDMANAGER_H_