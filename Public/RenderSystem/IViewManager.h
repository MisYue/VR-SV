/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  视图管理接口			                                        */
/* 时间： 2015-05-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IVIEWMANAGER_H_
#define _IVIEWMANAGER_H_

#pragma once
//#include <osgQt/GraphicsWindowQt>
#include "IRenderView.h"
#include "IRenderViewUI.h"

namespace VR_Soft
{
	class IDrawAttribute;

	class OSGRENDER_DLL IViewManager : public CSingleton<IViewManager>
	{
	public:
		// 析构函数
		virtual ~IViewManager() { }
		// 创建视图
		virtual void CreateView(const VRString& strViewName, int x, int y, int width, int height) = 0;
		// 注册UI
		virtual void RegisterViewUI(IRenderViewUI* pRenderViewUI) = 0;
		// 反注册UI
		virtual void UnReginsterViewUI(IRenderViewUI* pRenderViewUI) = 0;
		// 查询视图
		virtual IRenderView* GetRenderView(const VRString& strViewName) const = 0;
		// 添加渲染节点到视图中
		//virtual void AddNode(osg::Node* pNode, const VRString& strViewName) = 0;
		// 进行刷新
		virtual void Flush(void) = 0;
		// 进行归一初始化
		virtual void Realize(void) = 0;
		// 添加渲染属性
		virtual void AddEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) = 0;
		// 移除渲染属性
		virtual void RemoveEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) = 0;
		// 获得索引 不存在直接返回-1
		virtual int GetIndexEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) = 0;
		// 通过索引获得渲染属性
		virtual IEntityDrawManager* GetEntityDrawManager(const int index) = 0;
	};
}

#endif // _IVIEWMANAGER_H_