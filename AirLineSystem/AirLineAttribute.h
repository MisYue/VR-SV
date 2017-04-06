/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线属性类			                                        */
/* 时间： 2015-08-04                                                    */
/* 修改时间:                                                            */
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
		// 初始化
		virtual void Init(void);
	};
}

#endif // _AIRLINEATTRIBUTE_H_