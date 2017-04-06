/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理实现类                                                */
/* 时间： 2015-11-28                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _RFMMEMENGINE_H_
#define _RFMMEMENGINE_H_

#pragma once
#include <Windows.h>
#include "inc/rfm2g_types.h"
#include "inc/rfm2g_api.h"
#include "inc/rfm2g_windows.h"

namespace VR_Soft
{
	class CRFMMemEngine
	{
	public:
		explicit CRFMMemEngine(void);
		~CRFMMemEngine(void);

	public:
		// 是否打开
		bool IsOpen(void) const;
		// 打开设备
		void Open(void);
		// 关闭设备
		void Close(void);
		// 写入发射内存卡
		bool Write(void* src, size_t offset, size_t count );
		// 从反射内存卡读取
		bool Read(void* dst, size_t offset, size_t count) const;

	private: 
		bool m_bOpen;
		RFM2GHANDLE m_rfm2Handle; // 发射卡句柄
	};
}



#endif // !_RFMMEMENGINE_H_