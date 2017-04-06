#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "SimTimeAttr.h"
#include "SimState.h"
#include "SimTime.h"

namespace VR_Soft
{
	CSimTime::CSimTime(void)
		:m_pIAttribute(NULL),
		m_pIState(NULL)
	{
	}

	CSimTime::~CSimTime(void)
	{
		VRSOFT_DELETE(m_pIState);
		VRSOFT_DELETE(m_pIAttribute);
	}

}

