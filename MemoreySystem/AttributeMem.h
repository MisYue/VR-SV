/************************************************************************
 作者： LJ                                                            
 用途:  模型属性对于的内存映射表
 时间： 2015-12-01                                                    
 修改时间: 
************************************************************************/
#ifndef _ATTRIBUTEMEM_H_
#define _ATTRIBUTEMEM_H_

#pragma once

#include "../../Public/VRSoft.h"
#include "MemObj.h"

namespace VR_Soft
{
	class CAttributeMem
	{
	public:
		CAttributeMem(void);
		CAttributeMem(const size_t offset, const uint64_t ID);
		// 拷贝构造
		CAttributeMem(const CAttributeMem& other);
		// 赋值构造
		CAttributeMem& operator= (const CAttributeMem& other);
		~CAttributeMem(void);


	public:
		// 设置属性
		size_t SetItem(IAttribute* pIAttribute, size_t offset);
		// 获得偏移量
		size_t GetOffset(const VRString& strName) const;
		// 获得内存值
		const CMemObj GetMenObj(const VRString& strName) const;
		// 获得自身偏移量
		size_t GetOffset(void) const;
		// 获得占用的空间
		int GetSize(const VRString& strName) const;
		// 获得占用的空间
		int GetSize(void) const;
		// 获得当前属性占用的所有空间
		int GetDataSize(void) const;
		// 获得数据
		void* GetData(void) const;
		// 设置数据
		void SetData(void* data);
		// 获得ID
		uint64_t GetID(void) const;

	protected:
		// 添加属性项
		void AddItem(IAttributeItem* pIAttributeItem, size_t offset, size_t count);
		// 移除属性项
		void Remove(IAttributeItem* pIAttributeItem);

	protected:
		typedef std::vector<CMemObj> ListMemObj; // 属性名称对应的偏移量

	private:
	//	VR_AUTO_MUTEX;
		ListMemObj m_lstMemObj; // 内存列表
		size_t m_nOffset; // 当前属性的偏移量
		int m_nSize; // 占用空间大小
		int m_nCount; // 包含属性个数
		uint64_t m_ID; // 属性值对应的ID
		mutable char* m_pszData; // 数据
	};
}


#endif // !_ATTRIBUTEMEM_H_