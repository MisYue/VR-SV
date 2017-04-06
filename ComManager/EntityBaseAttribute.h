/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基本属性类		                                        */
/* 时间： 2016-03-18                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _BASEATTRIBUTE_H_
#define _BASEATTRIBUTE_H_

#pragma once

namespace VR_Soft
{

	class CEntityBaseAttribute : public CAttributeImp<IEntityBaseAttribute>
	{
	public:
		// 构造函数
		explicit CEntityBaseAttribute(IEntityBase* pIEntityBase);
		// 析构函数
		virtual ~CEntityBaseAttribute(void);

	public:
		// 初始化
		virtual void Init();
		// 设置实体名称
		virtual void SetEntityName(const VRString& strName);
		// 获得实体名称
		virtual VRString GetEntityName(void) const;
		// 设置ID号 内部调用
		virtual void SetEntityID(IEntityID* pEntityID);
		// 设置ID号
		virtual void SetEntityID(const uint64_t uid);
		// 获得ID号
		virtual uint64_t GetEntityID(void) const;
		// 设置坐标系
		virtual void SetEntityCoordinate(const EntityCoordinate ec) ;
		// 获得坐标系
		virtual EntityCoordinate GetEntityCoordinate(void) const ;
		// 设置类型
		virtual void SetEntityType(const VRString& strType );
		// 获得类型
		virtual VRString GetEntityType(void) const ;

	public:
		// 初始化通过xml节点初始化
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement);

	public:
		// 属性
		//AutoProperty(osg::Vec3d, Postion);
		DECLARE_PROPERTY(CEntityBaseAttribute, uint64_t, ID);
		DECLARE_PROPERTY(CEntityBaseAttribute, EntityCoordinate, EntityCoordinate);
		DECLARE_PROPERTY(CEntityBaseAttribute, VRString, Name);
		DECLARE_PROPERTY(CEntityBaseAttribute, VRString, Type);
		//property<CEntityBaseAttribute, osg::Vec3d>

	private: 
		//IEntityID* m_pIEntityID; // 模型标志 内存中唯一标志符号
		uint64_t m_uID;
		VRString m_strEntityName;
		EntityCoordinate m_entityCoordinate; // 是否依赖地球
		VRString m_strType; // 类型
	};

}


#endif // _BASEATTRIBUTE_H_