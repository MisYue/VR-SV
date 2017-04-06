/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ͼ����ʵ����		                                        */
/* ʱ�䣺 2015-05-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _VIEWMANAGER_H_
#define _VIEWMANAGER_H_

#pragma once

#include <osgViewer/CompositeViewer>

class IRenderView;


namespace VR_Soft
{
	class IRenderViewUI;

	class CViewManager : public IViewManager
	{
	public:
		explicit CViewManager(void);
		virtual ~CViewManager(void);

		// ������ͼ
		virtual void CreateView(const VRString& strViewName, int x, int y, int width, int height );
		// ע��UI
		virtual void RegisterViewUI(IRenderViewUI* pRenderViewUI);
		// ��ע��UI
		virtual void UnReginsterViewUI(IRenderViewUI* pRenderViewUI);
		// ��ѯ��ͼ
		virtual IRenderView* GetRenderView(const VRString& strViewName) const;
		// �����Ⱦ�ڵ㵽��ͼ��
		//virtual void AddNode(osg::Node* pNode, const VRString& strViewName);
		// ˢ��
		virtual void Flush(void);
		// ���й�һ��ʼ��
		virtual void Realize(void) ;

	public:
		// �����Ⱦ����
		virtual void AddEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) ;
		// �Ƴ���Ⱦ����
		virtual void RemoveEntityDrawManager(IEntityDrawManager* pIEntityDrawManager);
		// �������
		virtual int GetIndexEntityDrawManager(IEntityDrawManager* pIEntityDrawManager);
		// ͨ�����������Ⱦ����
		virtual IEntityDrawManager* GetEntityDrawManager(const int index);
		// ɾ�����е�View
		void RemoveAllView(void);

	protected:
		// ɾ�����еĽ���
		void RemoveAllViewUI(void);
		
		// ��ѯ��Ⱦ�����Ƿ����
		bool IsHandEntityDrawManager(IEntityDrawManager* pIEntityDrawManager) const;

	protected:
		// ÿһ֡ǰ����
		void PreFrame(void);
		// ���ø���
		void Frame(void);
		// ÿһ֡�����
		void PostFrame(void);

	protected:
		typedef std::map<VRString, IRenderViewUI*> MapStrViewUI;
		typedef std::vector<IRenderView* > ListRenderViews;
		typedef std::vector<IEntityDrawManager*> ListEntityDrawManagers;
	private:
		bool m_bFirst; // �Ƿ��һ�ν���
		MapStrViewUI m_mapStrViewUI; // ���汣��ӿ�
		ListRenderViews m_listRenderViews; // ��ͼ���
		ListEntityDrawManagers m_lstEntityDrawManagers; // ��Ⱦ���Լ���

		osgViewer::CompositeViewer* m_pCompositeViewer;
	};
}


#endif // _VIEWMANAGER_H_