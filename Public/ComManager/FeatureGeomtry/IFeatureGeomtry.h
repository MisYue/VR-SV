/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���򼸺���ͷ�ļ�		                                        */
/* ʱ�䣺 2016-07-14                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IFEATUREGEOMTRY_H_
#define _PUBLIC_IFEATUREGEOMTRY_H_

namespace VR_Soft
{
	class VRSOFT_DLL IFeatureGeomtry
	{
	public: 
		// ���ؼ���
		enum Technique
		{
			TECHNIQUE_MAP,
			TECHNIQUE_SCENE,
			TECHNIQUE_GPU,
			TECHNIQUE_DRAPE
		};

		// ����ģ��Ƕ��
		enum Clamping
		{
			CLAMP_NONE,
			CLAMP_TO_TERRAIN,
			CLAMP_RELATIVE_TO_TERRAIN,
			CLAMP_ABSOLUTE
		};

	public:
		// ��������
		virtual ~IFeatureGeomtry(void) { }
		// ������ɫ
		virtual void SetColor(const osg::Vec4& vColor) = 0;
		// �����ɫ
		virtual osg::Vec4 GetColor(void) const = 0;
		// �����߿�
		virtual void SetWidth(const float fWidth) = 0;
		// ����߿�
		virtual float GetWidth(void) const = 0;
		// �������ؼ���
		virtual void SetTechnique(const Technique technique) = 0;
		// ������ؼ���
		virtual Technique GetTechnique(void) const = 0;
		// ���ø߳�
		virtual void SetClamping(const Clamping clamping) = 0;
		// ���ģ��Ƕ��
		virtual  Clamping GetClamping(void) const = 0;
		// ������е�
		virtual std::vector<osg::Vec3d> GetAllPoints(void) const = 0;
		// �������е�
		virtual void SetAllPoints(const std::vector<osg::Vec3d>& listPoints) = 0;
		// ���������
		virtual osg::Vec3d GetPoint(const int index) = 0;
		// ���õ�
		virtual void SetPoint(const int index, const osg::Vec3d& vPoint) = 0;
		// �Ƴ���
		virtual void Remove(const int index) = 0;
		// �Ƴ����еĵ�
		virtual void RemoveAll(void) = 0;
		// ����2D��ͼ
		virtual void SetMapNode2D(EarthMap* pEarthMap) = 0;
		// ����3D��ͼ
		virtual void SetMapNode3D(EarthMap* pEarthMap) = 0;
		// �����Ⱦ�ڵ�
		virtual DrawObj* GetDrawObj2D(void) const = 0;
		// �����Ⱦ�ڵ�
		virtual DrawObj* GetDrawObj3D(void) const = 0;
	};
}

#endif // !_PUBLIC_IFEATUREGEOMTRY_H_