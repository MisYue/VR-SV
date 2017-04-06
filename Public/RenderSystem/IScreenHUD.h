/************************************************************************
 作者： LJ                                                            
 用途:  抬头HUD屏幕接口
 时间： 2015-11-28                                                    
 修改时间:                                                            
************************************************************************/

#ifndef _PUBLIC_ISCREENHUD_H_
#define _PUBLIC_ISCREENHUD_H_

namespace VR_Soft
{
	class OSGRENDER_DLL IScreenHUD
	{
	public: 
		// 析构函数
		virtual ~IScreenHUD() { }
		// 设置窗口名称
		virtual void SetHUDName(const VRString& strName) = 0;
		// 获得窗口名称
		virtual const VRString& GetHUDName(void) const = 0;
		// 移动位置
		virtual void Move(int x, int y, int width, int height)  = 0;
		// 设置文字
		virtual void SetText(const VRString& strText) = 0;
		// 设置背景颜色
		virtual void SetBgColor(const float r, const float g, const float b, const float a = 1.0f) = 0;
		// 显示
		virtual void Show(void) = 0;
		// 隐藏
		virtual void Hide(void) = 0;
		// 显示隐藏状态
		virtual bool ShowState(void)const = 0;
	};
}

#endif