/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  电磁系统入口													*/
/* 时间： 2015-05-22                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ELECMAGONSTATE_H_
#define _ELECMAGONSTATE_H_

#pragma once

namespace VR_Soft
{
	/************************************************************************/
	/*                            开机状态                                  */
	/************************************************************************/
	class CElectMagOnState : public IState
	{
	public:
		explicit CElectMagOnState(void);
		virtual ~CElectMagOnState(void);

	public:
		// 进入状态
		virtual void Enter(IEntityBase* pEntityBase);
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase);
		// 离开状态
		virtual void Exit(IEntityBase* pEntityBase);

		// 消息处理
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);

	private:
		osg::Vec3d m_vRadius;
		osg::Vec3d m_vRadiusUp;
	};

	/************************************************************************/
	/*                            扫描状态                                  */
	/************************************************************************/
	class CElectMagScanState : public IState
	{
	public:
		explicit CElectMagScanState(void);
		virtual ~CElectMagScanState(void);

	public:
		// 进入状态
		virtual void Enter(IEntityBase* pEntityBase);
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase);
		// 离开状态
		virtual void Exit(IEntityBase* pEntityBase);

		// 消息处理
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);
	};
}


#endif //  _ELECMAGONSTATE_H_