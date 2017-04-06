/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����Բ��Թ�����	                                        */
/* ʱ�䣺 2015-11-15                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���ʵ�����
		virtual void AddStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy);
		// ���ʵ�����
		virtual void AddStrategy(IEntityBase* pIEntity, const VRString& strStrategyType);
		// �Ƴ���ǰ�Ĳ���
		virtual void RemoveStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy);
		// ������в���
		virtual IStrategyManager::ListStrategys GetAllStrategy(IEntityBase* pIEntity);
		// ������еĲ���
		virtual const ListStrategys& GetAllStrategy(IEntityBase* pIEntity) const;
		// ������еĲ���
		virtual const IStrategyManager::ListStrategyFactorys GetAllStrategyFactory(void) const ;

	public:
		// ��ʼ��
		void Init(void);
		// ɾ�����еĲ���
		void RemoveAllStrategy(void);

	protected:
		// �������
		void LoadStrategy(void);
		// ���ص���dll�ļ�
		void LoadStrategyDll(const VRString& strPathName);
		// �Ƿ񱻼���
		bool IsLoaded(const VRString& strElecName) const;
		
	protected:
		typedef std::map<IEntityBase*, IStrategyManager::ListStrategys> ListEntityStrategy;
		typedef std::map<VRString, IStrategyFactory*> ListStrategyFactorys;
		typedef std::map<VRString, CDyLib*> ListStrategyPlugin;

	private:
		ListEntityStrategy m_lstEntityStrategy;
		ListStrategyFactorys m_lstFactorys; // �����б�
		ListStrategyPlugin m_lstStrategyPlugin; // ����
	};
}


#endif //!_STRATEGYMANAGER_H_