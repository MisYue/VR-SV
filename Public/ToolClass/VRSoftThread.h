/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ϵͳ�̻߳���			                                        */
/* ʱ�䣺 2015-09-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _VRSOFTTHREAD_H_
#define _VRSOFTTHREAD_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_TOOLCLASS_DLL CVRSoftThread
	{
	public:
		explicit CVRSoftThread(void);
		virtual ~CVRSoftThread(void);

	public:
		// ��ʼ�����߳�
		void Start(void);
		// �����߳�
		void Join(void);
		// �̹߳���
		void Suspend(void);
		// �Ƿ�ֹͣ
		bool IsStop(void);
		// �Ƿ����
		bool IsSuspend(void);

	protected:
		// �����߳�
		virtual void Run(void);
		

	private:
		// ѭ��ִ���߳�
		void Loop(void);

	private:
		bool m_bStop; // �Ƿ�ֹͣ
		bool m_bSuspend; // �Ƿ����
		boost::thread* m_pBoostThread; // ���߳�
	};
}


#endif // _VRSOFTTHREAD_H_