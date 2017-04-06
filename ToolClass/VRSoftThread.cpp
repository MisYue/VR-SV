#define VRSOFT_TOOLCLASS_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"

namespace VR_Soft
{
	CVRSoftThread::CVRSoftThread(void) : m_bStop(false), m_bSuspend(false),m_pBoostThread(NULL)
	{
	}


	CVRSoftThread::~CVRSoftThread(void)
	{
		m_bStop = true;

		if (NULL == m_pBoostThread)
		{
			return;
		}
		m_pBoostThread->interrupt();
		m_pBoostThread->join();
		VRSOFT_DELETE(m_pBoostThread);
	}

	// 启动线程
	void CVRSoftThread::Start(void)
	{
		if (NULL == m_pBoostThread)
		{
			boost::function0<void> f = boost::bind(&CVRSoftThread::Loop, this);
			m_pBoostThread = new boost::thread(f);
		}

		m_bSuspend = false;
		
	}

	// 结束线程
	void CVRSoftThread::Join()
	{
		m_bStop = true;
	}

	// 线程挂起
	void CVRSoftThread::Suspend(void)
	{
		m_bSuspend = true;
	}

	// 是否停止
	bool CVRSoftThread::IsStop(void)
	{
		return (m_bStop);
	}

	// 是否挂起
	bool CVRSoftThread::IsSuspend(void)
	{
		return (m_bSuspend);
	}

	// 子类函数
	void CVRSoftThread::Run(void)
	{

	}

	// 循环执行线程
	void CVRSoftThread::Loop(void)
	{
		// 线程循环
		while(!m_bStop)
		{
			// 判断是否挂起状态
			if (m_bSuspend)
			{
				boost::this_thread::sleep(boost::posix_time::seconds(1));
				continue;
			}
			// 调用函数
			Run();
		}
	}

}

