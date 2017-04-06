/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  生成系统唯一标识符	                                        */
/* 时间： 2015-12-01                                                    */
/* 修改时间:                                                            */
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

		// 生成UUID
		static int64_t Generate(void);
	};
	
}

#endif // !_PUBLICE_UUID_H_