#pragma once

#include <osg/Geode>
#include <osg/Texture>
#include <osg/Program>
#include <osg/Camera>
#include <osg/Geometry>
#include <osg/PolygonMode>

#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/Texture2DArray>
#include <osg/Texture2DMultisample>
#include <osg/Texture3D>
#include <osg/TextureRectangle>
#include <osg/TextureCubeMap>

class UserPPU
{
public:
	static UserPPU *Instance();

	enum PassType { FORWARD_PASS, DEFERRED_PASS };

	struct PassData
	{
		bool activated;
		PassType type;
		std::string name;
		osg::ref_ptr<osg::Camera> pass;

		PassData() : activated(true), type(FORWARD_PASS) {}

		PassData& operator=( const PassData& pd )
		{
			activated = pd.activated; type = pd.type;
			name = pd.name; pass = pd.pass;
			return *this;
		}

		bool isDisplayPass() const
		{ return pass.valid() && pass->getRenderOrder()!=osg::Camera::PRE_RENDER; }
	};
	
	~UserPPU(void);

	osg::Camera* createPass( PassType type, std::string name, bool bQuad = true );

	//-------------------------------
	//type=1d size只x有用，y=0,z=0
	//type=2d size只x,y有用,z=0
	//type=2darray 
	//type=2dmultisample size中z表示采样数目
	//type=3d 
	//type=rectangle size只x,y有用,z=0
	//type=cubemap size只x,y有用,z=0
	//name:名称需要唯一
	osg::Texture* createTexture( std::string type, 
		std::string name, const osg::Vec3s& size, 
		GLint internalformat, GLint sourceformat,
		GLint sourceType, osg::Texture::FilterMode minFilter, 
		osg::Texture::FilterMode magFilter, osg::Texture::WrapMode wrapS, 
		osg::Texture::WrapMode wrapT, osg::Texture::WrapMode wrapR );	

	//---------------------------------------
	//type:vertex,fragment,geometry,tess_control,tess_evaluation
	//name:shader名称
	//shaderSource:shader源代码，若为文件，则空
	//shaderFile:shader文件，若为源码，则空
	osg::Shader* createShader( std::string type, std::string name, 
		std::string shaderSource, std::string shaderFile);

	//输入纹理至相机状态机
	void renderForBindTexture(osg::StateSet* stateset, std::string name, osg::Texture* textureBuffer, int unit);

	//最终输出，需将相机状态恢复
	void renderForOutput( osg::Camera *camera, double nW, double nH );

	//输出至绑定纹理
	void renderToTexture(osg::Camera *camera,
		osg::Texture * textureBuffer,
		unsigned int level = 0, 
		unsigned int face=0, 
		bool mipMapGeneration=false,
		unsigned int multisampleSamples = 0,
		unsigned int multisampleColorSamples = 0,
		osg::Camera::ImplicitBufferAttachmentMask renderMask = osg::DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT,
		osg::Camera::ImplicitBufferAttachmentMask resolveMask = osg::DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT);

	void renderToTexture2DArray(
		osg::Camera *camera,
		osg::Texture2DArray *textureBuffer,
		int nLayer,
		unsigned int multisampleSamples = 0,
		unsigned int multisampleColorSamples = 0);

	void multiRenderToTexture(
		osg::Camera *camera,
		osg::Camera::BufferComponent bc1, 
		osg::Texture *textureBuffer1,
		unsigned int face1,
		osg::Camera::BufferComponent bc2, 
		osg::Texture *textureBuffer2,
		unsigned int face2,
		osg::Camera::ImplicitBufferAttachmentMask renderMask = osg::DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT,
		osg::Camera::ImplicitBufferAttachmentMask resolveMask = osg::DisplaySettings::DEFAULT_IMPLICIT_BUFFER_ATTACHMENT);

	bool setTexture( const std::string& name, osg::Texture* tex );

	bool removeTexture( const std::string& name );

	osg::Texture* getTexture( const std::string& name );
	const osg::Texture* getTexture( const std::string& name ) const;

	typedef std::map<std::string, osg::ref_ptr<osg::Texture> > TextureMap;
	const TextureMap& getTextureMap() const 
	{ 
		return _textureMap; 
	}

	typedef std::vector<PassData> PassList;

	PassList& getPassList() 
	{
		return _passList; 
	}

	int getNumPass() 
	{ 
		return getPassList().size(); 
	}

	bool removePass( const std::string& name );

	void clearPassList( )
	{ 
		getPassList().clear(); 
	}

	bool getPassData( const std::string& name, PassData& data );

	bool setPassActivated( const std::string& name, bool activated );

	bool getPassActivated( const std::string& name );

	bool setPassIndex( const std::string& name, unsigned int index );

	unsigned int getPassIndex( const std::string& name );

	osg::Program* createProgram( std::string name, 
		int files, char** fileNames, char* options = NULL);

	bool setProgram( const std::string& name, osg::Program* pgm );

	bool removeProgram( const std::string& name );

	osg::Program* getProgram( const std::string& name );
	const osg::Program* getProgram( const std::string& name ) const;

	typedef std::map<std::string, osg::ref_ptr<osg::Program> > ProgramMap;
	const ProgramMap& getProgramMap() const 
	{ 
		return _programMap; 
	}

	bool setOEStateSet( const std::string& name, osg::StateSet* ss );

	bool removeOEStateSet( const std::string& name );

	osg::StateSet* getOEStateSet( const std::string& name );

	typedef std::map<std::string, osg::ref_ptr<osg::StateSet> > StateSetMap;
	const StateSetMap& getStateSetMap() const 
	{ 
		return _stateSetMap; 
	}

	osg::Geode* createScreenQuad( osg::Vec3f corner, osg::Vec2f dims, osg::Vec2s textureSize = osg::Vec2s(1.0, 1.0) );

private:
	UserPPU(void);

	char *textFileRead(char *fn) ;

private:
	PassList _passList;
	TextureMap _textureMap;
	ProgramMap _programMap;
	StateSetMap _stateSetMap;
};
