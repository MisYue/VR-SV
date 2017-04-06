#include <boost/foreach.hpp>
#include <boost/filesystem/path.hpp>

#include "../../Public/VRSoft.h"
#include "EntityFileOperator.h"
#include "EntityManager.h"

namespace VR_Soft
{
	CEntityFile::CEntityFile(const VRString& strPath )
		:m_strPath(strPath)
	{
		m_pXmlDocument = new TiXmlDocument;
	}


	CEntityFile::~CEntityFile(void)
	{
		VRSOFT_DELETE(m_pXmlDocument);
	}

	// ���ļ����м���
	bool CEntityFile::Parse( void)
	{
		if (!IsVaild())
		{
			return (false);
		}

		// ��ȡxml�ļ�
		// m_pXmlDocument->LoadFile(m_strPath.c_str());
		bool bOk = m_pXmlDocument->LoadFile(m_strPath.c_str());
		if (!bOk)
		{
			VRString str = m_pXmlDocument->ErrorDesc();
			ILogManager::GetInstance().SetLogMessage(m_strName + "��ȡʧ��:" + str , ERROR_NOT_FIND);
			return (false);
		}

		 TiXmlElement*pRootElement  = m_pXmlDocument->RootElement();//��ȡ��һ��element�ڵ�
		 ParseBaseInfo(pRootElement);

		 // ��ȡ��һ���ڵ�
		 TiXmlElement* pSubElement = pRootElement->FirstChildElement();
		 ParseAttribute(pSubElement);
		 return (true);
	}

	// �ж��Ƿ�Ϊxml
	bool CEntityFile::IsVaild( void )
	{
		// �ж��Ƿ�Ϊxml�ļ�
		boost::filesystem::path path(m_strPath);
		if (0 == path.extension().string().compare(".xml"))
		{
			return (true);
		}

		return (false);
	}

	// �����ļ� ʵ�������Ϣ
	void CEntityFile::ParseBaseInfo( const TiXmlElement* pElement)
	{
		try
		{
			// �������
			m_strType = pElement->Attribute("TYPE");
			m_strName = pElement->Attribute("NAME");
		}
		catch (std::exception& e)
		{
			ILogManager::GetInstance().SetLogMessage(m_strName + "����������Ϣʧ��" + e.what(), ERROR_NOT_FIND);
		}
	}

	// ��������
	void CEntityFile::ParseAttribute( TiXmlElement* pElement )
	{
		try
		{
			// ��ȡ����
			while(NULL != pElement)
			{
				// �������
				VRString strType = pElement->Attribute("TYPE");
				m_listAttributes[strType] = pElement;
				pElement = pElement->NextSiblingElement();
			}
		}
		catch (std::exception& e)
		{
			ILogManager::GetInstance().SetLogMessage(m_strName + "����������Ϣʧ��" + e.what(), ERROR_NOT_FIND);
		}
	}

	// �������
	VR_Soft::VRString CEntityFile::GetType( void ) const
	{
		return (m_strType);
	}

	// �������
	VR_Soft::VRString CEntityFile::GetName( void ) const
	{
		return (m_strName);
	}

	// ������е�����
	ListString CEntityFile::GetAllAttribute( void ) const
	{
		ListString listStrAttribute;
		for (ListAttributes::const_iterator cstItor = m_listAttributes.begin();
			m_listAttributes.end() != cstItor; ++cstItor)
		{
			listStrAttribute.push_back(cstItor->first);
		}

		return (listStrAttribute);
	}

	// ������Խڵ�
	TiXmlElement* CEntityFile::GetXmlElement( const VRString& strAttribute ) const
	{
		ListAttributes::const_iterator cstItor = m_listAttributes.find(strAttribute);
		if (m_listAttributes.end() == cstItor)
		{
			return (NULL);
		}

		return (cstItor->second);
	}

	IEntityBase* CEntityFile::CreateEntity( const VRString& strName, const uint64_t ID )
	{
		// �ж��Ƿ�Ϊ��ǰ������
		if (0 != strName.compare(m_strName))
		{
			return (NULL);
		}

		// ����ʵ��
		CEntityManager* pEntityManager = dynamic_cast<CEntityManager*>(IEntityManager::GetInstancePtr());
		IEntityBase* pIEntity = pEntityManager->CreateEntityByFactory(m_strType, ID);
		if (NULL == pIEntity)
		{
			return (NULL);
		}

		// ��������
		pIEntity->SetName(strName);
		CreateAttribute(pIEntity);

		return (pIEntity);
	}

	// ��������
	void CEntityFile::CreateAttribute( IEntityBase* pIEntity )
	{
		// ��������б�
		for (ListAttributes::const_iterator cstItor = m_listAttributes.begin(); m_listAttributes.end() != cstItor; ++cstItor)
		{
			// ��ȡ����
			TiXmlElement* pTiXmlElement = cstItor->second;
			const VRString& strType = pTiXmlElement->Attribute("TYPE");

			if (0 == strType.compare("��������"))
			{
				pIEntity->GetBaseAttribute()->ReadXmlNode(pTiXmlElement);
				continue;
			}
			
			// ������Թ���
			IAttributeFactory* pIAttrbiteFactory = IAttributeManager::GetInstance().GetFactory(strType);
			
			// ��������
			IAttribute* pIAttribute = pIAttrbiteFactory->CreateInstance(pIEntity);
			// ��������
			pIEntity->AddAttributes(pIAttribute);
			// ����xml
			pIAttribute->ReadXmlNode(pTiXmlElement);
		}
	}
}
