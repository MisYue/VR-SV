/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体管理类			                                        */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#pragma once

#include "EntityFactoryManager.h"

#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	class CEntityManager : public IEntityManager
	{
	public:
		explicit CEntityManager(void);
		virtual ~CEntityManager(void);

	public:
		// 添加视图模型
		virtual void AddEntity(IEntityBase* pIEntity);
		// 移除对象
		virtual void RemoveEntity(IEntityBase* pIEntity);
		// 移除对象 
		virtual void RemoveEntity(const VRString& strName);
		// 移除对象
		virtual void RemoveEntity(const uint64_t ID);
		// 删除所有的子实例
		virtual void RemoveAllEntity(void);
		// 获取所有的子集
		virtual const std::vector<IEntityBase*>& GetAllEntities(void) const;
		// 获得类型子集
		virtual std::vector<IEntityBase*> GetEntities(const VRString& strType) const ;
		// 获得模型个数
		virtual int GetCount(void) const;
		// 通过名称查询实体 找到第一个实现的值直接返回
		virtual IEntityBase* GetEntity(const uint64_t uID) const;
		// 获得实体模型
		virtual IEntityBase* GetEntity(const VRString& strEntityName) const;
		// 模型更新（每一更新帧调用)
		virtual void EntityUpdate(const CDateTime& dt);
		// 获得工厂管理
		virtual IEntityFactoryManager* GetEntityFactoryManager(void);
		// 通过组名称来查询对应的实体
		virtual IEntityBase* CreateEntity(const VRString& strName, const uint64_t ID);
		// 修改实体名称
		virtual void ChangeEntityName(IEntityBase* pIEntity, const VRString& strOld, const VRString& strNew) const ;


	public:
		// 添加观察者
		virtual void Attach(IEntityManagerUI* pIEntityManagerUI) ;
		// 移除观察者
		virtual void Detach(IEntityManagerUI* pIEntityManagerUI) ;

	public:
		// 初始化
		void Init(void);
		// 移除工厂
		void RemoveFactory(IEntityBaseFactory* pIEntityBaseFactory);
		// 通过工厂创建系统实体非文件实体
		IEntityBase* CreateEntityByFactory(const VRString& strName, const uint64_t ID);
		// 移除所有的工厂
		void RemoveAllFactroy(void);

	protected:
		typedef boost::unordered_map<uint64_t, IEntityBase*> ListIDEntities; // 实体类型
		typedef std::vector<IEntityBase*> VectEntities; // 仿真实体集合
		typedef std::vector<uint64_t> VectEntityIDs;
		typedef boost::unordered_map<IEntityBaseFactory*, VectEntityIDs> ListFactoryEntities; // 实体工厂对应

		typedef boost::unordered_set<IEntityManagerUI*> ListEntityManagerUI;

	private:
		ListIDEntities m_listIDEntities; // ID和模型列表
		VectEntities m_vecEntities; // 仿真实体集合

		CEntityFactoryManager m_entityFactoryManager; // 实体工厂管理
		ListFactoryEntities m_listFactoryEntities; // 实体工厂对应

		ListEntityManagerUI m_listEntityManagerUI; // 界面工厂

		VR_AUTO_MUTEX
	};
}

#endif // _ENTITYMANAGER_H_