/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������	                                                    */
/* ʱ�䣺 2016-04-08                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _SIMSINGLETHREAD_H_
#define _SIMSINGLETHREAD_H_

#pragma once

namespace VR_Soft
{
	class CEntityThread : public CVRSoftThread
	{
	public:
		// ���캯��
		CEntityThread(void);
		// ��������
		virtual ~CEntityThread(void);


	protected:
		// �����߳�
		virtual void Run(void);
	};

}

#endif // ! _SIMSINGLETHREAD_H_