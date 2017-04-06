/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ⱦ�����幤���ӿ�											*/
/* ʱ�䣺 2016-07-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _FEATUREGEOMTRY_H_
#define _FEATUREGEOMTRY_H_

#include <osgEarthSymbology/Style>
#include <osgEarthSymbology/Geometry>
#include <osgEarthAnnotation/FeatureNode>

namespace VR_Soft
{
	class CFeatureGeomtry : public IFeatureGeomtry
	{
	public:
		// ���캯��
		explicit CFeatureGeomtry(OsgEarthGeomtry* pOsgEarthGeomtry);
		// ��������
		virtual ~CFeatureGeomtry(void);

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
		virtual void SetTechnique(const Technique technique) ;
		// ������ؼ���
		virtual Technique GetTechnique(void) const;
		// ���ø߳�
		virtual void SetClamping(const Clamping clamping) ;
		// ���ģ��Ƕ��
		virtual  Clamping GetClamping(void) const ;
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
		// ������Ⱦ��
		void SetGeomtry( osgEarth::Symbology::Geometry* pGeomtry );
		// ���¼�����
		void UpdateDrawable(void);
	private:
		osgEarth::Symbology::Style m_style;  // 3D������ʽ
		osgEarth::Symbology::Style m_style2D; // 2D������ʽ
		osgEarth::Symbology::Geometry* m_pGeomety; // ������

		osgEarth::Annotation::FeatureNode* m_pFeatureNode2D; // 3D����
		osgEarth::Annotation::FeatureNode* m_pFeatureNode3D; // 2D����

		osg::Vec4 m_vColor; // ��ɫ
		float m_fWidth; // �߿�
		Technique m_tchnique;
		Clamping m_clamping;

	};
}

#endif // !_FEATUREGEOMTRY_H_