/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ͼ�������ӿ�	                                            */
/* ʱ�䣺 2015-05-19                                                    */
/* �޸�ʱ��:                                                            */
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
		// ��������
		virtual void SetName(const VRString& strName) = 0;
		// �������
		virtual VRString GetName(void) const = 0;
		// ��ӽڵ�����ͼ
		virtual void AddDataToView(osg::Node* pNode) = 0;
		// ��ø��ڵ�
		virtual osg::Node* GetRootData(void) = 0;
		// �������
		virtual void ClearData(void) = 0;
		// ������ͼ
		virtual osgViewer::View* GetView(void) const = 0;
		// ��ò���������
		virtual IManipulatorManager* GetManipulatorManager(void) = 0;
		// ����HUD����
		virtual IScreenHUD* CreateSreenHUD(int x, int y, int width, int height, const VRString& strName) = 0;
	};
}


#endif //_IRENDERVIEW_H_