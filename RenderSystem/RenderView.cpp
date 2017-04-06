#define OSGRENDER_PLUGIN_EXPORT
#include <osgViewer/View>
#include <osgEarthUtil/EarthManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgUtil/Optimizer>

#include "../../Public/RenderSystem/RenderSystem.h"
#include "PickHeader.h"
#include "ManipulatorManager.h"
#include "ScreenHUD.h"
#include "RenderView.h"
#include "DrawTrajectoryManager.h"

namespace VR_Soft
{
	CRenderView::CRenderView(void)
	{
		m_pView = new osgViewer::View;
		m_pManipulator = new CManipulatorManager(this);
		m_pRoot = new osg::Group;
	
	//	m_pView->addEventHandler(new CPickHeader(this));
	}


	CRenderView::~CRenderView(void)
	{
		VRSOFT_DELETE(m_pManipulator);
	}

	// 设置名称
	void CRenderView::SetName(const VRString& strName)
	{
		m_pView->setName(strName);
	}

	// 获得名称
	VRString CRenderView::GetName(void) const
	{
		return (m_pView->getName());
	}

	// 返回视图
	osgViewer::View* CRenderView::GetView(void) const
	{
		return (m_pView);
	}

	// 添加节点入视图
	void CRenderView::AddDataToView(osg::Node* pNode)
	{
		// 多线程 锁
		VR_MUTEX_AUTO

		osgUtil::Optimizer optimizer;
		optimizer.optimize(pNode);
		// 添加到渲染列表中
		m_listRenderNodes.push(pNode);
	}

	// 获得根节点
	osg::Node* CRenderView::GetRootData(void)
	{
		return (m_pRoot);
	}

	// 清空数据
	void CRenderView::ClearData(void) 
	{
		// 移除所有的子节点
		// 获得所有父节点
		typedef osg::Node::ParentList Parents;
		Parents& listParent = m_pRoot->getParents();
		for (Parents::iterator itor = listParent.begin(); listParent.end() != itor; ++itor)
		{
			(*itor)->removeChild(m_pRoot);
		}

		//m_pView->getCamera()->releaseGLObjects();
	}

	// 获得操作器管理
	IManipulatorManager* CRenderView::GetManipulatorManager(void)
	{
		return (m_pManipulator);
	}

	// 创建HUD窗口
	IScreenHUD* CRenderView::CreateSreenHUD( int x, int y, int width, int height, const VRString& strName )
	{
		CScreenHUD* pScreenHUD = new CScreenHUD(strName);
		m_pRoot->addChild(pScreenHUD);
		pScreenHUD->Move(x, y, width, height);
		IRenderManager::GetInstance().GetScreenManager()->AddScreenHUD(pScreenHUD);
		IComManager::GetInstance().WriteLogMsg(strName + "创建成功");

		return (pScreenHUD);
	}

	// 更新视图
	void CRenderView::UpdateView(void)
	{
		// 遍历是否含有节点插入
		while (!m_listRenderNodes.empty())
		{
			osg::Node* pNode = m_listRenderNodes.back();

			// 添加到根节点中
			m_pRoot->addChild(pNode);

			// 弹出队列
			m_listRenderNodes.pop();

			if (NULL == m_pView->getSceneData())
			{
				/*	osg::Node* pDrawObj = IRenderManager::GetInstance().GetTrajectoryManager()->GetDrawObj();
				m_pRoot->addChild(pDrawObj);*/
				m_pView->setSceneData(m_pRoot);
			}

		}
	}

}
