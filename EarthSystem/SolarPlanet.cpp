#define VRSOFT_PLUGIN_EXPORT
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include "../../Public/VRSoft.h"
#include "SolarPlanet.h"

namespace VR_Soft
{
	CSolarPlanet::CSolarPlanet(double radius, const VRString& strName, \
		const VRString& strTexture) : m_dRadius(radius)
	{
	}


	CSolarPlanet::~CSolarPlanet(void)
	{
	}

	// 创建星球
	osg::Node* CSolarPlanet::GetPlane(void)
	{
		return (CreatePlane());
	}

	// 创建星球
	osg::Node* CSolarPlanet::CreatePlane(void)
	{
		// 创建行星球体
		osg::Geometry* pPlanetShpere = new osg::Geometry;

		// 创建颜色体
		osg::Vec4Array* pColor = new osg::Vec4Array(1);
		(*pColor)[0] = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		pPlanetShpere->setColorArray(pColor, osg::Array::BIND_OVERALL);

		// 创建坐标系(采用极坐标)
		const unsigned int numX = 1000;
		const unsigned int numY = 500;
		const unsigned int numVertice = numX * numY;

		// 设置顶点
		osg::Vec3Array* pCoords = new osg::Vec3Array(numVertice);
		pPlanetShpere->setVertexArray(pCoords);

		// 设置法线
		osg::Vec3Array* pNormals = new osg::Vec3Array(numVertice);
		pPlanetShpere->setNormalArray(pNormals, osg::Array::BIND_PER_VERTEX);

		// 设置纹理
		osg::Vec2Array* pTexCoords = new osg::Vec2Array(numVertice);
		pPlanetShpere->setTexCoordArray(0, pTexCoords);
		pPlanetShpere->setTexCoordArray(1, pTexCoords);

		// 创建球体
		CreateSphere(pPlanetShpere, numX, numY, pCoords, pNormals, pTexCoords);

		return (CreateGeodeSphere(pPlanetShpere));
	}

	// 创建球体
	void CSolarPlanet::CreateSphere(osg::Geometry* pGeom, const unsigned int numX, const unsigned int numY, \
		osg::Vec3Array* pCoords, osg::Vec3Array* pNormals, osg::Vec2Array* pTexCoords)
	{
		// 步长
		const double dStep = osg::PI / (double)(numX - 1);
		const double dAzim = 2.0 * osg::PI / (double)(numY - 1);

		// x步长 y步长
		const double xStep = 1.0 / (double)(numX - 1);
		const double yStep = 1.0 / (double)(numY - 1);

		// 步长角
		double dAngleStep = -osg::PI_2;

		//临时变量
		double ty = 0.0f;
		unsigned int vert = 0;

		// 循环创建
		for (unsigned j = 0; j < numY; ++j, dAngleStep += dStep, ty += yStep)
		{
			double azim = 0.0;
			double tx = 0.0;

			for (unsigned int i = 0; i < numX; ++i, ++vert, azim += dAzim, tx += xStep)
			{
				osg::Vec3 direction(cos(azim) * cos(dAngleStep), sin(azim) * cos(dAngleStep), sin(dAngleStep));
				// 设置顶点
				(*pCoords)[vert].set(direction * m_dRadius);
				// 设置发现
				(*pNormals)[vert].set(direction);
				// 设置纹理坐标
				(*pTexCoords)[vert].set(tx,ty);
			}
		}

		// 设置绘制体顶点
		for (unsigned j = 0; j < (numY - 1); ++j)
		{
			unsigned int curr_row = j * numX;
			unsigned int next_row = curr_row + numX;

			osg::DrawElementsUShort* pElements = new osg::DrawElementsUShort(GL_QUAD_STRIP);

			for (unsigned int i = 0; i < (numX - 1); ++i)
			{
				pElements->push_back(next_row + 1);
				pElements->push_back(curr_row + 1);
			}
			pGeom->addPrimitiveSet(pElements);
		}
	}

	// 创建球形几何体
	osg::Node* CSolarPlanet::CreateGeodeSphere(osg::Geometry* pGeom)
	{
		// 创建球形几何体指针
		osg::Geode* pGeodeSphere = new osg::Geode;
		pGeodeSphere->setName(m_strPlanetName);

		if( !m_strTextureName.empty() )
		{
			osg::Image* pImage = osgDB::readImageFile( m_strTextureName );
			if ( NULL == pImage)
			{
				osg::Texture2D* tex2d = new osg::Texture2D( pImage );
				tex2d->setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
				tex2d->setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );
				pGeodeSphere->getOrCreateStateSet()->setTextureAttributeAndModes( 0, tex2d, osg::StateAttribute::ON );
			}
		}

		pGeodeSphere->addDrawable(pGeom);
		return (pGeodeSphere);
	}

}

