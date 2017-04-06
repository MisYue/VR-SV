/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体渲染属性接口类	                                        */
/* 时间： 2016-08-10                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ENTITYDRAWATTRIUBTE_H_
#define _ENTITYDRAWATTRIUBTE_H_

#pragma once

namespace VR_Soft
{
	class CEntityDrawAttribute : public CAttributeImp<IEntityDrawAttribute>
	{
	public:
		// 构造函数
		explicit CEntityDrawAttribute(IEntityBase* pIEntityBase);
		// 析构函数
		virtual ~CEntityDrawAttribute(void);

	public:
		// 初始化
		virtual void Init();
		// 获得位置
		virtual void SetPosition(const osg::Vec3d& vPos) ;
		// 获得位置
		virtual osg::Vec3d GetPosition(void) const ;
		// 设置缩放
		virtual void SetScale(const osg::Vec3d& vScale) ;
		// 获得缩放
		virtual osg::Vec3d GetScale(void) const ;
		// 设置旋转
		virtual void SetRotate(const osg::Vec3d& vRot);
		// 获得旋转
		virtual osg::Vec3d GetRotate(void) const ;
		// 设置显示模式
		virtual void SetDrawModel(const DrawModel dm);
		// 获得显示模式
		virtual DrawModel GetDrawModel(void) const;
		// 设置二维显示图片
		virtual void SetEntity2D(const VRString& strFile);
		// 获得二维显示图片
		virtual VRString GetEntity2D(void) const;
		// 是否改变当前的二维图片
		virtual bool ChangeEntity2D(void) const;

	public:
		// 初始化通过xml节点初始化
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement);

	public:
		// 属性
		DECLARE_PROPERTY(CEntityDrawAttribute, osg::Vec3d, Position);
		DECLARE_PROPERTY(CEntityDrawAttribute, osg::Vec3d, Scale);
		DECLARE_PROPERTY(CEntityDrawAttribute, osg::Vec3d, Rotate);
		DECLARE_PROPERTY(CEntityDrawAttribute, DrawModel, DrawModel);
		DECLARE_PROPERTY(CEntityDrawAttribute, VRString, Entity2D);

	private:
		osg::Vec3d m_vPostion; // 位置
		osg::Vec3d m_vScale; // 缩放
		osg::Vec3d m_vRotate; // 旋转
		DrawModel m_drawModel; // 显示模式
		VRString m_strFile; // 二维图片
		mutable bool m_bChange2D; // 是否改变二维图片

	};

	class CEntityDrawAttributeFactory : public IAttributeFactory	
	{
	public:
		CEntityDrawAttributeFactory(void):m_strAttributeName("实体渲染属性") { }
		virtual ~CEntityDrawAttributeFactory(void) { }
		virtual const VRString& GetName(void) const { return (m_strAttributeName); }
		virtual IAttribute* CreateInstance(IEntityBase* pIEntity) { return (new CEntityDrawAttribute(pIEntity)); }
	private:
		VRString m_strAttributeName;
	};	
}


#endif // !_ENTITYDRAWATTRIUBTE_H_