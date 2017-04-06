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

	// �����߳�
	void CVRSoftThread::Start(void)
	{
		if (NULL == m_pBoostThread)
		{
			boost::function0<void> f = boost::bind(&CVRSoftThread::Loop, this);
			m_pBoostThread = new boost::thread(f);
		}

		m_bSuspend = false;
		
	}

	// �����߳�
	void CVRSoftThread::Join()
	{
		m_bStop = true;
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
			// ���ú���
			Run();
		}
	}

}

