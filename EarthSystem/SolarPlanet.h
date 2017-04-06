#ifndef _SOLAYPLANET_H_
#define _SOLAYPLANET_H_

#pragma once

namespace VR_Soft
{
	class CSolarPlanet : public osg::MatrixTransform
	{
	public:
		CSolarPlanet(double radius, const VRString& strName, const VRString& strTexture);
		~CSolarPlanet(void);

	public:
		// ��ȡ����
		osg::Node* GetPlane(void);

	protected:
		// ��������
		osg::Node* CreatePlane(void);
		// ��������
		void CreateSphere(osg::Geometry* pGeom, const unsigned int numX, const unsigned int numY, \
			osg::Vec3Array* pCoords, osg::Vec3Array* pNormals, osg::Vec2Array* pTexCoords);
		// �������μ�����
		osg::Node* CreateGeodeSphere(osg::Geometry* pGeom);

	private:
		double m_dRadius; // �뾶
		VRString m_strPlanetName; // ��������
		VRString m_strTextureName; // ��������
	};
}

#endif // _SOLAYPLANET_H_
