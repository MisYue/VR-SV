#pragma once

#include "../../Public/EntitySystem/AttributeImp.h"

namespace VR_Soft
{
	class CSignalWaveAttribute : public CAttributeImp<IAttribute>
	{
	public:
		CSignalWaveAttribute(IEntityBase* pIEntityComponent, const VRString& strName);
		virtual ~CSignalWaveAttribute(void);

		virtual void Init(void);
	};
}


