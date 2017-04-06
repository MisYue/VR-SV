#include "../../Public/VRSoft.h"
#include "EntityDrawAttribute.h"

namespace VR_Soft
{
	CEntityDrawAttribute::CEntityDrawAttribute(IEntityBase* pIEntityBase)
		:CAttributeImp<IEntityDrawAttribute>(pIEntityBase, "ʵ����Ⱦ����"), \
		m_vPostion(0, 0, 0), m_vScale(1, 1, 1),	m_vRotate(0, 0, 0),\
		m_drawModel(DM_2D_3D),m_strFile("entity.png"), m_bChange2D(false)
	{
	}


	CEntityDrawAttribute::~CEntityDrawAttribute(void)
	{
	}

	// ��ʼ��
	void CEntityDrawAttribute::Init()
	{
		DEFINITION_PROPERTY(Position, &CEntityDrawAttribute::SetPosition, &CEntityDrawAttribute::GetPosition, "λ��", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(Scale, &CEntityDrawAttribute::SetScale, &CEntityDrawAttribute::GetScale, "����", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(Rotate, &CEntityDrawAttribute::SetRotate, &CEntityDrawAttribute::GetRotate, "��ת", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(DrawModel, &CEntityDrawAttribute::SetDrawModel, &CEntityDrawAttribute::GetDrawModel, "��ʾģʽ", "", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(DrawModel, "����ά", DM_2D_3D);
		ADDENUM_PROPERTY(DrawModel, "��ά", DM_2D);
		ADDENUM_PROPERTY(DrawModel, "��ά", DM_3D);

		DEFINITION_PROPERTY(Entity2D, &CEntityDrawAttribute::SetEntity2D, &CEntityDrawAttribute::GetEntity2D, "��άͼƬ", "", "", CTRL_EDIT);
	}

	// ����λ��
	void CEntityDrawAttribute::SetPosition(const osg::Vec3d& vPos)
	{
		m_vPostion = vPos;

		// ����
		GetEntity()->NeedUpdate();
	}

	// ���λ��
	osg::Vec3d CEntityDrawAttribute::GetPosition(void) const
	{
		return (m_vPostion);
	}

	// ��������
	void CEntityDrawAttribute::SetScale(const osg::Vec3d& vScale)
	{
		m_vScale = vScale; 
	}

	// �������
	osg::Vec3d CEntityDrawAttribute::GetScale(void) const
	{
		return (m_vScale);
	}

	// ������ת
	void CEntityDrawAttribute::SetRotate(const osg::Vec3d& vRot)
	{
		// ���óɻ���
		m_vRotate.set(osg::DegreesToRadians(vRot.x()), osg::DegreesToRadians(vRot.y()), osg::DegreesToRadians(vRot.z()));
	}

	// �����ת
	osg::Vec3d CEntityDrawAttribute::GetRotate(void) const
	{
		return (m_vRotate);
	}

	// ������ʾģʽ
	void CEntityDrawAttribute::SetDrawModel( const IEntityDrawAttribute::DrawModel dm )
	{
		m_drawModel = dm;
	}

	IEntityDrawAttribute::DrawModel CEntityDrawAttribute::GetDrawModel( void ) const
	{
		return (m_drawModel);
	}

	// ���ö�ά��ʾͼƬ
	void CEntityDrawAttribute::SetEntity2D( const VRString& strFile )
	{
		if (0 == strFile.compare(m_strFile))
		{
			return;
		}

		m_bChange2D = true;
		m_strFile = strFile;
	}

	// ��ö�ά��ʾͼƬ
	VRString CEntityDrawAttribute::GetEntity2D( void ) const
	{
		return (m_strFile);
	}

	// �Ƿ�ı䵱ǰ�Ķ�άͼƬ
	bool CEntityDrawAttribute::ChangeEntity2D( void ) const
	{
		bool bChange2D = m_bChange2D;
		if (bChange2D)
		{
			m_bChange2D = false;
		}
		return (bChange2D);
	}

	// ��ʼ��ͨ��xml�ڵ��ʼ��
	void CEntityDrawAttribute::ReadXmlNode( TiXmlElement* pTiXmlElement )
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
			if (0 == strValue.compare("λ��"))
			{
				TiXmlElement* pChildXmlElement = pSubXmlElement->FirstChildElement();
				osg::Vec3d vPos;
				while(NULL != pChildXmlElement)
				{
					VRString strChildValue = pChildXmlElement->Value();
					if (0 == strChildValue.compare("����"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vPos.x() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("γ��"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vPos.y() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("�߶�"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vPos.z() = CVRStringUtil::StringToNumber<double>(strText);						
					}

					pChildXmlElement = pChildXmlElement->NextSiblingElement();
				}

				// ����λ��
				GetItem("λ��")->SetValue(vPos);
			}
			else if (0 == strValue.compare("����"))
			{
				TiXmlElement* pChildXmlElement = pSubXmlElement->FirstChildElement();
				osg::Vec3d vScale;
				while(NULL != pChildXmlElement)
				{
					VRString strChildValue = pChildXmlElement->Value();
					if (0 == strChildValue.compare("����X"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vScale.x() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("����Y"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vScale.y() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("����Z"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vScale.z() = CVRStringUtil::StringToNumber<double>(strText);						
					}

					pChildXmlElement = pChildXmlElement->NextSiblingElement();
				}
				GetItem("����")->SetValue(vScale);
			}
			else if (0 == strValue.compare("��ת"))
			{
				TiXmlElement* pChildXmlElement = pSubXmlElement->FirstChildElement();
				osg::Vec3d vRotate;
				while(NULL != pChildXmlElement)
				{
					VRString strChildValue = pChildXmlElement->Value();
					if (0 == strChildValue.compare("�����"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vRotate.z() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("������"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vRotate.x() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("������"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vRotate.y() = CVRStringUtil::StringToNumber<double>(strText);						
					}

					pChildXmlElement = pChildXmlElement->NextSiblingElement();
				}
				GetItem("��ת")->SetValue(vRotate);
			}
			else if (0 == strValue.compare("��ʾģʽ"))
			{
				VRString strText = pSubXmlElement->GetText();
				strText = CVRStringUtil::ToUpper(strText);
				GetItem("��ʾģʽ")->SetValue(strText);
			}
			else if (0 == strValue.compare("��άͼƬ"))
			{
				VRString strText = pSubXmlElement->GetText();
				strText = CVRStringUtil::ToUpper(strText);
				GetItem("��άͼƬ")->SetValue(strText);
			}

			// ��ȡ��һ������
			pSubXmlElement = pSubXmlElement->NextSiblingElement();
		}
	}

}

