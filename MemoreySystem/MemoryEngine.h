/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  �ڴ湲�������� ���ڴ����д��Ͷ���
 ʱ�䣺 2015-10-21                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _MEMORYENGINE_H_
#define _MEMORYENGINE_H_

#pragma once

//#include "../../Public/VRSoft.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/segment_manager.hpp>

namespace VR_Soft
{
	class CRFMMemEngine; 

	class CMemoryEngine
	{
	public:
		// ���캯��
		explicit CMemoryEngine(void);
		// ��������
		~CMemoryEngine(void);

	public:
		// д���ڴ�
		//bool Write(const VRString& strName, const VRVariant& var);
		// д���ڴ�
		bool Write(void* src, size_t offset, size_t count );
		// �����ڴ�
		bool Read(void* dst, size_t offset, size_t count) const;
		// ���ƫ��λ��
		size_t GetCurOffset(void) const;
		// ����ƫ��λ��
		void SetCurOffset(const size_t offset) ;

		// ��ð忨ָ�����
		CRFMMemEngine* GetRFMMemEngine(void) const; 

		// ��ʼ������
		void InitEngine(void);

	protected:
		template <class T>
		bool Wirte(const VRString& strName, const T& val )
		{
			//float* pT = m_pShardMemObj->find_or_construct<float>(strName)();
			//*pT = val;
			return (true);
		}

	private:
		boost::interprocess::shared_memory_object * m_pShardMemObj; // boost�����ڴ湲������
		//boost::interprocess::segment_manager* m_pSegment_Manager; // �ڴ����
		boost::interprocess::mapped_region* m_pMapRegion; // boost �����ڴ������
		char* m_szMemSart; // ��¼�ڴ���ʵ��
		mutable size_t m_nCurPos; // ��ǰ��ƫ��λ��
		size_t m_nStartData; // ���ݼ�¼��ʼλ��
		size_t m_nCount;
		size_t m_nOffset; // �忨ƫ����
		char* m_pszTemp;

		CRFMMemEngine* m_pRFMMenEgn; // �����ڴ濨����

		friend class CMemMap;
	};
}

#endif // _MEMORYENGINE_H_