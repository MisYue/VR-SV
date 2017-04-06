#include <boost/function/function0.hpp>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "ViewManager.h"
#include "RenderThread.h"

namespace VR_Soft
{
	CRenderThread::CRenderThread(IViewManager* pIViewManager):m_pIViewManager(pIViewManager),m_bExit(false)
	{
	}

	CRenderThread::CRenderThread(void):m_pIViewManager(NULL),m_bExit(false)
	{
	}


	CRenderThread::~CRenderThread(void)
	{
		m_pIViewManager = NULL;
		/*m_pIViewManager = NULL;

		if (NULL != m_pBoostThread)
		{
			m_pBoostThread->interrupt();
			m_pBoostThread->join();
		}
	
		
		VRSOFT_DELETE(m_pBoostThread);*/
	}

	// �Ƿ�����߳�
	bool CRenderThread::IsEndTheard(void)
	{
		return (m_bExit);
	}

	/*void CRenderThread::Start(void)
	{
		boost::function0<void> f = boost::bind(&CRenderThread::Run, this);
		m_pBoostThread = new boost::thread(f);
		
	}*/

	// ִ��
	void CRenderThread::Run(void)
	{
		// ѭ������Ⱦ
	/*	while (true)
		{*/
		// �����Ƿ�Ϊ��
		if (NULL == m_pIViewManager)
		{
			return;
			//break;
		}
		// ����ˢ��
		m_pIViewManager->Flush();
		//}
	}

	// ִ�н���֮��
	void CRenderThread::Exit(void)
	{
		m_bExit =  true;
	}

}

