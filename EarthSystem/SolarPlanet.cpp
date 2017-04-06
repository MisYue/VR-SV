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

	// ��������
	osg::Node* CSolarPlanet::GetPlane(void)
	{
		return (CreatePlane());
	}

	// ��������
	osg::Node* CSolarPlanet::CreatePlane(void)
	{
		// ������������
		osg::Geometry* pPlanetShpere = new osg::Geometry;

		// ������ɫ��
		osg::Vec4Array* pColor = new osg::Vec4Array(1);
		(*pColor)[0] = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		pPlanetShpere->setColorArray(pColor, osg::Array::BIND_OVERALL);

		// ��������ϵ(���ü�����)
		const unsigned int numX = 1000;
		const unsigned int numY = 500;
		const unsigned int numVertice = numX * numY;

		// ���ö���
		osg::Vec3Array* pCoords = new osg::Vec3Array(numVertice);
		pPlanetShpere->setVertexArray(pCoords);

		// ���÷���
		osg::Vec3Array* pNormals = new osg::Vec3Array(numVertice);
		pPlanetShpere->setNormalArray(pNormals, osg::Array::BIND_PER_VERTEX);

		// ��������
		osg::Vec2Array* pTexCoords = new osg::Vec2Array(numVertice);
		pPlanetShpere->setTexCoordArray(0, pTexCoords);
		pPlanetShpere->setTexCoordArray(1, pTexCoords);

		// ��������
		CreateSphere(pPlanetShpere, numX, numY, pCoords, pNormals, pTexCoords);

		return (CreateGeodeSphere(pPlanetShpere));
	}

	// ��������
	void CSolarPlanet::CreateSphere(osg::Geometry* pGeom, const unsigned int numX, const unsigned int numY, \
		osg::Vec3Array* pCoords, osg::Vec3Array* pNormals, osg::Vec2Array* pTexCoords)
	{
		// ����
		const double dStep = osg::PI / (double)(numX - 1);
		const double dAzim = 2.0 * osg::PI / (double)(numY - 1);

		// x���� y����
		const double xStep = 1.0 / (double)(numX - 1);
		const double yStep = 1.0 / (double)(numY - 1);

		// ������
		double dAngleStep = -osg::PI_2;

		//��ʱ����
		double ty = 0.0f;
		unsigned int vert = 0;

		// ѭ������
		for (unsigned j = 0; j < numY; ++j, dAngleStep += dStep, ty += yStep)
		{
			double azim = 0.0;
			double tx = 0.0;

			for (unsigned int i = 0; i < numX; ++i, ++vert, azim += dAzim, tx += xStep)
			{
				osg::Vec3 direction(cos(azim) * cos(dAngleStep), sin(azim) * cos(dAngleStep), sin(dAngleStep));
				// ���ö���
				(*pCoords)[vert].set(direction * m_dRadius);
				// ���÷���
				(*pNormals)[vert].set(direction);
				// ������������
				(*pTexCoords)[vert].set(tx,ty);
			}
		}

		// ���û����嶥��
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

	// �������μ�����
	osg::Node* CSolarPlanet::CreateGeodeSphere(osg::Geometry* pGeom)
	{
		// �������μ�����ָ��
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

