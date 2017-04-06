/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  弹道线实体													*/
/* 时间： 2016-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _TRAJECTLINEENTITY_H_
#define _TRAJECTLINEENTITY_H_

#pragma once

namespace VR_Soft
{
	class CTrajectLine;
	class CTrajectLineAttribute;

	class CTrajectLineEntity : public CEntityBaseImp<ITrajectoryLineEntity>
	{
	public:
		explicit CTrajectLineEntity(void);
		virtual ~CTrajectLineEntity(void);

	public:
		// 初始化
		virtual void Init(void);
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine);
		// 获得类型
		virtual const VRString GetEntityType(void) const;

		// 模型更新（每一更新帧调用)
		virtual void EntityUpdate(const CDateTime& dt);
		// 添加实体进行设置
		virtual void AddEntityBase(IEntityBase* pIEntityBase) ;
		// 移除实体
		virtual void RemoveEntityBase(IEntityBase* pIEntityBase);
		// 获得所有的实体
		virtual std::vector<IEntityBase* > GetAllEntity(void) const ;

	public:
		// 设置渲染属性
		void SetTrajectLineAttribute(CTrajectLineAttribute* pTrajectLineAttribute);
		void SimRun( const CDateTime& dt );
	private:
		typedef std::vector<uint64_t> ListEntityBase;
		ListEntityBase m_listEntityBasees;

		CTrajectLineAttribute* m_pTrajectLineAttribute;
	};
}


#endif // !_TRAJECTLINEENTITY_H_