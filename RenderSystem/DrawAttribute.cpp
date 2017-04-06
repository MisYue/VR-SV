#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "DrawAttribute.h"
#include <osg/MatrixTransform>

#include "MeshManager.h"


namespace VR_Soft
{
	CDrawAttribute::CDrawAttribute(IEntityBase* pIEntityBase, const VRString& strDrawName )
		:CAttributeImp<IMeshDrawAttribute>(pIEntityBase, "��άģ������"), m_pNode(NULL),m_strMeshName(strDrawName)
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
		DEFINITION_PROPERTY(MeshName, &CDrawAttribute::SetMeshName, &CDrawAttribute::GetMeshName, "��άʵ��", "��άʵ��", "", CTRL_ITEM_SELECT);
		DEFINITION_PROPERTY(Light, &CDrawAttribute::SetLightOff, &CDrawAttribute::GetLightOff, "����", "����", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(Light, "TRUE", true);
		ADDENUM_PROPERTY(Light, "FALSE", false);
	}

	void CDrawAttribute::Update(void)
	{
		// �жϵ�ǰ�������Ǳ�����
		IAttributeItem* pIAttrItem = GetItem("��άʵ��");
		if (pIAttrItem->IsChanged())
		{
			// �����Ⱦ������
			GetEntity()->GetDrawManager()->ChangerMeshDrawAttribute(this, m_strMeshName);
		}

		IAttributeItem* pILightAttrItem = GetItem("����");
		if (pILightAttrItem->IsChanged())
		{
			// �����Ⱦ������
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

	// �����Ⱦ��
	DrawObj* CDrawAttribute::GetDrawObj(void)
	{
		return (m_pNode);
	}

	// ����·��
	void CDrawAttribute::SetMeshPath(const VRString& strMeshPath)
	{
		// �жϵ�ǰ�������Ǳ�����
		IAttributeItem* pIAttrItem = GetItem("·��");
		if (!pIAttrItem->IsChanged())
		{
			return;
		}

		pIAttrItem->SetValue(strMeshPath);
	}

	// ���·��
	VR_Soft::VRString CDrawAttribute::GetMeshPath(void)
	{
		// �жϵ�ǰ�������Ǳ�����
		IAttributeItem* pIAttrItem = GetItem("·��");
		if (!pIAttrItem->IsChanged())
		{
			return "";
		}

		return (pIAttrItem->GetValueToString());
	}

	// ������Ⱦ��
	void CDrawAttribute::SetDrawObj(DrawObj* pDrawObj)
	{
		m_pNode = pDrawObj;
	}

	// ����ʵ������
	void CDrawAttribute::SetMeshName(const VRString& strMeshName)
	{
		m_strMeshName = strMeshName;
	}

	// ���ʵ������
	VRString CDrawAttribute::GetMeshName(void) const
	{
		return (m_strMeshName);
	}

	// �����Ƿ�رչ���
	void CDrawAttribute::SetLightOff(bool bOff)
	{
		m_bLight = bOff;
	}

	// �����Ƿ�رչ���
	bool CDrawAttribute::GetLightOff(void) const
	{
		return (m_bLight);
	}

	// ��ʼ��ͨ��xml�ڵ��ʼ��
	void CDrawAttribute::ReadXmlNode( TiXmlElement* pTiXmlElement )
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
			if (0 == strValue.compare("��άʵ��"))
			{
				const VRString strText = pSubXmlElement->GetText();
				GetItem("��άʵ��")->SetValue(strText);
			}
			/*	else if (0 == strValue.compare("��άͼƬ"))
			{
			const VRString strText = pSubXmlElement->GetText();
			SetImageName(strText);
			}*/
			else if (0 == strValue.compare("����"))
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

			// ��ȡ��һ������
			pSubXmlElement = pSubXmlElement->NextSiblingElement();
		}
	}

}
