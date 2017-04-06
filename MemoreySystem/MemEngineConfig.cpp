#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "MemEngineConfig.h"

namespace VR_Soft
{
	CMemEngineConfig::CMemEngineConfig(void)
		:m_pIConfig(NULL)
	{
		// ��ȡ��ǰ·��
		const VRString& strPath = IComManager::GetInstance(\
			).GetComManagerConfig()->GetCurPath() +  "/Config/MemoreySystem/memEngine.cfg";
		m_pIConfig = CreateConfigFileInstance(strPath);
		m_pIConfig->OpenFile();
		m_pIConfig->ReadConfig();

		IConfigManager::GetInstance().AddConfig(this);

		// ��ʼ��
		Init();
	}


	CMemEngineConfig::~CMemEngineConfig(void)
	{
	}

	void CMemEngineConfig::SetConfigFile( const VRString& strfile )
	{
		// ���������ļ�
		if (NULL == m_pIConfig)
		{
			return; 
		}

		// �������ļ�
		m_pIConfig->OpenFile(strfile);
		m_pIConfig->ReadConfig();
	}

	// �����Ҫ����Ŀռ��С
	int CMemEngineConfig::GetMenCount( void ) const
	{
		return m_nCount;	
	}

	// �����ʼ��ַ
	int CMemEngineConfig::GetStartAddr( void ) const
	{
		return (m_nStartAddr);
	}

	// ������ݱ�ʶ��С
	int CMemEngineConfig::GetStructCount( void ) const
	{
		return (m_nStructCount);
	}

	void CMemEngineConfig::Init( void )
	{
		// ��С
		VRString str = m_pIConfig->GetItemValue("MemEngine", "count");
		m_nCount = atoi(str.c_str());

		// ���ݸ�ʽ��
		str = m_pIConfig->GetItemValue("MemEngine", "struct");
		m_nStructCount = atoi(str.c_str());

		// ��ʼ��ַ
		str = m_pIConfig->GetItemValue("MemEngine", "start");
		m_nStartAddr = atoi(str.c_str());
	}

	// �����ļ�
	bool CMemEngineConfig::SaveConfigFile( void )
	{
		return (true);
	}



}
