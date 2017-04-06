#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "SimTime.h"
#include "SimSingleThreadEngine.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
#include <sys/types.h>
#include <fcntl.h>
#include <windows.h>
#include <winbase.h>
#endif 

namespace VR_Soft
{
	// ���캯��
	CSimSingleThreadEngine::CSimSingleThreadEngine(CSimTime* pSimTime)
		:CVRSoftThread(),m_pSimTime(pSimTime)
	{
	}

	// ��������
	CSimSingleThreadEngine::~CSimSingleThreadEngine(void)
	{
	}

	// ֱ������
	void CSimSingleThreadEngine::RunSimple(void)
	{
		// �߳�ѭ��
		while(1)
		{
			//// �ж��Ƿ����״̬
			//if (CVRSoftThread::IsSuspend())
			//{
			//	boost::this_thread::sleep(boost::posix_time::seconds(1));
			//	continue;
			//}
			// ���ú���
			Run();
		}
	}

	// �����߳�
	void CSimSingleThreadEngine::Run(void)
	{
		// ֱ�ӵ���ʱ����� ���и���
		m_pSimTime->EntityUpdate(0.0);

		LARGE_INTEGER liFrequency,t1,t2;
		t2.QuadPart=0;
		double dCalAccumlateTime=0;

		QueryPerformanceFrequency(&liFrequency);
		printf("���� CPU Ƶ��: %u \n",liFrequency);

		do 
		{

			ProcessSimCmd();
			(0==simEnginePara_.dSimLogicTime)?
				(simEnginePara_.dWallTime=0):(simEnginePara_.dWallTime=(double)(t2.QuadPart-wallStarTime_.QuadPart)*1000/liFrequency.QuadPart);
			simEngineCtrlor_.UpdateWallTime(simEnginePara_.dWallTime);

			if (VRSimEngine_RUN_STATE_end==runState_)
			{
				Sleep(300);
				if (printInfo_) printf("stop");

				//QueryPerformanceCounter(&t1);//���㺯�������¿�ʼ��ʱ
				//Sleep(90);
				//QueryPerformanceCounter(&t2);
				//dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;
				//printf("*********************�����ʱ: %f ����\n",dCalAccumlateTime);
			}
			else if (VRSimEngine_RUN_STATE_pause==runState_)
			{
				if (printInfo_) printf("pause_");
				Sleep(99);
				QueryPerformanceCounter(&t2);

			}
			else if (VRSimEngine_RUN_STATE_run==runState_)
			{

				QueryPerformanceCounter(&t1);//���㺯�������¿�ʼ��ʱ

				0!=simEnginePara_.dSimLogicTime?
					dOverheadTime_=(double)(t1.QuadPart-t2.QuadPart)*1000/liFrequency.QuadPart:dOverheadTime_=0;

				Frame();
				simEnginePara_.dSimLogicTime+=simEnginePara_.dLogicSimStep;
				++frameCount_;

				if (printInfo_) 
				{
					QueryPerformanceCounter(&t2);
					dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;
					printf("*********************�����ʱ: %f ����\n",dCalAccumlateTime);
				}

				do 
				{

					QueryPerformanceCounter(&t2);
					dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	

					//2�ͷ�CPU�Ż�1
					for (;loopStep_-dCalAccumlateTime>=100;)
					{
						(0==simEnginePara_.dSimLogicTime)?
							(simEnginePara_.dWallTime=0):(simEnginePara_.dWallTime=(double)(t2.QuadPart-wallStarTime_.QuadPart)*1000/liFrequency.QuadPart);
						simEngineCtrlor_.UpdateWallTime(simEnginePara_.dWallTime);

						Sleep(80);

						QueryPerformanceCounter(&t2);
						dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	
					}

					//3�ͷ�CPU�Ż�2
					for (;loopStep_-dCalAccumlateTime>=25.5;)
					{
						(0==simEnginePara_.dSimLogicTime)?
							(simEnginePara_.dWallTime=0):(simEnginePara_.dWallTime=(double)(t2.QuadPart-wallStarTime_.QuadPart)*1000/liFrequency.QuadPart);
						simEngineCtrlor_.UpdateWallTime(simEnginePara_.dWallTime);

						Sleep(15);

						QueryPerformanceCounter(&t2);
						dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	
					}


				} while (dCalAccumlateTime<=loopStep_-dOverheadTime_);

				simEngineCtrlor_.UpdateSimTime(simEnginePara_.dSimLogicTime);

				if (printInfo_)  printf("-----------------����ʵ�ʺ�ʱ-------------: %f ����\n",dCalAccumlateTime+dOverheadTime_);
				if (printInfo_)  printf("----------����ʱ��--: %f ��\n",simEnginePara_.dSimLogicTime/1000);


			}		
		} while (VRSimEngine_RUN_STATE_Exiting!=runState_);

	}

	// ��÷���ָ��
	void CSimSingleThreadEngine::ProcessSimCmd(void)
	{

	}

}
