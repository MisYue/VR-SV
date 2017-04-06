/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ͼ����ӿ�			                                        */
/* ʱ�䣺 2015-05-15                                                    */
/* �޸�ʱ��:                                                            */
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
		// ��������
		virtual ~IViewManager() { }
		// ������ͼ
		virtual void CreateView(const VRString& strViewName, int x, int y, int width, int height) = 0;
		// ע��UI
		virtual void RegisterViewUI(IRenderViewUI* pRenderViewUI) = 0;
		// ��ע��UI
		virtual void UnReginsterViewUI(IRenderViewUI* pRenderViewUI) = 0;
		// ��ѯ��ͼ
		virtual IRenderView* GetRenderView(const VRString& strViewName) const = 0;
		// �����Ⱦ�ڵ㵽��ͼ��
		//virtual void AddNode(osg::Node* pNode, const VRString& strViewName) = 0;
		// ����ˢ��
		virtual void Flush(void) = 0;
		// ���й�һ��ʼ��
		virtual void Realize(void) = 0;
		// �����Ⱦ����
		virtual void AddEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) = 0;
		// �Ƴ���Ⱦ����
		virtual void RemoveEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) = 0;
		// ������� ������ֱ�ӷ���-1
		virtual int GetIndexEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) = 0;
		// ͨ�����������Ⱦ����
		virtual IEntityDrawManager* GetEntityDrawManager(const int index) = 0;
	};
}

#endif // _IVIEWMANAGER_H_