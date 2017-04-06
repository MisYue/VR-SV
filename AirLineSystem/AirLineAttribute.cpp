#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "AirLineAttribute.h"


namespace VR_Soft
{
	CAirLineAttribute::CAirLineAttribute(IEntityBase* pIEntityComponent, const VRString& strName)
		:CAttributeImp<IAttribute>(pIEntityComponent, strName)
	{
	}


	CAirLineAttribute::~CAirLineAttribute(void)
	{
	}

	// ��ʼ��
	void CAirLineAttribute::Init(void)
	{
		// ������ɫ����
		IAttributeItem* pIAttribute = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "��ɫ", "��ɫ", "", \
			osg::Vec4(1.0f, 1.0f, 1.0f, 1.0), CTRL_TREE);
		AddAttrItem(pIAttribute);

		// ��С
		pIAttribute = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "��С", "��С", "��", 1.0f);
		AddAttrItem(pIAttribute);
	}

}

