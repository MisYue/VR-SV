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

namespace VR_Soft
{
	class CEntityManager : public IEntityComposite
	{
	public:
		explicit CEntityManager(const VRString& strComponentName);
		virtual ~CEntityManager(void);

	public:
		// 获得实体模型
		virtual IEntityComponent* GetEntity(const VRString& strEntityID) const;
		// 添加视图模型
		virtual void AddEntity(IEntityComponent* pIEntity);
		// 移除对象
		virtual void RemoveEntity(IEntityComponent* pIEntity);
		// 移除对象 
		virtual void RemoveEntity(const VRString& strName);
		// 删除所有的子实例
		virtual void RemoveAllEntity(void);
		// 改变实体模型名称方便进行查找
		virtual bool ChangeEntityName(IEntityComponent* pIEntity, const VRString& strNewName);
		// 获取所有的子集
		virtual const LstEntitys GetLstEntitys(void) const;
		// 通过名称查询实体 找到第一个实现的值直接返回
		virtual IEntityComponent* GetEntity(const VRString& strName);
		// 通过组名称来查询对应的实体
		virtual IEntityComponent* GetEntity(const VRString& strCompName, const VRString& strEntityID);
		// 通过组类型获得对应的实体
		virtual IEntityComponent* GetEntity(IEntityComponent* pIComponent, const VRString& strEntityID);
		// 模型更新（每一更新帧调用)
		virtual void EntityUpdate(double dt);
		// 获得工厂管理
		virtual IEntityFactoryManager* GetEntityFactoryManager(void);
		// 通过组名称来创建对应的实体
		virtual IEntityComponent* CreateEntity(const VRString& strCompName, const VRString& strType, const uint64_t ID);
		// 通过组名称来查询对应的实体
		virtual IEntityComponent* CreateEntity(IEntityComponent* pIComponent, const VRString& strType, const uint64_t ID);

	private:

	protected:
		typedef std::map<VRString, IEntityComponent*> MapStrEntity;

	private:
		MapStrEntity m_mapStrEntity; // 实体管理列表

		CEntityFactoryManager m_entityFactoryManager; // 实体工厂管理

		VR_AUTO_MUTEX
	};
}

#endif // _ENTITYMANAGER_H_