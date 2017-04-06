/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ⱦϵͳ�ӿ�ͨ����չ�ӿ�ʵ��QT��������UI�ӿ�                  */
/* ʱ�䣺 2015-05-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IRENDERVIEWUI_H_
#define _IRENDERVIEWUI_H_

#pragma once

namespace osgViewer
{
	class View;
}

namespace osg
{
	class Camera;
	class Node;
}

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL IRenderViewUI : public IPluginUI
	{
	public:
		// ��������
		virtual ~IRenderViewUI() { }
		// ��ʼ��UI // ��param ת�� osg::GraphicsContext::Traits* pTraits
		virtual void InitUI(void* param = NULL, int nParam = 0) = 0;
		// ��ʼ�����
		virtual void InitCamera(osg::Camera* pCamera) = 0;
		// ��ý��洰��
		virtual const VRString GetUIName(void) const = 0;
		// ��ɳ�ʼ��
		virtual void CreateVRWindow(osgViewer::View* pView) = 0;
		// ����UI
		virtual void Update(void* param = NULL, int nParam = 0 ) = 0;
	};
};

#endif