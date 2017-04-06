/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �״�����				                                        */
/* ʱ�䣺 2015-06-02                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _RADARATTRIBUTE_H_
#define _RADARATTRIBUTE_H_
#pragma once

#include "../../Public/EntitySystem/AttributeImp.h"

namespace VR_Soft
{
	class IRadar; 

	class CRadarAttribute : public CAttributeImp<IAttribute>
	{
	public:
		explicit CRadarAttribute(IRadar* pIRadar, const VRString& strName);
		virtual ~CRadarAttribute(void);

	public:
		// ��ʼ��
		void Init(void);
	protected:
		typedef std::map<VRString, VRString> MapStrName;

	};

}

#endif // _RADARATTRIBUTE_H_