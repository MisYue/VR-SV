/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ģ�Ͳ��Խӿ�			                                        */
/* ʱ�䣺 2015-06-29                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ISTRATEGY_H_
#define _PUBLIC_ISTRATEGY_H_

namespace VR_Soft
{
	class IEntityBase; 

	class IStrategy
	{
	public:
		// ��������
		virtual ~IStrategy() { }
		// ����ģ��
		virtual void SetEntity(IEntityBase* pIEntity) = 0;
		// ���ģ��
		virtual IEntityBase* GetEntity(void) const = 0;
		// ÿһ֡���е���
		virtual void Execute(double dt) = 0;
		// ��ò�������
		virtual VRString GeType(void) const = 0;
		// ���ò�������
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

		// ����ģ��
		virtual void SetEntity(IEntityBase* pIEntity)
		{
			m_pIEntityBase = pIEntity;
		}

		// ���ģ��
		virtual IEntityBase* GetEntity(void) const
		{
			return (m_pIEntityBase);
		}

		// ��ò�������
		virtual VRString GeType(void) const 
		{
			return (m_strType);
		}

		// ���ò�������
		virtual void SetType(const VRString& strType)
		{
			m_strType = strType;
		}

	private:
		IEntityBase* m_pIEntityBase; // ʵ�����
		VRString m_strType; // ��������
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