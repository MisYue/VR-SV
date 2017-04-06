
#include "../../Public/EarthSystem/EarthSystem.h"
#include "OsgEarth.h"

#include "OsgEarth2D.h"
#include "OsgEarth3D.h"

#include <fstream>
#include <boost/regex.hpp>  
#include <boost/filesystem.hpp>

#include <osgEarth/MapNode>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgViewer/View>
#include <osg/Camera>

namespace VR_Soft
{
	COsgEarth::COsgEarth(void)
		:m_pMapNode(NULL), m_pRoot(new osg::Group),
		m_pCamera(NULL)
	{
	}


	COsgEarth::~COsgEarth(void)
	{
	}

	// 获得对应的地球节点
	EarthMap* COsgEarth::GetEarthMap( void ) const
	{
		return (m_pMapNode);
	}

	// 添加视图
	void COsgEarth::Attach( IRenderView* pIRenderView )
	{
		// 将地球根目录管理添加到渲染节点里面
		pIRenderView->AddDataToView(GetRoot());

		// 获得名称
		m_strViewName = pIRenderView->GetName();
	}

	// 配置地球数据
	osgEarth::MapNode* COsgEarth::InitMapNode( osgEarth::MapNode* pNodeMap )
	{
		m_pGraticuleNode = new osgEarth::Util::GraticuleNode(pNodeMap);
		GetRoot()->addChild(m_pGraticuleNode);
		m_pGraticuleNode->setVisible(false);
		return (pNodeMap);
	}

	// 获得根节点
	osg::Group* COsgEarth::GetRoot( void ) const
	{
		return (m_pRoot);
	}

	// 获得视图
	IRenderView* COsgEarth::GetRenderView( void ) const
	{
		// 查询视图
		IRenderManager* pIRenderManager = dynamic_cast<IRenderManager*>(\
			IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(INSTANCE_NAME_RENDERSYSTEM));
		if (NULL == pIRenderManager)
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("获取视图插件失败:GetRenderView", ERROR_NOT_FIND);
			return (NULL);
		}

		IRenderView* pIView = pIRenderManager->QuaryViewBayName(m_strViewName);
		return (pIView);
		
	}

	// 显示网格线
	void COsgEarth::SetGraticuleState( bool bShow )
	{
		if (NULL != m_pGraticuleNode)
		{
			m_pGraticuleNode->setVisible(bShow);
		}
	}

	// 获得网格线是否显示
	bool COsgEarth::GetGraticuleState( void ) const
	{
		if (NULL != m_pGraticuleNode)
		{
			return (m_pGraticuleNode->getVisible());
		}

		return (false);
	}

//////////////////////////////////////////////////////////////////////////
	// 创建2D地图
	COsgEarth* CEarthFactory::CreateEarth2D( osgEarth::MapNode* pMapNode )
	{
		COsgEarth* pOsgEarth2D = new COsgEarth2D;
		pOsgEarth2D->InitMapNode(pMapNode);
		return (pOsgEarth2D);
	}

	// 创建3D地图
	COsgEarth* CEarthFactory::CreateEarth3D( osgEarth::MapNode* pMapNode )
	{
		COsgEarth* pOsgEarth3D = new COsgEarth3D;
		pOsgEarth3D->InitMapNode(pMapNode);

		return (pOsgEarth3D);
	}

}