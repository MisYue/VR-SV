#pragma once  
#ifdef FaceLIBDLL  
#define FACEAPI _declspec(dllexport)  
#else  
#define FACEAPI  _declspec(dllimport)  
#endif 
#include "Lib.h"

//$(ProjectName)
//////////////////////////////////////////////////////////////////////////
class FindFirstNamedNodeVisitor : public osg::NodeVisitor  
{  
public:  
	FindFirstNamedNodeVisitor(const std::string& name):  
	  osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),  
		  _name(name), _foundNode(NULL) {}  

	  virtual void apply(osg::Node& node);  
	  std::string _name;  
	  osg::Node *_foundNode;  
}; 
//////////////////////////////////////////////////////////////////////////
class RotateCallBack : public osg::NodeCallback
{
public:
	RotateCallBack(osg::Vec3 rotateAxis,double rotatespeed):osg::NodeCallback(),_rotateAxis(rotateAxis),_rotateSpeed(rotatespeed)
	{
		_rotateAngle = 0.0;
	}

	void setRotateSpeed(double speed);
	double getRotateSpeed();
	virtual void operator()(osg::Node* nd,osg::NodeVisitor* nv);
private:
	osg::Vec3d _rotateAxis;
	double _rotateSpeed;
	double _rotateAngle;
};
//////////////////////////////////////////////////////////////////////////
class ManipulatorSceneHandler : public osgGA::GUIEventHandler
{
public:
	ManipulatorSceneHandler()
	{

	}
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
};
//////////////////////////////////////////////////////////////////////////
class ViewerWidget :public QWidget , public osgViewer::Viewer
{
	Q_OBJECT
public:
	ViewerWidget();
	ViewerWidget(osg::Node *scene /* = NULL */);
	QWidget* getRenderWidget(osgQt::GraphicsWindowQt* gw,osg::Node *scene);
	osgQt::GraphicsWindowQt* CreatGraphicsWindow(int x,int y,int w,int h,const std::string &name /* = "" */,bool windowDecoration /* = false */);
	virtual void paintEvent(QPaintEvent* event);
	void setScence(osg::ref_ptr<osg::Node> v_n);
	osg::ref_ptr<osg::Node> getScence();
	void InitLevel();
private slots:
		void ChangeBackgroundColor();
		void GetChangColor(const QColor&);
private:
	QTimer _timer;
	osg::ref_ptr<osg::Node> v_root;
	QColorDialog *_pColorDialog;
	QColor _pcolor;
	int _iLevel;
signals:
	void SendLevelAndColor(int,QColor);
};
