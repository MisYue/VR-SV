/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  地下防御系统接口		                                        */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IUNDERGROUNDSYSTEM_H_
#define _PUBLIC_IUNDERGROUNDSYSTEM_H_

namespace VR_Soft
{
	const VRString UNDERGROUNDSYSTEM_TYPENAME = "UNDERGROUNDSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_UNDERGROUNDSYSTEM = "UNDERGROUNDSYSTEM";
	const VRString UNDERGROUNDSYSTEM_DISC = "地下防御系统";

	class VRSOFT_PLUGIN_DLL IUndergroundManager : public CSingleton<IUndergroundManager>, public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~IUndergroundManager() { }
		// 设置显示的视图名称
		virtual void SetViewName(const VRString& strViewName = "mainView") = 0;
	};
}

#endif // _PUBLIC_IUNDERGROUNDSYSTEM_H_