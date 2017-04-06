#include <map>
#include <list>
#include <algorithm>
#include "../../Public/VRSoft.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "AirLineBind.h"

namespace VR_Soft
{
	CAirLineBind::CAirLineBind(void)
	{
	}

	CAirLineBind::~CAirLineBind(void)
	{
	}

	// 绑定航线
	void CAirLineBind::Bind(IEntityBase* pIEntity, IAirLine* pIAriLine)
	{
		// 查询航线
		ListAirLineBinds::iterator itor = m_lstAirLineBinds.find(pIAriLine);
		if (m_lstAirLineBinds.end() == itor)
		{
			ListEntityBases lstEntityBases;
			lstEntityBases.push_back(pIEntity);
			m_lstAirLineBinds[pIAriLine] = lstEntityBases;

			return;
		}

		ListEntityBases& lstEntityBases = itor->second;
		ListEntityBases::const_iterator cstItor = std::find(lstEntityBases.begin(), lstEntityBases.end(), pIEntity);
		if (lstEntityBases.end() != cstItor)
		{
			return;
		}
		lstEntityBases.push_back(pIEntity);

	}

	// 解除绑定
	void CAirLineBind::UnBind( IEntityBase* pIEntity, IAirLine* pIAriLine)
	{
		// 查询航线
		ListAirLineBinds::iterator itor = m_lstAirLineBinds.find(pIAriLine);
		if (m_lstAirLineBinds.end() == itor)
		{
			return;
		}

		ListEntityBases& lstEntityBases = itor->second;
		ListEntityBases::iterator lineItor = std::find(lstEntityBases.begin(), lstEntityBases.end(), pIEntity);
		if (lstEntityBases.end() != lineItor)
		{
			lstEntityBases.erase(lineItor);
		}
	}

	// 获得航线
	IAirLine* CAirLineBind::GetAirLine(IEntityBase* pIEntity) const
	{
		// 遍历所有的航线
		ListAirLineBinds::const_iterator cstItor = m_lstAirLineBinds.begin();
		for (; m_lstAirLineBinds.end() != cstItor; ++cstItor)
		{
			ListEntityBases lstEntityBases = cstItor->second;
			ListEntityBases::const_iterator cstItorLine = std::find(lstEntityBases.begin(), lstEntityBases.end(), pIEntity);
			if (lstEntityBases.end() != cstItorLine)
			{
				return (cstItor->first);
			}
		}

		return (NULL);
	}

}
