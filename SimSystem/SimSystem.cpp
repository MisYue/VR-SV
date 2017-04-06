#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/SimSystem/SimSystem.h"
#include "SimSingleThreadEngine.h"
#include "SimTime.h"
#include "SimSystem.h"

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CSimManagerFactory::FACTORY_TYPE_NAME = SIMSYSTEM_TYPENAME;
	///////////////////////////////////////////////

	// ���캯��
	CSimSystem::CSimSystem(const VRString& strName)
		:ISimManager(),
		m_pSimTime(NULL),
		m_pSimThreadEngine(NULL)
	{
		SetName(strName);
	}

	// ��������
	CSimSystem::~CSimSystem(void)
	{
		// ɾ������ʱ��
		m_pSimThreadEngine->Join();
		VRSOFT_DELETE(m_pSimThreadEngine);
		VRSOFT_DELETE(m_pSimTime);
		
	}

	// �����Ƿ�Ϊ������
	void CSimSystem::SetServer(const bool bServer)
	{
		// ���Ϊ������ �������̣߳����к�̨����
		if (bServer && (NULL != m_pSimTime))
		{
			m_pSimThreadEngine->Start();
		}

		m_bServer = bServer;
	}

	// ������������
	void CSimSystem::SetCmd(const SimCmd simCmd)
	{
		switch(simCmd)
		{
		case ISimManager::Accelerate:
			{
				IAttributeItem* pItem = m_pSimTime->GetAttribute()->GetItem("SimMulti");
				double dSimMulti = pItem->GetValueToDobule();
				pItem->SetValue(dSimMulti * 2);
			}
			break;
		
		case ISimManager::Decelerate:
			{
				IAttributeItem* pItem = m_pSimTime->GetAttribute()->GetItem("SimMulti");
				double dSimMulti = pItem->GetValueToDobule();
				pItem->SetValue(dSimMulti * 0.2);
			}
			break;

		case ISimManager::Start:
			{
				IAttributeItem* pItem = m_pSimTime->GetAttribute()->GetItem("SimCmd");
				pItem->SetSelect(0);
			}
			break;

		default:
			break;
		}
	}

	// ������Ϊһ����������ֱ�ӽ���ѭ��
	void CSimSystem::Run(void)
	{
		m_bServer = true;
		if (NULL == m_pSimThreadEngine)
		{
			// ��ʼ��
			Init();
		}

		// �����߳�
		m_pSimThreadEngine->RunSimple();
	}

	// ��ȡ��������
	const VRString& CSimSystem::GetTypeName(void) const
	{
		return (CSimManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��ʼ��ϵͳ
	void CSimSystem::Init(void)
	{
		m_pSimTime = new CSimTime;
		m_pSimTime->Init();

		// ��ʼ���߳�
		m_pSimThreadEngine = new CSimSingleThreadEngine(m_pSimTime);
	}

}
