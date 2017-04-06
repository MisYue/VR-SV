/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  视图适配器		                                            */
/* 时间： 2015-05-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _RENDERVIEW_H_
#define _RENDERVIEW_H_
#pragma once

#include <queue>

#include "../../Public/Thread/VRThread.h"

namespace VR_Soft
{
	class CManipulatorManager;

	class CRenderView : public IRenderView
	{
	public:
		explicit CRenderView(void);
		virtual ~CRenderView(void);
		// 设置名称
		virtual void SetName(const VRString& strName);
		// 获得名称
		virtual VRString GetName(void) const;
		// 添加节点入视图
		virtual void AddDataToView(osg::Node* pNode);
		// 获得根节点
		virtual osg::Node* GetRootData(void);
		// 清空数据
		virtual void ClearData(void) ;
		// 返回视图
		virtual osgViewer::View* GetView(void) const;
		// 获得操作器管理
		virtual IManipulatorManager* GetManipulatorManager(void);
		// 创建HUD窗口
		virtual IScreenHUD* CreateSreenHUD(int x, int y, int width, int height, const VRString& strName);

	public:
		// 更新视图
		void UpdateView(void);
		
	private:
		osgViewer::View* m_pView;// 视图
		CManipulatorManager* m_pManipulator; // 操作选择器
		osg::Group* m_pRoot;

		typedef std::queue<osg::Node*> ListRenderNodes;
		ListRenderNodes m_listRenderNodes; // 渲染缓存列表

		VR_AUTO_MUTEX // 多线程
	};
}


#endif //_RENDERVIEW_H_