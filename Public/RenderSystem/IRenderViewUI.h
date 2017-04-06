/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  渲染系统接口通过扩展接口实现QT或者其他UI接口                  */
/* 时间： 2015-05-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IRENDERVIEWUI_H_
#define _IRENDERVIEWUI_H_

#pragma once

namespace osgViewer
{
	class View;
}

namespace osg
{
	class Camera;
	class Node;
}

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL IRenderViewUI : public IPluginUI
	{
	public:
		// 析构函数
		virtual ~IRenderViewUI() { }
		// 初始化UI // 将param 转换 osg::GraphicsContext::Traits* pTraits
		virtual void InitUI(void* param = NULL, int nParam = 0) = 0;
		// 初始化相机
		virtual void InitCamera(osg::Camera* pCamera) = 0;
		// 获得界面窗口
		virtual const VRString GetUIName(void) const = 0;
		// 完成初始化
		virtual void CreateVRWindow(osgViewer::View* pView) = 0;
		// 更新UI
		virtual void Update(void* param = NULL, int nParam = 0 ) = 0;
	};
};

#endif