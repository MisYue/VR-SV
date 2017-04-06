#include "../../Public/VRSoft.h"
#include "EntityBaseAttribute.h"
#include <boost/lexical_cast.hpp>

namespace VR_Soft
{
	// 构造函数
	CEntityBaseAttribute::CEntityBaseAttribute(IEntityBase* pIEntityBase)
		:CAttributeImp<IEntityBaseAttribute>(pIEntityBase, "基础属性"), \
		m_strEntityName(""), m_entityCoordinate(EARTH),m_strType("")
	{
	}

	// 析构函数
	CEntityBaseAttribute::~CEntityBaseAttribute(void)
	{
		
	}

	// 初始化
	void CEntityBaseAttribute::Init()
	{
		DEFINITION_PROPERTY(Name, &CEntityBaseAttribute::SetEntityName, &CEntityBaseAttribute::GetEntityName, "名称", "", "", CTRL_EDIT);
		DEFINITION_PROPERTY(EntityCoordinate, &CEntityBaseAttribute::SetEntityCoordinate, &CEntityBaseAttribute::GetEntityCoordinate,"坐标系", "EARTH", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(EntityCoordinate, "MODEL", MODEL);
		ADDENUM_PROPERTY(EntityCoordinate, "EARTH", EARTH);
		ADDENUM_PROPERTY(EntityCoordinate, "WORLD", WORLD);

		DEFINITION_PROPERTY(Type, &CEntityBaseAttribute::SetEntityType, &CEntityBaseAttribute::GetEntityType, "类型", "", "", CTRL_EDIT);
	}

	// 设置实体名称
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

	// 设置ID号
	void CEntityBaseAttribute::SetEntityID(const uint64_t uid)
	{
		m_uID = uid;
	}

	// 获得ID号
	uint64_t CEntityBaseAttribute::GetEntityID(void) const
	{
		return (m_uID);
	}

	// 设置是否依赖地球
	void CEntityBaseAttribute::SetEntityCoordinate(const IEntityBaseAttribute::EntityCoordinate ec)
	{
		m_entityCoordinate = ec;
	}

	// 获得是否依赖地球
	IEntityBaseAttribute::EntityCoordinate CEntityBaseAttribute::GetEntityCoordinate(void) const
	{
		return (m_entityCoordinate); //(GetItem("依赖地球")->GetValueToBool()); 
	}

	// 设置类型
	void CEntityBaseAttribute::SetEntityType( const VRString& strType )
	{
		m_strType = strType;
	}

	// 获得类型
	VR_Soft::VRString CEntityBaseAttribute::GetEntityType( void ) const
	{
		return (m_strType);
	}

	// 初始化通过xml节点初始化
	void CEntityBaseAttribute::ReadXmlNode( TiXmlElement* pTiXmlElement )
	{
		if (NULL == pTiXmlElement)
		{
			return ;
		}

		// 获得属性
		TiXmlElement* pSubXmlElement = pTiXmlElement->FirstChildElement();
		while (NULL != pSubXmlElement)
		{
			VRString strValue = pSubXmlElement->Value();
			if (0 == strValue.compare("名称"))
			{
				const VRString strText = pSubXmlElement->GetText();
				GetItem("名称")->SetValue(strText);
			}
			else if (0 == strValue.compare("坐标系"))
			{
				VRString strText = pSubXmlElement->GetText();
				// 转换成小写
				//strText = CVRStringUtil::ToUpper(strText);
				GetItem("坐标系")->SetValue(strText);
			}

			// 读取下一个属性
			pSubXmlElement = pSubXmlElement->NextSiblingElement();
		}
	}

}
