/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  osgEarth3D����		                                        */
/* ʱ�䣺 2016-06-30                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _OSGEARTH3D_H_
#define _OSGEARTH3D_H_

#pragma once

#include "OsgEarth.h"

#include <osgEarthUtil/MeasureTool>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/Sky>


namespace VR_Soft
{
	class CSynchroManipulator;

	class COsgEarth3D : public COsgEarth
	{
	public:
		explicit COsgEarth3D();
		~COsgEarth3D(void);

	public:
		// �����ͼ
		virtual void Attach(IRenderView* pIRenderView);

	public:
		// ���ʵ��
		virtual void AddEntity(IEntityBase* pIEntity);
		// ��Ӽ�����Ⱦ��
		virtual void AddFeatureGeomtry(const IFeatureGeomtry* pIFeatureGoemtry);
		// ���õ�������
		virtual osgEarth::MapNode* InitMapNode(osgEarth::MapNode* pNodeMap);

	protected:
		// ��ʼ��������ع���
		void InitEarthTool(IRenderView* pIRenderView);

	public:
		// �����պ���
		void AddSkyBox(osgEarth::MapNode* pMapNode );
		// ���ָ����
		void AddNorthArrow(CSynchroManipulator* pSynchroManip, IRenderView* pIView );
		// ���㿪��
		void DistanceEnable( bool bEnable );
		// ������㹦�ܿ���
		bool GetDistanceEnable(void) const;

	private:
		osg::ref_ptr<osgEarth::Util::MeasureToolHandler> m_pMeasureToolHandler;
		osgViewer::View* m_pView;
		osgEarth::Util::Controls::ControlCanvas* m_pCanvas;
		bool m_bDistanceEnable; // ���㿪�ر�־

		osg::ref_ptr<osgEarth::Util::SkyNode> m_pSkyNode; // ��պ���
	};
}


#endif // !_OSGEARTH2D_H_