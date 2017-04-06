#include "../../Public/VRSoft.h"
#include "EntityBaseAttribute.h"
#include <boost/lexical_cast.hpp>

namespace VR_Soft
{
	// ���캯��
	CEntityBaseAttribute::CEntityBaseAttribute(IEntityBase* pIEntityBase)
		:CAttributeImp<IEntityBaseAttribute>(pIEntityBase, "��������"), \
		m_strEntityName(""), m_entityCoordinate(EARTH),m_strType("")
	{
	}

	// ��������
	CEntityBaseAttribute::~CEntityBaseAttribute(void)
	{
		
	}

	// ��ʼ��
	void CEntityBaseAttribute::Init()
	{
		DEFINITION_PROPERTY(Name, &CEntityBaseAttribute::SetEntityName, &CEntityBaseAttribute::GetEntityName, "����", "", "", CTRL_EDIT);
		DEFINITION_PROPERTY(EntityCoordinate, &CEntityBaseAttribute::SetEntityCoordinate, &CEntityBaseAttribute::GetEntityCoordinate,"����ϵ", "EARTH", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(EntityCoordinate, "MODEL", MODEL);
		ADDENUM_PROPERTY(EntityCoordinate, "EARTH", EARTH);
		ADDENUM_PROPERTY(EntityCoordinate, "WORLD", WORLD);

		DEFINITION_PROPERTY(Type, &CEntityBaseAttribute::SetEntityType, &CEntityBaseAttribute::GetEntityType, "����", "", "", CTRL_EDIT);
	}

	// ����ʵ������
	void CEntityBaseAttribute::SetEntityName(const VRString& strName)
	{
		if (0 == m_strEntityName.compare(strName))
		{
			return;
		}

		VRString strOldName = m_strEntityName;
		m_strEntityName = strName;

		IEntityManager::GetInstance().ChangeEntityName(GetEntity(), strOldName, m_strEntityName);
	}


	VRString CEntityBaseAttribute::GetEntityName(void) const
	{
		return (m_strEntityName);
	}

	void CEntityBaseAttribute::SetEntityID(IEntityID* pEntityID)
	{
		m_uID = pEntityID->GetEntityID();
	}

	// ����ID��
	void CEntityBaseAttribute::SetEntityID(const uint64_t uid)
	{
		m_uID = uid;
	}

	// ���ID��
	uint64_t CEntityBaseAttribute::GetEntityID(void) const
	{
		return (m_uID);
	}

	// �����Ƿ���������
	void CEntityBaseAttribute::SetEntityCoordinate(const IEntityBaseAttribute::EntityCoordinate ec)
	{
		m_entityCoordinate = ec;
	}

	// ����Ƿ���������
	IEntityBaseAttribute::EntityCoordinate CEntityBaseAttribute::GetEntityCoordinate(void) const
	{
		return (m_entityCoordinate); //(GetItem("��������")->GetValueToBool()); 
	}

	// ��������
	void CEntityBaseAttribute::SetEntityType( const VRString& strType )
	{
		m_strType = strType;
	}

	// �������
	VR_Soft::VRString CEntityBaseAttribute::GetEntityType( void ) const
	{
		return (m_strType);
	}

	// ��ʼ��ͨ��xml�ڵ��ʼ��
	void CEntityBaseAttribute::ReadXmlNode( TiXmlElement* pTiXmlElement )
	{
		if (NULL == pTiXmlElement)
		{
			return ;
		}

		// �������
		TiXmlElement* pSubXmlElement = pTiXmlElement->FirstChildElement();
		while (NULL != pSubXmlElement)
		{
			VRString strValue = pSubXmlElement->Value();
			if (0 == strValue.compare("����"))
			{
				const VRString strText = pSubXmlElement->GetText();
				GetItem("����")->SetValue(strText);
			}
			else if (0 == strValue.compare("����ϵ"))
			{
				VRString strText = pSubXmlElement->GetText();
				// ת����Сд
				//strText = CVRStringUtil::ToUpper(strText);
				GetItem("����ϵ")->SetValue(strText);
			}

			// ��ȡ��һ������
			pSubXmlElement = pSubXmlElement->NextSiblingElement();
		}
	}

}
