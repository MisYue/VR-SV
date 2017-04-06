#include "../../Public/VRSoft.h"
#include "CameraInfo.h"

#include <Windows.h>
#include <osg/Geometry>
#include <osg/Viewport>


namespace VR_Soft
{
	CameraInfoCallback::CameraInfoCallback(osg::Group *group, double width, double height)
	{
		m_pCamera = createCameraInfoHUD(0, width, 0, height);
		m_pCameraInfoGroup = group;

		m_pCameraInfoGroup->addChild( m_pCamera );
	}

	CameraInfoCallback::~CameraInfoCallback()
	{

	}

	void CameraInfoCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
	{
		if (m_pText)
		{
			UpdateCameraInfo();
		}

		traverse(node, nv);
	}

	osg::Camera *CameraInfoCallback::createCameraInfoHUD(double left, double right, double bottom, double top)
	{
		osg::Camera* camera = new osg::Camera;

		camera->setProjectionMatrix(osg::Matrix::ortho2D(left,right,bottom,top));
		camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		camera->setViewMatrix(osg::Matrix::identity());
		camera->setClearMask(GL_DEPTH_BUFFER_BIT);
		camera->setRenderOrder(osg::Camera::POST_RENDER);
		camera->setAllowEventFocus(false);

		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		camera->addChild( geode.get() );
		geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

		{
			std::string timesFont("Font/simsun.ttc");
			osg::Vec3 position(200.0f,10.0f,0.0f);

			m_pText = new  osgText::Text;
			geode->addDrawable( m_pText );

			m_pText->setFont(timesFont);
			m_pText->setPosition(position);

			m_pText->setColor(osg::Vec4(1,1,1,1.0f));
			m_pText->setCharacterSize(17.0f);
		}

		{
			osg::BoundingBox bb;
			for(unsigned int i=0;i<geode->getNumDrawables();++i)
			{
				bb.expandBy(geode->getDrawable(i)->getBound());
			}

			osg::Geometry* geom = new osg::Geometry;

			osg::Vec3Array* vertices = new osg::Vec3Array;
			float depth = bb.zMin()-0.1;
			vertices->push_back(osg::Vec3(bb.xMin(),bb.yMax(),depth));
			vertices->push_back(osg::Vec3(bb.xMin(),bb.yMin(),depth));
			vertices->push_back(osg::Vec3(bb.xMax(),bb.yMin(),depth));
			vertices->push_back(osg::Vec3(bb.xMax(),bb.yMax(),depth));

			geom->setVertexArray(vertices);

			osg::Vec3Array* normals = new osg::Vec3Array;
			normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
			geom->setNormalArray(normals);
			geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

			osg::Vec4Array* colors = new osg::Vec4Array;
			colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,0.5f));
			geom->setColorArray(colors);
			geom->setColorBinding(osg::Geometry::BIND_OVERALL);

			geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

			osg::StateSet* stateset = geom->getOrCreateStateSet();
			stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
			stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

			geode->addDrawable(geom);
		}

		return camera;
	}

	void CameraInfoCallback::setCameraInfo(const VRString& strInfo)
	{
		m_strInfo = strInfo;
	}

	std::string CameraInfoCallback::getCameraInfo()
	{
		return m_strInfo;
	}

	std::string ws2s(const std::wstring& ws)
	{
		std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";

		setlocale(LC_ALL, "chs");

		const wchar_t* _Source = ws.c_str();

		size_t _Dsize = 2 * ws.size() + 1;

		char *_Dest = new char[_Dsize];

		memset(_Dest,0,_Dsize);

		wcstombs(_Dest,_Source,_Dsize);

		std::string result = _Dest;

		delete []_Dest;

		setlocale(LC_ALL, curLocale.c_str());

		return result;
	}

	std::wstring s2ws(const std::string& s)
	{
		setlocale(LC_ALL, "chs"); 

		const char* _Source = s.c_str();

		size_t _Dsize = s.size() + 1;

		wchar_t *_Dest = new wchar_t[_Dsize];

		wmemset(_Dest, 0, _Dsize);

		mbstowcs(_Dest,_Source,_Dsize);

		return (_Dest);
	}


	void CameraInfoCallback::UpdateCameraInfo()
	{
		std::wstring wstr = s2ws(m_strInfo);

		m_pText->setText(wstr.c_str());
	}

	void CameraInfoCallback::Resize(double width, double height)
	{
		m_pCamera->setProjectionMatrix(osg::Matrix::ortho2D(0,width, 0, height));
		m_pCamera->setViewMatrix(osg::Matrix::identity());
	}

}
