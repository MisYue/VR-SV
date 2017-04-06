#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/ElectMagSystem/IRadar.h"
#include "../../Public/EntitySystem/AttributeImp.h"
#include "SignalWaveAttribute.h"

namespace VR_Soft
{
	CSignalWaveAttribute::CSignalWaveAttribute(IEntityBase* pIEntityComponent, const VRString& strName)
		:CAttributeImp<IAttribute>(pIEntityComponent, strName)
	{
	}


	CSignalWaveAttribute::~CSignalWaveAttribute(void)
	{
	}

	void CSignalWaveAttribute::Init(void)
	{

	}
}
