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

	// 是否结束线程
	bool CRenderThread::IsEndTheard(void)
	{
		return (m_bExit);
	}

	/*void CRenderThread::Start(void)
	{
		boost::function0<void> f = boost::bind(&CRenderThread::Run, this);
		m_pBoostThread = new boost::thread(f);
		
	}*/

	// 执行
	void CRenderThread::Run(void)
	{
		// 循环的渲染
	/*	while (true)
		{*/
		// 设置是否为空
		if (NULL == m_pIViewManager)
		{
			return;
			//break;
		}
		// 调用刷新
		m_pIViewManager->Flush();
		//}
	}

	// 执行结束之后
	void CRenderThread::Exit(void)
	{
		m_bExit =  true;
	}

}

