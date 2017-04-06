/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体类				                                        */
/* 时间： 2016-06-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ENTITYBASE_H_
#define _ENTITYBASE_H_

#pragma once

namespace VR_Soft
{
	////////////////////////////系统模型//////////////////////////////////////////////
	class CEntityBase : public CEntityBaseImp<IEntityBase>
	{
	public:
		// 构造函数
		explicit CEntityBase(void);
		// 析构函数
		virtual ~CEntityBase(void);

	public:
		// 初始化
		virtual void Init(void);
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine);
		// 获得类型
		virtual const VRString GetEntityType(void) const;
	};

	////////////////////////////系统模型生成器//////////////////////////////////////////////
	class CEntityBaseBuilder : public IEntityBulider
	{
	public:
		// 构造函数
		explicit CEntityBaseBuilder(void);
		// 析构函数
		virtual ~CEntityBaseBuilder(void);

	public:
		// 创建渲染管理属性
		virtual void CreateDrawManager(void);
		// 创建渲染属性
		virtual void CreateDrawAttribute(void);
		// 创建其它的属性
		virtual void CreateAttribute(void) ;
		// 获得名称
		virtual VRString CreateEntityName(void) const ;
		// 获得产品
		virtual IEntityBase* GetEntity(void);
		// 是否创建运动属性 返回true 则创建
		virtual bool IsCreateMoveAttribute(void);

	private:
		CEntityBase* m_pEntityBase;
	};

	// 注册系统工厂
	REGISTER_BASEENTITY_FACTORY(CEntityBaseBuilder, "系统模型")
}


#endif