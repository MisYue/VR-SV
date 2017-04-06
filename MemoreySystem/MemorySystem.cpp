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


	// 构造函数
	CMemorySystem::CMemorySystem(const VRString& strName)
		:IMemoryManager(),m_pMemMap(NULL), m_pMemEngine(NULL), m_pMemConfig(NULL)
	{
		SetName(strName);
	}

	// 析构函数
	CMemorySystem::~CMemorySystem(void)
	{
		// 获得

		VRSOFT_DELETE(m_pMemMap);
		VRSOFT_DELETE(m_pMemConfig);
		VRSOFT_DELETE(m_pMemEngine);
	}

	// 获取类型名称
	const VRString& CMemorySystem::GetTypeName(void) const
	{
		return (CMemoryManagerFactory::FACTORY_TYPE_NAME);
	}

	// 初始化系统
	void CMemorySystem::Init(void)
	{
		m_pMemConfig = new CMemEngineConfig;
		m_pMemEngine = new CMemoryEngine;
		m_pMemMap = new CMemMap(m_pMemEngine);
	}


	// 写入内存
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

	// 转换小写函数
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

	// 读取内存
	VRVariant CMemorySystem::Read(const uint64_t ID,  const VRString& strName, const char* pszType,  bool &bChang )
	{
		char* pszLowType =  strlwr(const_cast<char*>(pszType));
		// 查询是否获得当前的内存偏移量
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

	// 按类型写入
	void CMemorySystem::WriteInt(const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<int>(ID, strName, var);
	}

	// 读取整形
	int CMemorySystem::ReadInt( const uint64_t ID, const VRString& strName, bool& bChange )
	{
	/*	int nValue = 0;*/
		return (ReadTemplate<int>( ID, strName, bChange));
		//return (nValue);
	}

	// 写入float
	void CMemorySystem::WriteFlot(const uint64_t ID,  const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<float>(ID, strName, var);
	}

	// 读取float
	float CMemorySystem::ReadFloat( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//float fValue = 0.0f;
		return ReadTemplate<float>(ID, strName, bChange);
		//return (fValue);
	}

	// 写入double
	void CMemorySystem::WriteDouble( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<double>(ID, strName, var);
	}

	// 读取double
	double CMemorySystem::ReadDouble( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//double dValue = 0.0;
		return ReadTemplate<double>(ID, strName, bChange);
		//return (dValue);
	}

	// 写入Vec3
	void CMemorySystem::WriteVec3( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<osg::Vec3>(ID, strName, var);
	}

	// 写入Vec3d
	void CMemorySystem::WriteVec3d( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		WriteTemplate<osg::Vec3d>(ID, strName, var);
	}

	// 读取vec3
	osg::Vec3 CMemorySystem::ReadVec3( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//osg::Vec3 vValue(0.0f, 0.0f, 0.0f);
		return ReadTemplate<osg::Vec3>(ID, strName, bChange);
		//return (vValue);
	}

	// 读取vec3
	osg::Vec3d CMemorySystem::ReadVec3d( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//osg::Vec3 vValue(0.0f, 0.0f, 0.0f);
		return ReadTemplate<osg::Vec3d>(ID, strName, bChange);
		//return (vValue);
	}

	// 写入bool
	void CMemorySystem::WriteBool( const uint64_t ID, const VRString& strName, const VRVariant& var )
	{
		 WriteTemplate<bool>(ID, strName, var);
	}

	// 读取bool
	bool CMemorySystem::ReadBool( const uint64_t ID, const VRString& strName, bool& bChange )
	{
		//bool bValue;
		return ReadTemplate<bool>(ID, strName, bChange);
		//return (bValue);
	}

	// 写入发射内存卡
	bool CMemorySystem::WriteToCard( void* src, size_t offset, size_t count )
	{
		return (m_pMemEngine->GetRFMMemEngine()->Write(src, offset, count));
	}

	// 从反射内存卡读取
	bool CMemorySystem::ReadFromCard( void* dst, size_t offset, size_t count ) const
	{
		return (m_pMemEngine->GetRFMMemEngine()->Read(dst, offset, count));
	}

	// 更新内存映射表
	bool CMemorySystem::UpdateMemTab( const uint64_t oldID, const uint64_t newID, IEntityBase* pIEntity )
	{
		return (m_pMemMap->UpdateMemTab(oldID, newID, pIEntity));
	}

	// 初始化内存
	void CMemorySystem::InitMemory( void )
	{
		m_pMemEngine->InitEngine();
	}

}

