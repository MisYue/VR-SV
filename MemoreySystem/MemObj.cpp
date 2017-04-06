#include <memory.h>
#include "../../Public/VRSoft.h"
#include "MemObj.h"

namespace VR_Soft
{
	// 默认构造
	CMemObj::CMemObj( void )
		:m_strName(""),
		m_offset(-1),
		m_count(-1),
		m_pszData(NULL)
	{

	}

	// 带参构造
	CMemObj::CMemObj(const char* pszName, size_t offset, size_t cnt)
		:m_strName(pszName),
		m_offset(offset),
		m_count(cnt),
		m_pszData(NULL)
	{
		m_nsizeName = m_strName.size();

		int n = sizeof(size_t) << 1;
		// 占用内存大小
		m_nSize = (sizeof(int) << 1) + (sizeof(size_t) << 1) + m_nsizeName;

		// 转换成类数据
		ConvertToData();
	}

	// 拷贝构造
	CMemObj::CMemObj( const CMemObj& other )
		:m_nsizeName(other.m_nsizeName),
		m_strName(other.m_strName),
		m_offset(other.m_offset),
		m_count(other.m_count),
		m_nSize(other.m_nSize)
	{
		m_pszData = new char[m_nSize];
		memcpy(m_pszData, other.m_pszData, m_nSize);
	}

	CMemObj::~CMemObj(void)
	{
		VRSOFT_DELETE_ARRAY(m_pszData);
	}

	// 赋值操作符
	CMemObj CMemObj::operator=( const CMemObj& other )
	{
		m_nsizeName = other.m_nsizeName;
		m_strName = other.m_strName;
		m_offset = other.m_offset;
		m_count = other.m_count;
		m_nSize = other.m_nSize;

		// 删除已有内存
		VRSOFT_DELETE_ARRAY(m_pszData);
		m_pszData = new char[m_nSize];
		memcpy(m_pszData, other.m_pszData, m_nSize);

		return (*this);
	}

	// 获得占用映射表内存大小
	int CMemObj::GetSize( void ) const
	{
		return (m_nSize);
	}

	// 获得内存
	void* CMemObj::GetData( void ) const
	{
		// 创建内存数组 
		
		return (m_pszData);
	}

	// 设置内存
	void CMemObj::SetData( void* data )
	{
		// 获得类大小
		memcpy(&m_nSize, data, sizeof(int));

		// 重新分配类大小
		VRSOFT_DELETE_ARRAY(m_pszData);
		m_pszData = new char[m_nSize];
		memcpy(m_pszData, data, m_nSize);

		// 调用转换函数
		ConvertToClass();
		
	}

	// 将类转换成内存值
	void CMemObj::ConvertToData( void ) const
	{
		// 内存分配如下 类大小 + 名称大小 + 名称 + 偏移量 + 占用大小
		m_pszData = new char[m_nSize];
		memset(m_pszData, 0, m_nSize);

		int nOffset = sizeof(int);
		memcpy((void*)m_pszData, &m_nSize, sizeof(int));
		// 保存名称大小
		memcpy((void*)(m_pszData + nOffset), &m_nsizeName, sizeof(int));
		nOffset += sizeof(int);
		// 保存名称
		memcpy((void*)(m_pszData + nOffset), m_strName.data(), m_nsizeName);
		nOffset += m_nsizeName;
		// 保存偏移量
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));
		nOffset += sizeof(size_t);
		// 保存占用内存量
		memcpy((void*)(m_pszData + nOffset), &m_count, sizeof(int));
	}

	// 内存转换成类
	void CMemObj::ConvertToClass( void )
	{
		// 类大小已经在上面获取
		int nOffset = sizeof(int);

		// 获得名称大小
		memcpy(&m_nsizeName, (void*)(m_pszData + nOffset), sizeof(int));
		nOffset += sizeof(int);

		// 获得类型名称
		char szName[256] = {0};
		memcpy(szName, (void*)(m_pszData + nOffset), m_nsizeName);
		nOffset += m_nsizeName;
		m_strName = szName;

		// 获得偏移量
		memcpy(&m_offset, (void*)(m_pszData + nOffset), sizeof(size_t));
		nOffset += sizeof(size_t);

		// 获得占用空间
		memcpy(&m_count, (void*)(m_pszData + nOffset), sizeof(int));
	}

	// 设置偏移量
	void CMemObj::SetOffset( const size_t offset )
	{
		m_offset = offset;

		// 重置内存
		int nOffset = (sizeof(int) << 1) + m_nsizeName;
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));
	}

	// 获得偏移量
	size_t CMemObj::GetOffset( void ) const
	{
		return (m_offset);
	}

	// 设置占用空间
	void CMemObj::SetCount( const size_t cnt )
	{
		m_count = cnt;

		// 重置内存
		int nOffset = (sizeof(int) << 1) + m_nsizeName + sizeof(size_t);
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));
	}

	// 获得占用空间大小
	int CMemObj::GetCount( void ) const
	{
		return (m_count);
	}

	// 设置偏移量和空间
	void CMemObj::SetOffsetAndCount( const size_t offset, const size_t cnt )
	{
		m_offset = offset;

		// 重置内存
		int nOffset = (sizeof(int) << 1) + m_nsizeName;
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));

		m_count = cnt;

		// 重置内存
		nOffset += sizeof(size_t);
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));
	}

	// 获得偏移量和空间
	void CMemObj::GetOffsetAndCount( size_t& offset, size_t& cnt )
	{
		offset = m_offset;
		cnt = m_count;

	}

	// 等号操作符
	bool CMemObj::operator==( const VRString& strName ) const
	{
		return (0 == m_strName.compare(strName));
	}

	

}
