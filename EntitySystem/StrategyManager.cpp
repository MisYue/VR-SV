#define VRSOFT_PLUGIN_EXPORT
#include <algorithm>
#include <list>
#include <map>
#include "../../Public/VRSoft.h"
#include "../../Public/EntitySystem/EntitySystem.h"
#include "StrategyManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// ע��ص�����
	typedef IStrategyFactory* (*DLL_INSTANLL_TRATEGY)(void);
	typedef void (*DLL_UNINSTANLL_TRATEGY)(IStrategyFactory* pIStrategyFactory);
	////////////////////////////////////

	// ���캯��
	CStrategyManager::CStrategyManager(void)
	{
	}

	// ��������
	CStrategyManager::~CStrategyManager(void)
	{
	}

	// ���ʵ�����
	void CStrategyManager::AddStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy)
	{
		if (NULL == pIEntity)
		{
			return;
		}

		// ��ѯ��ǰ��ʵ��
		ListEntityStrategy::iterator itor = m_lstEntityStrategy.find(pIEntity);
		// ��һ�����
		if (m_lstEntityStrategy.end() == itor)
		{
			IStrategyManager::ListStrategys lstStragey;
			pIStrategy->SetEntity(pIEntity);
			lstStragey.push_back(pIStrategy);
			m_lstEntityStrategy[pIEntity] = lstStragey;
			IComManager::GetInstance().WriteLogMsg("ģ��" + pIEntity->GetName() + "�ɹ���Ӳ���");
			return;
		}

		// �ҵ�ģ��
		IStrategyManager::ListStrategys& lstStrategy = itor->second;
		// ���ҵ�ǰ�ĵ�ǰ�Ĳ���
		IStrategyManager::ListStrategys::const_iterator cstItor = std::find(lstStrategy.begin(), lstStrategy.end(), pIStrategy);
		if (lstStrategy.end() != cstItor)
		{
			// ��ǰģ�ʹ��ڵ�ǰ�Ĳ���
			return;
		}

		// ��ӵ�ϵͳģ�Ͳ�����
		pIStrategy->SetEntity(pIEntity);
		lstStrategy.push_back(pIStrategy);
		IComManager::GetInstance().WriteLogMsg("ģ��" + pIEntity->GetName() + "�ɹ���Ӳ���");
	}

	// ���ʵ�����
	void CStrategyManager::AddStrategy(IEntityBase* pIEntity, const VRString& strStrategyType)
	{
		// ͨ�����ͻ�ù���
		ListStrategyFactorys::const_iterator cstItor = m_lstFactorys.find(strStrategyType);
		if (m_lstFactorys.end() == cstItor)
		{
			IComManager::GetInstance().WriteLogMsg("�����ڵ�ǰ����" + strStrategyType, ERROR_NOT_FIND);
			return;
		}

		IStrategy* pIStrategy = cstItor->second->GetInstance();
		AddStrategy(pIEntity, pIStrategy);

	}

	// �Ƴ���ǰ�Ĳ���
	void CStrategyManager::RemoveStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy)
	{
		if (NULL == pIEntity)
		{
			return;
		}
		// ��ѯ��ǰ��ʵ��
		ListEntityStrategy::iterator itor = m_lstEntityStrategy.find(pIEntity);
		// ��һ�����
		if (m_lstEntityStrategy.end() == itor)
		{
			return;
		}

		// �ҵ�ģ��
		ListStrategys& lstStrategy = itor->second;
		// ���ҵ�ǰ�ĵ�ǰ�Ĳ���
		ListStrategys::iterator cstItor = std::find(lstStrategy.begin(), lstStrategy.end(), pIStrategy);
		lstStrategy.erase(cstItor);
	}

	// ������в���
	IStrategyManager::ListStrategys CStrategyManager::GetAllStrategy(IEntityBase* pIEntity)
	{
		ListStrategys lstStrategy;
		if (NULL == pIEntity)
		{
			return lstStrategy;
		}
		// ��ѯ��ǰ��ʵ��
		ListEntityStrategy::const_iterator itor = m_lstEntityStrategy.find(pIEntity);
		// ��һ�����
		if (m_lstEntityStrategy.end() == itor)
		{
			return lstStrategy;
		}

		lstStrategy = itor->second;
		return (lstStrategy);
	}

	// ������еĲ���
	const IStrategyManager::ListStrategys& CStrategyManager::GetAllStrategy(IEntityBase* pIEntity) const
	{
		// ��ѯ��ǰ��ʵ��
		ListEntityStrategy::const_iterator itor = m_lstEntityStrategy.find(pIEntity);
		// ��һ�����
	/*	if (m_lstEntityStrategy.end() == itor)
		{
			return lstStrategy;
		}*/

		return (itor->second);
	}

	const IStrategyManager::ListStrategyFactorys CStrategyManager::GetAllStrategyFactory(void) const
	{
		IStrategyManager::ListStrategyFactorys lstFactory ;
		ListStrategyFactorys::const_iterator cstItor = m_lstFactorys.begin();
		for (; m_lstFactorys.end() != cstItor; ++cstItor)
		{
			lstFactory.push_back(cstItor->second);
		}

		return (lstFactory);
	}

	// ��ʼ��
	void CStrategyManager::Init(void)
	{
		LoadStrategy();
	}

	// �������
	void CStrategyManager::LoadStrategy(void)
	{
		const VRString& strPath  = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Strategy/";
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strPath, "*.dll", files);

		// �������е��ļ�
		Files::const_iterator cstItor = files.begin();
		for (; files.end() != cstItor; ++cstItor)
		{
			LoadStrategyDll(strPath + (*cstItor));
		}
	}

	// ���ص���dll�ļ�
	void CStrategyManager::LoadStrategyDll(const VRString& strPathName)
	{
		// �жϵ�ǰ�ļ��Ѿ�������
		if (IsLoaded(strPathName))
		{
			return ;
		}

		// �����ļ�
		CDyLib* pDyLib = new CDyLib(strPathName);
		if (NULL == pDyLib)
		{
			IComManager::GetInstance().WriteLogMsg("���Բ��:"+ strPathName +" ʧ��", ERROR_MALLOC);
			VRSOFT_DELETE(pDyLib);
			return;
		}

		try
		{
			pDyLib->Load();
		}
		catch (...)
		{
			return;
		}

		// ������ں���
		DLL_INSTANLL_TRATEGY pFunction = (DLL_INSTANLL_TRATEGY)pDyLib->GetSymbol("InstanllStrategy");

		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("���Բ��:"+ strPathName +"δʶ��", ERROR_NOT_FIND);
			delete pDyLib;
			return;
		}

		// ���뵽����
		m_lstStrategyPlugin[strPathName] = pDyLib;

		
		// ִ�к���
		IStrategyFactory* pIFactory = pFunction();

		// �ж��Ƿ񴴽��ɹ�
		if (NULL == pIFactory)
		{
			return;
		}

		m_lstFactorys[pIFactory->GetType()] = pIFactory;
	}

	// �Ƿ񱻼���
	bool CStrategyManager::IsLoaded(const VRString& strElecName) const
	{
		ListStrategyPlugin::const_iterator cstItor = m_lstStrategyPlugin.find(strElecName);
		return (m_lstStrategyPlugin.end() != cstItor);
	}

	// ɾ�����еĲ���
	void CStrategyManager::RemoveAllStrategy()
	{
	//	throw std::logic_error("The method or operation is not implemented.");
	}

}

