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

	// �Ƿ��
	bool CRFMMemEngine::IsOpen( void ) const
	{
		return (m_bOpen);
	}

	// ���豸
	void CRFMMemEngine::Open( void )
	{
		char device[20];
		#define DEVICE_PREFIX   "\\\\.\\rfm2g"
		RFM2G_INT32    numDevice = 1;
		sprintf(device, "%s%d", DEVICE_PREFIX, numDevice);

		RFM2G_STATUS result = RFM2gOpen( device, &m_rfm2Handle );
		if( result != RFM2G_SUCCESS )
		{
			IComManager::GetInstance().WriteLogMsg("�ڴ淢�俨��ʧ��", ERRROR_OPENFAILD);
			return;
		}
		
		m_bOpen = true;
		IComManager::GetInstance().WriteLogMsg("�ڴ淢�俨��");
	}

	// �ر��豸
	void CRFMMemEngine::Close( void )
	{
		// �ж��Ƿ��Ѿ���
		if (!IsOpen())
		{
			return;
		}

		// �ر��豸
		RFM2gClose( &m_rfm2Handle );
		m_bOpen = false;
		IComManager::GetInstance().WriteLogMsg("�ڴ淢�俨�ر�");
	}

	// д�뷢���ڴ濨
	bool CRFMMemEngine::Write( void* src, size_t offset, size_t count )
	{
		RFM2G_STATUS result = RFM2gWrite(m_rfm2Handle, offset, src, count);
		if (result == RFM2G_SUCCESS)
		{
			return (true);
		}

		return (false);
	}

	// �ӷ����ڴ濨��ȡ
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
