#include "UserPPU.h"

#include "ScreenAlignedQuad.h"

UserPPU *UserPPU::Instance()
{
	static UserPPU instance;

	return &instance;
}

UserPPU::UserPPU(void)
{
}

UserPPU::~UserPPU(void)
{
}

//-------------------------------
//type=1d size只x有用，y=0,z=0
//type=2d size只x,y有用,z=0
//type=2darray 
//type=2dmultisample size中z表示采样数目
//type=3d 
//type=rectangle size只x,y有用,z=0
//type=cubemap size只x,y有用,z=0
//name:名称需要唯一
osg::Texture* UserPPU::createTexture( std::string type, 
									 std::string name, const osg::Vec3s& size, 
									 GLint internalformat, GLint sourceformat,
									 GLint sourceType, osg::Texture::FilterMode minFilter, 
									 osg::Texture::FilterMode magFilter, osg::Texture::WrapMode wrapS, 
									 osg::Texture::WrapMode wrapT, osg::Texture::WrapMode wrapR )
{
	osg::ref_ptr<osg::Texture> texture;

	if ( type=="1d" )
	{
		osg::Texture1D* tex1D = new osg::Texture1D;
		tex1D->setTextureWidth( size.x() );

		texture = tex1D;
	}
	else if ( type=="2d" )
	{
		osg::Texture2D* tex2D = new osg::Texture2D;
		tex2D->setTextureSize( size.x(), size.y() );

		texture = tex2D;
	}
	else if ( type=="2darray" )
	{
		osg::Texture2DArray* tex2DArray = new osg::Texture2DArray;
		tex2DArray->setTextureSize( size.x(), size.y(), size.z() );

		texture = tex2DArray;
	}
	else if ( type=="2dmultisample" )
	{
		osg::Texture2DMultisample* tex2DMultisample = new osg::Texture2DMultisample;
		tex2DMultisample->setTextureSize( size.x(), size.y() );
		tex2DMultisample->setNumSamples( size.z() );

		texture = tex2DMultisample;
	}
	else if ( type=="3d" )
	{
		osg::Texture3D* tex3D = new osg::Texture3D;
		tex3D->setTextureSize( size.x(), size.y(), size.z() );

		texture = tex3D;
	}
	else if ( type=="rectangle" )
	{
		osg::TextureRectangle* texRect = new osg::TextureRectangle;
		texRect->setTextureSize( size.x(), size.y() );

		texture = texRect;
	}
	else if ( type=="cubemap" )
	{
		osg::TextureCubeMap* texCubemap = new osg::TextureCubeMap;
		texCubemap->setTextureSize( size.x(), size.y() );

		texture = texCubemap;
	}
	else 
	{
		texture = new osg::Texture2D;
	}

	texture->setResizeNonPowerOfTwoHint( false );
	texture->setFilter( osg::Texture::MIN_FILTER, minFilter );
	texture->setFilter( osg::Texture::MAG_FILTER, magFilter );
	texture->setWrap(osg::Texture::WRAP_S, wrapS );
	texture->setWrap(osg::Texture::WRAP_T, wrapT );
	texture->setWrap(osg::Texture::WRAP_R, wrapR );

	texture->setInternalFormat( internalformat );
	texture->setSourceFormat( sourceformat );
	texture->setSourceType( sourceType );

	setTexture(name, texture.get());

	return texture.get();
}

osg::Camera* UserPPU::createPass( PassType type, std::string name, bool bQuad )
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setName(name);
	camera->setClearMask( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	camera->setRenderOrder( osg::Camera::PRE_RENDER );
	camera->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER_OBJECT );
	//camera->setCullCallback( new PassCullCallback(this, type) );

	if ( type==DEFERRED_PASS )
	{
		camera->setAllowEventFocus( false );
		camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF_INHERIT_VIEWPOINT );

		camera->setProjectionMatrix( osg::Matrix::ortho2D(-1.0, 1.0, -1.0, 1.0) );
		camera->setViewMatrix( osg::Matrix::identity() );

		if (bQuad)
		{
			camera->addChild( createScreenQuad(osg::Vec3f(-1.0, -1.0, -1.0), osg::Vec2f(2.f, 2.f) ) );
		}
	}
	else
	{
		camera->setReferenceFrame( osg::Transform::RELATIVE_RF );
	}

	PassData newData;
	newData.activated = true;
	newData.type = type;
	newData.name = name;
	newData.pass = camera;

	getPassList().push_back( newData );

	return camera.get();
}

//输出至绑定纹理
void UserPPU::renderToTexture( osg::Camera *camera,
							  osg::Texture * textureBuffer,
							  unsigned int level, unsigned int face, 
							  bool mipMapGeneration,
							  unsigned int multisampleSamples,
							  unsigned int multisampleColorSamples,
							  osg::Camera::ImplicitBufferAttachmentMask renderMask,
							  osg::Camera::ImplicitBufferAttachmentMask resolveMask)
{
	camera->setViewport( 0, 0, 
		textureBuffer->getTextureWidth(), 
		textureBuffer->getTextureHeight()  );

	camera->setImplicitBufferAttachmentMask(renderMask, resolveMask);

	camera->attach( osg::Camera::COLOR_BUFFER0, textureBuffer, 
		level, face, mipMapGeneration, multisampleSamples, multisampleColorSamples );
}

void UserPPU::renderToTexture2DArray( osg::Camera *camera,
									 osg::Texture2DArray *textureBuffer,
									 int nLayer,
									 unsigned int multisampleSamples,
									 unsigned int multisampleColorSamples)
{
	camera->setViewport( 0, 0, 
		textureBuffer->getTextureWidth(), 
		textureBuffer->getTextureHeight() );

	for (int nI=0; nI<nLayer; ++nI) 
	{
		osg::Image *image = textureBuffer->getImage(nI);

		if (!image)
		{
			image = new osg::Image;
			image->allocateImage(
				textureBuffer->getTextureWidth(), textureBuffer->getTextureHeight(), 1, 
				textureBuffer->getSourceFormat(), textureBuffer->getSourceType());
		}

		camera->attach(osg::Camera::BufferComponent(osg::Camera::COLOR_BUFFER0+nI), 
			image, multisampleSamples, multisampleColorSamples);

		textureBuffer->setImage(nI, image);
	}
}

void UserPPU::multiRenderToTexture(
								   osg::Camera *camera,
								   osg::Camera::BufferComponent bc1, 
								   osg::Texture *textureBuffer1,
								   unsigned int face1,
								   osg::Camera::BufferComponent bc2, 
								   osg::Texture *textureBuffer2,
								   unsigned int face2,
								   osg::Camera::ImplicitBufferAttachmentMask renderMask,
								   osg::Camera::ImplicitBufferAttachmentMask resolveMask)
{
	camera->setViewport( 0, 0,
		textureBuffer1->getTextureWidth(), 
		textureBuffer1->getTextureHeight() );

	camera->setImplicitBufferAttachmentMask(renderMask, resolveMask);

	camera->attach( bc1, textureBuffer1, 0, face1 );
	camera->attach( bc2, textureBuffer2, 0, face2 );
}

//输入纹理至相机状态机
void UserPPU::renderForBindTexture( osg::StateSet* stateset, std::string name, osg::Texture* textureBuffer, int unit )
{
	stateset->addUniform( new osg::Uniform(name.c_str(), unit) );

	stateset->setTextureAttributeAndModes( unit, textureBuffer, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );
}

//最终输出，需将相机状态恢复
void UserPPU::renderForOutput( osg::Camera *camera, double nW, double nH )
{
	camera->setViewport(0, 0, nW, nH);

	camera->setRenderOrder( osg::Camera::NESTED_RENDER );
	camera->setClearMask( 0 );

	camera->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER );
}

osg::Geode* UserPPU::createScreenQuad( osg::Vec3f corner, osg::Vec2f dims, osg::Vec2s textureSize )
{
	osg::Geometry* geom = new ScreenAlignedQuad(corner, dims, textureSize);

	osg::ref_ptr<osg::Geode> quad = new osg::Geode;
	quad->addDrawable( geom );

	int values = osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED;
	quad->getOrCreateStateSet()->setAttribute(
		new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL), values );
	quad->getOrCreateStateSet()->setMode( GL_LIGHTING, values );
	return quad.release();
}

bool UserPPU::removePass( const std::string& name )
{
	PassList& passList = getPassList();

	for ( unsigned int i=0; i<passList.size(); ++i )
	{
		if ( passList[i].name==name )
		{
			passList.erase( getPassList().begin()+i );

			return true;
		}
	}

	return false;
}

bool UserPPU::getPassData( const std::string& name, PassData& data )
{
	PassList& passList = getPassList();

	for ( unsigned int i=0; i<passList.size(); ++i )
	{
		const PassData& pd = passList[i];

		if ( pd.name == name )
		{
			data = pd;

			return true;
		}
	}

	return false;
}

bool UserPPU::setPassActivated( const std::string& name, bool activated )
{
	PassList& passList = getPassList();

	for ( unsigned int i=0; i<passList.size(); ++i )
	{
		PassData& pd = passList[i];

		if ( pd.name==name )
		{
			pd.activated = activated;

			return true;
		}
	}

	return false;
}

bool UserPPU::getPassActivated( const std::string& name )
{
	PassList& passList = getPassList();

	for ( unsigned int i=0; i<passList.size(); ++i )
	{
		if ( passList[i].name==name )
			return passList[i].activated;
	}

	return false;
}

bool UserPPU::setPassIndex( const std::string& name, unsigned int index )
{
	PassData passToInsert;
	unsigned int insertIndex = index;

	if ( insertIndex >= getPassList().size() )
		return false;

	PassList& passList = getPassList();
	for ( unsigned int i=0; i<passList.size(); ++i )
	{
		const PassData& pd = passList[i];

		if ( pd.name == name )
		{
			if ( i != insertIndex )
			{
				passToInsert = pd;
				passList.erase( getPassList().begin()+i );

				if ( i < insertIndex ) 
					insertIndex--;
			}

			break;
		}
	}

	if ( passToInsert.pass.valid() )
	{
		passList.insert( passList.begin()+insertIndex, passToInsert );

		return true;
	}

	return false;
}

unsigned int UserPPU::getPassIndex( const std::string& name )
{
	PassList& passList = getPassList();

	for ( unsigned int i=0; i<passList.size(); ++i )
	{
		if ( passList[i].name == name )
			return i;
	}

	return passList.size();
}

bool UserPPU::setTexture( const std::string& name, osg::Texture* tex )
{
	TextureMap::iterator itr = _textureMap.find(name);

	if ( itr!=_textureMap.end() )
	{
		itr->second = tex;

		return false;
	}
	else
	{
		_textureMap[name] = tex;

		return true;
	}
}

bool UserPPU::removeTexture( const std::string& name )
{
	TextureMap::iterator itr = _textureMap.find(name);

	if ( itr==_textureMap.end() ) 
		return false;

	_textureMap.erase( itr );

	return true;
}

osg::Texture* UserPPU::getTexture( const std::string& name )
{
	TextureMap::iterator itr = _textureMap.find(name);

	if ( itr==_textureMap.end() ) 
		return NULL;
	else 
		return itr->second.get();
}

const osg::Texture* UserPPU::getTexture( const std::string& name ) const
{
	TextureMap::const_iterator itr = _textureMap.find(name);

	if ( itr==_textureMap.end() ) 
		return NULL;
	else 
		return itr->second.get();
}

bool UserPPU::setProgram( const std::string& name, osg::Program* pgm )
{
	ProgramMap::iterator itr = _programMap.find(name);

	if ( itr!=_programMap.end() )
	{
		itr->second = pgm;

		return false;
	}
	else
	{
		_programMap[name] = pgm;

		return true;
	}
}

bool UserPPU::removeProgram( const std::string& name )
{
	ProgramMap::iterator itr = _programMap.find(name);

	if ( itr==_programMap.end() ) 
		return false;

	_programMap.erase( itr );

	return true;
}

osg::Program* UserPPU::getProgram( const std::string& name )
{
	ProgramMap::iterator itr = _programMap.find(name);

	if ( itr==_programMap.end() ) 
		return NULL;
	else 
		return itr->second.get();
}

const osg::Program* UserPPU::getProgram( const std::string& name ) const
{
	ProgramMap::const_iterator itr = _programMap.find(name);

	if ( itr==_programMap.end() ) 
		return NULL;
	else 
		return itr->second.get();
}

bool UserPPU::setOEStateSet( const std::string& name, osg::StateSet* ss )
{
	StateSetMap::iterator itr = _stateSetMap.find(name);

	if ( itr!=_stateSetMap.end() )
	{
		itr->second = ss;

		return false;
	}
	else
	{
		_stateSetMap[name] = ss;

		return true;
	}
}

bool UserPPU::removeOEStateSet( const std::string& name )
{
	StateSetMap::iterator itr = _stateSetMap.find(name);

	if ( itr==_stateSetMap.end() ) 
		return false;

	_stateSetMap.erase( itr );

	return true;
}

osg::StateSet* UserPPU::getOEStateSet( const std::string& name )
{
	StateSetMap::iterator itr = _stateSetMap.find(name);

	if ( itr==_stateSetMap.end() ) 
		return NULL;
	else 
		return itr->second.get();
}

//---------------------------------------
//type:vertex,fragment,geometry,tess_control,tess_evaluation
//name:shader名称
//shaderSource:shader源代码，若为文件，则空
//shaderFile:shader文件，若为源码，则空
osg::Shader* UserPPU::createShader( std::string type, std::string name, 
									   std::string shaderSource, std::string shaderFile)
{
	osg::ref_ptr<osg::Shader> shader;

	if ( type=="vertex" ) 
	{
		shader = new osg::Shader(osg::Shader::VERTEX);
	}
	else if ( type=="fragment" )
	{
		shader = new osg::Shader(osg::Shader::FRAGMENT);
	}
	else if ( type=="geometry" ) 
	{
		shader = new osg::Shader(osg::Shader::GEOMETRY);
	}
	else if ( type=="tess_control" ) 
	{
		shader = new osg::Shader(osg::Shader::TESSCONTROL);
	}
	else if ( type=="tess_evaluation" ) 
	{
		shader = new osg::Shader(osg::Shader::TESSEVALUATION);
	}
	else 
	{
		shader = new osg::Shader;
	}

	shader->setName( name );

	if (shaderSource.size() > 1)
	{
		shader->setShaderSource( shaderSource );
	} 
	else if (shaderFile.size() > 1)
	{
		shader->loadShaderSourceFromFile( shaderFile );
	}

	return shader.release();
}

char *UserPPU::textFileRead(char *fn) 
{
	FILE *fp;
	char *content = NULL;
	int count = 0;
	if (fn != NULL) 
	{
		fp = fopen(fn, "rt");
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) 
			{
				content = (char*) malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}

			fclose(fp);
		} 
		else 
		{
			printf("could not open \"%s\"\n", fn);
			exit(1);
		}
	}

	return content;
}

osg::Program* UserPPU::createProgram( std::string name, 
									 int files, char** fileNames, char* options )
{
	osg::ref_ptr<osg::Program> program = new osg::Program;
	program->setName(name);

	const char **contents = (const char**) malloc(files * sizeof(char*));

	std::string shader = "";

	bool geo = false;
	for (int i = 0; i < files; ++i)
	{
		contents[i] = textFileRead(fileNames[i]);

		shader += contents[i];

		if (strstr(contents[i], "_GEOMETRY_") != NULL)
		{
			geo = true;
		}
	}

	std::string op = options == NULL ? "" : options;

	std::string shader_vs = "#define _VERTEX_\n" + op + shader;
	osg::Shader* vs = createShader( "vertex", name + "_vs", shader_vs, "" );
	program->addShader( vs );

	if (geo)
	{
		std::string shader_gs = "#define _GEOMETRY_\n" + op + shader;
		osg::Shader* gs = createShader( "geometry", name + "_gs", shader_gs, "" );
		program->addShader( gs );

		program->setParameter( GL_GEOMETRY_VERTICES_OUT_EXT, 3 * 5 );
		program->setParameter( GL_GEOMETRY_INPUT_TYPE_EXT, GL_TRIANGLES );
		program->setParameter( GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLE_STRIP );
	}

	std::string shader_ps = "#define _FRAGMENT_\n" + op + shader;
	osg::Shader* ps = createShader( "fragment", name + "_ps", shader_ps, "" );
	program->addShader( ps );

	setProgram(name, program.get());

	for (int i = 0; i < files; ++i)
	{
		free((void*) contents[i]);
	}

	return program.get();
}