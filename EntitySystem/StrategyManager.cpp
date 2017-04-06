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
	// 注册回调函数
	typedef IStrategyFactory* (*DLL_INSTANLL_TRATEGY)(void);
	typedef void (*DLL_UNINSTANLL_TRATEGY)(IStrategyFactory* pIStrategyFactory);
	////////////////////////////////////

	// 构造函数
	CStrategyManager::CStrategyManager(void)
	{
	}

	// 析构函数
	CStrategyManager::~CStrategyManager(void)
	{
	}

	// 添加实体策略
	void CStrategyManager::AddStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy)
	{
		if (NULL == pIEntity)
		{
			return;
		}

		// 查询当前的实体
		ListEntityStrategy::iterator itor = m_lstEntityStrategy.find(pIEntity);
		// 第一次添加
		if (m_lstEntityStrategy.end() == itor)
		{
			IStrategyManager::ListStrategys lstStragey;
			pIStrategy->SetEntity(pIEntity);
			lstStragey.push_back(pIStrategy);
			m_lstEntityStrategy[pIEntity] = lstStragey;
			IComManager::GetInstance().WriteLogMsg("模型" + pIEntity->GetName() + "成功添加策略");
			return;
		}

		// 找到模型
		IStrategyManager::ListStrategys& lstStrategy = itor->second;
		// 查找当前的当前的策略
		IStrategyManager::ListStrategys::const_iterator cstItor = std::find(lstStrategy.begin(), lstStrategy.end(), pIStrategy);
		if (lstStrategy.end() != cstItor)
		{
			// 当前模型存在当前的策略
			return;
		}

		// 添加到系统模型策略中
		pIStrategy->SetEntity(pIEntity);
		lstStrategy.push_back(pIStrategy);
		IComManager::GetInstance().WriteLogMsg("模型" + pIEntity->GetName() + "成功添加策略");
	}

	// 添加实体策略
	void CStrategyManager::AddStrategy(IEntityBase* pIEntity, const VRString& strStrategyType)
	{
		// 通过类型获得工厂
		ListStrategyFactorys::const_iterator cstItor = m_lstFactorys.find(strStrategyType);
		if (m_lstFactorys.end() == cstItor)
		{
			IComManager::GetInstance().WriteLogMsg("不存在当前类型" + strStrategyType, ERROR_NOT_FIND);
			return;
		}

		IStrategy* pIStrategy = cstItor->second->GetInstance();
		AddStrategy(pIEntity, pIStrategy);

	}

	// 移除当前的策略
	void CStrategyManager::RemoveStrategy(IEntityBase* pIEntity, IStrategy* pIStrategy)
	{
		if (NULL == pIEntity)
		{
			return;
		}
		// 查询当前的实体
		ListEntityStrategy::iterator itor = m_lstEntityStrategy.find(pIEntity);
		// 第一次添加
		if (m_lstEntityStrategy.end() == itor)
		{
			return;
		}

		// 找到模型
		ListStrategys& lstStrategy = itor->second;
		// 查找当前的当前的策略
		ListStrategys::iterator cstItor = std::find(lstStrategy.begin(), lstStrategy.end(), pIStrategy);
		lstStrategy.erase(cstItor);
	}

	// 获得所有策略
	IStrategyManager::ListStrategys CStrategyManager::GetAllStrategy(IEntityBase* pIEntity)
	{
		ListStrategys lstStrategy;
		if (NULL == pIEntity)
		{
			return lstStrategy;
		}
		// 查询当前的实体
		ListEntityStrategy::const_iterator itor = m_lstEntityStrategy.find(pIEntity);
		// 第一次添加
		if (m_lstEntityStrategy.end() == itor)
		{
			return lstStrategy;
		}

		lstStrategy = itor->second;
		return (lstStrategy);
	}

	// 获得所有的策略
	const IStrategyManager::ListStrategys& CStrategyManager::GetAllStrategy(IEntityBase* pIEntity) const
	{
		// 查询当前的实体
		ListEntityStrategy::const_iterator itor = m_lstEntityStrategy.find(pIEntity);
		// 第一次添加
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

	// 初始化
	void CStrategyManager::Init(void)
	{
		LoadStrategy();
	}

	// 导入策略
	void CStrategyManager::LoadStrategy(void)
	{
		const VRString& strPath  = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Strategy/";
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strPath, "*.dll", files);

		// 遍历所有的文件
		Files::const_iterator cstItor = files.begin();
		for (; files.end() != cstItor; ++cstItor)
		{
			LoadStrategyDll(strPath + (*cstItor));
		}
	}

	// 加载单个dll文件
	void CStrategyManager::LoadStrategyDll(const VRString& strPathName)
	{
		// 判断当前文件已经被加载
		if (IsLoaded(strPathName))
		{
			return ;
		}

		// 加载文件
		CDyLib* pDyLib = new CDyLib(strPathName);
		if (NULL == pDyLib)
		{
			IComManager::GetInstance().WriteLogMsg("策略插件:"+ strPathName +" 失败", ERROR_MALLOC);
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

		// 查找入口函数
		DLL_INSTANLL_TRATEGY pFunction = (DLL_INSTANLL_TRATEGY)pDyLib->GetSymbol("InstanllStrategy");

		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("策略插件:"+ strPathName +"未识别", ERROR_NOT_FIND);
			delete pDyLib;
			return;
		}

		// 加入到表中
		m_lstStrategyPlugin[strPathName] = pDyLib;

		
		// 执行函数
		IStrategyFactory* pIFactory = pFunction();

		// 判断是否创建成功
		if (NULL == pIFactory)
		{
			return;
		}

		m_lstFactorys[pIFactory->GetType()] = pIFactory;
	}

	// 是否被加载
	bool CStrategyManager::IsLoaded(const VRString& strElecName) const
	{
		ListStrategyPlugin::const_iterator cstItor = m_lstStrategyPlugin.find(strElecName);
		return (m_lstStrategyPlugin.end() != cstItor);
	}

	// 删除所有的策略
	void CStrategyManager::RemoveAllStrategy()
	{
	//	throw std::logic_error("The method or operation is not implemented.");
	}

}

