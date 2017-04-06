/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  同步操作器管理类	                                            */
/* 时间： 2016-07-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_SYNCHROMANIPMANNAGER_H_
#define _PUBLIC_SYNCHROMANIPMANNAGER_H_

#include <osgEarth/Viewpoint>

namespace VR_Soft
{
	class OSGEARTH_DLL ISynchroManIpManager : public CSingleton<ISynchroManIpManager>
	{
	public:
		// 析构函数
		virtual ~ISynchroManIpManager(void) { }
		// 设置视点
		virtual void SetViewPoint(const osgEarth::Viewpoint& vp, double duration_s =0.0) = 0;
		// 获得视点
		virtual osgEarth::Viewpoint GetViewPoint(void) const = 0;
		// 跟踪实体模型
		virtual void SetTrackEntity(const uint64_t uID) = 0;
		// 断开跟踪模型
		virtual void BreakTrackEntity(void) = 0;

	};
}

#endif // !_PUBLIC_SYNCHROMANIPMANNAGER_H_