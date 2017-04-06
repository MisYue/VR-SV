/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  λ����ʾ����			                                        */
/* ʱ�䣺 2016-09-14                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PLOTPLACE_H_
#define _PLOTPLACE_H_

#pragma once

#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthSymbology/Geometry>

namespace VR_Soft
{
	class CPlotPlaceGeomtry : public IPlaceFeatureGeomtry
	{
	public:
		// ���캯��
		explicit CPlotPlaceGeomtry(void);
		// ��������
		virtual ~CPlotPlaceGeomtry(void);

	public:
		// ������ɫ
		virtual void SetColor(const osg::Vec4& vColor);
		// �����ɫ
		virtual osg::Vec4 GetColor(void) const;
		// �����߿�
		virtual void SetWidth(const float fWidth);
		// ����߿�
		virtual float GetWidth(void) const ;
		// �������ؼ���
		virtual void SetTechnique(const IFeatureGeomtry::Technique technique) ;
		// ������ؼ���
		virtual IFeatureGeomtry::Technique GetTechnique(void) const;
		// ���ø߳�
		virtual void SetClamping(const IFeatureGeomtry::Clamping clamping) ;
		// ���ģ��Ƕ��
		virtual  IFeatureGeomtry::Clamping GetClamping(void) const ;
		// ������е�
		virtual std::vector<osg::Vec3d> GetAllPoints(void) const ;
		// �������е�
		virtual void SetAllPoints(const std::vector<osg::Vec3d>& listPoints);
		// ���������
		virtual osg::Vec3d GetPoint(const int index) ;
		// ���õ�
		virtual void SetPoint(const int index, const osg::Vec3d& vPoint) ;
		// �Ƴ���
		virtual void Remove(const int index) ;
		// �Ƴ����еĵ�
		virtual void RemoveAll(void) ;
		// ����2D��ͼ
		virtual void SetMapNode2D(EarthMap* pEarthMap) ;
		// ����3D��ͼ
		virtual void SetMapNode3D(EarthMap* pEarthMap) ;
		// �����Ⱦ�ڵ�
		virtual DrawObj* GetDrawObj2D(void) const ;
		// �����Ⱦ�ڵ�
		virtual DrawObj* GetDrawObj3D(void) const ;

	public:
		// ��������
		virtual void SetText(const VRString& strText) ;
		// ����ͼ��
		virtual void SetIcon(const VRString& strIcon) ;

		// ������Ⱦ��
		void SetGeomtry( osgEarth::Symbology::Geometry* pGeomtry );
		// ���¼�����
		void UpdateDrawable(void);
	private:
		osgEarth::Symbology::Style m_style;  // 3D������ʽ
		osgEarth::Symbology::Style m_style2D; // 2D������ʽ

		osgEarth::Annotation::PlaceNode* m_pPlaceNode2D; // 3D����
		osgEarth::Annotation::PlaceNode* m_pPlaceNode3D; // 2D����

		osg::Vec4 m_vColor; // ��ɫ
		float m_fWidth; // �߿�
		Technique m_tchnique;
		Clamping m_clamping;

	};

}

#endif // !__PLOTPLACE_H_