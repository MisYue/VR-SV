/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  渲染管理系统接口		                                        */
/* 时间： 2015-05-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IRENDERMANAGER_H_
#define _IRENDERMANAGER_H_

#pragma once

namespace VR_Soft
{
	const VRString RENDERSYSTEM_TYPENAME = "RENDERSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_RENDERSYSTEM = "RENDERSYSTEM";
	const VRString RENDERSYSTEM_DISC = "渲染系统";

	class IViewManager;
	class IScreenHUDManager;
	class IDrawAttributeFactory;
	class IMeshManager;
	class IDrawTrajectoryManager;

	class OSGRENDER_DLL IRenderManager : public CSingleton<IRenderManager>, public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~IRenderManager() {}
		// 获取视图管理器
		virtual IViewManager* GetViewManager(void) const = 0;
		// 获得屏幕窗口管理对象
		virtual IScreenHUDManager* GetScreenManager(void) const = 0;
		// 查询视图对象
		virtual IRenderView* QuaryViewBayName(const VRString& strViewName) const = 0;
		// 执行渲染
		virtual void Render(void) = 0;
		// 注册事件
		virtual void RegisterEvnet(IEvent* pIEvent, const VRString& strViewName = "mainView") = 0;
		// 反注册事件
		virtual void UnRegisterEvnet(IEvent* pIEvent, const VRString& strViewName = "mainView") = 0;
		// 获得渲染属性工厂
		virtual IDrawAttributeFactory* GetDrawAttributeFactory(void) const = 0;
		// 获得三维实体管理类
		virtual IMeshManager* GetMeshManager(void) = 0;
		// 获得轨迹管理类
		virtual IDrawTrajectoryManager* GetTrajectoryManager(void) = 0;
	};
}

#endif  // _IRENDERMANAGER_H_