#include <memory.h>
#include "../../Public/VRSoft.h"
#include "MemObj.h"

namespace VR_Soft
{
	// Ĭ�Ϲ���
	CMemObj::CMemObj( void )
		:m_strName(""),
		m_offset(-1),
		m_count(-1),
		m_pszData(NULL)
	{

	}

	// ���ι���
	CMemObj::CMemObj(const char* pszName, size_t offset, size_t cnt)
		:m_strName(pszName),
		m_offset(offset),
		m_count(cnt),
		m_pszData(NULL)
	{
		m_nsizeName = m_strName.size();

		int n = sizeof(size_t) << 1;
		// ռ���ڴ��С
		m_nSize = (sizeof(int) << 1) + (sizeof(size_t) << 1) + m_nsizeName;

		// ת����������
		ConvertToData();
	}

	// ��������
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

	// ��ֵ������
	CMemObj CMemObj::operator=( const CMemObj& other )
	{
		m_nsizeName = other.m_nsizeName;
		m_strName = other.m_strName;
		m_offset = other.m_offset;
		m_count = other.m_count;
		m_nSize = other.m_nSize;

		// ɾ�������ڴ�
		VRSOFT_DELETE_ARRAY(m_pszData);
		m_pszData = new char[m_nSize];
		memcpy(m_pszData, other.m_pszData, m_nSize);

		return (*this);
	}

	// ���ռ��ӳ����ڴ��С
	int CMemObj::GetSize( void ) const
	{
		return (m_nSize);
	}

	// ����ڴ�
	void* CMemObj::GetData( void ) const
	{
		// �����ڴ����� 
		
		return (m_pszData);
	}

	// �����ڴ�
	void CMemObj::SetData( void* data )
	{
		// ������С
		memcpy(&m_nSize, data, sizeof(int));

		// ���·������С
		VRSOFT_DELETE_ARRAY(m_pszData);
		m_pszData = new char[m_nSize];
		memcpy(m_pszData, data, m_nSize);

		// ����ת������
		ConvertToClass();
		
	}

	// ����ת�����ڴ�ֵ
	void CMemObj::ConvertToData( void ) const
	{
		// �ڴ�������� ���С + ���ƴ�С + ���� + ƫ���� + ռ�ô�С
		m_pszData = new char[m_nSize];
		memset(m_pszData, 0, m_nSize);

		int nOffset = sizeof(int);
		memcpy((void*)m_pszData, &m_nSize, sizeof(int));
		// �������ƴ�С
		memcpy((void*)(m_pszData + nOffset), &m_nsizeName, sizeof(int));
		nOffset += sizeof(int);
		// ��������
		memcpy((void*)(m_pszData + nOffset), m_strName.data(), m_nsizeName);
		nOffset += m_nsizeName;
		// ����ƫ����
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));
		nOffset += sizeof(size_t);
		// ����ռ���ڴ���
		memcpy((void*)(m_pszData + nOffset), &m_count, sizeof(int));
	}

	// �ڴ�ת������
	void CMemObj::ConvertToClass( void )
	{
		// ���С�Ѿ��������ȡ
		int nOffset = sizeof(int);

		// ������ƴ�С
		memcpy(&m_nsizeName, (void*)(m_pszData + nOffset), sizeof(int));
		nOffset += sizeof(int);

		// �����������
		char szName[256] = {0};
		memcpy(szName, (void*)(m_pszData + nOffset), m_nsizeName);
		nOffset += m_nsizeName;
		m_strName = szName;

		// ���ƫ����
		memcpy(&m_offset, (void*)(m_pszData + nOffset), sizeof(size_t));
		nOffset += sizeof(size_t);

		// ���ռ�ÿռ�
		memcpy(&m_count, (void*)(m_pszData + nOffset), sizeof(int));
	}

	// ����ƫ����
	void CMemObj::SetOffset( const size_t offset )
	{
		m_offset = offset;

		// �����ڴ�
		int nOffset = (sizeof(int) << 1) + m_nsizeName;
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));
	}

	// ���ƫ����
	size_t CMemObj::GetOffset( void ) const
	{
		return (m_offset);
	}

	// ����ռ�ÿռ�
	void CMemObj::SetCount( const size_t cnt )
	{
		m_count = cnt;

		// �����ڴ�
		int nOffset = (sizeof(int) << 1) + m_nsizeName + sizeof(size_t);
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));
	}

	// ���ռ�ÿռ��С
	int CMemObj::GetCount( void ) const
	{
		return (m_count);
	}

	// ����ƫ�����Ϳռ�
	void CMemObj::SetOffsetAndCount( const size_t offset, const size_t cnt )
	{
		m_offset = offset;

		// �����ڴ�
		int nOffset = (sizeof(int) << 1) + m_nsizeName;
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));

		m_count = cnt;

		// �����ڴ�
		nOffset += sizeof(size_t);
		memcpy((void*)(m_pszData + nOffset), &m_offset, sizeof(size_t));
	}

	// ���ƫ�����Ϳռ�
	void CMemObj::GetOffsetAndCount( size_t& offset, size_t& cnt )
	{
		offset = m_offset;
		cnt = m_count;

	}

	// �ȺŲ�����
	bool CMemObj::operator==( const VRString& strName ) const
	{
		return (0 == m_strName.compare(strName));
	}

	

}
