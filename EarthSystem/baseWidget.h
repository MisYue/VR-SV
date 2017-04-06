
/*********************************************************************************
**�����ǻ��࣬�������һ�����ڲ���������_baseCanvas�����ڲ���_widgetBase��_widgetDisplay
**_widgetBase�ڴ��ڹ������д����ϲ㣬������Ӧ����¼���_widgetDisplay����Ϊ��ʾ�ã�
**�ڴ��ڹ������д����²㡣
********************************************************************************/
#pragma once
#include <osgWidget/Canvas>

namespace VR_Soft
{

#define ALPHA_ANIMATION_STEP	0.05		///< ALPHA��������0.05

	class BaseWidget
	{
	public:
		BaseWidget(const osg::Vec4& color,osg::Vec2 location,osg::Vec2 size, std::string *imagefiles);
		~BaseWidget(void);

		enum MOUSESTATE
		{		
			MOUSE_PUSH,			///< ��갴��
			MOUSE_RELEASE,		///< ����ɿ�
			MOUSE_LEAVE,		///< ����뿪
			MOUSE_OVER,			///< ���ͣ��
			MOUSE_DRAG,			///< �����ק
			DEFAULT
		};

		/// ��ȡ�������λ�ã���λ����_widgetBase��������Ϊ����ԭ�㣩
		osgWidget::XYCoord getXYcoord() {return _location;}		
		osgWidget::Canvas* getBaseCanvas() {return _baseCanvas;}
		osgWidget::Widget* getBaseWidget() {return _widgetBase;}
		osgWidget::Widget* getDisplayWidget() {return _widgetDisplay;}
		osgWidget::Widget* createWidget(std::string name,std::string imageFile,osg::Vec2 size, osgWidget::Widget::Layer layer);	

		MOUSESTATE _mouseState;
		static bool _isMouseOverBaseWidget; /// ��̬�����������λ��_widgetBase��Χ�ڣ���ֵΪtrue������ʵ�����̣�Compass��������Walker����������Zoom���ؼ��������ͬ����

	public:
		virtual bool mousePush(osgWidget::Event& event);
		virtual bool mouseRelease(osgWidget::Event& event);
		virtual bool mouseLeave(osgWidget::Event& event);
		virtual bool mouseOver(osgWidget::Event& event);
		virtual bool mouseDrag(osgWidget::Event& event);

	private:
		osg::ref_ptr<osgWidget::Canvas>  _baseCanvas;		///< _widgetBase�������ڹ���ȡ��
		osg::ref_ptr<osgWidget::Widget>  _widgetBase;		///< ����¼������ڲ�����
		osg::ref_ptr<osgWidget::Widget>  _widgetDisplay;	///< ��ʾ���ڲ�����
		osgWidget::XYCoord _location;						///< �������λ�ã���λ����_widgetBase��������Ϊ����ԭ�㣩
	};
}
