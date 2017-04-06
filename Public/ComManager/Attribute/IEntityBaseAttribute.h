/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基本属性接口类	                                        */
/* 时间： 2016-03-18                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IBASETTRIBUTE_H_
#define _PUBLICE_IBASETTRIBUTE_H_

namespace VR_Soft
{
	class IEntityID;

	class VRSOFT_DLL IEntityBaseAttribute : public IAttribute
	{
	public:
		// 坐标系统
		enum EntityCoordinate
		{
			MODEL, // 模型坐标系
			EARTH, // 地面坐标系
			WORLD // 世界坐标系
		};

	public:
		// 析构函数
		virtual ~IEntityBaseAttribute(void) { }
		// 设置实体名称
		virtual void SetEntityName(const VRString& strName) = 0;
		// 获得实体名称
		virtual VRString GetEntityName(void) const = 0;
		// 设置ID号 内部调用
		virtual void SetEntityID(IEntityID* pEntityID) = 0;
		// 设置ID号
		virtual void SetEntityID(const uint64_t uid) = 0;
		// 获得ID号
		virtual uint64_t GetEntityID(void) const = 0;
		// 设置坐标系
		virtual void SetEntityCoordinate(const EntityCoordinate ec) = 0 ;
		// 获得坐标系
		virtual EntityCoordinate GetEntityCoordinate(void) const = 0;
		// 设置类型
		virtual void SetEntityType(const VRString& strType ) = 0;
		// 获得类型
		virtual VRString GetEntityType(void) const = 0;
	};
}

#endif // !_PUBLICE_IBASETTRIBUTE_H_