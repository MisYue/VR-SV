#pragma once

#include "../../Public/EntitySystem/AttributeImp.h"

namespace VR_Soft
{
	class CGroundRadarAttribute : public CAttributeImp<IAttribute>
	{
	public:
		explicit CGroundRadarAttribute(IRadar* pIRadar, const VRString& strName);
		virtual ~CGroundRadarAttribute(void);

	public:
		// ��ʼ��
		virtual void Init(void);
	};

}

