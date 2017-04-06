/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ģ�Ͳ��Թ���ӿ�		                                        */
/* ʱ�䣺 2015-11-15                                                    */
/* �޸�ʱ��:                                                            */
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
		// ��������
		virtual ~IStrategyManager(void) { }
		// ���ʵ�����
		virtual void AddStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy) = 0;
		// ���ʵ�����
		virtual void AddStrategy(IEntityBase* pIEntity, const VRString& strStrategyType) = 0;
		// �Ƴ���ǰ�Ĳ���
		virtual void RemoveStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy) = 0;
		// ������в���
		virtual ListStrategys GetAllStrategy(IEntityBase* pIEntity)  = 0;
		// ������еĲ���
		virtual const ListStrategys& GetAllStrategy(IEntityBase* pIEntity) const = 0;
		// ������еĲ���
		virtual const ListStrategyFactorys GetAllStrategyFactory(void) const = 0;
	};
}

#endif // !_ISTRATEGYMANAGER_H_