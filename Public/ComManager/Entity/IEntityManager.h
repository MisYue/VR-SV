/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  模型管理组件	                                                */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IENTITYMANAGER_H_
#define _IENTITYMANAGER_H_

namespace VR_Soft
{
	class IAttributeUIFactory;
	class IEntityManagerUI;
	class IStrategyManager;

	class VRSOFT_DLL IEntityManager : public CSingleton<IEntityManager>
	{
	public:
		// 析构函数
		virtual ~IEntityManager() { }
		// 添加视图模型
		virtual void AddEntity(IEntityBase* pIEntity) = 0;
		// 移除对象
		virtual void RemoveEntity(IEntityBase* pIEntity) = 0;
		// 移除对象 
		virtual void RemoveEntity(const VRString& strName) = 0;
		// 删除所有的子实例
		virtual void RemoveAllEntity(void) = 0;
		// 获取所有的子集
		virtual const std::vector<IEntityBase*>& GetAllEntities(void) const = 0;
		// 获得类型子集
		virtual std::vector<IEntityBase*> GetEntities(const VRString& strType) const = 0;
		// 通过名称查询实体 找到第一个实现的值直接返回
		virtual IEntityBase* GetEntity(const uint64_t uID) const = 0;
		// 获得实体模型
		virtual IEntityBase* GetEntity(const VRString& strEntityName) const = 0;
		// 获得模型个数
		virtual int GetCount(void) const  = 0;
		// 模型更新（每一更新帧调用)
		virtual void EntityUpdate(const CDateTime& dt) = 0;
		// 获得工厂管理
		virtual IEntityFactoryManager* GetEntityFactoryManager(void) = 0;
		// 通过组名称来查询对应的实体
		virtual IEntityBase* CreateEntity(const VRString& strName, const uint64_t ID) = 0;
		// 修改实体名称
		virtual void ChangeEntityName(IEntityBase* pIEntity, const VRString& strOld, const VRString& strNew) const = 0;
		// 添加观察者 
		virtual void Attach(IEntityManagerUI* pIEntityManagerUI) = 0;
		// 移除观察者
		virtual void Detach(IEntityManagerUI* pIEntityManagerUI) = 0;
	};
}

#endif // _IENTITYMANAGER_H_