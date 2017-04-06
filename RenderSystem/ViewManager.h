/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  视图管理实现类		                                        */
/* 时间： 2015-05-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _VIEWMANAGER_H_
#define _VIEWMANAGER_H_

#pragma once

#include <osgViewer/CompositeViewer>

class IRenderView;


namespace VR_Soft
{
	class IRenderViewUI;

	class CViewManager : public IViewManager
	{
	public:
		explicit CViewManager(void);
		virtual ~CViewManager(void);

		// 创建视图
		virtual void CreateView(const VRString& strViewName, int x, int y, int width, int height );
		// 注册UI
		virtual void RegisterViewUI(IRenderViewUI* pRenderViewUI);
		// 反注册UI
		virtual void UnReginsterViewUI(IRenderViewUI* pRenderViewUI);
		// 查询视图
		virtual IRenderView* GetRenderView(const VRString& strViewName) const;
		// 添加渲染节点到视图中
		//virtual void AddNode(osg::Node* pNode, const VRString& strViewName);
		// 刷新
		virtual void Flush(void);
		// 进行归一初始化
		virtual void Realize(void) ;

	public:
		// 添加渲染属性
		virtual void AddEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) ;
		// 移除渲染属性
		virtual void RemoveEntityDrawManager(IEntityDrawManager* pIEntityDrawManager);
		// 获得索引
		virtual int GetIndexEntityDrawManager(IEntityDrawManager* pIEntityDrawManager);
		// 通过索引获得渲染属性
		virtual IEntityDrawManager* GetEntityDrawManager(const int index);
		// 删除所有的View
		void RemoveAllView(void);

	protected:
		// 删除所有的界面
		void RemoveAllViewUI(void);
		
		// 查询渲染属性是否存在
		bool IsHandEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) const;

	protected:
		// 每一帧前调用
		void PreFrame(void);
		// 调用更新
		void Frame(void);
		// 每一帧后调用
		void PostFrame(void);

	protected:
		typedef std::map<VRString, IRenderViewUI*> MapStrViewUI;
		typedef std::vector<IRenderView* > ListRenderViews;
		typedef std::vector<IEntityDrawManager*> ListEntityDrawManagers;
	private:
		bool m_bFirst; // 是否第一次进入
		MapStrViewUI m_mapStrViewUI; // 界面保存接口
		ListRenderViews m_listRenderViews; // 视图组合
		ListEntityDrawManagers m_lstEntityDrawManagers; // 渲染属性集合

		osgViewer::CompositeViewer* m_pCompositeViewer;
	};
}


#endif // _VIEWMANAGER_H_