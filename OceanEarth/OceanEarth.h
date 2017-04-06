#pragma once

#include <osg/PagedLOD>
#include <osgEarth/MapNode>
#include <osgEarth/SpatialReference>

namespace VR_Soft
{
	class COceanEarth : public osg::Group
	{
	public:
		COceanEarth(osgEarth::MapNode *mapNode);
		~COceanEarth(void);

		const osgEarth::SpatialReference* getSRS() 
		{
			return _srs.get(); 
		}

		void setSeaLevel(float level);

		void traverse(osg::NodeVisitor& nv);

	private:
		void setSRS(const osgEarth::SpatialReference* srs) { _srs = srs; }

		void rebuild();

		void applyOptions();

		long lrandom(long *seed);

		float frandom(long *seed);

		float grandom( float mean, float stdDeviation, long *seed );

		void generateWaves();
		void generateMesh();

		double getTime();

		void initTexture();

	private:
		osg::ref_ptr<const osgEarth::SpatialReference> _srs;

		osg::observer_ptr<osgEarth::MapNode> _parentMapNode;

		osg::ref_ptr<osg::Uniform> _seaLevel, _lowFeather, _highFeather;
		osg::ref_ptr<osg::Uniform> _maxRange, _fadeRange;

		//----------------------------------------

		int m_resolution;

		osg::Matrixd m_oldLtoo;

		osg::Vec3d m_offset;

		int m_nbWaves;
		float m_lambdaMin;
		float m_lambdaMax;
		float m_heightMax;
		osg::Vec4f m_seaColor;

		float m_sigmaXsq;
		float m_sigmaYsq;
		float m_meanHeight;
		float m_heightVariance;
		float m_amplitudeMax;

		osg::ref_ptr<osg::Image> _imageWave;
	};

}

