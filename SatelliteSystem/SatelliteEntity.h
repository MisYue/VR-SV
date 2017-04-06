/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  卫星实体														*/
/* 时间： 2016-04-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SATELLITEENTITY_H_
#define _SATELLITEENTITY_H_

#pragma once

namespace VR_Soft
{
	class CSatalliteTrajectoryDraw;

	class CSatelliteEntity  : public CEntityBaseImp<ISatelliteEntity>
	{
	public:
		// 构造函数
		CSatelliteEntity(void);
		// 析构函数
		virtual ~CSatelliteEntity(void);

	public:
		// 初始化
		virtual void Init(void);
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine);
		// 获得类型
		virtual const VRString GetEntityType(void) const;

		// 模型更新（每一更新帧调用)
		virtual void EntityUpdate(const CDateTime& dt);

	public:
		// 设置算法策略
		virtual void SetTrajectory(ITrajectory* pITrajectory) ;
		// 获得算法策略
		virtual ITrajectory* GetTrajectory(void);
		// 生成轨道
		virtual void GenerateTrajectory(void) ;
		// 设置两行根数
		virtual void SetTle(ITle* pITle) ;
		// 获得两行根数
		virtual ITle* GetTle(void) const;

	private:
		ITrajectory* m_pITrajecoty; // 算法策略
		ITle* m_pITile; // 轨道参数

		CSatalliteTrajectoryDraw* m_pTrajectoryDrawAttribute;
	};
}


#endif // !_SATELLITEENTITY_H_