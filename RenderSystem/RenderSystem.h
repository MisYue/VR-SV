/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  渲染管理系统接口		                                        */
/* 时间： 2015-05-15                                                    */
/* 修改时间:						                                    */
/************************************************************************/
#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

//#include "rendersystem_global.h"

#include "RenderThread.h"

namespace VR_Soft
{
	class IScreenHUDManager;
	class CScreenHUDManager;
	class IScreenHUDManager;
	class CDrawAttributeFactory;
	class CMeshManager;
	class CInpute;
	class CDrawTrajectoryManager;

	class CRenderSystem : public IRenderManager
	{
	public:
		explicit CRenderSystem(const VRString& strName);
		virtual ~CRenderSystem(void);

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 初始化系统
		virtual void Init(void);
		// 获取视图管理器
		virtual IViewManager* GetViewManager(void) const;
		// 获得屏幕窗口管理对象
		virtual IScreenHUDManager* GetScreenManager(void) const;
		// 查询视图对象
		virtual IRenderView* QuaryViewBayName(const VRString& strViewName) const;
		// 执行渲染
		virtual void Render(void);
		// 注册事件
		virtual void RegisterEvnet(IEvent* pIEvent, const VRString& strViewName = "mainView");
		// 反注册事件
		virtual void UnRegisterEvnet(IEvent* pIEvent, const VRString& strViewName = "mainView");
		// 获得渲染属性工厂
		virtual IDrawAttributeFactory* GetDrawAttributeFactory(void) const ;
		// 获得三维实体管理类
		virtual IMeshManager* GetMeshManager(void);
		// 获得轨迹管理类
		virtual IDrawTrajectoryManager* GetTrajectoryManager(void) ;

	public:
		SET_GET_PROPERTY(Name, VRString, str);

	private:
		VRString m_strName;

		IViewManager* m_pIViewManager; // 视图管理
		CScreenHUDManager* m_pScreenHUDManager; // 屏幕窗口管理
		CRenderThread* m_pRenderThread;

		CDrawAttributeFactory* m_pDrawAttributeFactory; // 属性工厂
		CMeshManager* m_pMeshManager; // 实体管理对象
		CDrawTrajectoryManager* m_pDrawTrajectoryManager; // 绘制线管理类

		VR_AUTO_MUTEX
	};

	// 注册工厂类
	REGISTER_COMFACTORY(CRenderSystem, RenderManager, RENDERSYSTEM_TYPENAME, INSTANCE_NAME_RENDERSYSTEM, RENDERSYSTEM_DISC);
}


#endif // RENDERSYSTEM_H
