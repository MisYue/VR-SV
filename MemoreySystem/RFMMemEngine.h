/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������ʵ����                                                */
/* ʱ�䣺 2015-11-28                                                    */
/* �޸�ʱ��:                                                            */
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
		// �Ƿ��
		bool IsOpen(void) const;
		// ���豸
		void Open(void);
		// �ر��豸
		void Close(void);
		// д�뷢���ڴ濨
		bool Write(void* src, size_t offset, size_t count );
		// �ӷ����ڴ濨��ȡ
		bool Read(void* dst, size_t offset, size_t count) const;

	private: 
		bool m_bOpen;
		RFM2GHANDLE m_rfm2Handle; // ���俨���
	};
}



#endif // !_RFMMEMENGINE_H_