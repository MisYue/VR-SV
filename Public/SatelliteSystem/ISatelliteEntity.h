/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备接口														*/
/* 时间： 2015-11-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PULIC_ISATELLITE_H_
#define _PULIC_ISATELLITE_H_

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL ISatelliteEntity : public IEntityBase
	{
	public:
		// 析构函数
		virtual ~ISatelliteEntity(void) { }

	public:
		// 设置算法策略
		virtual void SetTrajectory(ITrajectory* pITrajectory)  = 0;
		// 获得算法策略
		virtual ITrajectory* GetTrajectory(void)  = 0;
		// 生成轨道
		virtual void GenerateTrajectory(void) = 0;
		// 设置两行根数
		virtual void SetTle(ITle* pITle) = 0;
		// 获得两行根数
		virtual ITle* GetTle(void) const = 0;

	};


}

#endif // !_PULIC_ISATELLITE_H_