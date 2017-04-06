/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  模型策略接口			                                        */
/* 时间： 2015-06-29                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ISTRATEGY_H_
#define _PUBLIC_ISTRATEGY_H_

namespace VR_Soft
{
	class IEntityBase; 

	class IStrategy
	{
	public:
		// 析构函数
		virtual ~IStrategy() { }
		// 设置模型
		virtual void SetEntity(IEntityBase* pIEntity) = 0;
		// 获得模型
		virtual IEntityBase* GetEntity(void) const = 0;
		// 每一帧进行调用
		virtual void Execute(double dt) = 0;
		// 获得策略类型
		virtual VRString GeType(void) const = 0;
		// 设置策略类型
		virtual void SetType(const VRString& strType) = 0;
	};

	template <class T>
	class CStrategyImp : public T
	{
	public:
		explicit CStrategyImp()
			:m_pIEntityBase(NULL)
		{

		}

		// 设置模型
		virtual void SetEntity(IEntityBase* pIEntity)
		{
			m_pIEntityBase = pIEntity;
		}

		// 获得模型
		virtual IEntityBase* GetEntity(void) const
		{
			return (m_pIEntityBase);
		}

		// 获得策略类型
		virtual VRString GeType(void) const 
		{
			return (m_strType);
		}

		// 设置策略类型
		virtual void SetType(const VRString& strType)
		{
			m_strType = strType;
		}

	private:
		IEntityBase* m_pIEntityBase; // 实体对象
		VRString m_strType; // 策略类型
	};

	class IStrategyFactory
	{
	public: 
		virtual const VRString GetType(void) const = 0;
		virtual IStrategy* GetInstance(void) = 0;
	};

#define REGISTER_STRATEGY_FACTORY(export_maroc, classname, strategytype) \
	class export_maroc CStrategyFactory : public IStrategyFactory \
	{ \
	public: \
	virtual const VRString GetType(void) const { return (strategytype); } \
	virtual IStrategy* GetInstance(void) { IStrategy* pIStrategy = new classname; pIStrategy->SetType(strategytype); return(pIStrategy);  }\
	};  \

#define INSTALL_STRATEGY_PLUGIN(export_maroc) \
	EXTERN_CPP export_maroc CStrategyFactory* InstanllStrategy(void) \
	{ \
		IStrategyFactory* pIStrategyFactory = new CStrategyFactory;\
		return(new CStrategyFactory); \
	} \
	EXTERN_CPP export_maroc void UnInstallStrategy(CStrategyFactory* pIFactory) { VRSOFT_DELETE(pIFactory); } \

}

#endif