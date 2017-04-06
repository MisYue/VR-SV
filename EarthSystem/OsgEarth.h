/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  osgEarth����		                                            */
/* ʱ�䣺 2016-07-01                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _OSGEARTH_H_
#define _OSGEARTH_H_

#pragma once

#include <boost/regex.hpp>
#include <osgEarth/MapNode>
#include <osgEarthUtil/GraticuleNode>
#include <osgEarthUtil/AutoClipPlaneHandler>

namespace VR_Soft
{
	class IRenderView;

	class COsgEarth : public IEarth
	{
	public:
		explicit COsgEarth(void);
		virtual ~COsgEarth(void);

	public:
		// �����ͼ
		virtual void Attach(IRenderView* pIRenderView);
		// ��ö�Ӧ�ĵ���ڵ�
		virtual EarthMap* GetEarthMap(void) const;
		// ��ʾ������
		void SetGraticuleState(bool bShow);
		// ����������Ƿ���ʾ
		bool GetGraticuleState(void) const;
		

	public:
		// ���ʵ�嵽���ֵ��򳡾���
		virtual void AddEntity(IEntityBase* pIEntity) = 0;
		// ��Ӽ�����Ⱦ��
		virtual void AddFeatureGeomtry(const IFeatureGeomtry* pIFeatureGoemtry) = 0;

	public:
		// �����ͼ
		IRenderView* GetRenderView(void) const;
		// �����ͼ����
		inline const VRString& GetRenderName(void) const { return (m_strViewName); }
		// ���õ�������
		virtual osgEarth::MapNode* InitMapNode(osgEarth::MapNode* pNodeMap);

	protected:
		// ��ø��ڵ�
		virtual osg::Group* GetRoot(void) const ;
		

	protected:
		osgEarth::MapNode* m_pMapNode;
		osgEarth::Util::GraticuleNode* m_pGraticuleNode;
		osg::Group* m_pRoot;
		VRString m_strViewName;
		osg::Camera* m_pCamera;
	};

/////////////////////////////��������/////////////////////////////////////////////
	class COsgEarth2D;
	class COsgEarth3D;

	class CEarthFactory
	{
	public: 
		// ����2D��ͼ
		static COsgEarth* CreateEarth2D(osgEarth::MapNode* pMapNode);
		// ����3D��ͼ
		static COsgEarth* CreateEarth3D(osgEarth::MapNode* pMapNode);
	};
}


#endif // !_OSGEARTH_H_