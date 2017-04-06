#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/ElectMagSystem/ICommonWave.h"
#include "RadarAttribute.h"
#include "RadarFactory.h"

#include <osg/LineWidth>
#include <osg/AnimationPath>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Texture2D>
#include <osg/Geometry>
#include "SignalWaveAttribute.h"
#include "SignalWave.h"


#include <osgEarth/MapNode>
#include <osgEarth/SpatialReference>
#include <osgEarthUtil/ExampleResources>
#include <osgEarthSymbology/Style>
#include <osgEarthAnnotation/ModelNode>
#include <osgEarthSymbology/IconSymbol>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthSymbology/LineSymbol>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthUtil/AnnotationEvents>
#include <osgEarthAnnotation/HighlightDecoration>

namespace VR_Soft
{
	CSignalWave::CSignalWave(void)
	{
		_sampleVerCnt = 0;

		_pGeode = new osg::Geode;
		_pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING	, osg::StateAttribute::OFF);
		_pGeode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		_pGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		addChild( _pGeode );
	}

	CSignalWave::~CSignalWave(void)
	{
	}


	bool CSignalWave::createShape( double radius_start , double radius_end, eShapeType type, int sampleVerticesCount , double delta_offset )
	{
		if ( radius_start < 0 || radius_end < 0.0 || sampleVerticesCount < 2 )
			return false;

		_sampleVerCnt = sampleVerticesCount;
		_objHeight = 1.0;

		_eShapeType = type;

		if (_eShapeType == Shape_Circle)
		{
		} 
		else if (_eShapeType == Shape_Triangle)
		{
			_sampleVerCnt = 3;
		}
		else if (_eShapeType == Shape_Quad)
		{
			_sampleVerCnt = 4;
		}

		osg::ref_ptr< osg::Geometry > pGeometry;
		double	theta = osg::inDegrees( delta_offset );

		for (int i = 0; i < _sampleVerCnt; ++i)
		{
			pGeometry = new osg::Geometry;
			pGeometry->setUseDisplayList( false );

			osg::Vec3Array*	vertices = new osg::Vec3Array( 4 );
			osg::Vec3Array*	normals = new osg::Vec3Array(4);

			(*vertices)[0] = osg::Vec3( radius_start * cos( theta ), radius_start * sin( theta ), 0.0 );
			(*vertices)[1] = osg::Vec3( radius_end * cos( theta ), radius_end * sin( theta ), _objHeight );

			(*normals)[0] = osg::Vec3( cos( theta ), sin( theta ), 0.0 );
			(*normals)[1] = osg::Vec3( cos( theta ), sin( theta ), 0.0 );

			theta -= osg::inDegrees( 360.0 / _sampleVerCnt );

			(*vertices)[2] = osg::Vec3( radius_end * cos( theta ), radius_end * sin( theta ), _objHeight );
			(*vertices)[3] = osg::Vec3( radius_start * cos( theta ), radius_start * sin( theta ), 0.0 );

			(*normals)[2] = osg::Vec3( cos( theta ), sin( theta ), 0.0 );
			(*normals)[3] = osg::Vec3( cos( theta ), sin( theta ), 0.0 );

			pGeometry->setVertexArray( vertices );
			pGeometry->addPrimitiveSet( new osg::DrawArrays( GL_QUADS, 0, 4 ) );
			pGeometry->setNormalArray( normals );
			pGeometry->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );

			osg::Vec4Array*	colors = new osg::Vec4Array( 1 );
			(*colors)[0] = osg::Vec4d( 1.0, 1.0, 1.0, 1.0 );
			pGeometry->setColorArray( colors );
			pGeometry->setColorBinding( osg::Geometry::BIND_OVERALL );

			_pGeode->addDrawable( pGeometry );
		}

		return true;
	}


	bool CSignalWave::setTexture(  osg::Vec4 color, int colorMask, double textureHeight )
	{
		if (textureHeight < 0 )
			return false;

		_TexHeight = textureHeight;

		osg::ref_ptr<osg::Geometry>	pGeometry;

		//根据掩码生成纹理
		osg::ref_ptr<osg::Image> pImage = new osg::Image;
		pImage->allocateImage(1 ,32 ,1, GL_RGBA, GL_FLOAT);				//32 ： int -> 32 bit
		pImage->setInternalTextureFormat(GL_RGBA);

		int	filterMask = 0xF0;

		osg::Vec4 * dataPtr = (osg::Vec4 *)pImage->data();
		for ( int i = 0; i < 32; i++ )
		{
			if ( ( colorMask & filterMask ) != 0 )
			{
				*dataPtr = color;
			}

			++dataPtr;
			filterMask >>= 1 ;
		}

		osg::ref_ptr<osg::Texture2D> pTexture2D = new osg::Texture2D;
		pTexture2D->setImage(pImage);
		pTexture2D->setWrap(osg::Texture::WRAP_S , osg::Texture::CLAMP_TO_EDGE);
		pTexture2D->setWrap(osg::Texture::WRAP_T , osg::Texture::REPEAT);
		pTexture2D->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR );
		pTexture2D->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );

		//纹理坐标
		double	texOffset = 0.0;
		for ( int i = 0; i < _sampleVerCnt; ++i )
		{
			pGeometry = _pGeode->getDrawable(i)->asGeometry();
			osg::Vec2Array*	texcoords = new osg::Vec2Array(4);

			(*texcoords)[0] = osg::Vec2( 0.0, texOffset * i / _sampleVerCnt );
			(*texcoords)[1] = osg::Vec2( 0.0, 
				_objHeight /_TexHeight * texOffset *  i  / _sampleVerCnt );
			(*texcoords)[2] = osg::Vec2( 1.0, 
				_objHeight /_TexHeight * texOffset *  ( i + 1 ) / _sampleVerCnt );
			(*texcoords)[3] = osg::Vec2( 1.0, 
				texOffset * ( i + 1 ) / _sampleVerCnt );

			pGeometry->setTexCoordArray( 0, texcoords );
			pGeometry->getOrCreateStateSet()->setTextureAttributeAndModes( 0, pTexture2D, osg::StateAttribute::ON );
		}

		return false;
	}

	double CSignalWave::startTrans( double loopTime )
	{
		double	tmpTime = 0.0;
		osg::ref_ptr< osg::Geometry > pGeometry;
		for( int i = 0; i < _sampleVerCnt; ++i )
		{
			osg::ref_ptr<SignalCallBack> pTextureCB = new SignalCallBack;
			tmpTime = pTextureCB->_loopTime;
			pTextureCB->_loopTime = loopTime;
			pTextureCB->lastTime = pTextureCB->clock.tick();
			pGeometry = _pGeode->getDrawable( i )->asGeometry();
			pGeometry->setUpdateCallback( pTextureCB );
		}

		return tmpTime;
	}

	void CSignalWave::stopTrans()
	{
		double		tempTime = 0.0;
		osg::ref_ptr< osg::Geometry > pGeometry;

		for( int i = 0; i < _sampleVerCnt; ++i )
		{
			pGeometry = _pGeode->getDrawable( i )->asGeometry();
			pGeometry->setUpdateCallback( NULL );
		}
	}

	bool CSignalWave::setPosition( osg::Vec3d start, osg::Vec3d end )
	{
		osg::Vec3f forward;
		forward = end - start;
		_objHeight = forward.length();
		forward.normalize();

		osg::ref_ptr<osg::Geometry>  pGeometry ;
		for ( int i = 0; i < _sampleVerCnt; ++i )
		{
			pGeometry = _pGeode->getDrawable(i)->asGeometry();

			osg::Vec3Array *pArray3D = dynamic_cast<osg::Vec3Array *>( pGeometry->getVertexArray());
			osg::Vec2Array *pArray2D = dynamic_cast<osg::Vec2Array *>( pGeometry->getTexCoordArray(0) );

			double baseTexCoord = pArray2D->at( 0 )[1];

			//修改顶部坐标
			pArray3D->at(1)[2] = _objHeight;
			pArray3D->at(2)[2] = _objHeight;

			pArray2D->at(1)[1] = _objHeight / _TexHeight + baseTexCoord;
			pArray2D->at(2)[1] = _objHeight / _TexHeight + baseTexCoord;
		}

		//修改完高度后，平移旋转到合适位置。
		setMatrix( osg::Matrix::rotate( osg::Z_AXIS, forward ) * osg::Matrix::translate(start) );

		return true;
	}


	osg::Node* CSignalWave::GetDrawObj(osgEarth::MapNode* pMapNode)
	{
		osgEarth::Symbology::Style style;
		style.getOrCreate<osgEarth::Symbology::ModelSymbol>()->setModel(this);
		osgEarth::Annotation::ModelNode* pModelNode = new osgEarth::Annotation::ModelNode(pMapNode, style);

		pModelNode->setName(this->getName());
		return (pModelNode);
	}

	osg::Node* CSignalWave::GetDrawObj(void)
	{
		return (this);
	}

	// 获得类型
	const VRString CSignalWave::GetEntityType(void) const
	{
		return ("commontType");
	}

	// 设置名称
	void CSignalWave::SetName(const VRString& strName)
	{
 		ICommonWave::SetName(strName);
// 		if (NULL != m_pIAttr)
// 		{
// 			((CRadarAttribute*)m_pIAttr)->SetName(strName);
// 		}

		setName(strName);
	}

	// 初始化
	void CSignalWave::Init(void)
	{
		/*createShape( 1000.0, 50000.0, CSignalWave::Shape_Circle, 32);

		setTexture( osg::Vec4( 0.40, 0.0, 0.0, 0.4 ), 0x0303F3F3, 100.0 );

		setPosition( osg::Vec3(0,0,0), osg::Vec3(-50000,0,500000) );
		startTrans(2.1);*/
		createShape( 100.0, 50000.0, CSignalWave::Shape_Circle , 450 );

		/*
		@起始半径
		@结束半径
		@类型：圆形、三角形、方形
		@每一个图元的高度
		*/
		setTexture( osg::Vec4( 0.40, 0.0, 0.0, 0.4 ), 0x0303F3F3, 50000.0);

		/*
		@开始位置
		@结束位置
		*/
		setPosition( osg::Vec3(0,0,0), osg::Vec3(-50000,0,500000) );

		/*
		@速度
		*/
		startTrans(0.2);
		//createShape( 100.0, 500.0, CSignalWave::Shape_Quad );

		//setTexture( osg::Vec4( 0.40, 0.0, 0.0, 0.4 ), 0x0303F3F3, 1000.0 );

		//setPosition( osg::Vec3(1000,0,0), osg::Vec3(-500,0,5000) );
		//startTrans(0.2);
	}

	//--------------------------

	CSignalWave::SignalCallBack::SignalCallBack()
	{
		_loopTime = 0;
		return;
	}


	void CSignalWave::SignalCallBack::update(osg::NodeVisitor * nv, osg::Drawable * drawable)
	{
		osg::Timer_t curTime = clock.tick();
		double deltaTime_s = clock.delta_s( lastTime, curTime );

		osg::ref_ptr<osg::Geometry> pGeometry = dynamic_cast<osg::Geometry *>(drawable);
		osg::Vec2Array * pArray = dynamic_cast<osg::Vec2Array *>(pGeometry->getTexCoordArray(0));

		if (pArray == NULL)
			return;

		double texDeltaCoor = deltaTime_s / _loopTime;

		double oldValue;
		for (unsigned int i = 0; i < pArray->size(); ++i)
		{
			oldValue = pArray->at(i)[1];
			pArray->at(i)[1] = oldValue - texDeltaCoor;
		}

		pGeometry->dirtyBound();

		drawable->dirtyDisplayList();

		pArray->dirty();

		lastTime = curTime;
		return;
	}

	// 创建属性对象
	IAttribute* CSignalWave::CreateAttribute(void)
	{
		return (new CSignalWaveAttribute(this, "SignalWave"));
	}

	// 初始化状态机
	void CSignalWave::InitStateMachine(IStateMachine* pIStateMachine)
	{

	}

}

