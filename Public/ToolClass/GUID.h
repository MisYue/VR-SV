/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳΨһ��ʶ��	                                        */
/* ʱ�䣺 2015-12-01                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_GUID_H_
#define _PUBLICE_GUID_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_TOOLCLASS_DLL CGUID
	{
	public:
		CGUID(void) ;
		~CGUID(void);

		// ����UUID
		static int64_t Generate(void);
	};
	
}

#endif // !_PUBLICE_UUID_H_