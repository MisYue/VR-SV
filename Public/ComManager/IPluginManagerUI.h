/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理界面对外接口                                          */
/* 时间： 2015-07-23                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IPLUGINMANGERUI_H_
#define _IPLUGINMANGERUI_H_

namespace VR_Soft
{
	class IPluginManagerUI
	{
	public:
		// 析构函数
		virtual ~IPluginManagerUI(void) 
		{
			IComManager::GetInstance().GetComManagerUI()->UnRegisterUI(this);
		}
		// 初始化
		virtual void InitUI(const IComManagerUI::PluginInfoList& lstPluginInfo) = 0;
	};
}

#endif // _IPLUGINMANGERUI_H_