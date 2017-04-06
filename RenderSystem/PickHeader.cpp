#define OSGRENDER_PLUGIN_EXPORT
#include <osgGA/GUIEventHandler>
#include <osgViewer/View>
#include "../../Public/RenderSystem/RenderSystem.h"
#include "RenderView.h"
#include "EventList.h"
#include "ScreenHUD.h"
#include "ScreenHUDManager.h"
#include "PickHeader.h"

namespace VR_Soft
{
	CPickHeader::CPickHeader(CRenderView* pRenderView)
		:m_bClick(false),m_pRenderView(pRenderView)
	{
	}


	CPickHeader::~CPickHeader(void)
	{
	}

	bool CPickHeader::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{
		osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
		if (NULL == view)
		{
			return (true);
		}

		// ����߶�
		float fheight = view->getCamera()->getViewport()->height();

		// ���»��ƴ�С
		Resize(view->getCamera()->getViewport()->width(), view->getCamera()->getViewport()->height());

		switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::PUSH):
			{
				// �����жϵ�ǰ���¼�
				if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == ea.getButtonMask())
				{
					m_bClick = true;
					pick(view,ea);
					IEvent::GetInstance().SetMouseButton(MS_LEFT);
				}
				else if (osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON == ea.getButtonMask())
				{
					IEvent::GetInstance().SetMouseButton(MS_RIGHT);
				}
				else if (osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON == ea.getButtonMask())
				{
					IEvent::GetInstance().SetMouseButton(MS_MIDDILE);
				}

				IEvent::GetInstance().SetMousePosition2D(osg::Vec2d(ea.getX(), /*fheight -*/ ea.getY()));
				
				return false;
			}

		case(osgGA::GUIEventAdapter::RELEASE):
			{
				//osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
				//if (view) pick(view,ea);

				//// �����жϵ�ǰ���¼�
				//if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == ea.getButtonMask())
				//{
				//	CEventList::GetInstance().OnLButtonUp(ea.getX(), fheight - ea.getY(),view->getName());
				//}
				//else if (osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON == ea.getButtonMask())
				//{
				//	CEventList::GetInstance().OnRButtonUp(ea.getX(), fheight - ea.getY(), view->getName());
				//}

				return false;
			}

		case (osgGA::GUIEventAdapter::KEYDOWN):
			{
				IEvent::GetInstance().SetKey((KeySymbol)ea.getKey());
				return (false);
			}
	
		default:
			return false;
		}
	}

	void CPickHeader::pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea)
	{
		osgUtil::LineSegmentIntersector::Intersections intersections;

		std::string strEntityName="";

		if (view->computeIntersections(ea,intersections))
		{
			for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
				hitr != intersections.end();
				++hitr)
			{
				osg::Node* node = hitr->nodePath.empty() ? 0 : hitr->nodePath.back();
				if (node && !node->getName().empty()) 
				{
					strEntityName = node->getName();

					// ���õ�ǰѡ�еĵ���
					// ͨ�����ƻ�ö���
					IEntityBase* pIEntity = IEntityManager::GetInstance().GetEntity(strEntityName);

					if (NULL == pIEntity)
					{
						continue;
					}

					// ����һ��
					if (m_bClick)
					{
						IComManager::GetInstance().GetAttributeManager()->SetCurrentEntityBase(pIEntity);
					}
					
					break;
				}
			}
		}
	}

	// ������Ļ����
	void CPickHeader::Resize( int width, int height )
	{
		// �����Ļ����
		IScreenHUDManager* pIScreenHUDManager = IRenderManager::GetInstance().GetScreenManager();
		CScreenHUDManager* pScreenHUDManager = dynamic_cast<CScreenHUDManager*>(pIScreenHUDManager);
		if (NULL == pScreenHUDManager)
		{
			return;
		}

		// ������еĴ���
		typedef CScreenHUDManager::ListScreenHUDs ListScreenHUDs;
		ListScreenHUDs lstScreenHUD = pScreenHUDManager->GetScreenHUD(m_pRenderView);

		ListScreenHUDs::iterator itor = lstScreenHUD.begin();
		for (; itor != lstScreenHUD.end(); ++itor)
		{
			(*itor)->OnResize(width, height);
		}

	}

}
