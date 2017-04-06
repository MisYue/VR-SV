/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  模型策略管理接口		                                        */
/* 时间： 2015-11-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ISTRATEGYMANAGER_H_
#define _ISTRATEGYMANAGER_H_

namespace VR_Soft
{
	class IEntityBase;
	class IStrategy;

	class IStrategyManager
	{
	public:
		typedef std::list<IStrategy*> ListStrategys;
		typedef std::list<IStrategyFactory*> ListStrategyFactorys;
	public:
		// 析构函数
		virtual ~IStrategyManager(void) { }
		// 添加实体策略
		virtual void AddStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy) = 0;
		// 添加实体策略
		virtual void AddStrategy(IEntityBase* pIEntity, const VRString& strStrategyType) = 0;
		// 移除当前的策略
		virtual void RemoveStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy) = 0;
		// 获得所有策略
		virtual ListStrategys GetAllStrategy(IEntityBase* pIEntity)  = 0;
		// 获得所有的策略
		virtual const ListStrategys& GetAllStrategy(IEntityBase* pIEntity) const = 0;
		// 获得所有的策略
		virtual const ListStrategyFactorys GetAllStrategyFactory(void) const = 0;
	};
}

#endif // !_ISTRATEGYMANAGER_H_