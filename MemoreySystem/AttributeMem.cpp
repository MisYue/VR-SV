#include <algorithm>
#include "../../Public/VRSoft.h"
#include "AttributeMem.h"

namespace VR_Soft
{
	CAttributeMem::CAttributeMem(void)
		:m_nOffset(0),
		m_nSize(sizeof(size_t) + (sizeof(int) << 1) + sizeof(uint64_t)),
		m_nCount(0),
		m_ID(0),
		m_pszData(NULL)
	{
	}

	CAttributeMem::CAttributeMem(const size_t offset, const uint64_t ID)
		:m_nOffset(offset),
		m_nSize(sizeof(size_t) + (sizeof(int) << 1) + sizeof(uint64_t)),
		m_nCount(0),
		m_ID(ID),
		m_pszData(NULL)
	{
	}

	// 拷贝构造
	CAttributeMem::CAttributeMem( const CAttributeMem& other )
		:m_nOffset(other.m_nOffset),
		m_nSize(other.m_nSize),
		m_nCount(other.m_nCount),
		m_ID(other.m_ID),
		m_pszData(NULL)
	{
		if (NULL == other.m_pszData)
		{
			return;
		}
		// std::copy(other.m_lstMemObj.begin(), other.m_lstMemObj.end(), m_lstMemObj.begin());
		m_lstMemObj.clear();
		ListMemObj::const_iterator cstItor = other.m_lstMemObj.begin();
		for (; other.m_lstMemObj.end() != cstItor; ++cstItor)
		{
			m_lstMemObj.push_back(*cstItor);
		}
		// 删除原来的值
		VRSOFT_DELETE_ARRAY(m_pszData);
		m_pszData = new char[m_nSize];
		memcpy(m_pszData, other.m_pszData, m_nSize);
	}

	// 赋值构造
	CAttributeMem& CAttributeMem::operator=( const CAttributeMem& other )
	{
		m_nOffset = other.m_nOffset;
		m_nSize = other.m_nSize;
		m_nCount = other.m_nCount;
		m_ID = other.m_ID;
		/*m_lstMemObj.resize(m_nCount);
		std::copy(other.m_lstMemObj.begin(), other.m_lstMemObj.end(), m_lstMemObj.begin());*/
		m_lstMemObj.clear();
		ListMemObj::const_iterator cstItor = other.m_lstMemObj.begin();
		for (; other.m_lstMemObj.end() != cstItor; ++cstItor)
		{
			m_lstMemObj.push_back(*cstItor);
		}
		
		if (NULL == other.m_pszData)
		{
			return (*this);
		}
		// 删除原来的值
		VRSOFT_DELETE_ARRAY(m_pszData);
		m_pszData = new char[m_nSize];
		memcpy(m_pszData, other.m_pszData, m_nSize);
		return (*this);
	}


	CAttributeMem::~CAttributeMem(void)
	{
		// 删除原来的值
		VRSOFT_DELETE_ARRAY(m_pszData);
	}

	// 设置属性
	size_t CAttributeMem::SetItem( IAttribute* pIAttribute, size_t offset )
	{
		size_t tempOffset = offset;

		// 遍历所有的属性项
		const IAttribute::LstAttrItems& lstAttrItems = pIAttribute->GetAttrItems();
		IAttribute::LstAttrItems::const_iterator cstItor = lstAttrItems.begin();
		for (; lstAttrItems.end() != cstItor; ++cstItor)
		{
			IAttributeItem* pIAttributeItem = *cstItor;
			size_t itemSize = pIAttributeItem->GetSize();
			AddItem(pIAttributeItem, tempOffset, itemSize);
			tempOffset += itemSize;
		}

		if (!m_lstMemObj.empty())
		{
			m_nCount = m_lstMemObj.size();
		}
		else
		{
			m_nCount = 0;
		}

		return (tempOffset);
	}

	// 添加属性项
	void CAttributeMem::AddItem(IAttributeItem* pIAttributeItem, size_t offset, size_t count)
	{
	//	VR_MUTEX_AUTO
		// 获得属性项名称
		const VRString& strName = pIAttributeItem->GetTypeName();
		if (-1 != GetOffset(strName))
		{
			return;
		}
		
		CMemObj memObj(strName.c_str(), offset, count);
		m_lstMemObj.push_back(memObj);

		m_nSize += memObj.GetSize();
		
	}

	// 移除属性项
	void CAttributeMem::Remove(IAttributeItem* pIAttributeItem)
	{
	//	VR_MUTEX_AUTO
		// 获得属性项名称
		const VRString& strName = pIAttributeItem->GetTypeName();
		ListMemObj::iterator itor = std::find(m_lstMemObj.begin(), m_lstMemObj.end(), strName);
		if (m_lstMemObj.end() == itor)
		{
			return;
		}

		m_lstMemObj.erase(itor);
		if (!m_lstMemObj.empty())
		{
			m_nCount = m_lstMemObj.size();
		}
		else
		{
			m_nCount = 0;
		}
	}

	// 获得偏移量
	size_t CAttributeMem::GetOffset(const VRString& strName ) const
	{
		// 查找偏移量 不存在 则返回-1
		ListMemObj::const_iterator cstItor = std::find(m_lstMemObj.begin(), m_lstMemObj.end(), strName);
		if (m_lstMemObj.end() == cstItor)
		{
			return (-1);
		}

		const CMemObj& memObj = *cstItor;
		return (memObj.GetOffset());

	}

	// 获得自身偏移量
	size_t CAttributeMem::GetOffset( void ) const
	{
		return (m_nOffset);
	}

	// 获得占用的空间
	int CAttributeMem::GetSize( void ) const
	{
		return (m_nSize);
	}

	// 获得占用的空间
	int CAttributeMem::GetSize( const VRString& strName ) const
	{
		// 查找偏移量 不存在 则返回-1
		ListMemObj::const_iterator cstItor = std::find(m_lstMemObj.begin(), m_lstMemObj.end(), strName);
		if (m_lstMemObj.end() == cstItor)
		{
			return (-1);
		}

		const CMemObj& memObj = *cstItor;
		return (memObj.GetCount());
	}

	// 获得数据
	void* CAttributeMem::GetData( void ) const
	{
		// 删除原来的值
		VRSOFT_DELETE_ARRAY(m_pszData);
		m_pszData = new char[m_nSize];
		memset(m_pszData, 0, m_nSize);

		size_t offset = sizeof(int);
		memcpy(m_pszData, &m_nSize, offset);

		// 写入偏移量
		memcpy((void*)(m_pszData + offset), &m_nOffset, sizeof(size_t));
		offset += sizeof(size_t);

		// 写入个数
		memcpy((void*)(m_pszData + offset), &m_nCount, sizeof(int));
		offset += sizeof(int);

		// 写入ID
		memcpy((void*)(m_pszData + offset), &m_ID, sizeof(uint64_t));
		offset += sizeof(uint64_t);

		// 遍历所有的值
		ListMemObj::const_iterator cstItor = m_lstMemObj.begin();
		for (; m_lstMemObj.end() != cstItor; ++cstItor)
		{
			memcpy((void*)(m_pszData + offset), cstItor->GetData(), cstItor->GetSize());
			offset += cstItor->GetSize();
		}

		return (m_pszData);
	}

	// 设置数据
	void CAttributeMem::SetData( void* data )
	{
		// 清空原来的值
		m_lstMemObj.clear();

		// 解析原来得值
		size_t nOffset =  sizeof(size_t);
		memcpy(&m_nSize, data, sizeof(size_t));

		// 转换成char* 进行读内存中的值
		char* pszData = static_cast<char*>(data);

		// 读取偏移量
		// 读取包含个数
		memcpy(&m_nOffset, (void*)(pszData + nOffset), sizeof(size_t));
		nOffset += sizeof(size_t);

		// 读取包含个数
		memcpy(&m_nCount, (void*)(pszData + nOffset), sizeof(int));
		nOffset += sizeof(int);

		// 读取ID
		memcpy(&m_ID, (void*)(pszData + nOffset), sizeof(uint64_t));
		nOffset += sizeof(uint64_t);

		// 循环遍历
		for (int index = 0; index < m_nCount; ++index)
		{
			// 读取第一个大小值
			int nSize = 0;
			memcpy(&nSize, (void*)(pszData + nOffset), sizeof(int));

			// 读取整个内存
			char* pszTemp = new char[nSize];
			memset(pszTemp, 0, nSize);
			memcpy(pszTemp, (void*)(pszData + nOffset), nSize);

			CMemObj memObj;
			memObj.SetData(pszTemp);
			m_lstMemObj.push_back(memObj);

			nOffset += nSize;
			VRSOFT_DELETE_ARRAY(pszTemp);
		}
	}

	// 获得当前属性占用的所有空间
	int CAttributeMem::GetDataSize( void ) const
	{
		int nSize = 0;
		// 遍历所有的值
		ListMemObj::const_iterator cstItor = m_lstMemObj.begin();
		for (; m_lstMemObj.end() != cstItor; ++cstItor)
		{
			nSize += cstItor->GetCount();
		}

		return (nSize);
	}

	// 获得ID
	uint64_t CAttributeMem::GetID( void ) const
	{
		return (m_ID);
	}

	// 获得内存值
	const CMemObj CAttributeMem::GetMenObj( const VRString& strName ) const
	{
		// 查找偏移量 不存在 则返回-1
		ListMemObj::const_iterator cstItor = std::find(m_lstMemObj.begin(), m_lstMemObj.end(), strName);
		if (m_lstMemObj.end() == cstItor)
		{
			return (CMemObj());
		}

		return (*cstItor);
	}

}
