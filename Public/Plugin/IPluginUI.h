/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  插件UI接口通过扩展接口实现QT或者其他UI接口					*/
/* 时间： 2015-05-21                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IPLUGINUI_H_
#define _IPLUGINUI_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL IPluginUI
	{
	public:
		// 初始化界面
		virtual void InitUI(void* param = NULL, int nParam = 0) { }
		// 获得名称
		virtual const VRString GetUIName(void) const { return ("no ui"); }
		// 更新UI
		virtual void Update(void* param = NULL, int nParam = 0 ) { }
		// 撤销初始化
		virtual void UnInit(void) { }
	};
}

#endif //_IPLUGINUI_H_