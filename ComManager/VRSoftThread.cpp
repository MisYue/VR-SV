

#include "../../Public/VRSoft.h"

namespace VR_Soft
{
	CVRSoftThread::CVRSoftThread(void) : m_bStop(false), m_bSuspend(false),m_pBoostThread(NULL),m_bIsStop(true)
	{
	}


	CVRSoftThread::~CVRSoftThread(void)
	{
		if (!m_bStop)
		{
			m_pBoostThread->interrupt();
			m_pBoostThread->join();
		}
		m_bStop = true;

		if (NULL == m_pBoostThread)
		{
			return;
		}
	
		VRSOFT_DELETE(m_pBoostThread);
	}

	// �����߳�
	void CVRSoftThread::Start(void)
	{
		if (NULL == m_pBoostThread)
		{
			boost::function0<void> f = boost::bind(&CVRSoftThread::Loop, this);
			m_pBoostThread = new boost::thread(f);
			m_pBoostThread->detach();
		}

		m_bSuspend = false;

		m_bIsStop = false;
		
	}

	// �����߳�
	void CVRSoftThread::Join()
	{
		m_bStop = true;
		if (NULL == m_pBoostThread)
		{
			return;
		}
		m_pBoostThread->interrupt();
		//boost::this_thread::sleep(boost::posix_time::seconds(3));
		m_pBoostThread->join();
	//	boost::this_thread::sleep(boost::posix_time::seconds(3));

		while(!m_bIsStop)
		{

		}
	}

	// �̹߳���
	void CVRSoftThread::Suspend(void)
	{
		m_bSuspend = true;
	}

	// �Ƿ�ֹͣ
	bool CVRSoftThread::IsStop(void)
	{
		return (m_bStop);
	}

	// �Ƿ����
	bool CVRSoftThread::IsSuspend(void)
	{
		return (m_bSuspend);
	}

	// ���ຯ��
	void CVRSoftThread::Run(void)
	{

	}

	// �߳̽���֮��ִ��
	void CVRSoftThread::Exit(void)
	{

	}

	// ѭ��ִ���߳�
	void CVRSoftThread::Loop(void)
	{
		// �߳�ѭ��
		while(!m_bStop)
		{
			// �ж��Ƿ����״̬
			if (m_bSuspend)
			{
				boost::this_thread::sleep(boost::posix_time::seconds(1));
				continue;
			}

			/** �ֶ����߳��м����жϵ㣬�жϵ㲻Ӱ���������ִ�� */  
			boost::this_thread::interruption_point();  
			// ���ú���
			Run();

			/** �ֶ����߳��м����жϵ㣬�жϵ㲻Ӱ���������ִ�� */  
			boost::this_thread::interruption_point();  
		}

		// �߳�ִ����β
		Exit();

		m_bIsStop = true;
	}

}

