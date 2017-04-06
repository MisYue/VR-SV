/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  轨迹算法策略接口		                                        */
/* 时间： 2015-08-04                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ITRAJECTORY_H_
#define _PUBLIC_ITRAJECTORY_H_

namespace VR_Soft
{
	struct TrajectoryInfo
	{
		double dt;			// 时间
		osg::Vec3d vGeoPos; // 地理坐标
		osg::Vec3d vEcfPos; // 地固系下的位置信息
		osg::Vec3d vEcfVel; // 地固系下的速度信息
		osg::Vec3d vEciPos; // 地惯系下的位置信息
		osg::Vec3d vEciVel; // 地惯系下的速度信息
		osg::Vec3d vRot; // 姿态
	};

	class ITrajectoryEntity;

	class ITrajectory
	{
	public:
		typedef std::vector<TrajectoryInfo> ListTrajectoryInfo;

	public:
		// 析构函数
		virtual ~ITrajectory() { }
		// 获得弹道数据
		virtual const ListTrajectoryInfo& GetTrajectoryPoint(void) const = 0;
		// 弹道算法
		virtual void AlgorithmTrajectoryPoint(void) = 0;
		// 设置弹道对象
		virtual void SetTrajectoryEntity(IEntityBase* pITrajectoryEntity) = 0;
	};
}

#endif // _PUBLIC_ITRAJECTORY_H_