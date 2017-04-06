/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体渲染管理类		                                        */
/* 时间： 2016-03-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ENTITYDRAWMANAGER_H_
#define _ENTITYDRAWMANAGER_H_

#pragma once

#include <vector>
#include <osgEarthAnnotation/ModelNode>
#include <osg/LOD>

namespace VR_Soft
{
	class CEntityDrawManger : public IEntityDrawManager
	{
		typedef std::vector<IDrawAttribute* > ListDrawAttribtes;
	public:
		// 构造函数
		explicit CEntityDrawManger(IEntityBase* pIEntityBase);
		// 析构函数
		virtual ~CEntityDrawManger(void);

	public:
		// 获得实体
		virtual IEntityBase* GetEntity(void) const ;
		// 设置地球体
		virtual void SetMapNode3D(osgEarth::MapNode* pMapNode);
		// 设置地球体
		virtual void SetMapNode2D(osgEarth::MapNode* pMapNode);
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void);
		// 获得渲染体2D 
		virtual DrawObj* GetDrawObj2D(void);
		// 获得根渲染体
		virtual DrawObj* GetRootDrawObj(void);
		// 添加渲染体
		virtual void Add(IDrawAttribute* pIDrawAttribute);
		// 移除渲染属性
		virtual void Remove(IDrawAttribute* pIDrawAttribute);
		// 移除渲染属性
		virtual void Remove(const VRString& strName) ;
		// 移除所有渲染属性
		virtual void RemoveAll();
		// 修改实体渲染
		virtual void ChangerMeshDrawAttribute(IDrawAttribute* pIDrawAttribute, const VRString& strName) ;
		// 获得渲染属性
		virtual IDrawAttribute* GetAttribute(const VRString& strName) const ;
		// 更新属性
		virtual void Update(void);

	protected:
		// 初始化
		void Init(void);
		// 查找是否存在当前的属性
		bool IsHand(IDrawAttribute* pIDrawAttribte);
		// 获得索引值
		int GetIndexDrawAttribute(IDrawAttribute* pIDrawAttribute);
		// 改变二维图片
		void ChangeEntity2D( const VRString& strEntity2D );

	private:
		IEntityBase* m_pIEntityBase; // 实体对象
		osg::Group* m_pRoot;
		osg::MatrixTransform* m_pMtRoot;  // 旋转体
		osg::MatrixTransform* m_pMtRoot2D; // 
		ListDrawAttribtes m_lstDrawAttribute; // 渲染属性集合
	//	osgEarth::Annotation::ModelNode* m_pModelNode; // 设置显示体
		osgEarth::MapNode* m_pMapNode3D; // 地图节点
		osgEarth::MapNode* m_pMapNode2D; // 地图节点

		osg::LOD* m_pLod;
		osg::Geode* m_p2DImage; // 二维显示图片
		osg::MatrixTransform* m_p3DRoot; // 三维显示节点

		VR_AUTO_MUTEX; 
	};

}

#endif // ! _ENTITYDRAWMANAGER_H_