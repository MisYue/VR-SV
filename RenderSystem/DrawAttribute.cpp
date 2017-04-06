#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "DrawAttribute.h"
#include <osg/MatrixTransform>

#include "MeshManager.h"


namespace VR_Soft
{
	CDrawAttribute::CDrawAttribute(IEntityBase* pIEntityBase, const VRString& strDrawName )
		:CAttributeImp<IMeshDrawAttribute>(pIEntityBase, "三维模型属性"), m_pNode(NULL),m_strMeshName(strDrawName)
		,m_bLight(true)
	{
		m_pNode = CMeshManager::GetInstance().GetDrawObj(strDrawName); //osgDB::readNodeFile("cow.osg");
	//	m_pGroup = new osg::Group;
	//	m_pGroup->addChild(CMeshManager::GetInstance().GetDrawObj("T72"));
	}


	CDrawAttribute::~CDrawAttribute(void)
	{
		//osg::Parameters&  m_pNode->getParents();
	}

	void CDrawAttribute::Init()
	{
		DEFINITION_PROPERTY(MeshName, &CDrawAttribute::SetMeshName, &CDrawAttribute::GetMeshName, "三维实体", "三维实体", "", CTRL_ITEM_SELECT);
		DEFINITION_PROPERTY(Light, &CDrawAttribute::SetLightOff, &CDrawAttribute::GetLightOff, "光照", "光照", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(Light, "TRUE", true);
		ADDENUM_PROPERTY(Light, "FALSE", false);
	}

	void CDrawAttribute::Update(void)
	{
		// 判断当前的属性是被更新
		IAttributeItem* pIAttrItem = GetItem("三维实体");
		if (pIAttrItem->IsChanged())
		{
			// 获得渲染管理类
			GetEntity()->GetDrawManager()->ChangerMeshDrawAttribute(this, m_strMeshName);
		}

		IAttributeItem* pILightAttrItem = GetItem("光照");
		if (pILightAttrItem->IsChanged())
		{
			// 获得渲染管理类
			if (m_bLight)
			{
				m_pNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
			}
			else
			{
				m_pNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
			}
		}
	}

	// 获得渲染体
	DrawObj* CDrawAttribute::GetDrawObj(void)
	{
		return (m_pNode);
	}

	// 设置路径
	void CDrawAttribute::SetMeshPath(const VRString& strMeshPath)
	{
		// 判断当前的属性是被更新
		IAttributeItem* pIAttrItem = GetItem("路径");
		if (!pIAttrItem->IsChanged())
		{
			return;
		}

		pIAttrItem->SetValue(strMeshPath);
	}

	// 获得路径
	VR_Soft::VRString CDrawAttribute::GetMeshPath(void)
	{
		// 判断当前的属性是被更新
		IAttributeItem* pIAttrItem = GetItem("路径");
		if (!pIAttrItem->IsChanged())
		{
			return "";
		}

		return (pIAttrItem->GetValueToString());
	}

	// 设置渲染体
	void CDrawAttribute::SetDrawObj(DrawObj* pDrawObj)
	{
		m_pNode = pDrawObj;
	}

	// 设置实体名称
	void CDrawAttribute::SetMeshName(const VRString& strMeshName)
	{
		m_strMeshName = strMeshName;
	}

	// 获得实体名称
	VRString CDrawAttribute::GetMeshName(void) const
	{
		return (m_strMeshName);
	}

	// 设置是否关闭光照
	void CDrawAttribute::SetLightOff(bool bOff)
	{
		m_bLight = bOff;
	}

	// 设置是否关闭光照
	bool CDrawAttribute::GetLightOff(void) const
	{
		return (m_bLight);
	}

	// 初始化通过xml节点初始化
	void CDrawAttribute::ReadXmlNode( TiXmlElement* pTiXmlElement )
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
			if (0 == strValue.compare("三维实体"))
			{
				const VRString strText = pSubXmlElement->GetText();
				GetItem("三维实体")->SetValue(strText);
			}
			/*	else if (0 == strValue.compare("二维图片"))
			{
			const VRString strText = pSubXmlElement->GetText();
			SetImageName(strText);
			}*/
			else if (0 == strValue.compare("光照"))
			{
				const VRString strText = pSubXmlElement->GetText();
				if (0 == strText.compare("true"))
				{
					SetLightOff(true);
				}
				else
				{
					SetLightOff(true);
				}
			}

			// 读取下一个属性
			pSubXmlElement = pSubXmlElement->NextSiblingElement();
		}
	}

}
