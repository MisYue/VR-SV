/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ⱦ����ϵͳ�ӿ�		                                        */
/* ʱ�䣺 2015-05-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IRENDERMANAGER_H_
#define _IRENDERMANAGER_H_

#pragma once

namespace VR_Soft
{
	const VRString RENDERSYSTEM_TYPENAME = "RENDERSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_RENDERSYSTEM = "RENDERSYSTEM";
	const VRString RENDERSYSTEM_DISC = "��Ⱦϵͳ";

	class IViewManager;
	class IScreenHUDManager;
	class IDrawAttributeFactory;
	class IMeshManager;
	class IDrawTrajectoryManager;

	class OSGRENDER_DLL IRenderManager : public CSingleton<IRenderManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~IRenderManager() {}
		// ��ȡ��ͼ������
		virtual IViewManager* GetViewManager(void) const = 0;
		// �����Ļ���ڹ������
		virtual IScreenHUDManager* GetScreenManager(void) const = 0;
		// ��ѯ��ͼ����
		virtual IRenderView* QuaryViewBayName(const VRString& strViewName) const = 0;
		// ִ����Ⱦ
		virtual void Render(void) = 0;
		// ע���¼�
		virtual void RegisterEvnet(IEvent* pIEvent, const VRString& strViewName = "mainView") = 0;
		// ��ע���¼�
		virtual void UnRegisterEvnet(IEvent* pIEvent, const VRString& strViewName = "mainView") = 0;
		// �����Ⱦ���Թ���
		virtual IDrawAttributeFactory* GetDrawAttributeFactory(void) const = 0;
		// �����άʵ�������
		virtual IMeshManager* GetMeshManager(void) = 0;
		// ��ù켣������
		virtual IDrawTrajectoryManager* GetTrajectoryManager(void) = 0;
	};
}

#endif  // _IRENDERMANAGER_H_