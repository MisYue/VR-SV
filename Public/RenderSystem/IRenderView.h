/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  视图适配器接口	                                            */
/* 时间： 2015-05-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IRENDERVIEW_H_
#define _IRENDERVIEW_H_
#pragma once

namespace VR_Soft
{
	class IManipulatorManager;
	class IScreenHUD;

	class OSGRENDER_DLL IRenderView
	{
	public:
		virtual ~IRenderView(void) { }
		// 设置名称
		virtual void SetName(const VRString& strName) = 0;
		// 获得名称
		virtual VRString GetName(void) const = 0;
		// 添加节点入视图
		virtual void AddDataToView(osg::Node* pNode) = 0;
		// 获得根节点
		virtual osg::Node* GetRootData(void) = 0;
		// 清空数据
		virtual void ClearData(void) = 0;
		// 返回视图
		virtual osgViewer::View* GetView(void) const = 0;
		// 获得操作器管理
		virtual IManipulatorManager* GetManipulatorManager(void) = 0;
		// 创建HUD窗口
		virtual IScreenHUD* CreateSreenHUD(int x, int y, int width, int height, const VRString& strName) = 0;
	};
}


#endif //_IRENDERVIEW_H_