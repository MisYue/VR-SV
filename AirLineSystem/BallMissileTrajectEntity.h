/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  弹道导弹弹道线实体											*/
/* 时间： 2016-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _BALLMISSILETRAJECTENTITY_H_
#define _BALLMISSILETRAJECTENTITY_H_

#pragma once

namespace VR_Soft
{
/*	class CBallMissileAttribute;

	class CBallMissileTrajectEntity : public CEntityBaseImp<ITrajectoryLineEntity>
	{
	public:
		CBallMissileTrajectEntity(void);
		virtual ~CBallMissileTrajectEntity(void);

	public:
		// 初始化
		virtual void Init(void);
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine);
		// 获得类型
		virtual const VRString GetEntityType(void) const;

		// 模型更新（每一更新帧调用)
		virtual void EntityUpdate(const CDateTime& dt);
		// 获得渲染获得点数据
		virtual ITrajectory* GetTrajectory(void) const;
		// 添加实体
		virtual void AddEntityBase( IEntityBase* pIEntityBase );
		// 移除实体
		virtual void RemoveEntityBase( IEntityBase* pIEntityBase );
		// 获得所有实体
		virtual std::vector<IEntityBase* > GetAllEntity(void) const;

	public:
		// 设置属性
		void SetBallMissileAttribute(CBallMissileAttribute* BallMissileAttribute);
		// 获得属性
		CBallMissileAttribute* GetBallMissileAttribute(void) const;
		// 设置渲染数据点对象
		void SetTrajectory(ITrajectory* pITrajectory);
		// 是否开始计算
		bool IsAlgorithm(void) const;
		// 是否启用更新
		void SetAlgorithm(void);
		void SimRun( const CDateTime& dt );

	private:
		typedef std::vector<uint64_t> ListEntityBase;
		ListEntityBase m_listEntityBasees;

		ITrajectory* m_pITrajectory;
		CBallMissileAttribute* m_pBallMissileAttribute;
		bool m_bAlgorithm;
	};
	*/
}

#endif // !_BALLMISSILETRAJECTENTITY_H_