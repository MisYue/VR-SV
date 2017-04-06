/************************************************************************
 作者： LJ                                                            
 用途:  内存共享插件系统接口
 时间： 2015-10-21                                                    
 修改时间:                                                            
************************************************************************/

#ifndef _PUBLICE_MEMORYMANAGER_H_
#define _PUBLICE_MEMORYMANAGER_H_

namespace VR_Soft
{
	const VRString MEMORYSYSTEM_TYPENAME = "MEMORYSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_MEMORYSYSTEM = "MEMORYSYSTEM";
	const VRString MEMORYSYSTEM_DISC = "内存共享系统";

	class IMemoryManager : public CSingleton<IMemoryManager>, public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~IMemoryManager() { }
		// 写入内存
		virtual void Write(const uint64_t ID, const VRString& strName, const VRVariant& var) = 0;
		// 读取内存
		virtual VRVariant Read(const uint64_t ID, const VRString& strName, const char* pszType,  bool& bChang ) = 0;
		// 写入发射内存卡
		virtual bool WriteToCard(void* src, size_t offset, size_t count ) = 0;
		// 从反射内存卡读取
		virtual bool ReadFromCard(void* dst, size_t offset, size_t count) const = 0;
		// 更新内存映射表
		virtual bool UpdateMemTab(const uint64_t oldID, const uint64_t newID, IEntityBase* pIEntity) = 0;
		// 初始化内存
		virtual void InitMemory(void) = 0;
	};
}

#endif // _PUBLICE_MEMORYMANAGER_H_