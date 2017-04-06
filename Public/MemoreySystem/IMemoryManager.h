/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  �ڴ湲����ϵͳ�ӿ�
 ʱ�䣺 2015-10-21                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _PUBLICE_MEMORYMANAGER_H_
#define _PUBLICE_MEMORYMANAGER_H_

namespace VR_Soft
{
	const VRString MEMORYSYSTEM_TYPENAME = "MEMORYSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_MEMORYSYSTEM = "MEMORYSYSTEM";
	const VRString MEMORYSYSTEM_DISC = "�ڴ湲��ϵͳ";

	class IMemoryManager : public CSingleton<IMemoryManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~IMemoryManager() { }
		// д���ڴ�
		virtual void Write(const uint64_t ID, const VRString& strName, const VRVariant& var) = 0;
		// ��ȡ�ڴ�
		virtual VRVariant Read(const uint64_t ID, const VRString& strName, const char* pszType,  bool& bChang ) = 0;
		// д�뷢���ڴ濨
		virtual bool WriteToCard(void* src, size_t offset, size_t count ) = 0;
		// �ӷ����ڴ濨��ȡ
		virtual bool ReadFromCard(void* dst, size_t offset, size_t count) const = 0;
		// �����ڴ�ӳ���
		virtual bool UpdateMemTab(const uint64_t oldID, const uint64_t newID, IEntityBase* pIEntity) = 0;
		// ��ʼ���ڴ�
		virtual void InitMemory(void) = 0;
	};
}

#endif // _PUBLICE_MEMORYMANAGER_H_