/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ����ʱ��������������ʵʱ��ʱ������                     
 ʱ�䣺 2015-10-21                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _SIMSINGLETHREADENGINE_H_
#define _SIMSINGLETHREADENGINE_H_

#pragma once

namespace VR_Soft
{
	class CSimTime;

	class CSimSingleThreadEngine : public CVRSoftThread
	{
	public:
		// ���캯��
		explicit CSimSingleThreadEngine(CSimTime* pSimTime);
		// ��������
		virtual ~CSimSingleThreadEngine(void);
		// ֱ������
		virtual void RunSimple(void);

	protected:
		// �����߳�
		virtual void Run(void);

	protected:
		// ��÷���ָ��
		void ProcessSimCmd(void);

	private:
		CSimTime* m_pSimTime; // ����ʱ��
	};
}


#endif // _SIMSINGLETHREADENGINE_H_