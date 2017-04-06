/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  �ڴ�ӳ����ж�Ӧ���ڴ���
 ʱ�䣺 2015-12-02                                                    
 �޸�ʱ��: 
************************************************************************/

#ifndef _MEMOBJ_H_
#define _MEMOBJ_H_

#pragma once

namespace VR_Soft
{
	class CMemObj
	{
	public:
		// Ĭ�Ϲ���
		CMemObj(void);
		// ����
		CMemObj(const char* pszName, size_t ofset, size_t cnt);
		// ��������
		CMemObj(const CMemObj& other);
		~CMemObj(void);
		// ��ֵ������
		CMemObj operator=(const CMemObj& other);
		// �ȺŲ�����
		bool operator== (const VRString& strName) const;

	public:
		// ����ƫ����
		void SetOffset(const size_t offset);
		// ���ƫ����
		size_t GetOffset(void) const;
		// ����ռ�ÿռ�
		void SetCount(const size_t cnt);
		// ���ռ�ÿռ��С
		int GetCount(void) const;
		// ����ƫ�����Ϳռ�
		void SetOffsetAndCount(const size_t offset, const size_t cnt);
		// ���ƫ�����Ϳռ�
		void GetOffsetAndCount(size_t& offset, size_t& cnt);

	public:
		// ���ռ��ӳ����ڴ��С
		int GetSize(void) const;
		// ����ڴ�
		void* GetData(void) const;
		// �����ڴ�
		void SetData(void* data);

	protected:
		// ����ת�����ڴ�ֵ
		void ConvertToData(void) const;
		// �ڴ�ת������
		void ConvertToClass(void);


	private:
		int m_nsizeName;
		VRString m_strName;
		size_t m_offset; // ƫ����
		int m_count; // ��С
		int m_nSize; // ��ǰ���С
		mutable char* m_pszData; // �ַ�����
	};
}

#endif // !_MEMOBJ_H_