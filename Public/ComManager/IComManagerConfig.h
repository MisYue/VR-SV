/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理接口类                                                */
/* 时间： 2015-07-28                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ICOMMANAGERCOFIG_H_
#define _ICOMMANAGERCOFIG_H_

namespace VR_Soft
{
	class VRSOFT_DLL IComManagerConfig
	{
	public:
		// 析构函数
		virtual ~IComManagerConfig() { }
		// 初始化整个系统
		virtual void Init() = 0;
		// 获得路径
		virtual VRString GetCurPath(void) const = 0;		
	};
}

#endif // _ICOMMANAGERCOFIG_H_