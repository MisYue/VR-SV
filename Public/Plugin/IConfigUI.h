/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  配置类接口			                                        */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ICONFIGUI_H_
#define _ICONFIGUI_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL IConfigUI : public IPluginUI
	{
	public:
		// 析构
		virtual ~IConfigUI() {}
		// 初始化
		virtual void InitUI(void* param = NULL) = 0;
	};
}

#endif // _ICONFIGUI_H_