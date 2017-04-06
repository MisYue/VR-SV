/************************************************************************
 作者： LJ                                                            
 用途:  内存映射表中对应的内存项
 时间： 2015-12-02                                                    
 修改时间: 
************************************************************************/

#ifndef _MEMOBJ_H_
#define _MEMOBJ_H_

#pragma once

namespace VR_Soft
{
	class CMemObj
	{
	public:
		// 默认构造
		CMemObj(void);
		// 带参
		CMemObj(const char* pszName, size_t ofset, size_t cnt);
		// 拷贝构造
		CMemObj(const CMemObj& other);
		~CMemObj(void);
		// 赋值操作符
		CMemObj operator=(const CMemObj& other);
		// 等号操作符
		bool operator== (const VRString& strName) const;

	public:
		// 设置偏移量
		void SetOffset(const size_t offset);
		// 获得偏移量
		size_t GetOffset(void) const;
		// 设置占用空间
		void SetCount(const size_t cnt);
		// 获得占用空间大小
		int GetCount(void) const;
		// 设置偏移量和空间
		void SetOffsetAndCount(const size_t offset, const size_t cnt);
		// 获得偏移量和空间
		void GetOffsetAndCount(size_t& offset, size_t& cnt);

	public:
		// 获得占用映射表内存大小
		int GetSize(void) const;
		// 获得内存
		void* GetData(void) const;
		// 设置内存
		void SetData(void* data);

	protected:
		// 将类转换成内存值
		void ConvertToData(void) const;
		// 内存转换成类
		void ConvertToClass(void);


	private:
		int m_nsizeName;
		VRString m_strName;
		size_t m_offset; // 偏移量
		int m_count; // 大小
		int m_nSize; // 当前类大小
		mutable char* m_pszData; // 字符数组
	};
}

#endif // !_MEMOBJ_H_