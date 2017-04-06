/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  �����ڴ��С��ϵ����� ���ڴ�����Ҫ�ȶ�����в�ѯ��Ȼ���ٽ��ж��ڴ�
		�е�ֵ���з��ʲ���
 ʱ�䣺 2015-10-21                                                    
 �޸�ʱ��: 2015-11-06                                                           
************************************************************************/

#ifndef _MEMMAP_H_
#define _MEMMAP_H_

#pragma once

#include "AttributeMem.h"

namespace VR_Soft
{

	//���ͺ�allocator�Ķ��壬ʹ�ù����ڴ�ʱ��Ҫʹ��boost::interprocess��  
	//����ʵ�ֵ�����������ʹ�ñ�׼����
	/*typedef managed_shared_memory::segment_manager                       segment_manager_t; 
	typedef allocator<void, segment_manager_t>                           void_allocator;  
	typedef allocator<int, segment_manager_t>                            int_allocator;  
	typedef vector<int, int_allocator>                                   int_vector;  
	typedef allocator<int_vector, segment_manager_t>                     int_vector_allocator;  
	typedef vector<int_vector, int_vector_allocator>                     int_vector_vector;  
	typedef allocator<char, segment_manager_t>                           char_allocator;  
	typedef basic_string<char, std::char_traits<char>, char_allocator>   char_string;  */

	struct MemModel
	{
		MemModel()
			:m_offset(-1),
			m_count(-1)
		{
			m_offset = -1;
			m_count = -1;
		}

		MemModel(size_t offset, size_t count)
			:m_offset(offset),
			m_count(count)
		{

		}
		
		size_t m_offset; // ƫ����
		size_t m_count; // ��С
	};

	
	class CMemoryEngine;

	class CMemMap
	{
	public:
		CMemMap(CMemoryEngine* pMemEng);
		~CMemMap(void);

	public:
		// ����ڴ�ƫ����
		MemModel GetOffset(const uint64_t ID, const VRString& strName) const;
		// �����ڴ�ӳ���
		bool UpdateMemTab(const uint64_t oldID, const uint64_t newID, IEntityBase* pIEntity);

	protected:
		// ���µ�ǰ��ӳ���
		void UpdateMemMap(const uint64_t ID) const;
		// ���µ�ǰ������ڴ���
		void UpdateMemMapToMem(const uint64_t ID) const;
		// �жϵ�ǰ���ڴ�ӳ����Ƿ���Ҫ���¸���
		bool IsUpdateAllMemMap(const uint64_t ID) const;
		// �������е�ӳ���
		void UpdateAllMemMap(const uint64_t ID) const;
		// ��õ�ǰӳ���ƫ����
		size_t GetMapCurOffset(void) ;
		// ���õ�ǰƫ����
		void SetMapCurOffset(void);
	protected:
		// ���Ͷ���
		typedef std::map<uint64_t, CAttributeMem> ListAttributeMem; 

	private:
		//void_allocator* m_pVoidAlloc;
		mutable ListAttributeMem m_lstMemMap;
		CMemoryEngine* m_pMemEng; // ����ָ��
		size_t m_nStartPos; // ��ʼλ��
		size_t m_nCurPos; // ��ǰ�α��λ��
		mutable int m_nCurCount; // ��ǰƫ����
		int m_nCurSizePos; // ��ǰƫ������λ��
		int n_nCountPos; // ���ڱ�ע��ǰ������λ��
		int m_nDataPos; // ���ڱ�������Ϊλ��
		int m_nFlag ; // ��־λ

	//	volatile mutable bool m_bUpdate;

		// mutable boost::recursive_mutex mutex;
		VR_AUTO_MUTEX
	};
}

#endif // ! _MEMMAP_H_