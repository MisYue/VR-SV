/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ⱦ�̣߳�����boot�߳̿�                                      */
/* ʱ�䣺 2015-07-31                                                    */
/* �޸�ʱ��:						                                    */
/************************************************************************/

#ifndef _RENDERTHREAD_H_
#define _RENDERTHREAD_H_

#pragma once

#include <boost/thread.hpp>

namespace VR_Soft
{
	class CRenderThread : public CVRSoftThread
	{
	public:
		explicit CRenderThread(IViewManager* pIViewManager);
		explicit CRenderThread(void);

		~CRenderThread(void);

		// void operator() ();
	//	void Start(void);
		// ������ͼ����
		SET_GET_PROPERTY(ViewManager, IViewManager*, pI);

	public: 
		// �Ƿ�����߳�
		bool IsEndTheard(void);

	protected:
		// ִ��
		void Run(void);
		// ִ�н���֮��
		void Exit(void);

		// 

	private:
		IViewManager* m_pIViewManager; // ��ͼ����
		volatile bool m_bExit;
		//boost::thread* m_pBoostThread; // ���߳�
	};
}


#endif //_RENDERTHREAD_H_