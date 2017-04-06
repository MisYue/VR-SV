/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  卫星轨道														*/
/* 时间： 2016-04-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SATELLITETRAJECTORY_H_
#define _SATELLITETRAJECTORY_H_

#pragma once


class SGP4;
class Tle;

namespace VR_Soft
{
	class CSatalliteTrajectoryDraw;


	class CSatelliteTrajectory : public ITrajectory
	{
	public:
		// 构造函数
		CSatelliteTrajectory(void);
		// 析构函数
		virtual ~CSatelliteTrajectory(void);

	public:
		// 获得弹道数据
		virtual const ListTrajectoryInfo& GetTrajectoryPoint(void) const  { return (m_listTrajectroryPoint); }
		// 弹道算法
		virtual void AlgorithmTrajectoryPoint(void);
		// 设置弹道对象
		virtual void SetTrajectoryEntity(IEntityBase* pITrajectoryEntity);
		// 获取当前的位置
		osg::Vec3d GetCurPos(CSatalliteTrajectoryDraw* pSateliteTrjDraw, const CDateTime& dt);
		// 获得历元时间
		double GetEpoh(void) const;

	protected:
		// 初始化
		void InitSGP4(void);

	private:
		ITrajectory::ListTrajectoryInfo m_listTrajectroryPoint; // 轨迹数据顶点
		IEntityBase* m_pITrajectoryEntity; // 弹道实体
		Tle* m_pTle; // 两行根数
		SGP4* m_pSgp4;
	};

}

#endif // !_SATELLITETRAJECTORY_H_