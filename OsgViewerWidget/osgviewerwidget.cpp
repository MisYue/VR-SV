#define FaceLIBDLL
#include"osgviewerwidget.h"
//访问节点
void FindFirstNamedNodeVisitor::apply(osg::Node &node)
{
	if (node.getName() == _name)
	{
		_foundNode = &node;
		return ;
	}
	traverse(node);
};
////回调函数
void RotateCallBack::setRotateSpeed(double speed)
{
	_rotateSpeed = speed;
}

double RotateCallBack::getRotateSpeed()
{
	return _rotateSpeed;
}
void RotateCallBack::operator()(osg::Node* nd,osg::NodeVisitor* nv)
{
	osg::MatrixTransform *curren = dynamic_cast<osg::MatrixTransform*>(nd);
	if (curren)
	{
		osg::Vec3d currentTranlet = curren->getMatrix().getTrans();
		osg::Matrix newMatrix = osg::Matrix::rotate(_rotateAngle,_rotateAxis)*osg::Matrix::translate(currentTranlet);
		curren->setMatrix(newMatrix);
		_rotateAngle+= _rotateSpeed;
	}
	traverse(nd,nv);
}
////事件处理类
bool ManipulatorSceneHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer*>(&aa);  
	if (!viewer)  
		return false;  
	if (!viewer->getSceneData())  
		return false;  
	if (ea.getHandled())   
		return false;  

	osg::Group *root = viewer->getSceneData()->asGroup();  

	switch(ea.getEventType())  
	{  
	case(osgGA::GUIEventAdapter::KEYDOWN):  
		{  
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Left)  
			{  
				FindFirstNamedNodeVisitor fnv("yRotMT");  
				root->accept(fnv);  
				osg::Node *mtNode = fnv._foundNode;  
				osg::MatrixTransform *yRotMT = dynamic_cast<osg::MatrixTransform*>(mtNode);  
				if (!yRotMT)  
					return false;  

				RotateCallBack *rotCallback = dynamic_cast<RotateCallBack*>(yRotMT->getUpdateCallback());  

				if (!rotCallback)  
					return false;  

				double speed = rotCallback->getRotateSpeed();  
				speed += 0.02;  
				rotCallback->setRotateSpeed(speed);  

			}  

			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Right)  
			{  
				FindFirstNamedNodeVisitor fnv("yRotMT");  
				root->accept(fnv);  

				osg::Node *mtNode = fnv._foundNode;  
				osg::MatrixTransform *yRotMT = dynamic_cast<osg::MatrixTransform*>(mtNode);  
				if (!yRotMT)  
					return false;  

				RotateCallBack *rotCallback = dynamic_cast<RotateCallBack*>(yRotMT->getUpdateCallback());  

				if (!rotCallback)  
					return false;  

				double speed = rotCallback->getRotateSpeed();  
				speed -= 0.02;  
				rotCallback->setRotateSpeed(speed);  
			}  

			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)  
			{  
				FindFirstNamedNodeVisitor fnv("xRotMT");  
				root->accept(fnv);  

				osg::Node *mtNode = fnv._foundNode;  
				osg::MatrixTransform *xRotMT = dynamic_cast<osg::MatrixTransform*>(mtNode);  
				if (!xRotMT)  
					return false;  

				RotateCallBack *rotCallback = dynamic_cast<RotateCallBack*>(xRotMT->getUpdateCallback());  

				if (!rotCallback)  
					return false;  

				double speed = rotCallback->getRotateSpeed();  
				speed += 0.02;  
				rotCallback->setRotateSpeed(speed);  
			}  

			if (ea.getKey()== osgGA::GUIEventAdapter::KEY_Down)  
			{  
				FindFirstNamedNodeVisitor fnv("xRotMT");  
				root->accept(fnv);  

				osg::Node *mtNode = fnv._foundNode;  
				osg::MatrixTransform *xRotMT = dynamic_cast<osg::MatrixTransform*>(mtNode);  
				if (!xRotMT)  
					return false;  

				RotateCallBack *rotCallback = dynamic_cast<RotateCallBack*>(xRotMT->getUpdateCallback());  

				if (!rotCallback)  
					return false;  

				double speed = rotCallback->getRotateSpeed();  
				speed -= 0.02;  
				rotCallback->setRotateSpeed(speed);  
			}  

			if (ea.getKey()== osgGA::GUIEventAdapter::KEY_Page_Up)  
			{     
				FindFirstNamedNodeVisitor fnv("AimMT");  
				root->accept(fnv);  

				osg::Node *mtNode = fnv._foundNode;  
				osg::MatrixTransform *zoomMT = dynamic_cast<osg::MatrixTransform*>(mtNode);  
				if (!zoomMT)  
					return false;  

				osg::Vec3 trans = zoomMT->getMatrix().getTrans();  
				trans.set(trans.x(), trans.y(), trans.z() + 0.2);  
				zoomMT->setMatrix(osg::Matrix::translate(trans));  
			}  

			if (ea.getKey()== osgGA::GUIEventAdapter::KEY_Page_Down)  
			{  
				FindFirstNamedNodeVisitor fnv("AimMT");  
				root->accept(fnv);  

				osg::Node *mtNode = fnv._foundNode;  
				osg::MatrixTransform *zoomMT = dynamic_cast<osg::MatrixTransform*>(mtNode);  
				if (!zoomMT)  
					return false;  

				osg::Vec3 trans = zoomMT->getMatrix().getTrans();  
				trans.set(trans.x(), trans.y(), trans.z() - 0.2);  
				zoomMT->setMatrix(osg::Matrix::translate(trans));  
			}  
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Escape)
			{
				exit(0);
			}
		}  
	default: break;  
	}  
	return false;  
}
////窗口类
ViewerWidget::ViewerWidget(osg::Node *scene )
{
	this->setWindowTitle(QString::fromLocal8Bit("弹体破片线"));
	setMinimumWidth(480);
	//setMinimumHeight(480);
	QWidget *v_wdiget = getRenderWidget(CreatGraphicsWindow(0,0,600,400,"NEHE_7",true),scene);
	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(v_wdiget);
	this->setLayout(layout);
	_iLevel = 0;
	InitLevel();
	connect(&_timer,SIGNAL(timeout()),this,SLOT(update()));
	_timer.start(20);
};

QWidget* ViewerWidget::getRenderWidget(osgQt::GraphicsWindowQt* gw,osg::Node *scene)
{
	osg::Camera *camera = this->getCamera();
	camera->setClearColor(osg::Vec4(0.4,0.6,0.9,0.5));
	camera->setGraphicsContext(gw);
	const osg::GraphicsContext::Traits *traits = gw->getTraits();

	camera->setViewport(0,0,640,480);
	camera->setProjectionMatrixAsPerspective(45.0f,float(traits->width)/float(traits->height),5.0,500.0);
	//设定摄影机视点
	camera->setViewMatrixAsLookAt(osg::Vec3(0,0,1),osg::Vec3(0,0,0),osg::Vec3(0,1,0));
	osg::StateSet *globalstate = camera->getStateSet();
	if (globalstate)
	{
		osg::LightModel *lightModel = new osg::LightModel;
		lightModel->setAmbientIntensity(osg::Vec4(0,0,0,0));
		globalstate->setAttributeAndModes(lightModel,osg::StateAttribute::ON);
	}

	osgGA::OrbitManipulator *_obM = new osgGA::OrbitManipulator();
	_obM->setHomePosition(osg::Vec3d(0,0,1000),osg::Vec3d(0,0,0),osg::Vec3d(1,0,0));

	_obM->setDistance(10.0);
	_obM->setCenter(osg::Vec3d(0,0,0));
	this->setCameraManipulator(_obM);
	this->setSceneData(scene);
	this->addEventHandler(new ManipulatorSceneHandler());
	return gw->getGLWidget();
};

osgQt::GraphicsWindowQt* ViewerWidget::CreatGraphicsWindow(int x,int y,int w,int h,const std::string &name ,bool windowDecoration )
{
	osg::DisplaySettings *ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	//上下文属性
	traits->windowName = name;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->sampleBuffers = true;
	traits->doubleBuffer = true;
	traits->windowDecoration = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();


	return new osgQt::GraphicsWindowQt(traits.get());
}
void ViewerWidget::paintEvent(QPaintEvent* event)
{
	frame();
};
void ViewerWidget::setScence(osg::ref_ptr<osg::Node> v_n)
{
	v_root = v_n;
	this->getSceneData()->asGroup()->addChild(v_n);
};

osg::ref_ptr<osg::Node> ViewerWidget::getScence()
{
	return v_root;
}

void ViewerWidget::InitLevel()
{
	QGroupBox *groupBox_11;
	QGridLayout *gridLayout_2;
	QHBoxLayout *horizontalLayout_2;
	QPushButton *button_9;
	QLabel *label_9;

	QHBoxLayout *horizontalLayout_3;
	QPushButton *button_10;
	QLabel *label_10;

	QHBoxLayout *horizontalLayout_4;
	QPushButton *label_13;
	QLabel *label_14;

	QHBoxLayout *horizontalLayout_5;
	QPushButton *label_15;
	QLabel *label_16;

	QHBoxLayout *horizontalLayout_8;
	QPushButton *label_21;
	QLabel *label_22;

	QHBoxLayout *horizontalLayout_6;
	QPushButton *label_17;
	QLabel *label_18;

	QHBoxLayout *horizontalLayout_7;
	QPushButton *label_19;
	QLabel *label_20;

	QHBoxLayout *horizontalLayout_10;
	QPushButton *label_25;
	QLabel *label_26;

	QHBoxLayout *horizontalLayout_11;
	QPushButton *label_27;
	QLabel *label_28;

	QHBoxLayout *horizontalLayout_9;
	QPushButton *label_23;
	QLabel *label_24;

	groupBox_11 = new QGroupBox(this);
	groupBox_11->setGeometry(10,10,100,250);
	groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
	groupBox_11->setEnabled(true);
	groupBox_11->setStyleSheet(QString::fromUtf8(" QGroupBox {\n"
		"border-color:rgba(0, 0, 0, 180);\n"
		"background-color: rgba(155, 195, 255, 100);\n"
		"\n"
		"padding:0px;\n"
		"border-radius:0px; \n"
		" }"));
	groupBox_11->setWindowOpacity(1);
	groupBox_11->setWindowFlags(Qt::FramelessWindowHint);//这个是widget的标题栏和边框去掉
	groupBox_11->setAttribute(Qt::WA_TranslucentBackground);//这个是widget的背景弄透明

	gridLayout_2 = new QGridLayout(groupBox_11);
	gridLayout_2->setContentsMargins(0, 0, 0, 0);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
	gridLayout_2->setHorizontalSpacing(6);
	gridLayout_2->setVerticalSpacing(0);
	horizontalLayout_2 = new QHBoxLayout();
	horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
	button_9 = new QPushButton(groupBox_11);
	button_9->setObjectName(QString::fromUtf8("Level_1"));
	button_9->setMinimumSize(QSize(20, 20));
	button_9->setMaximumSize(QSize(20, 30));
	button_9->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 255, 4);"));
	connect(button_9,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_2->addWidget(button_9);

	label_9 = new QLabel(groupBox_11);
	label_9->setObjectName(QString::fromUtf8("label_10"));

	horizontalLayout_2->addWidget(label_9);


	gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

	horizontalLayout_3 = new QHBoxLayout();
	horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
	button_10 = new QPushButton(groupBox_11);
	button_10->setObjectName(QString::fromUtf8("Level_2"));
	button_10->setMinimumSize(QSize(20, 20));
	button_10->setMaximumSize(QSize(20, 30));
	button_10->setStyleSheet(QString::fromUtf8("background-color: rgb(110, 255, 0);"));
	connect(button_10,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_3->addWidget(button_10);

	label_10 = new QLabel(groupBox_11);
	label_10->setObjectName(QString::fromUtf8("label_12"));

	horizontalLayout_3->addWidget(label_10);


	gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

	horizontalLayout_4 = new QHBoxLayout();
	horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
	label_13 = new QPushButton(groupBox_11);
	label_13->setObjectName(QString::fromUtf8("Level_3"));
	label_13->setMinimumSize(QSize(20, 20));
	label_13->setMaximumSize(QSize(20, 30));
	label_13->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));
	connect(label_13,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_4->addWidget(label_13);

	label_14 = new QLabel(groupBox_11);
	label_14->setObjectName(QString::fromUtf8("label_14"));

	horizontalLayout_4->addWidget(label_14);


	gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

	horizontalLayout_5 = new QHBoxLayout();
	horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
	label_15 = new QPushButton(groupBox_11);
	label_15->setObjectName(QString::fromUtf8("Level_4"));
	label_15->setMinimumSize(QSize(20, 20));
	label_15->setMaximumSize(QSize(20, 30));
	label_15->setStyleSheet(QString::fromUtf8("background-color: rgb(4,255,110);"));
	connect(label_15,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_5->addWidget(label_15);

	label_16 = new QLabel(groupBox_11);
	label_16->setObjectName(QString::fromUtf8("label_16"));

	horizontalLayout_5->addWidget(label_16);


	gridLayout_2->addLayout(horizontalLayout_5, 3, 0, 1, 1);

	horizontalLayout_8 = new QHBoxLayout();
	horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
	label_21 = new QPushButton(groupBox_11);
	label_21->setObjectName(QString::fromUtf8("Level_5"));
	label_21->setMinimumSize(QSize(20, 20));
	label_21->setMaximumSize(QSize(20, 30));
	label_21->setStyleSheet(QString::fromUtf8("background-color: rgb(4,255,255);"));
	connect(label_21,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_8->addWidget(label_21);

	label_22 = new QLabel(groupBox_11);
	label_22->setObjectName(QString::fromUtf8("label_22"));

	horizontalLayout_8->addWidget(label_22);


	gridLayout_2->addLayout(horizontalLayout_8, 4, 0, 1, 1);

	horizontalLayout_6 = new QHBoxLayout();
	horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
	label_17 = new QPushButton(groupBox_11);
	label_17->setObjectName(QString::fromUtf8("Level_6"));
	label_17->setMinimumSize(QSize(20, 20));
	label_17->setMaximumSize(QSize(20, 30));
	label_17->setStyleSheet(QString::fromUtf8("background-color: rgb(0,125,255);"));
	connect(label_17,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_6->addWidget(label_17);

	label_18 = new QLabel(groupBox_11);
	label_18->setObjectName(QString::fromUtf8("label_18"));

	horizontalLayout_6->addWidget(label_18);


	gridLayout_2->addLayout(horizontalLayout_6, 5, 0, 1, 1);

	horizontalLayout_7 = new QHBoxLayout();
	horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
	label_19 = new QPushButton(groupBox_11);
	label_19->setObjectName(QString::fromUtf8("Level_7"));
	label_19->setMinimumSize(QSize(20, 20));
	label_19->setMaximumSize(QSize(20, 30));
	label_19->setStyleSheet(QString::fromUtf8("background-color: rgb(0,0,255);"));
	connect(label_19,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_7->addWidget(label_19);

	label_20 = new QLabel(groupBox_11);
	label_20->setObjectName(QString::fromUtf8("label_20"));

	horizontalLayout_7->addWidget(label_20);


	gridLayout_2->addLayout(horizontalLayout_7, 6, 0, 1, 1);

	horizontalLayout_10 = new QHBoxLayout();
	horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
	label_25 = new QPushButton(groupBox_11);
	label_25->setObjectName(QString::fromUtf8("Level_8"));
	label_25->setMinimumSize(QSize(20, 20));
	label_25->setMaximumSize(QSize(20, 30));
	label_25->setStyleSheet(QString::fromUtf8("background-color: rgb(120,0,255);"));
	connect(label_25,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_10->addWidget(label_25);

	label_26 = new QLabel(groupBox_11);
	label_26->setObjectName(QString::fromUtf8("label_26"));

	horizontalLayout_10->addWidget(label_26);


	gridLayout_2->addLayout(horizontalLayout_10, 7, 0, 1, 1);

	horizontalLayout_11 = new QHBoxLayout();
	horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
	label_27 = new QPushButton(groupBox_11);
	label_27->setObjectName(QString::fromUtf8("Level_9"));
	label_27->setMinimumSize(QSize(20, 20));
	label_27->setMaximumSize(QSize(20, 30));
	label_27->setStyleSheet(QString::fromUtf8("background-color: rgb(228,0,255);"));
	connect(label_27,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_11->addWidget(label_27);

	label_28 = new QLabel(groupBox_11);
	label_28->setObjectName(QString::fromUtf8("label_28"));

	horizontalLayout_11->addWidget(label_28);


	gridLayout_2->addLayout(horizontalLayout_11, 8, 0, 1, 1);

	horizontalLayout_9 = new QHBoxLayout();
	horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
	label_23 = new QPushButton(groupBox_11);
	label_23->setObjectName(QString::fromUtf8("Level_10"));
	label_23->setMinimumSize(QSize(20, 20));
	label_23->setMaximumSize(QSize(20, 30));
	label_23->setStyleSheet(QString::fromUtf8("background-color: rgb(255,0,158);"));
	connect(label_23,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_9->addWidget(label_23);

	label_24 = new QLabel(groupBox_11);
	label_24->setObjectName(QString::fromUtf8("label_24"));

	horizontalLayout_9->addWidget(label_24);


	gridLayout_2->addLayout(horizontalLayout_9, 9, 0, 1, 1);



	groupBox_11->setTitle(QString());
	button_9->setText(QString());
	label_9->setText(QApplication::translate("Form", "0.0-10.0", 0, QApplication::UnicodeUTF8));
	button_10->setText(QString());
	label_10->setText(QApplication::translate("Form", "10.0-20.0", 0, QApplication::UnicodeUTF8));
	label_13->setText(QString());
	label_14->setText(QApplication::translate("Form", "20.0-30.0", 0, QApplication::UnicodeUTF8));
	label_15->setText(QString());
	label_16->setText(QApplication::translate("Form", "30.0-40.0", 0, QApplication::UnicodeUTF8));
	label_21->setText(QString());
	label_22->setText(QApplication::translate("Form", "40.0-50.0", 0, QApplication::UnicodeUTF8));
	label_17->setText(QString());
	label_18->setText(QApplication::translate("Form", "50.0-60.0", 0, QApplication::UnicodeUTF8));
	label_19->setText(QString());
	label_20->setText(QApplication::translate("Form", "60.0-70.0", 0, QApplication::UnicodeUTF8));
	label_25->setText(QString());
	label_26->setText(QApplication::translate("Form", "70.0-80.0", 0, QApplication::UnicodeUTF8));
	label_27->setText(QString());
	label_28->setText(QApplication::translate("Form", "80.0-90.0", 0, QApplication::UnicodeUTF8));
	label_23->setText(QString());
	label_24->setText(QApplication::translate("Form", "90.0-100.0", 0, QApplication::UnicodeUTF8));
}
//
void ViewerWidget::ChangeBackgroundColor()
{
	QPushButton *_pButton = dynamic_cast<QPushButton*>(sender());
	QString red;
	QString blue;
	QString green;
	QString _colorStyle;

	if (_pButton != NULL)
	{
		if (_pButton->objectName() == "Level_1")
		{
			_iLevel = 1;
		}
		if (_pButton->objectName() == "Level_2")
		{
			_iLevel = 2;
		}
		if (_pButton->objectName() == "Level_3")
		{
			_iLevel = 3;
		}
		if (_pButton->objectName() == "Level_4")
		{
			_iLevel = 4;
		}
		if (_pButton->objectName() == "Level_5")
		{
			_iLevel = 5;
		}
		if (_pButton->objectName() == "Level_6")
		{
			_iLevel = 6;
		}
		if (_pButton->objectName() == "Level_7")
		{
			_iLevel = 7;
		}
		if (_pButton->objectName() == "Level_8")
		{
			_iLevel = 8;
		}
		if (_pButton->objectName() == "Level_9")
		{
			_iLevel = 9;
		}
		if (_pButton->objectName() == "Level_10")
		{
			_iLevel = 10;
		}
		_pColorDialog = new QColorDialog;
		connect(_pColorDialog,SIGNAL(colorSelected(const QColor&)),this,SLOT(GetChangColor(const QColor&))); 
		_pColorDialog->exec();
		red.setNum(_pcolor.red());
		blue.setNum(_pcolor.blue());
		green.setNum(_pcolor.green());

		red = red+","+green+","+blue;
		_colorStyle = "background-color: rgb("+red+");";
		_pButton->setStyleSheet(_colorStyle);
	}

}
//
void ViewerWidget::GetChangColor(const QColor& _color)
{
	_pcolor = _color;
	emit SendLevelAndColor(_iLevel,_pcolor);
}
//
