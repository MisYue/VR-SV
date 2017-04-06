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

	// ��������
	void CRenderView::SetName(const VRString& strName)
	{
		m_pView->setName(strName);
	}

	// �������
	VRString CRenderView::GetName(void) const
	{
		return (m_pView->getName());
	}

	// ������ͼ
	osgViewer::View* CRenderView::GetView(void) const
	{
		return (m_pView);
	}

	// ��ӽڵ�����ͼ
	void CRenderView::AddDataToView(osg::Node* pNode)
	{
		// ���߳� ��
		VR_MUTEX_AUTO

		osgUtil::Optimizer optimizer;
		optimizer.optimize(pNode);
		// ��ӵ���Ⱦ�б���
		m_listRenderNodes.push(pNode);
	}

	// ��ø��ڵ�
	osg::Node* CRenderView::GetRootData(void)
	{
		return (m_pRoot);
	}

	// �������
	void CRenderView::ClearData(void) 
	{
		// �Ƴ����е��ӽڵ�
		// ������и��ڵ�
		typedef osg::Node::ParentList Parents;
		Parents& listParent = m_pRoot->getParents();
		for (Parents::iterator itor = listParent.begin(); listParent.end() != itor; ++itor)
		{
			(*itor)->removeChild(m_pRoot);
		}

		//m_pView->getCamera()->releaseGLObjects();
	}

	// ��ò���������
	IManipulatorManager* CRenderView::GetManipulatorManager(void)
	{
		return (m_pManipulator);
	}

	// ����HUD����
	IScreenHUD* CRenderView::CreateSreenHUD( int x, int y, int width, int height, const VRString& strName )
	{
		CScreenHUD* pScreenHUD = new CScreenHUD(strName);
		m_pRoot->addChild(pScreenHUD);
		pScreenHUD->Move(x, y, width, height);
		IRenderManager::GetInstance().GetScreenManager()->AddScreenHUD(pScreenHUD);
		IComManager::GetInstance().WriteLogMsg(strName + "�����ɹ�");

		return (pScreenHUD);
	}

	// ������ͼ
	void CRenderView::UpdateView(void)
	{
		// �����Ƿ��нڵ����
		while (!m_listRenderNodes.empty())
		{
			osg::Node* pNode = m_listRenderNodes.back();

			// ��ӵ����ڵ���
			m_pRoot->addChild(pNode);

			// ��������
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
