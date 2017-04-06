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
	// 构造函数
	CSimSingleThreadEngine::CSimSingleThreadEngine(CSimTime* pSimTime)
		:CVRSoftThread(),m_pSimTime(pSimTime)
	{
	}

	// 析构函数
	CSimSingleThreadEngine::~CSimSingleThreadEngine(void)
	{
	}

	// 直接运行
	void CSimSingleThreadEngine::RunSimple(void)
	{
		// 线程循环
		while(1)
		{
			//// 判断是否挂起状态
			//if (CVRSoftThread::IsSuspend())
			//{
			//	boost::this_thread::sleep(boost::posix_time::seconds(1));
			//	continue;
			//}
			// 调用函数
			Run();
		}
	}

	// 运行线程
	void CSimSingleThreadEngine::Run(void)
	{
		// 直接调用时间对象 进行更新
		m_pSimTime->EntityUpdate(0.0);

		LARGE_INTEGER liFrequency,t1,t2;
		t2.QuadPart=0;
		double dCalAccumlateTime=0;

		QueryPerformanceFrequency(&liFrequency);
		printf("本机 CPU 频率: %u \n",liFrequency);

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

				//QueryPerformanceCounter(&t1);//计算函数，从新开始计时
				//Sleep(90);
				//QueryPerformanceCounter(&t2);
				//dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;
				//printf("*********************计算耗时: %f 豪秒\n",dCalAccumlateTime);
			}
			else if (VRSimEngine_RUN_STATE_pause==runState_)
			{
				if (printInfo_) printf("pause_");
				Sleep(99);
				QueryPerformanceCounter(&t2);

			}
			else if (VRSimEngine_RUN_STATE_run==runState_)
			{

				QueryPerformanceCounter(&t1);//计算函数，从新开始计时

				0!=simEnginePara_.dSimLogicTime?
					dOverheadTime_=(double)(t1.QuadPart-t2.QuadPart)*1000/liFrequency.QuadPart:dOverheadTime_=0;

				Frame();
				simEnginePara_.dSimLogicTime+=simEnginePara_.dLogicSimStep;
				++frameCount_;

				if (printInfo_) 
				{
					QueryPerformanceCounter(&t2);
					dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;
					printf("*********************计算耗时: %f 豪秒\n",dCalAccumlateTime);
				}

				do 
				{

					QueryPerformanceCounter(&t2);
					dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	

					//2释放CPU优化1
					for (;loopStep_-dCalAccumlateTime>=100;)
					{
						(0==simEnginePara_.dSimLogicTime)?
							(simEnginePara_.dWallTime=0):(simEnginePara_.dWallTime=(double)(t2.QuadPart-wallStarTime_.QuadPart)*1000/liFrequency.QuadPart);
						simEngineCtrlor_.UpdateWallTime(simEnginePara_.dWallTime);

						Sleep(80);

						QueryPerformanceCounter(&t2);
						dCalAccumlateTime=(double)(t2.QuadPart-t1.QuadPart)*1000/liFrequency.QuadPart;	
					}

					//3释放CPU优化2
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

				if (printInfo_)  printf("-----------------步长实际耗时-------------: %f 豪秒\n",dCalAccumlateTime+dOverheadTime_);
				if (printInfo_)  printf("----------仿真时间--: %f 秒\n",simEnginePara_.dSimLogicTime/1000);


			}		
		} while (VRSimEngine_RUN_STATE_Exiting!=runState_);

	}

	// 获得仿真指令
	void CSimSingleThreadEngine::ProcessSimCmd(void)
	{

	}

}
