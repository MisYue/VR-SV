/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  仿真系统整个系统进行仿真时间和对模型调度接口                  */
/* 时间： 2015-10-21                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ISIMMANAGERR_H_
#define _PUBLIC_ISIMMANAGERR_H_

namespace VR_Soft
{
	const VRString SIMSYSTEM_TYPENAME = "SIMSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_SIMSYSTEM = "SIMSYSTEM";
	const VRString SIMSYSTEM_DISC = "仿真控制系统";

	// 定义时间类型
#if defined(_MSC_VER)
	typedef __int64 TIME_T;
#else
	typedef unsigned long long TIME_T;
#endif

	class ISimManager : public CSingleton<ISimManager>, public IComManagerFace
	{
	public:
		// 枚举命令
		enum SimCmd
		{
			Start, // 引擎启动
			Pause, // 引擎暂停
			Accelerate, // 加速
			Decelerate, // 减速
			Stop, // 停止
			Reset, // 重置
			Close // 关闭
		};

	public:
		// 析构函数
		virtual ~ISimManager(void) { }
		// 设置是否为服务器
		virtual void SetServer(const bool bServer) = 0;
		// 返回是否为服务器
		virtual bool IsServer(void) const = 0;
		// 设置引擎命令
		virtual void SetCmd(const SimCmd simCmd) = 0;
	};
}

#endif // _PUBLIC_ISIMMANAGERR_H_