/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ģ�����Զ��ڵ��ڴ�ӳ���
 ʱ�䣺 2015-12-01                                                    
 �޸�ʱ��: 
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
		// ��������
		CAttributeMem(const CAttributeMem& other);
		// ��ֵ����
		CAttributeMem& operator= (const CAttributeMem& other);
		~CAttributeMem(void);


	public:
		// ��������
		size_t SetItem(IAttribute* pIAttribute, size_t offset);
		// ���ƫ����
		size_t GetOffset(const VRString& strName) const;
		// ����ڴ�ֵ
		const CMemObj GetMenObj(const VRString& strName) const;
		// �������ƫ����
		size_t GetOffset(void) const;
		// ���ռ�õĿռ�
		int GetSize(const VRString& strName) const;
		// ���ռ�õĿռ�
		int GetSize(void) const;
		// ��õ�ǰ����ռ�õ����пռ�
		int GetDataSize(void) const;
		// �������
		void* GetData(void) const;
		// ��������
		void SetData(void* data);
		// ���ID
		uint64_t GetID(void) const;

	protected:
		// ���������
		void AddItem(IAttributeItem* pIAttributeItem, size_t offset, size_t count);
		// �Ƴ�������
		void Remove(IAttributeItem* pIAttributeItem);

	protected:
		typedef std::vector<CMemObj> ListMemObj; // �������ƶ�Ӧ��ƫ����

	private:
	//	VR_AUTO_MUTEX;
		ListMemObj m_lstMemObj; // �ڴ��б�
		size_t m_nOffset; // ��ǰ���Ե�ƫ����
		int m_nSize; // ռ�ÿռ��С
		int m_nCount; // �������Ը���
		uint64_t m_ID; // ����ֵ��Ӧ��ID
		mutable char* m_pszData; // ����
	};
}


#endif // !_ATTRIBUTEMEM_H_