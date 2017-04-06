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

	// 构造函数
	CSimSystem::CSimSystem(const VRString& strName)
		:ISimManager(),
		m_pSimTime(NULL),
		m_pSimThreadEngine(NULL)
	{
		SetName(strName);
	}

	// 析构函数
	CSimSystem::~CSimSystem(void)
	{
		// 删除仿真时间
		m_pSimThreadEngine->Join();
		VRSOFT_DELETE(m_pSimThreadEngine);
		VRSOFT_DELETE(m_pSimTime);
		
	}

	// 设置是否为服务器
	void CSimSystem::SetServer(const bool bServer)
	{
		// 如果为服务器 则启动线程，进行后台计算
		if (bServer && (NULL != m_pSimTime))
		{
			m_pSimThreadEngine->Start();
		}

		m_bServer = bServer;
	}

	// 设置引擎命令
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

	// 单独作为一个进程运行直接进入循环
	void CSimSystem::Run(void)
	{
		m_bServer = true;
		if (NULL == m_pSimThreadEngine)
		{
			// 初始化
			Init();
		}

		// 运行线程
		m_pSimThreadEngine->RunSimple();
	}

	// 获取类型名称
	const VRString& CSimSystem::GetTypeName(void) const
	{
		return (CSimManagerFactory::FACTORY_TYPE_NAME);
	}

	// 初始化系统
	void CSimSystem::Init(void)
	{
		m_pSimTime = new CSimTime;
		m_pSimTime->Init();

		// 初始化线程
		m_pSimThreadEngine = new CSimSingleThreadEngine(m_pSimTime);
	}

}
