/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  时间系统管理插件接口		                                    */
/* 时间： 2015-09-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ITIMEMANAGER_H_
#define _PUBLIC_ITIMEMANAGER_H_

namespace VR_Soft
{
	const VRString TIMESYSTEM_TYPENAME = "TIMESYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_TIMESYSTEM = "TIMESYSTEM";
	const VRString TIMESYSTEM_DISC = "时间系统";

	class ITimeManager : public CSingleton<ITimeManager>, public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~ITimeManager() { }
		// 获得时间返回字符串
		virtual ITimer* GetTime(void)  = 0;
		// 加速
		virtual void Quicken(void) = 0;
		// 减速
		virtual void Moderate(void) = 0;
		// 暂停
		virtual void Suspend(void) = 0;
		// 恢复
		virtual void Recover(void) = 0;
		// 停止（复位）
		virtual void Stop(void) = 0;
		// 开始
		virtual void Start(void) = 0;
		// 跳转
		virtual void Jump(struct tm& t) = 0;
	};
}

#endif // _PUBLIC_ITIMEMANAGER_H_