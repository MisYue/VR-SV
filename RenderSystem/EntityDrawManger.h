/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����Ⱦ������		                                        */
/* ʱ�䣺 2016-03-19                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���캯��
		explicit CEntityDrawManger(IEntityBase* pIEntityBase);
		// ��������
		virtual ~CEntityDrawManger(void);

	public:
		// ���ʵ��
		virtual IEntityBase* GetEntity(void) const ;
		// ���õ�����
		virtual void SetMapNode3D(osgEarth::MapNode* pMapNode);
		// ���õ�����
		virtual void SetMapNode2D(osgEarth::MapNode* pMapNode);
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void);
		// �����Ⱦ��2D 
		virtual DrawObj* GetDrawObj2D(void);
		// ��ø���Ⱦ��
		virtual DrawObj* GetRootDrawObj(void);
		// �����Ⱦ��
		virtual void Add(IDrawAttribute* pIDrawAttribute);
		// �Ƴ���Ⱦ����
		virtual void Remove(IDrawAttribute* pIDrawAttribute);
		// �Ƴ���Ⱦ����
		virtual void Remove(const VRString& strName) ;
		// �Ƴ�������Ⱦ����
		virtual void RemoveAll();
		// �޸�ʵ����Ⱦ
		virtual void ChangerMeshDrawAttribute(IDrawAttribute* pIDrawAttribute, const VRString& strName) ;
		// �����Ⱦ����
		virtual IDrawAttribute* GetAttribute(const VRString& strName) const ;
		// ��������
		virtual void Update(void);

	protected:
		// ��ʼ��
		void Init(void);
		// �����Ƿ���ڵ�ǰ������
		bool IsHand(IDrawAttribute* pIDrawAttribte);
		// �������ֵ
		int GetIndexDrawAttribute(IDrawAttribute* pIDrawAttribute);
		// �ı��άͼƬ
		void ChangeEntity2D( const VRString& strEntity2D );

	private:
		IEntityBase* m_pIEntityBase; // ʵ�����
		osg::Group* m_pRoot;
		osg::MatrixTransform* m_pMtRoot;  // ��ת��
		osg::MatrixTransform* m_pMtRoot2D; // 
		ListDrawAttribtes m_lstDrawAttribute; // ��Ⱦ���Լ���
	//	osgEarth::Annotation::ModelNode* m_pModelNode; // ������ʾ��
		osgEarth::MapNode* m_pMapNode3D; // ��ͼ�ڵ�
		osgEarth::MapNode* m_pMapNode2D; // ��ͼ�ڵ�

		osg::LOD* m_pLod;
		osg::Geode* m_p2DImage; // ��ά��ʾͼƬ
		osg::MatrixTransform* m_p3DRoot; // ��ά��ʾ�ڵ�

		VR_AUTO_MUTEX; 
	};

}

#endif // ! _ENTITYDRAWMANAGER_H_