#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/MemoreySystem/MemorySystem.h"
#include "../../Public/MemoreySystem/MemTemplate.h"
#include "MemoryEngine.h"
#include "MemEngineConfig.h"
#include "RFMMemEngine.h"
#include "MemorySystem.h"

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CMemoryManagerFactory::FACTORY_TYPE_NAME = MEMORYSYSTEM_TYPENAME;
	///////////////////////////////////////////////


	// ���캯��
	CMemorySystem::CMemorySystem(const VRString& strName)
		:IMemoryManager(),m_pMemMap(NULL), m_pMemEngine(NULL), m_pMemConfig(NULL)
	{
		SetName(strName);
	}

	// ��������
	CMemorySystem::~CMemorySystem(void)
	{
		// ���

		VRSOFT_DELETE(m_pMemMap);
		VRSOFT_DELETE(m_pMemConfig);
		VRSOFT_DELETE(m_pMemEngine);
	}

	// ��ȡ��������
	const VRString& CMemorySystem::GetTypeName(void) const
	{
		return (CMemoryManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��ʼ��ϵͳ
	void CMemorySystem::Init(void)
	{
		m_pMemConfig = new CMemEngineConfig;
		m_pMemEngine = new CMemoryEngine;
		m_pMemMap = new CMemMap(m_pMemEngine);
	}


	// д���ڴ�
	void CMemorySystem::Write( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		if (typeid(int) == var.type())
		{
			WriteInt(ID, strName, var);
		}
		else if (typeid(float) == var.type())
		{
			WriteFlot(ID, strName, var);
		}
		else if (typeid(double) == var.type())
		{
			WriteDouble(ID, strName, var);
		}
		else if (typeid(bool) == var.type())
		{
			WriteBool(ID, strName, var);
		}
		else if (typeid(osg::Vec3) == var.type())
		{
			WriteVec3(ID, strName, var);
		}
		else if (typeid(osg::Vec3d) == var.type())
		{
			WriteVec3d(ID, strName, var);
		}
	}

	// ת��Сд����
	char* strlwr(char *str)
	{
		if(str == NULL)
			return NULL;

		char *p = str;
		while (*p != '\0')
		{
			if(*p >= 'A' && *p <= 'Z')
				*p = (*p) + 0x20;
			p++;
		}
		return str;
	}

	// ��ȡ�ڴ�
	VRVariant CMemorySystem::Read(const uint64_t ID,  const VRString& strName, const char* pszType,  bool &bChang )
	{
		char* pszLowType =  strlwr(const_cast<char*>(pszType));
		// ��ѯ�Ƿ��õ�ǰ���ڴ�ƫ����
	/*	MemModel m = m_pMemMap->GetOffset(ID, strName);
		if (-1 == m.m_offset)
		{
		bChang = false;
		return (VRVariant());
		}*/

		if (0 == strcmp(pszLowType, "int"))
		{
			return ReadInt(ID, strName, bChang);
		}
		else if (0 == strcmp(pszLowType, "float"))
		{
			return ReadFloat(ID, strName, bChang);
		}
		else if (0 == strcmp(pszLowType, "double"))
		{
			return ReadDouble(ID, strName, bChang);
		}
		else if (0 == strcmp(pszLowType, "bool"))
		{
			return ReadBool(ID, strName, bChang);
		}
		else if (0 == strcmp(pszLowType, "class osg::vec3f"))
		{
			return ReadVec3(ID, strName, bChang);
		}
		else if (0 == strcmp(pszLowType, "class osg::vec3d"))
		{
			return ReadVec3d(ID, strName, bChang);
		}

		return (VRVariant());
		//m_pMemEngine->Read(&var,m.offset, m.count);
	}

	// ������д��
	void CMemorySystem::WriteInt(const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<int>(ID, strName, var);
	}

	// ��ȡ����
	int CMemorySystem::ReadInt( const uint64_t ID, const VRString& strName, bool& bChange )
	{
	/*	int nValue = 0;*/
		return (ReadTemplate<int>( ID, strName, bChange));
		//return (nValue);
	}

	// д��float
	void CMemorySystem::WriteFlot(const uint64_t ID,  const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<float>(ID, strName, var);
	}

	// ��ȡfloat
	float CMemorySystem::ReadFloat( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//float fValue = 0.0f;
		return ReadTemplate<float>(ID, strName, bChange);
		//return (fValue);
	}

	// д��double
	void CMemorySystem::WriteDouble( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<double>(ID, strName, var);
	}

	// ��ȡdouble
	double CMemorySystem::ReadDouble( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//double dValue = 0.0;
		return ReadTemplate<double>(ID, strName, bChange);
		//return (dValue);
	}

	// д��Vec3
	void CMemorySystem::WriteVec3( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<osg::Vec3>(ID, strName, var);
	}

	// д��Vec3d
	void CMemorySystem::WriteVec3d( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<osg::Vec3d>(ID, strName, var);
	}

	// ��ȡvec3
	osg::Vec3 CMemorySystem::ReadVec3( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//osg::Vec3 vValue(0.0f, 0.0f, 0.0f);
		return ReadTemplate<osg::Vec3>(ID, strName, bChange);
		//return (vValue);
	}

	// ��ȡvec3
	osg::Vec3d CMemorySystem::ReadVec3d( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//osg::Vec3 vValue(0.0f, 0.0f, 0.0f);
		return ReadTemplate<osg::Vec3d>(ID, strName, bChange);
		//return (vValue);
	}

	// д��bool
	void CMemorySystem::WriteBool( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		 WriteTemplate<bool>(ID, strName, var);
	}

	// ��ȡbool
	bool CMemorySystem::ReadBool( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//bool bValue;
		return ReadTemplate<bool>(ID, strName, bChange);
		//return (bValue);
	}

	// д�뷢���ڴ濨
	bool CMemorySystem::WriteToCard( void* src, size_t offset, size_t count )
	{
		return (m_pMemEngine->GetRFMMemEngine()->Write(src, offset, count));
	}

	// �ӷ����ڴ濨��ȡ
	bool CMemorySystem::ReadFromCard( void* dst, size_t offset, size_t count ) const
	{
		return (m_pMemEngine->GetRFMMemEngine()->Read(dst, offset, count));
	}

	// �����ڴ�ӳ���
	bool CMemorySystem::UpdateMemTab( const uint64_t oldID, const uint64_t newID, IEntityBase* pIEntity )
	{
		return (m_pMemMap->UpdateMemTab(oldID, newID, pIEntity));
	}

	// ��ʼ���ڴ�
	void CMemorySystem::InitMemory( void )
	{
		m_pMemEngine->InitEngine();
	}

}

