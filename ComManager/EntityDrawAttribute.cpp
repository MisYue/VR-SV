#include "../../Public/VRSoft.h"
#include "EntityDrawAttribute.h"

namespace VR_Soft
{
	CEntityDrawAttribute::CEntityDrawAttribute(IEntityBase* pIEntityBase)
		:CAttributeImp<IEntityDrawAttribute>(pIEntityBase, "实体渲染属性"), \
		m_vPostion(0, 0, 0), m_vScale(1, 1, 1),	m_vRotate(0, 0, 0),\
		m_drawModel(DM_2D_3D),m_strFile("entity.png"), m_bChange2D(false)
	{
	}


	CEntityDrawAttribute::~CEntityDrawAttribute(void)
	{
	}

	// 初始化
	void CEntityDrawAttribute::Init()
	{
		DEFINITION_PROPERTY(Position, &CEntityDrawAttribute::SetPosition, &CEntityDrawAttribute::GetPosition, "位置", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(Scale, &CEntityDrawAttribute::SetScale, &CEntityDrawAttribute::GetScale, "缩放", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(Rotate, &CEntityDrawAttribute::SetRotate, &CEntityDrawAttribute::GetRotate, "旋转", "", "", CTRL_TREE);
		DEFINITION_PROPERTY(DrawModel, &CEntityDrawAttribute::SetDrawModel, &CEntityDrawAttribute::GetDrawModel, "显示模式", "", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(DrawModel, "二三维", DM_2D_3D);
		ADDENUM_PROPERTY(DrawModel, "二维", DM_2D);
		ADDENUM_PROPERTY(DrawModel, "三维", DM_3D);

		DEFINITION_PROPERTY(Entity2D, &CEntityDrawAttribute::SetEntity2D, &CEntityDrawAttribute::GetEntity2D, "二维图片", "", "", CTRL_EDIT);
	}

	// 设置位置
	void CEntityDrawAttribute::SetPosition(const osg::Vec3d& vPos)
	{
		m_vPostion = vPos;

		// 更新
		GetEntity()->NeedUpdate();
	}

	// 获得位置
	osg::Vec3d CEntityDrawAttribute::GetPosition(void) const
	{
		return (m_vPostion);
	}

	// 设置缩放
	void CEntityDrawAttribute::SetScale(const osg::Vec3d& vScale)
	{
		m_vScale = vScale; 
	}

	// 获得缩放
	osg::Vec3d CEntityDrawAttribute::GetScale(void) const
	{
		return (m_vScale);
	}

	// 设置旋转
	void CEntityDrawAttribute::SetRotate(const osg::Vec3d& vRot)
	{
		// 设置成弧度
		m_vRotate.set(osg::DegreesToRadians(vRot.x()), osg::DegreesToRadians(vRot.y()), osg::DegreesToRadians(vRot.z()));
	}

	// 获得旋转
	osg::Vec3d CEntityDrawAttribute::GetRotate(void) const
	{
		return (m_vRotate);
	}

	// 设置显示模式
	void CEntityDrawAttribute::SetDrawModel( const IEntityDrawAttribute::DrawModel dm )
	{
		m_drawModel = dm;
	}

	IEntityDrawAttribute::DrawModel CEntityDrawAttribute::GetDrawModel( void ) const
	{
		return (m_drawModel);
	}

	// 设置二维显示图片
	void CEntityDrawAttribute::SetEntity2D( const VRString& strFile )
	{
		if (0 == strFile.compare(m_strFile))
		{
			return;
		}

		m_bChange2D = true;
		m_strFile = strFile;
	}

	// 获得二维显示图片
	VRString CEntityDrawAttribute::GetEntity2D( void ) const
	{
		return (m_strFile);
	}

	// 是否改变当前的二维图片
	bool CEntityDrawAttribute::ChangeEntity2D( void ) const
	{
		bool bChange2D = m_bChange2D;
		if (bChange2D)
		{
			m_bChange2D = false;
		}
		return (bChange2D);
	}

	// 初始化通过xml节点初始化
	void CEntityDrawAttribute::ReadXmlNode( TiXmlElement* pTiXmlElement )
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
			if (0 == strValue.compare("位置"))
			{
				TiXmlElement* pChildXmlElement = pSubXmlElement->FirstChildElement();
				osg::Vec3d vPos;
				while(NULL != pChildXmlElement)
				{
					VRString strChildValue = pChildXmlElement->Value();
					if (0 == strChildValue.compare("经度"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vPos.x() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("纬度"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vPos.y() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("高度"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vPos.z() = CVRStringUtil::StringToNumber<double>(strText);						
					}

					pChildXmlElement = pChildXmlElement->NextSiblingElement();
				}

				// 设置位置
				GetItem("位置")->SetValue(vPos);
			}
			else if (0 == strValue.compare("缩放"))
			{
				TiXmlElement* pChildXmlElement = pSubXmlElement->FirstChildElement();
				osg::Vec3d vScale;
				while(NULL != pChildXmlElement)
				{
					VRString strChildValue = pChildXmlElement->Value();
					if (0 == strChildValue.compare("缩放X"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vScale.x() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("缩放Y"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vScale.y() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("缩放Z"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vScale.z() = CVRStringUtil::StringToNumber<double>(strText);						
					}

					pChildXmlElement = pChildXmlElement->NextSiblingElement();
				}
				GetItem("缩放")->SetValue(vScale);
			}
			else if (0 == strValue.compare("旋转"))
			{
				TiXmlElement* pChildXmlElement = pSubXmlElement->FirstChildElement();
				osg::Vec3d vRotate;
				while(NULL != pChildXmlElement)
				{
					VRString strChildValue = pChildXmlElement->Value();
					if (0 == strChildValue.compare("航向角"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vRotate.z() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("俯仰角"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vRotate.x() = CVRStringUtil::StringToNumber<double>(strText);						
					}
					else if (0 == strChildValue.compare("翻滚角"))
					{
						const VRString strText = pChildXmlElement->GetText();
						vRotate.y() = CVRStringUtil::StringToNumber<double>(strText);						
					}

					pChildXmlElement = pChildXmlElement->NextSiblingElement();
				}
				GetItem("旋转")->SetValue(vRotate);
			}
			else if (0 == strValue.compare("显示模式"))
			{
				VRString strText = pSubXmlElement->GetText();
				strText = CVRStringUtil::ToUpper(strText);
				GetItem("显示模式")->SetValue(strText);
			}
			else if (0 == strValue.compare("二维图片"))
			{
				VRString strText = pSubXmlElement->GetText();
				strText = CVRStringUtil::ToUpper(strText);
				GetItem("二维图片")->SetValue(strText);
			}

			// 读取下一个属性
			pSubXmlElement = pSubXmlElement->NextSiblingElement();
		}
	}

}

