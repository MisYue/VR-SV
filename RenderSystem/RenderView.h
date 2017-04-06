/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ͼ������		                                            */
/* ʱ�䣺 2015-05-19                                                    */
/* �޸�ʱ��:                                                            */
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
		// ��������
		virtual void SetName(const VRString& strName);
		// �������
		virtual VRString GetName(void) const;
		// ��ӽڵ�����ͼ
		virtual void AddDataToView(osg::Node* pNode);
		// ��ø��ڵ�
		virtual osg::Node* GetRootData(void);
		// �������
		virtual void ClearData(void) ;
		// ������ͼ
		virtual osgViewer::View* GetView(void) const;
		// ��ò���������
		virtual IManipulatorManager* GetManipulatorManager(void);
		// ����HUD����
		virtual IScreenHUD* CreateSreenHUD(int x, int y, int width, int height, const VRString& strName);

	public:
		// ������ͼ
		void UpdateView(void);
		
	private:
		osgViewer::View* m_pView;// ��ͼ
		CManipulatorManager* m_pManipulator; // ����ѡ����
		osg::Group* m_pRoot;

		typedef std::queue<osg::Node*> ListRenderNodes;
		ListRenderNodes m_listRenderNodes; // ��Ⱦ�����б�

		VR_AUTO_MUTEX // ���߳�
	};
}


#endif //_RENDERVIEW_H_