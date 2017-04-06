#define OSGRENDER_PLUGIN_EXPORT
#include <osg/Geometry>
#include <osg/Geode>
#include <osgText/Text>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "ScreenHUD.h"

namespace VR_Soft
{
	 class CUpdateHUD : public osg::NodeCallback
	 {
	 public:
		 CUpdateHUD(CScreenHUD* pScreenHUD):
		   m_pScreenHUD(pScreenHUD)
		   {
			   
		   }

		   virtual void operator() (osg::Node* node, osg::NodeVisitor* nv)
		   {
			   m_pScreenHUD->UpdateText();
			   traverse(node, nv);
		   }
		   
	 private:
		  CScreenHUD* m_pScreenHUD;
	 };

	CScreenHUD::CScreenHUD(const VRString& strName)
		:m_pText(NULL),
		m_x(0),
		m_y(0),
		m_width(100),
		m_height(100),
		m_bShow(true)
	{
		setName(strName);
		Init();
		//Test();
	}

	CScreenHUD::~CScreenHUD(void)
	{
	}

	void CScreenHUD::Init(void)
	{
		setRenderOrder(osg::Camera::POST_RENDER);
		setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		setViewport(700, 0, 300, 200);
		setViewMatrix(osg::Matrix::identity());
		setProjectionMatrix(osg::Matrix::ortho2D(m_x, m_x + m_width, m_y, m_y + m_height));
		setClearMask(GL_DEPTH_BUFFER_BIT);
		getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		// 根节点
		{
			m_pRoot = new osg::Group;
			m_pRoot->addUpdateCallback(new CUpdateHUD(this));
			addChild(m_pRoot);
		}

		// 创建背景
		{
			m_pBkGeode = new osg::Geode;
			m_pRoot->addChild(m_pBkGeode);

			osg::ref_ptr<osg::Vec3Array> vArray = new osg::Vec3Array;
			vArray->push_back(osg::Vec3(m_x, m_y, 0));
			vArray->push_back(osg::Vec3(m_x, m_y + m_height, 0));
			vArray->push_back(osg::Vec3(m_x + m_width, m_y + m_height, 0));
			vArray->push_back(osg::Vec3(m_x + m_width, m_y, 0));

			osg::ref_ptr<osg::Vec4Array> cArray = new osg::Vec4Array;
			cArray->push_back(osg::Vec4(0.0, 0.3, 0.0, 0.0));

			osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
			geometry->setVertexArray(vArray.get());
			geometry->setColorArray(cArray.get());

			geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
			geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vArray->size()));
			m_pBkGeode->addDrawable(geometry.get());
			m_pBkGeode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
			m_pRoot->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);

		}
		
		// 创建文字
		{
			std::string timesFont("Font/simsun.ttc");
			osg::Vec3 position(0,50,0.0f);
			osg::Geode* pGeode = new osg::Geode;
			m_pRoot->addChild(pGeode);

			m_pText = new  osgText::Text;
			pGeode->addDrawable( m_pText );

			m_pText->setFont(timesFont);
			m_pText->setPosition(position);

			m_pText->setColor(osg::Vec4(1,1,1,1.0f));
			m_pText->setCharacterSize(17.0f);
		}
		
	}

	void CScreenHUD::Test()
	{
		osg::ref_ptr<osg::Group> root = new osg::Group;
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
		osg::ref_ptr<osg::Vec3Array> vArray = new osg::Vec3Array;
		vArray->push_back(osg::Vec3(0.0, 0, 0.0));
		vArray->push_back(osg::Vec3(0, 800, 0.0));
		vArray->push_back(osg::Vec3(1920, 800, 0.0));
		vArray->push_back(osg::Vec3(1920, 0, 0.0));

		osg::ref_ptr<osg::Vec4Array> cArray = new osg::Vec4Array;
		cArray->push_back(osg::Vec4(0.0, 0.3, 0.0, 0.2));
		geometry->setVertexArray(vArray.get());
		geometry->setColorArray(cArray.get());

		geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vArray->size()));
		geode->addDrawable(geometry.get());
		geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		root->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);

		//root->addChild(createTest());
		root->addChild(geode.get());
		addChild(root.get());
	}

	// 移动位置
	void CScreenHUD::Move( int x, int y, int width, int height )
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;

		setProjectionMatrix(osg::Matrix::ortho2D(m_x, m_x + m_width, m_y, m_y + m_height));

		osg::ref_ptr<osg::Vec3Array> vArray = new osg::Vec3Array;
		vArray->push_back(osg::Vec3(m_x, m_y, 0));
		vArray->push_back(osg::Vec3(m_x, m_y + m_height, 0));
		vArray->push_back(osg::Vec3(m_x + m_width, m_y + m_height, 0));
		vArray->push_back(osg::Vec3(m_x + m_width, m_y, 0));

		osg::Geometry* pGeom = m_pBkGeode->getDrawable(0)->asGeometry();
		if (NULL == pGeom)
		{
			return;
		}
		pGeom->setVertexArray(vArray);

		osg::Vec3 vPos(m_x, m_y + height - 17, 0);
		m_pText->setPosition(vPos);
	}

	// 设置文字
	void CScreenHUD::SetText( const VRString& strText )
	{
		m_strText = strText;
	}

	// 设置背景颜色
	void CScreenHUD::SetBgColor( const float r, const float g, const float b, const float a /*= 1.0f*/ )
	{
		osg::Geometry* pGeom = m_pBkGeode->getDrawable(0)->asGeometry();
		if (NULL == pGeom)
		{
			return;
		}

		osg::Vec4Array* cArray = (osg::Vec4Array* )pGeom->getColorArray();
		(*cArray)[0].set(r, g, b, a);
	}

	// 设置窗口名称
	void CScreenHUD::SetHUDName( const VRString& strName )
	{
		setName(strName);
	}

	// 获得窗口名称
	const VRString& CScreenHUD::GetHUDName( void ) const
	{
		return (getName());
	}

	// 调整大小
	void CScreenHUD::OnResize( int width, int height )
	{
		setViewport(m_x, height - m_height - m_y, m_width, m_height);
	//	setProjectionMatrix(osg::Matrix::ortho2D());
	}

	// 显示
	void CScreenHUD::Show( void )
	{
		setNodeMask(0x01);
		m_bShow = true;
	}

	// 隐藏
	void CScreenHUD::Hide( void )
	{
		setNodeMask(0x00);
		m_bShow = false;
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

	// 更新文字
	void CScreenHUD::UpdateText( void )
	{
		std::wstring wstr = s2ws(m_strText);
		m_pText->setText(wstr.c_str());
	}
}
