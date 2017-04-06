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
		// 获取星球
		osg::Node* GetPlane(void);

	protected:
		// 创建星球
		osg::Node* CreatePlane(void);
		// 创建球体
		void CreateSphere(osg::Geometry* pGeom, const unsigned int numX, const unsigned int numY, \
			osg::Vec3Array* pCoords, osg::Vec3Array* pNormals, osg::Vec2Array* pTexCoords);
		// 创建球形几何体
		osg::Node* CreateGeodeSphere(osg::Geometry* pGeom);

	private:
		double m_dRadius; // 半径
		VRString m_strPlanetName; // 行星名称
		VRString m_strTextureName; // 纹理名称
	};
}

#endif // _SOLAYPLANET_H_
