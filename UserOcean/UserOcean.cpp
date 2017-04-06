#include "UserOcean.h"

#include <windows.h>

#include <osg/Depth>
#include <osg/CullFace>
#include <osg/Texture2D>

#include <osgUtil/CullVisitor>

#include <osgEarth/Map>
#include <osgEarth/MapOptions>
#include <osgEarth/MapNodeOptions>

#include <osgEarth/ImageLayer>
#include <osgEarth/TileSource>

#include <osgEarth/CullingUtils>

#include <osgEarth/VirtualProgram>

#include <osgEarthUtil/Sky>

#include <osgEarthDrivers/engine_mp/MPTerrainEngineOptions>

#include "SimpleOceanShaders"

#include "UserPPU.h"

UserOcean::UserOcean(osgEarth::MapNode *mapNode)
{
	_parentMapNode = mapNode;

	this->m_nbWaves = 60 * 3;
	this->m_lambdaMin = 0.02f;
	this->m_lambdaMax = 30.0;
	this->m_heightMax = 0.4f;//0.5;
	this->m_seaColor = osg::Vec4f(10.f / 255.f, 40.f / 255.f, 120.f / 255.f, 0.1f);
	this->m_resolution = 8 * 3;

	setSRS( mapNode? mapNode->getMapSRS() : 0L );
	rebuild();
}

UserOcean::~UserOcean(void)
{
}

void UserOcean::generateMesh()
{
	int nNum = getNumChildren();
	for (int nI=0; nI<nNum; ++nI)
	{
		osg::Node *node = getChild(nI);
		std::string name = node->getName();

		if (name.compare("Mesh") == 0)
		{
			removeChild(node);

			break;
		}
	}

	osg::Geode* geode = new osg::Geode;
	geode->setName("Mesh");

	addChild(geode);

	osg::Geometry* geom = new osg::Geometry;
	geode->addDrawable(geom);

	float f = 1.25f;
	int NX = int(f * 1920 / m_resolution);
	int NY = int(f * 1080 / m_resolution);

	osg::Vec3Array* vertices = new osg::Vec3Array( NX * NY );

	int n = 0;
	for (int i = 0; i < NY; ++i) 
	{
		for (int j = 0; j < NX; ++j) 
		{
			(*vertices)[n++] = osg::Vec3f(2.0*f*j/(NX-1.0f)-f, 2.0*f*i/(NY-1.0f)-f, 0.0);
		}
	}

	geom->setVertexArray(vertices);

	osg::VertexBufferObject* vbo = new osg::VertexBufferObject;
	vertices->setVertexBufferObject(vbo);

	osg::ElementBufferObject* ebo = new osg::ElementBufferObject;

	int vboSize = 0;
	osg::DrawElementsUInt* elements = new osg::DrawElementsUInt(GL_TRIANGLES, 6 * (NX - 1) * (NY-1));

	for (int i = 0; i < NY-1; ++i)
	{
		for (int j = 0; j < NX-1; ++j)
		{
			(*elements)[vboSize++] = (i*NX+j);
			(*elements)[vboSize++] = (i*NX+j+1);
			(*elements)[vboSize++] = ((i+1)*NX+j);
			(*elements)[vboSize++] = ((i+1)*NX+j);
			(*elements)[vboSize++] = (i*NX+j+1);
			(*elements)[vboSize++] = ((i+1)*NX+j+1);
		}
	}

	geom->addPrimitiveSet(elements); 

	elements->setElementBufferObject(ebo);

	geom->setUseDisplayList(false);
	geom->setUseVertexBufferObjects(true);
}

void UserOcean::rebuild()
{
	this->removeChildren( 0, this->getNumChildren() );

	if ( _parentMapNode.valid() )
	{
		const osgEarth::MapOptions&     parentMapOptions     = _parentMapNode->getMap()->getMapOptions();
		const osgEarth::MapNodeOptions& parentMapNodeOptions = _parentMapNode->getMapNodeOptions();

		// set up the map to "match" the parent map:
		osgEarth::MapOptions mo;
		mo.coordSysType() = parentMapOptions.coordSysType();
		mo.profile()      = _parentMapNode->getMap()->getProfile()->toProfileOptions();

		// new data model for the ocean:
		osgEarth::Map* oceanMap = new osgEarth::Map( mo );

		// ditto with the map node options:
		osgEarth::MapNodeOptions mno;
		if ( mno.enableLighting().isSet() )
			mno.enableLighting() = *mno.enableLighting();

		osgEarth::Drivers::MPTerrainEngine::MPTerrainEngineOptions mpoptions;
		mpoptions.heightFieldSkirtRatio() = 0.0;      // don't want to see skirts
		mpoptions.minLOD() = 20;
		mpoptions.maxLOD() = 20;
		//mpoptions.tileSize() = m_resolution;
		//mpoptions.firstLOD() = 0;

		// so we can the surface from underwater:
		mpoptions.clusterCulling() = false;       // want to see underwater

		mpoptions.enableBlending() = true;        // gotsta blend with the main node

		mpoptions.color() = osg::Vec4(0.2, 0.3, 0.5, 0.8);

		mno.setTerrainOptions( mpoptions );

		// make the ocean's map node:
		osgEarth::MapNode* oceanMapNode = new osgEarth::MapNode( oceanMap, mno );

		{
			osgEarth::ImageLayerOptions imageOption;
			imageOption.minResolution() = m_resolution;
			imageOption.minLevel() = 20;
			imageOption.maxResolution() = m_resolution;
			imageOption.maxLevel() = 20;
			imageOption.shared() = true;
			imageOption.visible() = false;

			{
				osgEarth::Config config("mask_layer");
				config.add("url", "./data/ocean_mask.tif");

				osgEarth::DriverConfigOptions tileSourceOption(config);
				tileSourceOption.setDriver("gdal");

				imageOption.driver() = tileSourceOption;
			}

			osgEarth::ImageLayer* maskLayer = new osgEarth::ImageLayer( "ocean-mask", imageOption );
			oceanMap->addImageLayer( maskLayer );

			int unit = maskLayer->shareImageUnit().get();
		}

		this->addChild( oceanMapNode );

		// set up the shaders.
		osg::StateSet* ss = this->getOrCreateStateSet();

		// install the shaders on the ocean map node.
		osgEarth::VirtualProgram* vp = osgEarth::VirtualProgram::getOrCreate( ss );
		vp->setName( "osgEarth SimpleOcean" );

		// use the appropriate shader for the active technique:
		std::string vertSource = source_vertMask;
		std::string fragSource = source_fragMask;

		vp->setFunction( "oe_ocean_vertex",   vertSource, osgEarth::ShaderComp::LOCATION_VERTEX_VIEW );
		vp->setFunction( "oe_ocean_fragment", fragSource, osgEarth::ShaderComp::LOCATION_FRAGMENT_COLORING, 0.6f );

		// install the slot attribute(s)
		ss->getOrCreateUniform( "ocean_data", osg::Uniform::SAMPLER_2D )->set( 0 );

		// set up the options uniforms.

		_seaLevel = new osg::Uniform(osg::Uniform::FLOAT, "ocean_seaLevel");
		ss->addUniform( _seaLevel.get() );

		_lowFeather = new osg::Uniform(osg::Uniform::FLOAT, "ocean_lowFeather");
		ss->addUniform( _lowFeather.get() );

		_highFeather = new osg::Uniform(osg::Uniform::FLOAT, "ocean_highFeather");
		ss->addUniform( _highFeather.get() );

		_maxRange = new osg::Uniform(osg::Uniform::FLOAT, "ocean_max_range");
		ss->addUniform( _maxRange.get() );

		_fadeRange = new osg::Uniform(osg::Uniform::FLOAT, "ocean_fade_range");
		ss->addUniform( _fadeRange.get() );

		// trick to mitigate z-fighting..
		//ss->setAttributeAndModes( new osg::Depth(osg::Depth::LEQUAL, 0.0, 1.0, false) );
		//ss->setRenderBinDetails( 15, "RenderBin" );

		// remove backface culling so we can see underwater
		// (use OVERRIDE since the terrain engine sets back face culling.)
		//ss->setAttributeAndModes( 
		//	new osg::CullFace(), 
		//	osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE );

		// force apply options:
		applyOptions();

		generateWaves();
		initTexture();
	}
	
	//generateMesh();
}

void UserOcean::applyOptions()
{
	setSeaLevel( 0.0f );

	_lowFeather->set( -100.0f );
	_highFeather->set( -10.0f );

	_maxRange->set( 1000000.0f );
	_fadeRange->set( 125000.0f );
}

void UserOcean::setSeaLevel(float level)
{
	_seaLevel->set( level );
}

void UserOcean::traverse(osg::NodeVisitor& nv)
{
	if ( nv.getVisitorType() == nv.CULL_VISITOR && _srs.valid() )
	{
		osgUtil::CullVisitor* cv = osgEarth::Culling::asCullVisitor(nv);
		if ( cv->getCurrentCamera() )
		{
			// find the current altitude:
			osg::Matrixd ctol = cv->getCurrentCamera()->getInverseViewMatrix();
			osg::Vec3d eye = osg::Vec3d(0,0,0) * ctol;
			osg::Vec3d local;
			double altitude;
			_srs->transformFromWorld(eye, local, &altitude);

			// check against max altitude:
			if ( altitude > 50000.0 )
			{
				m_oldLtoo = osg::Matrixd::identity();
				m_offset = osg::Vec3d(0.0, 0.0, 0.0);

				return;
			}

			// Set the near clip plane to account for an ocean sphere.
			// First, adjust for the sea level offset:
			//altitude -= (double)getSeaLevel();

			// clamp the absolute value so it will work above or below sea level
			// and so we don't attempt to set the near clip below 1:
			altitude = max( fabs(altitude), 1.0 );

			// we don't want the ocean participating in the N/F calculation:
			osg::CullSettings::ComputeNearFarMode mode = cv->getComputeNearFarMode();
			cv->setComputeNearFarMode( osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR );

			{
				osg::Vec3d cl = eye;

				float radius = _srs->getEllipsoid()->getRadiusEquator();

				radius = eye.length() - altitude;

				osg::Vec3 ux, uy, uz, oo;

				{
					uz = cl;
					uz.normalize(); // unit z vector of ocean frame, in local space

					if (m_oldLtoo != osg::Matrixd::identity())
					{
						ux = osg::Vec3d(m_oldLtoo(0,1), m_oldLtoo(1,1), m_oldLtoo(2,1)) ^ uz;

						ux.normalize();
					} 
					else 
					{
						ux = osg::Z_AXIS ^ uz;

						ux.normalize();
					}

					uy = uz ^ ux; // unit y vector
					oo = uz * radius; // origin of ocean frame, in local space
				}

				osg::Matrixd wtoo = osg::Matrixd(
					ux.x(), uy.x(), uz.x(), 0.0,
					ux.y(), uy.y(), uz.y(), 0.0,
					ux.z(), uy.z(), uz.z(), 0.0,
					0.0, 0.0, 0.0, 1.0);

				osg::Matrixd ltoo = osg::Matrixd::translate(-oo) * wtoo;

				// compute ctoo = cameraToOcean transform
				osg::Matrixd ctoo = ctol * ltoo;

				if (m_oldLtoo != osg::Matrixd::identity()) 
				{
					osg::Vec3d delta = ltoo * (osg::Vec3d(0, 0, 0) * osg::Matrixd::inverse(m_oldLtoo));

					m_offset += delta;
				}

				m_oldLtoo = ltoo;

				osg::Matrixd ctos = cv->getCurrentCamera()->getProjectionMatrix();

				osg::Matrixd stoc = osg::Matrixd::inverse(ctos);
				osg::Vec3d oc = osg::Vec3d(0, 0, 0) * ctoo;

				//this->getOrCreateStateSet()->getOrCreateUniform("cameraToOcean",osg::Uniform::FLOAT_MAT4)->set(ctoo);
				//this->getOrCreateStateSet()->getOrCreateUniform("screenToCamera",osg::Uniform::FLOAT_MAT4)->set(stoc);
				//this->getOrCreateStateSet()->getOrCreateUniform("cameraToScreen",osg::Uniform::FLOAT_MAT4)->set(ctos);

				//{
				//	osg::Matrixd matrix = osg::Matrixd::inverse(ctoo);

				//	osg::Matrix3 oceanToCamera(
				//		matrix(0,0), matrix(0,1), matrix(0,2),
				//		matrix(1,0), matrix(1,1), matrix(1,2),
				//		matrix(2,0), matrix(2,1), matrix(2,2));

				//	this->getOrCreateStateSet()->getOrCreateUniform("oceanToCamera",osg::Uniform::FLOAT_MAT3)->set(oceanToCamera);
				//}

				osg::Vec2 oceanOffset = osg::Vec2(m_offset.x(),m_offset.y());
				this->getOrCreateStateSet()->getOrCreateUniform("oceanOffset",osg::Uniform::FLOAT_VEC2)->set(oceanOffset);

				osg::Vec3 horizon1;
				osg::Vec3 horizon2;
				{
					float h = oc.z();

					osg::Vec4d var = stoc.preMult(osg::Vec4d(0.0, 0.0, 0.0, 1.0));
					var.w() = 0.0;
					var = ctoo.preMult(var);
					osg::Vec3d A0 = osg::Vec3d(var.x(), var.y(), var.z());

					var = stoc.preMult(osg::Vec4d(1.0, 0.0, 0.0, 0.0));
					var.w() = 0.0;
					var = ctoo.preMult(var);
					osg::Vec3d dA = osg::Vec3d(var.x(), var.y(), var.z());

					var = stoc.preMult(osg::Vec4d(0.0, 1.0, 0.0, 0.0));
					var.w() = 0.0;
					var = ctoo.preMult(var);
					osg::Vec3d B = osg::Vec3d(var.x(), var.y(), var.z());

					{
						double h1 = h * (h + 2.0 * radius);
						double h2 = (h + radius) * (h + radius);
						double alpha = B * B * h1 - B.z() * B.z() * h2;
						double beta0 = (A0 * B * h1 - B.z() * A0.z() * h2) / alpha;
						double beta1 = (dA * B * h1 - B.z() * dA.z() * h2) / alpha;
						double gamma0 = (A0 * A0 * h1 - A0.z() * A0.z() * h2) / alpha;
						double gamma1 = (A0 * dA * h1 - A0.z() * dA.z() * h2) / alpha;
						double gamma2 = (dA * dA * h1 - dA.z() * dA.z() * h2) / alpha;

						horizon1 = osg::Vec3(-beta0, -beta1, 0.0);
						this->getOrCreateStateSet()->getOrCreateUniform("horizon1",osg::Uniform::FLOAT_VEC3)->set(horizon1);

						horizon2 = osg::Vec3(beta0 * beta0 - gamma0, 2.0 * (beta0 * beta1 - gamma1), beta1 * beta1 - gamma2);
						this->getOrCreateStateSet()->getOrCreateUniform("horizon2",osg::Uniform::FLOAT_VEC3)->set(horizon2);
					}
				}

				this->getOrCreateStateSet()->getOrCreateUniform("time",osg::Uniform::FLOAT)->set(float(getTime()));

				this->getOrCreateStateSet()->getOrCreateUniform("radius",osg::Uniform::FLOAT)->set(radius);

				this->getOrCreateStateSet()->getOrCreateUniform("heightOffset",osg::Uniform::FLOAT)->set((float)m_meanHeight);

				this->getOrCreateStateSet()->getOrCreateUniform("hdrExposure",osg::Uniform::FLOAT)->set((float)0.4);

				{
					osgEarth::Util::SkyNode *sky = dynamic_cast<osgEarth::Util::SkyNode *>(getParent(0));

					if (sky)
					{
						osg::Vec4 sunDir = sky->getSunLight()->getPosition();

						osg::Vec3 oceanSunDir = osg::Vec3(sunDir.x(), sunDir.y(), sunDir.z()) ;

						oceanSunDir = osg::Matrix::transform3x3(oceanSunDir, ltoo);

						this->getOrCreateStateSet()->getOrCreateUniform("oceanSunDir",osg::Uniform::FLOAT_VEC3)->set(oceanSunDir);
					}
				}
				
				osg::Viewport *vp = cv->getCurrentCamera()->getViewport();

				double fovy = osg::DegreesToRadians( 80.0 );

				float pixelSize = atan(tan(fovy / 2.0f) / (vp->height() / 2.0f)); // angle under which a screen pixel is viewed from the camera

				osg::Vec4 lods = osg::Vec4(
					m_resolution,
					pixelSize * m_resolution,
					log(m_lambdaMin) / log(2.0f),
					(m_nbWaves - 1.0f) / (log(m_lambdaMax) / log(2.0f) -  log(m_lambdaMin) / log(2.0f)));

				this->getOrCreateStateSet()->getOrCreateUniform("lods",osg::Uniform::FLOAT_VEC4)->set(lods);
			}

			//cv->pushStateSet(this->getOrCreateStateSet());
			// visit the ocean:
			osg::Group::traverse( nv );

			//cv->popStateSet();

			cv->setComputeNearFarMode( mode );

			// just use the height above (or below) the ocean as the near clip
			// plane distance. Close enough and errs on the safe side.
			double oldNear = cv->getCalculatedNearPlane();

			double newNear = min( oldNear, altitude );
			if ( newNear < oldNear )
			{
				cv->setCalculatedNearPlane( newNear );
			}

			return;
		}
	}

	osg::Group::traverse( nv );
}

#define srnd() (2*frandom(&seed) - 1)

void UserOcean::generateWaves()
{
	long seed = 1234567;
	float min = log(m_lambdaMin) / log(2.0f);
	float max = log(m_lambdaMax) / log(2.0f);

	if (!_imageWave.valid())
	{
		_imageWave = new osg::Image;
		_imageWave->allocateImage(m_nbWaves,1,1,GL_RGBA,GL_FLOAT);
		_imageWave->setInternalTextureFormat(GL_RGBA32F_ARB);
	}

	osg::Vec4* waves = (osg::Vec4*)_imageWave->data();

	m_sigmaXsq = 0.0;
	m_sigmaYsq = 0.0;
	m_meanHeight = 0.0;
	m_heightVariance = 0.0;
	m_amplitudeMax = 0.0;

#define nbAngles 5 // even
#define angle(i) (1.5*(((i)%nbAngles)/(float)(nbAngles/2)-1))
#define dangle() (1.5/(float)(nbAngles/2))

	float Wa[nbAngles]; // normalised gaussian samples
	int index[nbAngles]; // to hash angle order
	float s=0;

	for (int i = 0; i < nbAngles; i++) 
	{
		index[i] = i;
		float a = angle(i);
		s += Wa[i] = exp(-0.5*a*a);
	}

	for (int i = 0; i < nbAngles; i++) 
	{
		Wa[i] /= s;
	}

	const float waveDispersion = 0.9f;//6;
	const float U0 = 10.0f;

	for (int i = 0; i < m_nbWaves; ++i)
	{
		float x = i / (m_nbWaves - 1.0f);

		float lambda = pow(2.0f, (1.0f - x) * min + x * max);
		float ktheta = grandom(0.0f, 1.0f, &seed) * waveDispersion;
		float knorm = 2.0f * osg::PI / lambda;
		float omega = sqrt(9.81f * knorm);
		float amplitude;

		float step = (max-min) / (m_nbWaves-1); // dlambda/di
		float omega0 = 9.81 / U0;

		if ((i%(nbAngles)) == 0) 
		{ 
			// scramble angle ordre
			for (int k = 0; k < nbAngles; k++) 
			{   // do N swap in indices
				int n1 = lrandom(&seed)%nbAngles, n2 = lrandom(&seed)%nbAngles, n;

				n = index[n1];
				index[n1] = index[n2];
				index[n2] = n;
			}
		}

		ktheta = waveDispersion * (angle(index[(i)%nbAngles]) + 0.4*srnd()*dangle());
		ktheta *= 1.0 / (1.0 + 40.0*pow(omega0/omega,4));
		amplitude = (8.1e-3*9.81*9.81) / pow(omega,5) * exp(-0.74*pow(omega0/omega,4));
		amplitude *= 0.5*sqrt(2*osg::PI*9.81/lambda)*nbAngles*step;
		amplitude = 3*m_heightMax*sqrt(amplitude);

		if (amplitude > 1.0f / knorm) 
		{
			amplitude = 1.0f / knorm;
		} 
		else if (amplitude < -1.0f / knorm) 
		{
			amplitude = -1.0f / knorm;
		}

		osg::Vec4 color = osg::Vec4(amplitude, omega, knorm * cos(ktheta), knorm * sin(ktheta));

		*waves++ = color;

		m_sigmaXsq += pow(cos(ktheta), 2.0f) * (1.0 - sqrt(1.0 - knorm * knorm * amplitude * amplitude));
		m_sigmaYsq += pow(sin(ktheta), 2.0f) * (1.0 - sqrt(1.0 - knorm * knorm * amplitude * amplitude));
		m_meanHeight -= knorm * amplitude * amplitude * 0.5f;
		m_heightVariance += amplitude * amplitude * (2.0f - knorm * knorm * amplitude * amplitude) * 0.25f;
		m_amplitudeMax += fabs(amplitude);
	}

	float var = 4.0f;
	m_amplitudeMax = 2.0f * var * sqrt(m_heightVariance);

	osg::Texture* waveTex = 
		UserPPU::Instance()->createTexture( 
		"1d", "waveTex", osg::Vec3s(m_nbWaves, 0, 0), GL_RGBA32F_ARB, GL_RGBA, GL_FLOAT,
		osg::Texture::NEAREST, osg::Texture::NEAREST, osg::Texture::CLAMP_TO_EDGE, 
		osg::Texture::CLAMP_TO_EDGE, osg::Texture::CLAMP_TO_EDGE );

	dynamic_cast<osg::Texture1D *>( UserPPU::Instance()->getTexture("waveTex") )->setImage(_imageWave);

	{
		this->getOrCreateStateSet()->getOrCreateUniform("nbWaves",osg::Uniform::FLOAT)->set((float)m_nbWaves);

		UserPPU::Instance()->
			renderForBindTexture(this->getOrCreateStateSet(), "wavesSampler", UserPPU::Instance()->getTexture("waveTex"), 4);

		this->getOrCreateStateSet()->getOrCreateUniform("seaRoughness",osg::Uniform::FLOAT)->set(m_sigmaXsq);

		this->getOrCreateStateSet()->getOrCreateUniform("seaColor",osg::Uniform::FLOAT_VEC3)->
			set(osg::Vec3(m_seaColor[0] * m_seaColor[3], m_seaColor[1] * m_seaColor[3], m_seaColor[2] * m_seaColor[3]));
	}
}

long UserOcean::lrandom(long *seed)
{
	*seed = (*seed * 1103515245 + 12345) & 0x7FFFFFFF;
	return *seed;
}

float UserOcean::frandom(long *seed)
{
	long r = lrandom(seed) >> (31 - 24);
	return r / (float)(1 << 24);
}

float UserOcean::grandom( float mean, float stdDeviation, long *seed )
{
	float x1, x2, w, y1;
	static float y2;
	static int use_last = 0;

	if (use_last)
	{
		y1 = y2;
		use_last = 0;
	} 
	else 
	{
		do 
		{
			x1 = 2.0f * frandom(seed) - 1.0f;
			x2 = 2.0f * frandom(seed) - 1.0f;
			w  = x1 * x1 + x2 * x2;
		} 
		while (w >= 1.0f);

		w  = sqrt((-2.0f * log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return mean + y1 * stdDeviation;
}

double UserOcean::getTime()
{
	__int64 time;
	__int64 cpuFrequency;

	QueryPerformanceCounter((LARGE_INTEGER*) &time);
	QueryPerformanceFrequency((LARGE_INTEGER*) &cpuFrequency);

	return time / double(cpuFrequency);
}

void UserOcean::initTexture()
{
	{
		float *data = new float[256*64*3];
		FILE *f = fopen("data/transmittance.raw", "rb");
		fread(data, 1, 256*64*3*sizeof(float), f);
		fclose(f);

		osg::Image *image = new osg::Image;
		image->setImage(256, 64, 1, GL_RGB16F_ARB, GL_RGB, GL_FLOAT, (unsigned char *)data, osg::Image::USE_NEW_DELETE);

		osg::Texture* transmittance = 
			UserPPU::Instance()->createTexture( "2d", "transmittance", 
			osg::Vec3s(256, 64, 0), 
			GL_RGB16F_ARB, GL_RGB, GL_FLOAT, 
			osg::Texture::LINEAR, osg::Texture::LINEAR, 
			osg::Texture::CLAMP_TO_EDGE, osg::Texture::CLAMP_TO_EDGE, osg::Texture::CLAMP_TO_EDGE);

		dynamic_cast<osg::Texture2D *>(transmittance)->setImage(image);

		UserPPU::Instance()->
			renderForBindTexture(this->getOrCreateStateSet(), "transmittanceSampler", 
			UserPPU::Instance()->getTexture("transmittance"), 5);
	}

	{
		float *data = new float[16*64*3];
		FILE *f = fopen("data/irradiance.raw", "rb");
		fread(data, 1, 16*64*3*sizeof(float), f);
		fclose(f);

		osg::Image *image = new osg::Image;
		image->setImage(64, 16, 1, GL_RGB16F_ARB, GL_RGB, GL_FLOAT, (unsigned char *)data, osg::Image::USE_NEW_DELETE);

		osg::Texture* irradiance = 
			UserPPU::Instance()->createTexture( "2d", "irradiance", 
			osg::Vec3s(64, 16, 0), 
			GL_RGB16F_ARB, GL_RGB, GL_FLOAT, 
			osg::Texture::LINEAR, osg::Texture::LINEAR, 
			osg::Texture::CLAMP_TO_EDGE, osg::Texture::CLAMP_TO_EDGE, osg::Texture::CLAMP_TO_EDGE);

		dynamic_cast<osg::Texture2D *>(irradiance)->setImage(image);

		UserPPU::Instance()->
			renderForBindTexture(this->getOrCreateStateSet(), "skyIrradianceSampler", 
			UserPPU::Instance()->getTexture("irradiance"), 6);
	}

	{
		//ÄÚÉ¢Éä
		int res = 64;
		int nr = res / 2;
		int nv = res * 2;
		int nb = res / 2;
		int na = 8;
		FILE *f = fopen("data/inscatter.raw", "rb");
		float *data = new float[nr*nv*nb*na*4];
		fread(data, 1, nr*nv*nb*na*4*sizeof(float), f);
		fclose(f);

		osg::Image *image = new osg::Image;
		image->setImage(na*nb, nv, nr, GL_RGB16F_ARB, GL_RGBA, GL_FLOAT, (unsigned char *)data, osg::Image::USE_NEW_DELETE);

		osg::Texture* inscatter = 
			UserPPU::Instance()->createTexture( "3d", "inscatter", 
			osg::Vec3s(32 * 8, 128, 32), 
			GL_RGBA16F_ARB, GL_RGB, GL_FLOAT, 
			osg::Texture::LINEAR, osg::Texture::LINEAR, 
			osg::Texture::CLAMP_TO_EDGE, osg::Texture::CLAMP_TO_EDGE, osg::Texture::CLAMP_TO_EDGE);

		dynamic_cast<osg::Texture3D *>(inscatter)->setImage(image);

		UserPPU::Instance()->
			renderForBindTexture(this->getOrCreateStateSet(), "inscatterSampler", 
			UserPPU::Instance()->getTexture("inscatter"), 7);
	}
}
