#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "MemEngineConfig.h"

namespace VR_Soft
{
	CMemEngineConfig::CMemEngineConfig(void)
		:m_pIConfig(NULL)
	{
		// 获取当前路径
		const VRString& strPath = IComManager::GetInstance(\
			).GetComManagerConfig()->GetCurPath() +  "/Config/MemoreySystem/memEngine.cfg";
		m_pIConfig = CreateConfigFileInstance(strPath);
		m_pIConfig->OpenFile();
		m_pIConfig->ReadConfig();

		IConfigManager::GetInstance().AddConfig(this);

		// 初始化
		Init();
	}


	CMemEngineConfig::~CMemEngineConfig(void)
	{
	}

	void CMemEngineConfig::SetConfigFile( const VRString& strfile )
	{
		// 设置配置文件
		if (NULL == m_pIConfig)
		{
			return; 
		}

		// 打开配置文件
		m_pIConfig->OpenFile(strfile);
		m_pIConfig->ReadConfig();
	}

	// 获得需要分配的空间大小
	int CMemEngineConfig::GetMenCount( void ) const
	{
		return m_nCount;	
	}

	// 获得起始地址
	int CMemEngineConfig::GetStartAddr( void ) const
	{
		return (m_nStartAddr);
	}

	// 获得数据标识大小
	int CMemEngineConfig::GetStructCount( void ) const
	{
		return (m_nStructCount);
	}

	void CMemEngineConfig::Init( void )
	{
		// 大小
		VRString str = m_pIConfig->GetItemValue("MemEngine", "count");
		m_nCount = atoi(str.c_str());

		// 数据格式区
		str = m_pIConfig->GetItemValue("MemEngine", "struct");
		m_nStructCount = atoi(str.c_str());

		// 起始地址
		str = m_pIConfig->GetItemValue("MemEngine", "start");
		m_nStartAddr = atoi(str.c_str());
	}

	// 保存文件
	bool CMemEngineConfig::SaveConfigFile( void )
	{
		return (true);
	}



}
