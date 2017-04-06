
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

	// ��ö�Ӧ�ĵ���ڵ�
	EarthMap* COsgEarth::GetEarthMap( void ) const
	{
		return (m_pMapNode);
	}

	// �����ͼ
	void COsgEarth::Attach( IRenderView* pIRenderView )
	{
		// �������Ŀ¼������ӵ���Ⱦ�ڵ�����
		pIRenderView->AddDataToView(GetRoot());

		// �������
		m_strViewName = pIRenderView->GetName();
	}

	// ���õ�������
	osgEarth::MapNode* COsgEarth::InitMapNode( osgEarth::MapNode* pNodeMap )
	{
		m_pGraticuleNode = new osgEarth::Util::GraticuleNode(pNodeMap);
		GetRoot()->addChild(m_pGraticuleNode);
		m_pGraticuleNode->setVisible(false);
		return (pNodeMap);
	}

	// ��ø��ڵ�
	osg::Group* COsgEarth::GetRoot( void ) const
	{
		return (m_pRoot);
	}

	// �����ͼ
	IRenderView* COsgEarth::GetRenderView( void ) const
	{
		// ��ѯ��ͼ
		IRenderManager* pIRenderManager = dynamic_cast<IRenderManager*>(\
			IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(INSTANCE_NAME_RENDERSYSTEM));
		if (NULL == pIRenderManager)
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("��ȡ��ͼ���ʧ��:GetRenderView", ERROR_NOT_FIND);
			return (NULL);
		}

		IRenderView* pIView = pIRenderManager->QuaryViewBayName(m_strViewName);
		return (pIView);
		
	}

	// ��ʾ������
	void COsgEarth::SetGraticuleState( bool bShow )
	{
		if (NULL != m_pGraticuleNode)
		{
			m_pGraticuleNode->setVisible(bShow);
		}
	}

	// ����������Ƿ���ʾ
	bool COsgEarth::GetGraticuleState( void ) const
	{
		if (NULL != m_pGraticuleNode)
		{
			return (m_pGraticuleNode->getVisible());
		}

		return (false);
	}

//////////////////////////////////////////////////////////////////////////
	// ����2D��ͼ
	COsgEarth* CEarthFactory::CreateEarth2D( osgEarth::MapNode* pMapNode )
	{
		COsgEarth* pOsgEarth2D = new COsgEarth2D;
		pOsgEarth2D->InitMapNode(pMapNode);
		return (pOsgEarth2D);
	}

	// ����3D��ͼ
	COsgEarth* CEarthFactory::CreateEarth3D( osgEarth::MapNode* pMapNode )
	{
		COsgEarth* pOsgEarth3D = new COsgEarth3D;
		pOsgEarth3D->InitMapNode(pMapNode);

		return (pOsgEarth3D);
	}

}