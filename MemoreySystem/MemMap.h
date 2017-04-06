/************************************************************************
 作者： LJ                                                            
 用途:  共享内存大小关系隐射表， 在内存中需要先对其进行查询，然后再进行对内存
		中的值进行访问操作
 时间： 2015-10-21                                                    
 修改时间: 2015-11-06                                                           
************************************************************************/

#ifndef _MEMMAP_H_
#define _MEMMAP_H_

#pragma once

#include "AttributeMem.h"

namespace VR_Soft
{

	//类型和allocator的定义，使用共享内存时需要使用boost::interprocess中  
	//重新实现的容器而不能使用标准容器
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
		
		size_t m_offset; // 偏移量
		size_t m_count; // 大小
	};

	
	class CMemoryEngine;

	class CMemMap
	{
	public:
		CMemMap(CMemoryEngine* pMemEng);
		~CMemMap(void);

	public:
		// 获得内存偏移量
		MemModel GetOffset(const uint64_t ID, const VRString& strName) const;
		// 更新内存映射表
		bool UpdateMemTab(const uint64_t oldID, const uint64_t newID, IEntityBase* pIEntity);

	protected:
		// 更新当前的映射表
		void UpdateMemMap(const uint64_t ID) const;
		// 更新当前隐射表到内存中
		void UpdateMemMapToMem(const uint64_t ID) const;
		// 判断当前的内存映射表是否需要重新更新
		bool IsUpdateAllMemMap(const uint64_t ID) const;
		// 更新所有的映射表
		void UpdateAllMemMap(const uint64_t ID) const;
		// 获得当前映射表偏移量
		size_t GetMapCurOffset(void) ;
		// 设置当前偏移量
		void SetMapCurOffset(void);
	protected:
		// 类型定义
		typedef std::map<uint64_t, CAttributeMem> ListAttributeMem; 

	private:
		//void_allocator* m_pVoidAlloc;
		mutable ListAttributeMem m_lstMemMap;
		CMemoryEngine* m_pMemEng; // 引擎指针
		size_t m_nStartPos; // 开始位置
		size_t m_nCurPos; // 当前游标的位置
		mutable int m_nCurCount; // 当前偏移量
		int m_nCurSizePos; // 当前偏移量的位置
		int n_nCountPos; // 用于标注当前个数的位置
		int m_nDataPos; // 用于保存数据为位置
		int m_nFlag ; // 标志位

	//	volatile mutable bool m_bUpdate;

		// mutable boost::recursive_mutex mutex;
		VR_AUTO_MUTEX
	};
}

#endif // ! _MEMMAP_H_