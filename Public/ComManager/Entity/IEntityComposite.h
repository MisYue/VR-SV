/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体组合管理类		                                        */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IENTITYCOMPOSITE_H_
#define _IENTITYCOMPOSITE_H_

namespace VR_Soft
{
	class IEntityFactoryManager;

	class VRSOFT_DLL IEntityComposite : public IEntityComponent
	{
	public:
		typedef std::list<IEntityComponent*> LstEntitys;
	public:
		// 析构函数
		virtual ~IEntityComposite(void) {}
		// 改变实体模型名称方便进行查找
		virtual bool ChangeEntityName(IEntityComponent* pIEntity, const VRString& strNewName) { return (false); }
		// 是否含有子集
		virtual bool IsExport(void) { return (true); }
		// 获得工厂管理
		virtual IEntityFactoryManager* GetEntityFactoryManager(void) { return (NULL); }
		// 添加对象
		virtual void AddEntity(IEntityComponent* pIEntity) { }
		// 移除对象
		virtual void RemoveEntity(IEntityComponent* pIEntity) { }
		// 移除对象 （不删除实际对象， 用于修改名称而已）
		virtual void RemoveEntity(const VRString& strName) { }
		// 删除所有对象
		virtual void RemoveAllEntity(void) { }
		// 查询获得对象
		virtual IEntityComponent* GetEntity(const VRString& strEntityID) { return (NULL); }
		// 获取所有的子集
		virtual const LstEntitys GetLstEntitys(void) const { LstEntitys lstEntitys; return (lstEntitys);  }
		// 通过组名称来查询对应的实体
		virtual IEntityComponent* GetEntity(const VRString& strCompName, const VRString& strEntityID) { return (NULL); }
		// 通过组名称来查询对应的实体
		virtual IEntityComponent* GetEntity(IEntityComponent* pIComponent, const VRString& strEntityID) { return (NULL); }
		// 通过组名称来创建对应的实体
		virtual IEntityComponent* CreateEntity(const VRString& strCompName, const VRString& strType, const uint64_t ID) { return (NULL); }
		// 通过组名称来查询对应的实体
		virtual IEntityComponent* CreateEntity(IEntityComponent* pIComponent, const VRString& strType, const uint64_t ID) { return (NULL); }

	};
}

#endif // _IENTITYCOMPOSITE_H_