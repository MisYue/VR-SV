/************************************************************************
 作者： LJ                                                            
 用途:  内存共享插件系统
 时间： 2015-10-21                                                    
 修改时间:                                                            
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
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 初始化系统
		virtual void Init(void);
		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	public:
		// 写入内存
		virtual void Write(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// 读取内存
		virtual VRVariant Read(const uint64_t ID, const VRString& strName, const char* pszType, bool& bChang);
		// 写入发射内存卡
		virtual bool WriteToCard(void* src, size_t offset, size_t count );
		// 从反射内存卡读取
		virtual bool ReadFromCard(void* dst, size_t offset, size_t count) const ;
		// 更新内存映射表
		virtual bool UpdateMemTab(const uint64_t oldID, const uint64_t newID, IEntityBase* pIEntity);
		// 初始化内存
		virtual void InitMemory(void);

	public:
		// 获得配置对象
		inline CMemEngineConfig* GetConfig(void) { return m_pMemConfig;}

	protected:
		// 写入整形
		void WriteInt(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// 读取整形
		int ReadInt(const uint64_t ID, const VRString& strName, bool& bChange);
		// 写入float
		void WriteFlot(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// 读取float
		float ReadFloat(const uint64_t ID, const VRString& strName, bool& bChange);
		// 写入double
		void WriteDouble(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// 读取double
		double ReadDouble(const uint64_t ID, const VRString& strName, bool& bChange);
		// 写入Vec3
		void WriteVec3(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// 写入Vec3
		void WriteVec3d(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// 读取vec3
		osg::Vec3 ReadVec3(const uint64_t ID, const VRString& strName, bool& bChange);
		// 读取vec3
		osg::Vec3d ReadVec3d(const uint64_t ID, const VRString& strName, bool& bChange);
		// 写入bool
		void WriteBool(const uint64_t ID, const VRString& strName, const VRVariant& var);
		// 读取bool
		bool ReadBool(const uint64_t ID, const VRString& strName, bool& bChange);

	protected:
		////////////////////////////////模版函数//////////////////////////////////////////
		template<typename type>
		void WriteTemplate(const uint64_t ID, const VRString& strName, const VRVariant& var)
		{
			MemModel m = m_pMemMap->GetOffset(ID, strName);
			if (-1 == m.m_offset)
			{
				return;			
			}

			// 直接更新
			type nValue = boost::any_cast<type>(var);
			m_pMemEngine->Write(&nValue, m.m_offset, m.m_count);

		}

		template <typename type>
		type ReadTemplate(const uint64_t ID, const VRString& strName, bool bChange)
		{
			// 查询是否获得当前的内存偏移量
			MemModel m = m_pMemMap->GetOffset(ID, strName);
			if (-1 == m.m_offset)
			{
				return (type());
			}

			// 读取值
			type tyValue;
			m_pMemEngine->Read(&tyValue, m.m_offset, m.m_count);

			return (tyValue);
		}

		//////////////////////////////////////////////////////////////////////////

	private:
		VRString m_strName;
		CMemMap* m_pMemMap; // 内存隐射
		CMemoryEngine* m_pMemEngine; // 内存引擎
		CMemEngineConfig* m_pMemConfig; // 内存配置类
	};

	// 注册工厂
	REGISTER_COMFACTORY(CMemorySystem, MemoryManager, MEMORYSYSTEM_TYPENAME, INSTANCE_NAME_MEMORYSYSTEM, MEMORYSYSTEM_DISC );
}


#endif //  _MEMORYSYSTEM_H_