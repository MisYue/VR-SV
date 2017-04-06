
#include <map>
#include <list>
#include <algorithm>
#include "../../Public/VRSoft.h"
#include "ComInstanceEnumerator.h"

namespace VR_Soft
{
	CComInstanceEnumerator::CComInstanceEnumerator(void):m_nInstanceCreateCount(0)
	{
	}

	CComInstanceEnumerator::~CComInstanceEnumerator(void)
	{
		// 回收插件
		MapStrInstance mapStrInstance = m_mapStrInstance;
		// 循环遍历
		for (MapStrInstance::iterator itor = mapStrInstance.begin(); \
			mapStrInstance.end() != itor; ++itor)
		{
			// 回收工厂
			for (ComFactoryList::iterator factoryItor = m_comFactorys.begin(); \
				m_comFactorys.end() != factoryItor; ++factoryItor)
			{
				VRString str = (*factoryItor)->GetMetaData().strType;
				if ((*factoryItor)->GetMetaData().strType == itor->second->GetName())
				{
					// 利用工厂进行回收资源
					(*factoryItor)->DestoryInstance(itor->second);
					m_mapStrInstance.erase(itor->first);
					break;
				}
			}
		}

		// 清空所有对象
		m_mapStrInstance.clear();
	}

	// 添加工厂
	void CComInstanceEnumerator::AddFactory(IComFactory* pIComFactory)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 添加到管理
		m_comFactorys.push_back(pIComFactory);

		const ComManagerMetaData& comMetaData = pIComFactory->GetMetaData();
		// 创建实例
		CreateComInstance(comMetaData.strType, comMetaData.strInstanceName);
	}

	// 删除工厂
	void CComInstanceEnumerator::RemoveFactory(IComFactory* pIComFactory)
	{
		// 依据工厂，查询到对应的实例 然后通过工厂进行直接消耗
		for (MapStrInstance::iterator itor = m_mapStrInstance.begin(); \
			m_mapStrInstance.end() != itor; ++itor)
		{
			IComManagerFace* instance = itor->second;
			const VRString& str = pIComFactory->GetMetaData().strType;
			const VRString& strInsTypeName = instance->GetTypeName();
			if (0 == str.compare(instance->GetTypeName()))
			{
				pIComFactory->DestoryInstance(instance);
				
				// 从map中删除
				m_mapStrInstance.erase(itor);
				break;
			}
		}
	}

	// 创建插件
	IComManagerFace* CComInstanceEnumerator::CreateComInstance(const VRString& strTypeName, const VRString& strInstnaceName)
	{
		// 查询该组件是否已经存在
		MapStrInstance::const_iterator cstItor = m_mapStrInstance.find(strInstnaceName);
		if (m_mapStrInstance.end() != cstItor)
		{
			// 写入日志
			IComManager::GetInstance().WriteLogMsg("组件:" + strInstnaceName + "已经被加载");
			return (cstItor->second);
		}

		IComManagerFace* pIInstance = NULL;
		// 插件工厂接口
		for (ComFactoryList::const_iterator cstItor = m_comFactorys.begin();  \
			m_comFactorys.end() != cstItor; ++cstItor)
		{
			if ((*cstItor)->GetMetaData().strType == strTypeName)
			{
				if (strInstnaceName.empty())
				{
					// generate a name
					VRString s;
					char szName[256] = {0};
					sprintf(szName, "Plugin%d",++m_nInstanceCreateCount);					
					pIInstance = (*cstItor)->CreateInstance(szName);
				}
				else
				{
					pIInstance = (*cstItor)->CreateInstance(strInstnaceName);
				}
				break;
			}
		}

		if (NULL == pIInstance)
		{
			IComManager::GetInstance().WriteLogMsg("加载" + pIInstance->GetName() + "未能初始化实例");
			return (pIInstance);
		}

		// 初始化插件
		pIInstance->Init();

		m_mapStrInstance[pIInstance->GetName()] = pIInstance;
		return (pIInstance);
	}

	// 获得实例
	IComManagerFace* CComInstanceEnumerator::GetComInstance(const VRString& strInstane) const
	{
		// 线程安全
		VR_MUTEX_AUTO;
		// 查询插件
		MapStrInstance::const_iterator cstItor = m_mapStrInstance.find(strInstane);
		if (m_mapStrInstance.end() == cstItor)
		{
			return (NULL);
		}

		// 存在插件
		return (cstItor->second);
	}
}
