#pragma once

#include <osg/Geometry>
#include <osg/TextureRectangle>

class ScreenAlignedQuad : public osg::Geometry
{
public:
	ScreenAlignedQuad( void );
	ScreenAlignedQuad( const osg::Vec3f& corner, const osg::Vec2f& dims, const osg::Vec2s& textureSize );
	ScreenAlignedQuad( const osg::Vec3f& corner, const osg::Vec2f& dims, osg::TextureRectangle* texture );
	ScreenAlignedQuad( const ScreenAlignedQuad &copy, const osg::CopyOp &copyop = osg::CopyOp::SHALLOW_COPY );

	virtual void build( const osg::Vec3f& corner, const osg::Vec2f& dims, const osg::Vec2s& textureSize );
	virtual void build( const osg::Vec3f& corner, const osg::Vec2f& dims, osg::TextureRectangle* texture );

protected:
	virtual ~ScreenAlignedQuad(void){};
};
