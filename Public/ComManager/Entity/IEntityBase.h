/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基类				                                        */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IENTITYBASE_H_
#define _IENTITYBASE_H_

#pragma once


namespace VR_Soft
{
	class IAttribute;
	class IStateMachine;
	class IEntityDrawManager;
	class IDrawAttribute;
	class IEntityBaseAttribute;
	class IEntityDrawAttribute;
	class IEntityID;
	class IMessage;
	class IEntityVisitor;

	class VRSOFT_DLL IEntityBase
	{
	public:
		typedef std::vector<IAttribute*> ListAttributes;

	public:
		// 析构函数
		virtual ~IEntityBase() { }

	public:
		// 初始化
		virtual void Init(void) = 0;
		// 获得类型
		virtual const VRString GetEntityType(void) const = 0;
		// 设置实体基本属性
		virtual void SetBaseAttribute(IEntityBaseAttribute* pIEntityBaseAttribute) = 0;
		// 获得基本属性对象
		virtual IEntityBaseAttribute* GetBaseAttribute(void) const = 0;
		// 设置实体渲染属性
		virtual void SetEntityDrawAttribute(IEntityDrawAttribute* pIEntityDrawAttribute) = 0;
		// 获得实体渲染属性
		virtual IEntityDrawAttribute* GetEntityDrawAttribute(void) const = 0;
		// 设置属性
		virtual void AddAttributes(IAttribute* pIAttribute) = 0;
		// 获得属性
		virtual IAttribute* GetAttribute(const VRString& strAttrName) const = 0;
		// 移除属性
		virtual bool RemoveAttribute(const VRString& strAttrName) = 0;
		// 添加属性群
		virtual void AddAttributes(const ListAttributes& lstAttribtes) = 0; 
		// 获得所有属性
		virtual ListAttributes GetAllAttribute(void) const = 0;
		// 设置渲染管理
		virtual void SetDrawManager(IEntityDrawManager* pIDrawManager) = 0;
		// 获得渲染管理
		virtual IEntityDrawManager* GetDrawManager(void) const  = 0;
		// 设置渲染属性
		virtual void AddDrawAttribute(IDrawAttribute* pIDrawAttribute) = 0;
		// 获得渲染属性
		virtual IDrawAttribute* GetDrawAttribute(const VRString& strName) = 0;
		// 移除渲染属性
		virtual void RemoveDrawAttribute(IDrawAttribute* pIDrawAttribute) = 0;

		// 标志
	public: 
		// 设置标志
		virtual void SetID(uint64_t uID) = 0;
		// 获得标志
		virtual const uint64_t GetID(void) const = 0;
		// 设置名称
		virtual void SetName(const VRString& strName) = 0;
		// 获得名称
		virtual VRString GetName(void) const = 0;
		// 需要更新
		virtual void NeedUpdate(void) = 0;
		// 是否有必要更新
		virtual bool IsUpdate(void) const = 0;
		// 模型更新（每一更新帧调用)
		virtual void EntityUpdate(const CDateTime& dt) = 0;

		// 消息相关
	public:
		// 处理消息
		virtual bool HandleMessage(const IMessage* pIMessage) = 0;
		// 获得状态机
		virtual IStateMachine* GetStateMachine(void) const = 0;
		// 设置状态机
		virtual void SetStateMachine(IStateMachine* pIStateMachine) = 0;
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine) = 0;
	};
}

#endif // _IENTITYBASE_H_