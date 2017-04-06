
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
		// ���ղ��
		MapStrInstance mapStrInstance = m_mapStrInstance;
		// ѭ������
		for (MapStrInstance::iterator itor = mapStrInstance.begin(); \
			mapStrInstance.end() != itor; ++itor)
		{
			// ���չ���
			for (ComFactoryList::iterator factoryItor = m_comFactorys.begin(); \
				m_comFactorys.end() != factoryItor; ++factoryItor)
			{
				VRString str = (*factoryItor)->GetMetaData().strType;
				if ((*factoryItor)->GetMetaData().strType == itor->second->GetName())
				{
					// ���ù������л�����Դ
					(*factoryItor)->DestoryInstance(itor->second);
					m_mapStrInstance.erase(itor->first);
					break;
				}
			}
		}

		// ������ж���
		m_mapStrInstance.clear();
	}

	// ��ӹ���
	void CComInstanceEnumerator::AddFactory(IComFactory* pIComFactory)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// ��ӵ�����
		m_comFactorys.push_back(pIComFactory);

		const ComManagerMetaData& comMetaData = pIComFactory->GetMetaData();
		// ����ʵ��
		CreateComInstance(comMetaData.strType, comMetaData.strInstanceName);
	}

	// ɾ������
	void CComInstanceEnumerator::RemoveFactory(IComFactory* pIComFactory)
	{
		// ���ݹ�������ѯ����Ӧ��ʵ�� Ȼ��ͨ����������ֱ������
		for (MapStrInstance::iterator itor = m_mapStrInstance.begin(); \
			m_mapStrInstance.end() != itor; ++itor)
		{
			IComManagerFace* instance = itor->second;
			const VRString& str = pIComFactory->GetMetaData().strType;
			const VRString& strInsTypeName = instance->GetTypeName();
			if (0 == str.compare(instance->GetTypeName()))
			{
				pIComFactory->DestoryInstance(instance);
				
				// ��map��ɾ��
				m_mapStrInstance.erase(itor);
				break;
			}
		}
	}

	// �������
	IComManagerFace* CComInstanceEnumerator::CreateComInstance(const VRString& strTypeName, const VRString& strInstnaceName)
	{
		// ��ѯ������Ƿ��Ѿ�����
		MapStrInstance::const_iterator cstItor = m_mapStrInstance.find(strInstnaceName);
		if (m_mapStrInstance.end() != cstItor)
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("���:" + strInstnaceName + "�Ѿ�������");
			return (cstItor->second);
		}

		IComManagerFace* pIInstance = NULL;
		// ��������ӿ�
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
			IComManager::GetInstance().WriteLogMsg("����" + pIInstance->GetName() + "δ�ܳ�ʼ��ʵ��");
			return (pIInstance);
		}

		// ��ʼ�����
		pIInstance->Init();

		m_mapStrInstance[pIInstance->GetName()] = pIInstance;
		return (pIInstance);
	}

	// ���ʵ��
	IComManagerFace* CComInstanceEnumerator::GetComInstance(const VRString& strInstane) const
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;
		// ��ѯ���
		MapStrInstance::const_iterator cstItor = m_mapStrInstance.find(strInstane);
		if (m_mapStrInstance.end() == cstItor)
		{
			return (NULL);
		}

		// ���ڲ��
		return (cstItor->second);
	}
}
