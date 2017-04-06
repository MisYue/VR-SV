/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性策略管理类	                                        */
/* 时间： 2015-11-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _STRATEGYMANAGER_H_
#define _STRATEGYMANAGER_H_

#pragma once


namespace VR_Soft
{
	class IStrategyFactory;

	class CStrategyManager : public IStrategyManager
	{
	public:
		explicit CStrategyManager(void);
		virtual ~CStrategyManager(void);

	public:
		// 添加实体策略
		virtual void AddStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy);
		// 添加实体策略
		virtual void AddStrategy(IEntityBase* pIEntity, const VRString& strStrategyType);
		// 移除当前的策略
		virtual void RemoveStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy);
		// 获得所有策略
		virtual IStrategyManager::ListStrategys GetAllStrategy(IEntityBase* pIEntity);
		// 获得所有的策略
		virtual const ListStrategys& GetAllStrategy(IEntityBase* pIEntity) const;
		// 获得所有的策略
		virtual const IStrategyManager::ListStrategyFactorys GetAllStrategyFactory(void) const ;

	public:
		// 初始化
		void Init(void);
		// 删除所有的策略
		void RemoveAllStrategy(void);

	protected:
		// 导入策略
		void LoadStrategy(void);
		// 加载单个dll文件
		void LoadStrategyDll(const VRString& strPathName);
		// 是否被加载
		bool IsLoaded(const VRString& strElecName) const;
		
	protected:
		typedef std::map<IEntityBase*, IStrategyManager::ListStrategys> ListEntityStrategy;
		typedef std::map<VRString, IStrategyFactory*> ListStrategyFactorys;
		typedef std::map<VRString, CDyLib*> ListStrategyPlugin;

	private:
		ListEntityStrategy m_lstEntityStrategy;
		ListStrategyFactorys m_lstFactorys; // 工厂列表
		ListStrategyPlugin m_lstStrategyPlugin; // 策略
	};
}


#endif //!_STRATEGYMANAGER_H_