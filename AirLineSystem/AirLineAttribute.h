/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������			                                        */
/* ʱ�䣺 2015-08-04                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _AIRLINEATTRIBUTE_H_
#define _AIRLINEATTRIBUTE_H_

#pragma once

namespace VR_Soft
{

	class CAirLineAttribute : public CAttributeImp<IAttribute>
	{
	public:
		explicit CAirLineAttribute(IEntityBase* pIEntityComponent, const VRString& strName);
		virtual ~CAirLineAttribute(void);

	public:
		// ��ʼ��
		virtual void Init(void);
	};
}

#endif // _AIRLINEATTRIBUTE_H_