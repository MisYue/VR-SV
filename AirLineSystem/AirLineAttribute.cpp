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

	// 初始化
	void CAirLineAttribute::Init(void)
	{
		// 创建颜色属性
		IAttributeItem* pIAttribute = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "颜色", "颜色", "", \
			osg::Vec4(1.0f, 1.0f, 1.0f, 1.0), CTRL_TREE);
		AddAttrItem(pIAttribute);

		// 大小
		pIAttribute = IComManager::GetInstance().GetAttributeManager()->CreateAttributeItem(this, "大小", "大小", "米", 1.0f);
		AddAttrItem(pIAttribute);
	}

}

