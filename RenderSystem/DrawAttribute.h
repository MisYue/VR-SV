/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体渲染属性			                                        */
/* 时间： 2015-08-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _DRAWATTRIBUTE_H_
#define _DRAWATTRIBUTE_H_

#pragma once

#include <osg/Group>

namespace VR_Soft
{
	class CDrawAttribute : public CAttributeImp<IMeshDrawAttribute>
	{
	public:
		explicit CDrawAttribute(IEntityBase* pIEntityBase, const VRString& strDrawName = "cow");
		virtual ~CDrawAttribute(void);

		// 初始化
		virtual void Init();
		// 更新
		virtual void Update(void);
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void);
		
		// 设置路径
		virtual void SetMeshPath(const VRString& strMeshPath);
		// 获得路径
		virtual VRString GetMeshPath(void) ;
		// 设置渲染体
		virtual void SetDrawObj(DrawObj* pDrawObj);

	public:
		// 初始化通过xml节点初始化
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement);
		
	public:
		// 设置实体名称
		void SetMeshName(const VRString& strMeshName);
		// 获得实体名称
		VRString GetMeshName(void) const;
		// 设置是否关闭光照
		void SetLightOff(bool bOff);
		// 设置是否关闭光照
		bool GetLightOff(void) const;

	public:
		DECLARE_PROPERTY(CDrawAttribute, VRString, MeshName);
		DECLARE_PROPERTY(CDrawAttribute, bool, Light);

	private:
		osg::Node* m_pNode;

		VRString m_strMeshName;
		bool m_bLight;
		//osg::Group* m_pGroup;
	};


	class CMeshAttributeFactory : public IAttributeFactory	
	{
	public:
		CMeshAttributeFactory(void):m_strAttributeName("三维模型属性") { }
		virtual ~CMeshAttributeFactory(void) { }
		virtual const VRString& GetName(void) const { return (m_strAttributeName); }
		virtual IAttribute* CreateInstance(IEntityBase* pIEntity) { return (new CDrawAttribute(pIEntity)); }
	private:
		VRString m_strAttributeName;
	};	

}

#endif