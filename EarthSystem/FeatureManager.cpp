#include "../../Public/EarthSystem/EarthSystem.h"
#include "FeatureManager.h"
#include "Feature.h"

namespace VR_Soft
{
	CFeatureManager::CFeatureManager(void)
		:m_pICurFeature(NULL)
	{
	}


	CFeatureManager::~CFeatureManager(void)
	{
		m_pICurFeature = NULL;
		Clear();
	}

	// ���ʸ������
	bool CFeatureManager::AddFeature( IFeature* pIFearth )
	{
		unsigned long ID = pIFearth->GetFID();
		ListFeatures::const_iterator cstItor = m_listFeatures.find(ID);
		if (m_listFeatures.end() == cstItor)
		{
			m_listFeatures.insert(ListFeatures::value_type(ID, pIFearth));
			return (true);
		}

		return (false);
	}

	// ���ʸ������
	bool CFeatureManager::AddFeature( osgEarth::Features::Feature* pIFeature )
	{
		unsigned long ID = pIFeature->getFID();
		ListFeatures::const_iterator cstItor = m_listFeatures.find(ID);
		if (m_listFeatures.end() != cstItor)
		{
			return (false);
		}

		CFeature* pFeature = new CFeature(pIFeature);
		m_listFeatures.insert(ListFeatures::value_type(ID, pFeature));
		return (false);
	}

	// �Ƴ�ʸ������
	void CFeatureManager::RemoveFeature( unsigned long ID )
	{
		ListFeatures::iterator itor = m_listFeatures.find(ID);
		if (m_listFeatures.end() == itor)
		{
			return;
		}

		VRSOFT_DELETE(itor->second);
		m_listFeatures.erase(itor);
	}

	// ��ѯID
	IFeature* CFeatureManager::GetFeature( unsigned long ID ) const
	{
		ListFeatures::const_iterator itor = m_listFeatures.find(ID);
		if (m_listFeatures.end() == itor)
		{
			return (NULL);
		}

		return (itor->second);
	}

	// ��õ�ǰ��ѡ���ʸ��
	IFeature* CFeatureManager::GetCurFeature( void ) const
	{
		return (m_pICurFeature);
	}

	// ���õ�ǰ��ʸ������
	void CFeatureManager::SetCurFeature( IFeature* pIFeature )
	{
		m_pICurFeature = pIFeature;
	}

	// ���õ�ǰ��ʸ������
	void CFeatureManager::SetCurFeature( unsigned long ID )
	{
		SetCurFeature(GetFeature(ID));
	}

	// �������
	void CFeatureManager::Clear( void )
	{
		ListFeatures::iterator itor = m_listFeatures.begin();
		for (; m_listFeatures.end() != itor; ++itor)
		{
			VRSOFT_DELETE(itor->second);
		}

		m_listFeatures.clear();
	}

}
