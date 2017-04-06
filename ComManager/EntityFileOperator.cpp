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

	// 从文件夹中加载
	bool CEntityFile::Parse( void)
	{
		if (!IsVaild())
		{
			return (false);
		}

		// 读取xml文件
		// m_pXmlDocument->LoadFile(m_strPath.c_str());
		bool bOk = m_pXmlDocument->LoadFile(m_strPath.c_str());
		if (!bOk)
		{
			VRString str = m_pXmlDocument->ErrorDesc();
			ILogManager::GetInstance().SetLogMessage(m_strName + "读取失败:" + str , ERROR_NOT_FIND);
			return (false);
		}

		 TiXmlElement*pRootElement  = m_pXmlDocument->RootElement();//获取第一个element节点
		 ParseBaseInfo(pRootElement);

		 // 读取下一个节点
		 TiXmlElement* pSubElement = pRootElement->FirstChildElement();
		 ParseAttribute(pSubElement);
		 return (true);
	}

	// 判断是否为xml
	bool CEntityFile::IsVaild( void )
	{
		// 判断是否为xml文件
		boost::filesystem::path path(m_strPath);
		if (0 == path.extension().string().compare(".xml"))
		{
			return (true);
		}

		return (false);
	}

	// 解析文件 实体基本信息
	void CEntityFile::ParseBaseInfo( const TiXmlElement* pElement)
	{
		try
		{
			// 获得属性
			m_strType = pElement->Attribute("TYPE");
			m_strName = pElement->Attribute("NAME");
		}
		catch (std::exception& e)
		{
			ILogManager::GetInstance().SetLogMessage(m_strName + "解析基础信息失败" + e.what(), ERROR_NOT_FIND);
		}
	}

	// 解析属性
	void CEntityFile::ParseAttribute( TiXmlElement* pElement )
	{
		try
		{
			// 读取属性
			while(NULL != pElement)
			{
				// 获得属性
				VRString strType = pElement->Attribute("TYPE");
				m_listAttributes[strType] = pElement;
				pElement = pElement->NextSiblingElement();
			}
		}
		catch (std::exception& e)
		{
			ILogManager::GetInstance().SetLogMessage(m_strName + "解析基础信息失败" + e.what(), ERROR_NOT_FIND);
		}
	}

	// 获得名称
	VR_Soft::VRString CEntityFile::GetType( void ) const
	{
		return (m_strType);
	}

	// 获得名称
	VR_Soft::VRString CEntityFile::GetName( void ) const
	{
		return (m_strName);
	}

	// 获得所有的属性
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

	// 获得属性节点
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
		// 判断是否为当前的类型
		if (0 != strName.compare(m_strName))
		{
			return (NULL);
		}

		// 创建实体
		CEntityManager* pEntityManager = dynamic_cast<CEntityManager*>(IEntityManager::GetInstancePtr());
		IEntityBase* pIEntity = pEntityManager->CreateEntityByFactory(m_strType, ID);
		if (NULL == pIEntity)
		{
			return (NULL);
		}

		// 设置名称
		pIEntity->SetName(strName);
		CreateAttribute(pIEntity);

		return (pIEntity);
	}

	// 创建属性
	void CEntityFile::CreateAttribute( IEntityBase* pIEntity )
	{
		// 获得属性列表
		for (ListAttributes::const_iterator cstItor = m_listAttributes.begin(); m_listAttributes.end() != cstItor; ++cstItor)
		{
			// 获取类型
			TiXmlElement* pTiXmlElement = cstItor->second;
			const VRString& strType = pTiXmlElement->Attribute("TYPE");

			if (0 == strType.compare("基础属性"))
			{
				pIEntity->GetBaseAttribute()->ReadXmlNode(pTiXmlElement);
				continue;
			}
			
			// 获得属性工厂
			IAttributeFactory* pIAttrbiteFactory = IAttributeManager::GetInstance().GetFactory(strType);
			
			// 创建属性
			IAttribute* pIAttribute = pIAttrbiteFactory->CreateInstance(pIEntity);
			// 创建属性
			pIEntity->AddAttributes(pIAttribute);
			// 解析xml
			pIAttribute->ReadXmlNode(pTiXmlElement);
		}
	}
}
