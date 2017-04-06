/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ⱦ����ϵͳ�ӿ�		                                        */
/* ʱ�䣺 2015-05-15                                                    */
/* �޸�ʱ��:						                                    */
/************************************************************************/
#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

//#include "rendersystem_global.h"

#include "RenderThread.h"

namespace VR_Soft
{
	class IScreenHUDManager;
	class CScreenHUDManager;
	class IScreenHUDManager;
	class CDrawAttributeFactory;
	class CMeshManager;
	class CInpute;
	class CDrawTrajectoryManager;

	class CRenderSystem : public IRenderManager
	{
	public:
		explicit CRenderSystem(const VRString& strName);
		virtual ~CRenderSystem(void);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��ʼ��ϵͳ
		virtual void Init(void);
		// ��ȡ��ͼ������
		virtual IViewManager* GetViewManager(void) const;
		// �����Ļ���ڹ������
		virtual IScreenHUDManager* GetScreenManager(void) const;
		// ��ѯ��ͼ����
		virtual IRenderView* QuaryViewBayName(const VRString& strViewName) const;
		// ִ����Ⱦ
		virtual void Render(void);
		// ע���¼�
		virtual void RegisterEvnet(IEvent* pIEvent, const VRString& strViewName = "mainView");
		// ��ע���¼�
		virtual void UnRegisterEvnet(IEvent* pIEvent, const VRString& strViewName = "mainView");
		// �����Ⱦ���Թ���
		virtual IDrawAttributeFactory* GetDrawAttributeFactory(void) const ;
		// �����άʵ�������
		virtual IMeshManager* GetMeshManager(void);
		// ��ù켣������
		virtual IDrawTrajectoryManager* GetTrajectoryManager(void) ;

	public:
		SET_GET_PROPERTY(Name, VRString, str);

	private:
		VRString m_strName;

		IViewManager* m_pIViewManager; // ��ͼ����
		CScreenHUDManager* m_pScreenHUDManager; // ��Ļ���ڹ���
		CRenderThread* m_pRenderThread;

		CDrawAttributeFactory* m_pDrawAttributeFactory; // ���Թ���
		CMeshManager* m_pMeshManager; // ʵ��������
		CDrawTrajectoryManager* m_pDrawTrajectoryManager; // �����߹�����

		VR_AUTO_MUTEX
	};

	// ע�Ṥ����
	REGISTER_COMFACTORY(CRenderSystem, RenderManager, RENDERSYSTEM_TYPENAME, INSTANCE_NAME_RENDERSYSTEM, RENDERSYSTEM_DISC);
}


#endif // RENDERSYSTEM_H
