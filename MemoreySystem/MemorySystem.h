/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  �ڴ湲����ϵͳ
 ʱ�䣺 2015-10-21                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _MEMORYSYSTEM_H_
#define _MEMORYSYSTEM_H_

#pragma once

#include "MemMap.h"

namespace VR_Soft
{
	class CMemoryEngine;
	class CMemEngineConfig;

	class CMemorySystem : public IMemoryManager
	{
	public:
		explicit CMemorySystem(const VRString& strName);
		virtual ~CMemorySystem(void);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��ʼ��ϵͳ
		virtual void Init(void);
		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	public:
		// д���ڴ�
		virtual void Write(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// ��ȡ�ڴ�
		virtual VRVariant Read(const uint64_t ID, const VRString& strName, const char* pszType, bool& bChang);
		// д�뷢���ڴ濨
		virtual bool WriteToCard(void* src, size_t offset, size_t count );
		// �ӷ����ڴ濨��ȡ
		virtual bool ReadFromCard(void* dst, size_t offset, size_t count) const ;
		// �����ڴ�ӳ���
		virtual bool UpdateMemTab(const uint64_t oldID, const uint64_t newID, IEntityBase* pIEntity);
		// ��ʼ���ڴ�
		virtual void InitMemory(void);

	public:
		// ������ö���
		inline CMemEngineConfig* GetConfig(void) { return m_pMemConfig;}

	protected:
		// д������
		void WriteInt(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// ��ȡ����
		int ReadInt(const uint64_t ID, const VRString& strName, bool& bChange);
		// д��float
		void WriteFlot(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// ��ȡfloat
		float ReadFloat(const uint64_t ID, const VRString& strName, bool& bChange);
		// д��double
		void WriteDouble(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// ��ȡdouble
		double ReadDouble(const uint64_t ID, const VRString& strName, bool& bChange);
		// д��Vec3
		void WriteVec3(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// д��Vec3
		void WriteVec3d(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// ��ȡvec3
		osg::Vec3 ReadVec3(const uint64_t ID, const VRString& strName, bool& bChange);
		// ��ȡvec3
		osg::Vec3d ReadVec3d(const uint64_t ID, const VRString& strName, bool& bChange);
		// д��bool
		void WriteBool(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// ��ȡbool
		bool ReadBool(const uint64_t ID, const VRString& strName, bool& bChange);

	protected:
		////////////////////////////////ģ�溯��//////////////////////////////////////////
		template<typename type>
		void WriteTemplate(const uint64_t ID, const VRString& strName, const VRVariant& var)
		{
			MemModel m = m_pMemMap->GetOffset(ID, strName);
			if (-1 == m.m_offset)
			{
				return;			
			}

			// ֱ�Ӹ���
			type nValue = boost::any_cast<type>(var);
			m_pMemEngine->Write(&nValue, m.m_offset, m.m_count);

		}

		template <typename type>
		type ReadTemplate(const uint64_t ID, const VRString& strName, bool bChange)
		{
			// ��ѯ�Ƿ��õ�ǰ���ڴ�ƫ����
			MemModel m = m_pMemMap->GetOffset(ID, strName);
			if (-1 == m.m_offset)
			{
				return (type());
			}

			// ��ȡֵ
			type tyValue;
			m_pMemEngine->Read(&tyValue, m.m_offset, m.m_count);

			return (tyValue);
		}

		//////////////////////////////////////////////////////////////////////////

	private:
		VRString m_strName;
		CMemMap* m_pMemMap; // �ڴ�����
		CMemoryEngine* m_pMemEngine; // �ڴ�����
		CMemEngineConfig* m_pMemConfig; // �ڴ�������
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CMemorySystem, MemoryManager, MEMORYSYSTEM_TYPENAME, INSTANCE_NAME_MEMORYSYSTEM, MEMORYSYSTEM_DISC );
}


#endif //  _MEMORYSYSTEM_H_