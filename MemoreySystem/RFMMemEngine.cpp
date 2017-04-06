#include <stdio.h>
#include <Windows.h>
// #include "../../Public/VRSoft.h"
//typedef unsigned long		ULONG;
//typedef unsigned char       UCHAR;
//typedef unsigned short		USHORT;
//typedef unsigned long		DWORD;
//typedef long				LONG;

#include "../../Public/VRSoft.h"
#include "RFMMemEngine.h"

#pragma comment(lib, "lib/rfm2gdll_stdc.lib")

namespace VR_Soft
{
	CRFMMemEngine::CRFMMemEngine(void)
		:m_bOpen(false)
	{
	}


	CRFMMemEngine::~CRFMMemEngine(void)
	{
		Close();
	}

	// 是否打开
	bool CRFMMemEngine::IsOpen( void ) const
	{
		return (m_bOpen);
	}

	// 打开设备
	void CRFMMemEngine::Open( void )
	{
		char device[20];
		#define DEVICE_PREFIX   "\\\\.\\rfm2g"
		RFM2G_INT32    numDevice = 1;
		sprintf(device, "%s%d", DEVICE_PREFIX, numDevice);

		RFM2G_STATUS result = RFM2gOpen( device, &m_rfm2Handle );
		if( result != RFM2G_SUCCESS )
		{
			IComManager::GetInstance().WriteLogMsg("内存发射卡打开失败", ERRROR_OPENFAILD);
			return;
		}
		
		m_bOpen = true;
		IComManager::GetInstance().WriteLogMsg("内存发射卡打开");
	}

	// 关闭设备
	void CRFMMemEngine::Close( void )
	{
		// 判断是否已经打开
		if (!IsOpen())
		{
			return;
		}

		// 关闭设备
		RFM2gClose( &m_rfm2Handle );
		m_bOpen = false;
		IComManager::GetInstance().WriteLogMsg("内存发射卡关闭");
	}

	// 写入发射内存卡
	bool CRFMMemEngine::Write( void* src, size_t offset, size_t count )
	{
		RFM2G_STATUS result = RFM2gWrite(m_rfm2Handle, offset, src, count);
		if (result == RFM2G_SUCCESS)
		{
			return (true);
		}

		return (false);
	}

	// 从反射内存卡读取
	bool CRFMMemEngine::Read( void* dst, size_t offset, size_t count ) const
	{
		RFM2G_STATUS result = RFM2gRead(m_rfm2Handle, offset, dst, count);
		if (result == RFM2G_SUCCESS)
		{
			return (true);
		}

		return (false);
	}

}
