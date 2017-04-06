/************************************************************************
 作者： LJ                                                            
 用途:  内存共享引擎类 对内存进行写入和读出
 时间： 2015-10-21                                                    
 修改时间:                                                            
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
		// 构造函数
		explicit CMemoryEngine(void);
		// 析构函数
		~CMemoryEngine(void);

	public:
		// 写入内存
		//bool Write(const VRString& strName, const VRVariant& var);
		// 写入内存
		bool Write(void* src, size_t offset, size_t count );
		// 读出内存
		bool Read(void* dst, size_t offset, size_t count) const;
		// 获得偏移位置
		size_t GetCurOffset(void) const;
		// 设置偏移位置
		void SetCurOffset(const size_t offset) ;

		// 获得板卡指针对象
		CRFMMemEngine* GetRFMMemEngine(void) const; 

		// 初始化引擎
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
		boost::interprocess::shared_memory_object * m_pShardMemObj; // boost库中内存共享对象库
		//boost::interprocess::segment_manager* m_pSegment_Manager; // 内存管理
		boost::interprocess::mapped_region* m_pMapRegion; // boost 库中内存隐射库
		char* m_szMemSart; // 记录内存其实点
		mutable size_t m_nCurPos; // 当前的偏移位置
		size_t m_nStartData; // 数据记录开始位置
		size_t m_nCount;
		size_t m_nOffset; // 板卡偏移量
		char* m_pszTemp;

		CRFMMemEngine* m_pRFMMenEgn; // 发射内存卡引擎

		friend class CMemMap;
	};
}

#endif // _MEMORYENGINE_H_