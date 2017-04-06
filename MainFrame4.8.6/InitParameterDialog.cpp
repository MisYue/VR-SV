#include "InitParameterDialog.h"
#include  "LineCallBack.h"
#include <strstream>
//
OperationDisplay::OperationDisplay()
{
		_listColor.push_back(osg::Vec4f(0.8,0.9,0.0,1.0));
        _listColor.push_back(osg::Vec4f(0.4,0.9,0.0,1.0));
		_listColor.push_back(osg::Vec4f(0.0,0.9,0.0,1.0));
		_listColor.push_back(osg::Vec4f(0.0,0.9,0.4,1.0));
		_listColor.push_back(osg::Vec4f(0.0,0.9,0.8,1.0));
		_listColor.push_back(osg::Vec4f(0.0,0.4,0.9,1.0));
		_listColor.push_back(osg::Vec4f(0.0,0.0,0.9,1.0));
		_listColor.push_back(osg::Vec4f(0.4,0.0,0.9,1.0));
		_listColor.push_back(osg::Vec4f(0.9,0.0,0.9,1.0));
		_listColor.push_back(osg::Vec4f(0.9,0.0,0.5,1.0));

		AxisLength = 0.0;
		DamageArea = 0.0;
		MassiveData = 0.0;
		RootScene = new osg::Group();
}
//创建目标区域
void OperationDisplay::BulidAimZoonGrid(osg::Group *root,Bit_AimDataStructure *AimLine,std::map<int,GridUnit> &ElementQuadList)
{
	osg::MatrixTransform *triangleMT = new osg::MatrixTransform;  
	triangleMT->setMatrix(osg::Matrix::translate(0.0, 0.0, 0.0));
	triangleMT->setName("AimMT"); 
	//总体区域网格
	osg::Geometry *AreaGeometry = new osg::Geometry;  
	osg::Vec3Array *AreaVertexArray = new osg::Vec3Array;  
	CoordinatesPosition AimArea_[4];
	AimLine->Get_AimArea(AimArea_);
	for (int i = 0; i < 4;++i)
	{
		AreaVertexArray->push_back(osg::Vec3(AimArea_[i].Get_x(),AimArea_[i].Get_y(),AimArea_[i].Get_z()));  
	}
	AreaGeometry->setVertexArray(AreaVertexArray); 
	osg::Vec4Array *RadColorArray = new osg::Vec4Array;  
	RadColorArray->push_back(osg::Vec4(1.0,1.0,1.0,1.0));
	AreaGeometry->setColorArray(RadColorArray);  
	AreaGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);  
	AreaGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, 4));
	//分割网格
	osg::Geometry *SplitGeometry = new osg::Geometry;  
	osg::Vec3Array *SplitVertexArray_ = new osg::Vec3Array;  
 

	osg::Geode *triangleGeode = new osg::Geode;  
	std::map<int,GridUnit>::iterator it_ = ElementQuadList.begin();
	std::vector<osg::Geometry*> GeometryList;
	for (;it_ != ElementQuadList.end();++it_)
	{
	    osg::Vec3Array *SplitVertexArray_ = new osg::Vec3Array;  
		osg::Vec3 _P_0(it_->second.UnitNode.Get_Node_0().Get_x(),it_->second.UnitNode.Get_Node_0().Get_y(),it_->second.UnitNode.Get_Node_0().Get_z());
		osg::Vec3 _P_1(it_->second.UnitNode.Get_Node_1().Get_x(),it_->second.UnitNode.Get_Node_1().Get_y(),it_->second.UnitNode.Get_Node_1().Get_z());
		osg::Vec3 _P_2(it_->second.UnitNode.Get_Node_2().Get_x(),it_->second.UnitNode.Get_Node_2().Get_y(),it_->second.UnitNode.Get_Node_2().Get_z());
		osg::Vec3 _P_3(it_->second.UnitNode.Get_Node_3().Get_x(),it_->second.UnitNode.Get_Node_3().Get_y(),it_->second.UnitNode.Get_Node_3().Get_z());
		SplitVertexArray_->push_back(_P_0);
		SplitVertexArray_->push_back(_P_2);
		SplitVertexArray_->push_back(_P_3);
		SplitVertexArray_->push_back(_P_1);

		osg::Geometry *SplitGeometry_ = new osg::Geometry;
		SplitGeometry_->setVertexArray(SplitVertexArray_); 
		SplitGeometry_->setColorArray(RadColorArray);  
		SplitGeometry_->setColorBinding(osg::Geometry::BIND_OVERALL);  
		SplitGeometry_->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, SplitVertexArray_->size()));
		GeometryList.push_back(SplitGeometry_);
		triangleGeode->addDrawable(SplitGeometry_);

		if (it_->second.DamageLevel >0)
		{
			osg::Geometry *quadGeometry = new osg::Geometry;  
			osg::Vec3Array *quadVertexArray = new osg::Vec3Array;  
			quadVertexArray->push_back(_P_0);  
			quadVertexArray->push_back(_P_2);  
			quadVertexArray->push_back(_P_3);  
			quadVertexArray->push_back(_P_1);  
			quadGeometry->setVertexArray(quadVertexArray);  
			quadGeometry->setSupportsDisplayList(false);
			quadGeometry->setUseVertexBufferObjects(true);

			osg::Vec4Array *quadColorArray = new osg::Vec4Array;  
			quadColorArray->push_back(GetTheUnitColor(it_->second.DamageLevel));  
			quadGeometry->setColorArray(quadColorArray);  
			quadGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);  

			osg::DrawElementsUByte *vertexIndices = new osg::DrawElementsUByte(osg::PrimitiveSet::QUADS, 4);  
			vertexIndices->push_back(0);  
			vertexIndices->push_back(1);  
			vertexIndices->push_back(2);  
			vertexIndices->push_back(3);  
			quadGeometry->addPrimitiveSet(vertexIndices);
			_listGeometry.insert(std::pair<int,osg::Geometry*>(it_->second.DamageLevel,quadGeometry));
			triangleGeode->addDrawable(quadGeometry);
		}
	}

	
	triangleMT->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	triangleMT->addChild(triangleGeode);  

	root->addChild(triangleMT);   
}
//创建坐标系
void OperationDisplay::BulidCoordinate(osg::Group *root,CoordinatesPosition centerPoint,osg::Vec3 RotateAngle,std::string Ctype)
{
	double LengthAxis = 0;
	double TSize = 4.0;
	
	//设置三角形的平移(glTranslate)  
	osg::MatrixTransform *triangleMT_ = new osg::MatrixTransform; 

	if (Ctype == "Rock_")
	{
		TSize = 1.5;
		LengthAxis = 60.0;
		
		osg::Matrix matrix_yaw = osg::Matrix::rotate(RotateAngle[2],osg::Z_AXIS); //航向角

		osg::Vec3f _vY(0.0,1.0,0.0);
		_vY = matrix_yaw*_vY;
		_vY.set(-_vY.x(),_vY.y(),_vY.z());

		osg::Matrix matrix_pitch = osg::Matrix::rotate(RotateAngle[1],_vY);//俯仰角

		triangleMT_->setMatrix(matrix_yaw*matrix_pitch*osg::Matrix::translate(osg::Vec3d(centerPoint.Get_x(),centerPoint.Get_y(),centerPoint.Get_z())));
	}
	else if (Ctype == "Aim_")
	{
		LengthAxis = AxisLength;
		triangleMT_->setMatrix(osg::Matrix::rotate(RotateAngle.x(),osg::X_AXIS,RotateAngle.y(),osg::Y_AXIS,RotateAngle.z(),osg::Z_AXIS)*osg::Matrix::translate(osg::Vec3d(centerPoint.Get_x(),centerPoint.Get_y(),centerPoint.Get_z()))); 
	}
	osg::ref_ptr<osgText::Font> font = osgText::readFontFile( "fonts/arial.ttf" );

	//绘制坐标系轴
	osg::Geometry *Xaxis_Geometry = new osg::Geometry;  
	osg::Geometry *Yaxis_Geometry = new osg::Geometry;
	osg::Geometry *Zaxis_Geometry = new osg::Geometry;


	//设置坐标轴点 
	//X轴
	osg::Vec3Array *XVertexArray = new osg::Vec3Array;  
	XVertexArray->push_back(osg::Vec3(0.0f,0.0f, 0.0f));  
	XVertexArray->push_back(osg::Vec3(LengthAxis,0.0f, 0.0f));  
	Xaxis_Geometry->setVertexArray(XVertexArray); 


	osg::ref_ptr<osgText::Text> text_x = new osgText::Text;  
	text_x->setFont( font.get() );  
	text_x->setFontResolution( 128, 128 );  
	text_x->setColor(osg::Vec4(1.0,0.0,0.0,1.0));  
	text_x->setCharacterSize(TSize);  
	text_x->setPosition( osg::Vec3( LengthAxis+3.0f, 0.0f, 2.0f ) );  
	text_x->setAxisAlignment( osgText::Text::XZ_PLANE );  
	text_x->setAlignment( osgText::Text::CENTER_TOP );  
	text_x->setText( Ctype+"X" );  

	//Y轴
	osg::Vec3Array *YVertexArray = new osg::Vec3Array;  
	YVertexArray->push_back(osg::Vec3(0.0f,0.0f, 0.0f));  
	YVertexArray->push_back(osg::Vec3(0.0f,LengthAxis, 0.0f));  
	Yaxis_Geometry->setVertexArray(YVertexArray);  

	osg::ref_ptr<osgText::Text> text_y = new osgText::Text;  
	text_y->setFont( font.get() );  
	text_y->setFontResolution( 128, 128 );  
	text_y->setColor(osg::Vec4(0.0,1.0,0.0,1.0));  
	text_y->setCharacterSize(TSize);  
	text_y->setPosition( osg::Vec3( 0.0f, LengthAxis+3.0f, 2.0f ) );  
	text_y->setAxisAlignment( osgText::Text::XZ_PLANE );  
	text_y->setAlignment( osgText::Text::CENTER_TOP );  
	text_y->setText(Ctype+"Y" );  

	//Z轴
	osg::Vec3Array *ZVertexArray = new osg::Vec3Array;  
	ZVertexArray->push_back(osg::Vec3(0.0f,0.0f, 0.0f));  
	ZVertexArray->push_back(osg::Vec3(0.0f,0.0f, LengthAxis));  
	Zaxis_Geometry->setVertexArray(ZVertexArray);  

	osg::ref_ptr<osgText::Text> text_z = new osgText::Text;  
	text_z->setFont( font.get() );  
	text_z->setFontResolution( 128, 128 );  
	text_z->setColor(osg::Vec4(0.0,0.0,1.0,1.0));  
	text_z->setCharacterSize(TSize);  
	text_z->setPosition( osg::Vec3( 0.0f, 0.0f, LengthAxis+3.0f ) );  
	text_z->setAxisAlignment( osgText::Text::XZ_PLANE );  
	text_z->setAlignment( osgText::Text::CENTER_TOP );  
	text_z->setText( Ctype+"Z" );  

	//设置X轴颜色  
	osg::Vec4Array *RadColorArray = new osg::Vec4Array;  
	RadColorArray->push_back(osg::Vec4(1.0,0.0,0.0,1.0));
	Xaxis_Geometry->setColorArray(RadColorArray);  
	Xaxis_Geometry->setColorBinding(osg::Geometry::BIND_OVERALL);  

	osg::Vec4Array *GreenColorArray = new osg::Vec4Array;  
	GreenColorArray->push_back(osg::Vec4(0.0,1.0,0.0,1.0));
	Yaxis_Geometry->setColorArray(GreenColorArray);  
	Yaxis_Geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec4Array *BlueColorArray = new osg::Vec4Array;  
	BlueColorArray->push_back(osg::Vec4(0.0,0.0,1.0,1.0));
	Zaxis_Geometry->setColorArray(BlueColorArray);  
	Zaxis_Geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	Xaxis_Geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));
	Yaxis_Geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));
	Zaxis_Geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));


	osg::Geode *triangleGeode = new osg::Geode;  

	//关闭光照  
	triangleGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);  
	triangleGeode->addDrawable(Xaxis_Geometry);  
	triangleGeode->addDrawable(text_x);
	triangleGeode->addDrawable(Yaxis_Geometry);
	triangleGeode->addDrawable(text_y);
	triangleGeode->addDrawable(Zaxis_Geometry);
	triangleGeode->addDrawable(text_z);
	triangleMT_->addChild(triangleGeode);  
	

	root->addChild(triangleMT_);   
}
//创建弹体
void OperationDisplay::BulidProjectile(osg::Group *root,WarheadPowerAnalysisData &warHead,CoordinatesPosition Frag_HitPosition,osg::Vec3 RotateAngle)
{
	osg::MatrixTransform *zoomMT = new osg::MatrixTransform; 
	osg::MatrixTransform *zoomMT_ = new osg::MatrixTransform;  
	osg::MatrixTransform *_iveMT = new osg::MatrixTransform;
	osg::Node *_iveNode = osgDB::readNodeFile("Resource/aim120.ive");
	_iveMT->addChild(_iveNode);
	_iveMT->setMatrix(osg::Matrix::scale(10,10,10));
	//_iveMT->setMatrix(osg::Matrix::rotate(osg::PI_2,osg::X_AXIS)*osg::Matrix::scale(10,10,10));
	zoomMT->addChild(_iveMT);
	zoomMT->setName("IveModle");

	osg::Geode *cylinder_inside = new osg::Geode;  
	osg::ShapeDrawable *cylinderDrawable_inside = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0,0,0), warHead.Get_ShellInterDiameter(), warHead.Get_WarheadLengthClylinder()));  
	cylinderDrawable_inside->setColor(osg::Vec4(0,0,1,0.4));  
	cylinder_inside->addDrawable(cylinderDrawable_inside);  
	cylinder_inside->setName("cylinderinside");


	osg::Geode *cylinder_outside = new osg::Geode;  
	osg::ShapeDrawable *cylinderDrawable_outside = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0,0,0), warHead.Get_ShellOuterDiameter(), warHead.Get_WarheadLengthClylinder()));  
	cylinderDrawable_outside->setColor(osg::Vec4(1,0,0,1));  
	cylinder_outside->addDrawable(cylinderDrawable_outside);  
	cylinder_outside->setName("cylinderoutside");

	osg::BlendFunc *blendFunc = new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE, 0.4, 0.4);  
	cylinderDrawable_outside->getOrCreateStateSet()->setRenderingHint(  
		osg::StateSet::TRANSPARENT_BIN );  
	cylinderDrawable_outside->getOrCreateStateSet()->setAttribute(blendFunc,  
		osg::StateAttribute::ON);  
 
	zoomMT_->addChild(cylinder_outside);
	zoomMT_->addChild(cylinder_inside);
	zoomMT_->setName("Cylinder");
	osg::Matrix matrix = osg::Matrix::rotate(osg::PI_2,osg::Y_AXIS);
	
	osg::Matrix matrix_yaw = osg::Matrix::rotate(RotateAngle[2],osg::Z_AXIS); //航向角
	osg::Vec3f _vY(0.0,1.0,0.0);
	_vY = matrix_yaw*_vY;
	_vY.set(-_vY.x(),_vY.y(),_vY.z());
	osg::Matrix matrix_pitch = osg::Matrix::rotate(RotateAngle[1],_vY);//俯仰角
	zoomMT_->setMatrix(matrix*matrix_yaw*matrix_pitch*osg::Matrix::translate(osg::Vec3d(Frag_HitPosition.Get_x(),Frag_HitPosition.Get_y(),Frag_HitPosition.Get_z())));
	zoomMT->setMatrix(matrix*matrix_yaw*matrix_pitch*osg::Matrix::translate(osg::Vec3d(Frag_HitPosition.Get_x(),Frag_HitPosition.Get_y(),Frag_HitPosition.Get_z())));

	//zoomMT_->setMatrix(osg::Matrix::rotate(RotateAngle.z(),osg::Z_AXIS,RotateAngle.y(),osg::Y_AXIS,RotateAngle.x(),osg::X_AXIS)*osg::Matrix::translate(Frag_HitPosition.Get_x(),Frag_HitPosition.Get_y(),Frag_HitPosition.Get_z()));
	root->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON); 
	root->addChild(zoomMT);
	zoomMT_->setNodeMask(0x00);
	root->addChild(zoomMT_);
};
//创建单片飞行线，没有停止
void OperationDisplay::BulidFragmentLine(osg::Group *root,CoordinatesPosition _p1,CoordinatesPosition _p2)
{
	//设置三角形的平移(glTranslate)  
	osg::MatrixTransform *triangleMT = new osg::MatrixTransform;  
	osg::ref_ptr<osgText::Font> font = osgText::readFontFile( "fonts/arial.ttf" );

	//绘制坐标系轴
	osg::Geometry *Xaxis_Geometry = new osg::Geometry;  


	//设置坐标轴点 
	osg::Vec3Array *XVertexArray = new osg::Vec3Array;  
	XVertexArray->push_back(osg::Vec3(_p1.Get_x(),_p1.Get_y(),_p1.Get_z()));  
	XVertexArray->push_back(osg::Vec3(_p2.Get_x(),_p2.Get_y(),_p2.Get_z()));  
	Xaxis_Geometry->setVertexArray(XVertexArray); 


	osg::ref_ptr<osgText::Text> text_x = new osgText::Text;  
	text_x->setFont( font.get() );  
	text_x->setFontResolution( 128, 128 );  
	text_x->setColor(osg::Vec4(1.0,0.0,0.0,1.0));  
	text_x->setCharacterSize(1.0);  
	text_x->setPosition(osg::Vec3(_p2.Get_x(),_p2.Get_y(),_p2.Get_z()));  
	text_x->setAxisAlignment( osgText::Text::XZ_PLANE );  
	text_x->setAlignment( osgText::Text::CENTER_TOP );  
	text_x->setText("X_Vec" );   

	//设置X轴颜色  
	osg::Vec4Array *RadColorArray = new osg::Vec4Array;  
	RadColorArray->push_back(osg::Vec4(1.0,0.0,0.0,1.0));
	Xaxis_Geometry->setColorArray(RadColorArray);  
	Xaxis_Geometry->setColorBinding(osg::Geometry::BIND_OVERALL);  


	Xaxis_Geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));


	osg::Geode *triangleGeode = new osg::Geode;  

	//关闭光照  
	triangleGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);  
	triangleGeode->addDrawable(Xaxis_Geometry);  
	triangleGeode->addDrawable(text_x);
	triangleMT->addChild(triangleGeode);  

	root->addChild(triangleMT);   
};
//创建单片飞行线与目标交汇
void OperationDisplay::BulidFragmentAimLineYDamage(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion)
{
	osg::MatrixTransform *triangleMT = new osg::MatrixTransform; 
	osg::MatrixTransform *ShackWaveMT = new osg::MatrixTransform;  

	ShackWaveMT->setMatrix(osg::Matrix::translate(0.0, 0.0, 0.0));  
	ShackWaveMT->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	triangleMT->setMatrix(osg::Matrix::translate(0.0, 0.0, 0.0));  
	triangleMT->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	ShockWaveCallBack *_Call = new ShockWaveCallBack(HitPostion);
	
	///////////////8-19
	osg::Geode *triangleGeode = new osg::Geode;  
	osg::Geometry *ScatteredGeometry = new osg::Geometry; 
	ScatteredGeometry->setUseVertexBufferObjects(true);  
	ScatteredGeometry->setUseDisplayList(false); 
	osg::Vec4Array *RadColorArray = new osg::Vec4Array;
	osg::Vec3Array *ScatteredVertexArray = new osg::Vec3Array;
	std::vector<FragMentLine>::iterator it_ =  AimFragmeList.begin();
	for (;it_ != AimFragmeList.end();++it_)
	{
		ScatteredVertexArray->push_back(osg::Vec3(it_->_PosBegin.Get_x(),it_->_PosBegin.Get_y(),it_->_PosBegin.Get_z()));
		ScatteredVertexArray->push_back(osg::Vec3(it_->_PosBegin.Get_x()+it_->_PosV.Get_x(),it_->_PosBegin.Get_y()+it_->_PosV.Get_y(),it_->_PosBegin.Get_z()+it_->_PosV.Get_z()));
		RadColorArray->push_back(osg::Vec4(1.0,0.0,0.0,1.0));
		RadColorArray->push_back(osg::Vec4(1.0,0.0,0.0,1.0));
	}
	ScatteredGeometry->setColorArray(RadColorArray);
	ScatteredGeometry->setVertexArray(ScatteredVertexArray);
	ScatteredGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);  
	ScatteredGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, ScatteredVertexArray->size()));
    ScatteredGeometry->setCullingActive(false);
	
	LineUpDataCallBack *_pCall = new LineUpDataCallBack(AimFragmeList,HitPostion,osg::Vec4(1.0,1.0,0.0,1.0));
	ScatteredGeometry->setUpdateCallback(_pCall);
	triangleGeode->addDrawable(ScatteredGeometry); 
	//////////////////////////////////////////////////////////////////////////
	
	triangleMT->addChild(triangleGeode);
	ShackWaveMT->setUpdateCallback(_Call);
	
	triangleMT->setName("DamageLine");
	NodeCallBackVec.push_back(_pCall);
	ShockWaveCallBackVec.push_back(_Call);
	root->addChild(triangleMT);  
	root->addChild(ShackWaveMT); 
};
//创建单片飞行线与未目标交汇
void OperationDisplay::BulidFragmentAimLineNoAttack(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion)
{
	osg::MatrixTransform *triangleMT = new osg::MatrixTransform;  
	triangleMT->setMatrix(osg::Matrix::translate(0.0, 0.0, 0.0));  
	triangleMT->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	///////////////8-19
	osg::Geode *triangleGeode = new osg::Geode;  
	osg::Geometry *ScatteredGeometry = new osg::Geometry; 
	ScatteredGeometry->setUseVertexBufferObjects(true);  
	ScatteredGeometry->setUseDisplayList(false); 
	osg::Vec4Array *RadColorArray = new osg::Vec4Array;
	osg::Vec3Array *ScatteredVertexArray = new osg::Vec3Array;
	std::vector<FragMentLine>::iterator it_ =  AimFragmeList.begin();
	for (;it_ != AimFragmeList.end();++it_)
	{
		ScatteredVertexArray->push_back(osg::Vec3(it_->_PosBegin.Get_x(),it_->_PosBegin.Get_y(),it_->_PosBegin.Get_z()));
		ScatteredVertexArray->push_back(osg::Vec3(it_->_PosBegin.Get_x()+it_->_PosV.Get_x(),it_->_PosBegin.Get_y()+it_->_PosV.Get_y(),it_->_PosBegin.Get_z()+it_->_PosV.Get_z()));
		RadColorArray->push_back(osg::Vec4(0.0,1.0,0.0,1.0));
		RadColorArray->push_back(osg::Vec4(0.0,1.0,0.0,1.0));
	}
	ScatteredGeometry->setColorArray(RadColorArray);
	ScatteredGeometry->setVertexArray(ScatteredVertexArray);
	ScatteredGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);  
	ScatteredGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, ScatteredVertexArray->size()));
	ScatteredGeometry->setCullingActive(false);

	LineUpDataCallBack *_pCall = new LineUpDataCallBack(AimFragmeList,HitPostion,osg::Vec4(1.0,0.0,1.0,1.0));
	ScatteredGeometry->setUpdateCallback(_pCall);
	triangleGeode->addDrawable(ScatteredGeometry); 
	//////////////////////////////////////////////////////////////////////////

	triangleMT->addChild(triangleGeode);
	triangleMT->setName("NOAttackLine");
	NodeCallBackVec.push_back(_pCall);
	root->addChild(triangleMT);   
};
//创建弹片飞行线与目标交汇，但未有毁伤效果
void OperationDisplay::BulidFragmentAimLineNoDamage(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion)
{
	osg::MatrixTransform *triangleMT = new osg::MatrixTransform;  
	triangleMT->setMatrix(osg::Matrix::translate(0.0, 0.0, 0.0));  
	triangleMT->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	///////////////8-19
	osg::Geode *triangleGeode = new osg::Geode;  
	osg::Geometry *ScatteredGeometry = new osg::Geometry; 
	ScatteredGeometry->setUseVertexBufferObjects(true);  
	ScatteredGeometry->setUseDisplayList(false); 
	osg::Vec4Array *RadColorArray = new osg::Vec4Array;
	osg::Vec3Array *ScatteredVertexArray = new osg::Vec3Array;
	std::vector<FragMentLine>::iterator it_ =  AimFragmeList.begin();
	for (;it_ != AimFragmeList.end();++it_)
	{
		ScatteredVertexArray->push_back(osg::Vec3(it_->_PosBegin.Get_x(),it_->_PosBegin.Get_y(),it_->_PosBegin.Get_z()));
		ScatteredVertexArray->push_back(osg::Vec3(it_->_PosBegin.Get_x()+it_->_PosV.Get_x(),it_->_PosBegin.Get_y()+it_->_PosV.Get_y(),it_->_PosBegin.Get_z()+it_->_PosV.Get_z()));
		RadColorArray->push_back(osg::Vec4(0.8,1.0,0.0,1.0));
		RadColorArray->push_back(osg::Vec4(0.8,1.0,0.0,1.0));
	}
	ScatteredGeometry->setColorArray(RadColorArray);
	ScatteredGeometry->setVertexArray(ScatteredVertexArray);
	ScatteredGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);  
	ScatteredGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, ScatteredVertexArray->size()));
	ScatteredGeometry->setCullingActive(false);

	LineUpDataCallBack *_pCall = new LineUpDataCallBack(AimFragmeList,HitPostion,osg::Vec4(0.0,1.0,1.0,1.0));
	ScatteredGeometry->setUpdateCallback(_pCall);
	triangleGeode->addDrawable(ScatteredGeometry); 
	//////////////////////////////////////////////////////////////////////////

	triangleMT->addChild(triangleGeode);
	triangleMT->setName("LineNoDamage");
	NodeCallBackVec.push_back(_pCall);
	root->addChild(triangleMT);   
};
//获取毁伤等级
int OperationDisplay::GetTheDamageLevel(int& Denergy)
{
	int DamageL = 0;
	if ((Denergy>0)&&(Denergy<=10))
	{
		DamageL = 1;
	}
	if ((Denergy>10)&&(Denergy<=20))
	{
		DamageL = 2;
	}
	if ((Denergy>20)&&(Denergy<=30))
	{
		DamageL = 3;
	}
	if ((Denergy>30)&&(Denergy<=40))
	{
		DamageL = 4;
	}
	if ((Denergy>40)&&(Denergy<=50))
	{
		DamageL = 5;
	}
	if ((Denergy>50)&&(Denergy<=60))
	{
		DamageL = 6;
	}
	if ((Denergy>60)&&(Denergy<=70))
	{
		DamageL = 7;
	}
	if ((Denergy>70)&&(Denergy<=80))
	{
		DamageL = 8;
	}
	if ((Denergy>80)&&(Denergy<=90))
	{
		DamageL = 9;
	}
	return DamageL;
}
//获取目标区域颜色
osg::Vec4f OperationDisplay::GetTheUnitColor(int& Level)
{
	osg::Vec4f UnitColor;
	switch(Level)
	{
	case Level_1:
		UnitColor = _listColor.at(0);
		break;
	case Level_2:
		UnitColor = _listColor.at(1);
		break;
	case Level_3:
		UnitColor = _listColor.at(2);
		break;
	case Level_4:
		UnitColor = _listColor.at(3);
		break;
	case Level_5:
		UnitColor = _listColor.at(4);
		break;
	case Level_6:
		UnitColor = _listColor.at(5);
		break;
	case Level_7:
		UnitColor = _listColor.at(6);
		break;
	case Level_8:
		UnitColor = _listColor.at(7);
		break;
	case Level_9:
		UnitColor = _listColor.at(8);
		break;
	case Level_10:
		UnitColor = _listColor.at(9);
		break;
	}
	return UnitColor;
}
//
void OperationDisplay::GetViewerWidget()
{
	InitPlotShrapnelLine();
	//return _pViewWidget;
}
//交汇界面
void OperationDisplay::InitPlotShrapnelLine()
{
	//建立存储毁伤网格变量
	int DamaA = 0;

	std::vector<FragMentLine> _AimFragmentLineList;
	std::vector<FragMentLine> _NDanamgeAimFragmentLineList;
	std::vector<FragMentLine> _NAimFragmentLineList;


	std::vector<int> AimConvergenceID;
	std::map<int,GridUnit> UnitGridList;

	//建立系统单位制
	Bit_UnitSystem System_US = Bit_UnitSystem( _UnitSystem.Get_LengthUnit() , _UnitSystem.Get_MassUnit() , _UnitSystem.Get_TimeUnit() );
	//建立指针对象,用于后续计算
	Bit_FragmentAnalyse *TheBit_FragmentAnalyse = new Bit_FragmentAnalyse( System_US );
	Bit_RocketAnalyse *TheBit_RocketAnalyse = new Bit_RocketAnalyse( System_US );


	//建立大地坐标系
	CoordinatesPosition Earth_Origin = CoordinatesPosition( 0 , 0 , 0 );
	CoordinatesPosition Earth_V1 = CoordinatesPosition( 1 , 0 , 0 );
	CoordinatesPosition Earth_V2 = CoordinatesPosition( 0 , 1 , 0 );
	CoordinateSystem CS_0( 1 , Earth_Origin , Earth_V1 , Earth_V2 );
	Bit_CSWithExpAndUS Earth_CSWithExpAndUS = Bit_CSWithExpAndUS( 0 , "大地坐标系" , CS_0 , 
		"原点为地心，X轴在赤道平面与本初子午面交线上，z轴沿极轴方向，y轴在赤道平面内与x轴、z轴成右手直角坐标系" , System_US );
	//建立目标坐标系
	CoordinatesPosition Aim_Origin = CoordinatesPosition( 0 , 0 , 0 );
	CoordinatesPosition Aim_V1 = CoordinatesPosition( 1 , 0 , 0 );
	CoordinatesPosition Aim_V2 = CoordinatesPosition( 0 , 1 , 0 );
	CoordinateSystem CS_1( 1 , Aim_Origin , Aim_V1 , Aim_V2 );
	Bit_CSWithExpAndUS Aim_CSWithExpAndUS = Bit_CSWithExpAndUS( 1 , "目标坐标系" , CS_1 , 
		"原点为目标群几何中心（假设目标群为规则区域，如矩形），x、y轴分别平行于目标群边界，z轴按右手坐标系竖直向上" , System_US );

	//建立目标数据结构
	//初始化炸点坐标（0,0,0），后续计算得到后用Set函数写入数据结构
	CoordinatesPosition Aim_HitPosition( 0 , 0 , 0 );
	//设置瞄准点坐标(暂定瞄准点为目标中心点)
	CoordinatesPosition AimP( 0 , 0 , 0 );
	int Aim_id = 1 , FirstNodeAfterDevide = 4 , FristElementAfterDevide = 0;
	double  Aim_Long = _TargetArea.Aim_Long , Aim_Wide = _TargetArea.Aim_Wide , Length_N_02 = _TargetArea.Length_N_02 , Length_N_13 = _TargetArea.Length_N_13 , AimCenterPointLat = _TargetArea.AimCenterPointLat , AimCenterPointLon = _TargetArea.AimCenterPointLon;
	if (Aim_Long >= Aim_Wide)
	{
		AxisLength = Aim_Long;
	}
	else
	{
		AxisLength = Aim_Wide;
	}
	//建立Bit_QuadMeshPlane对象，存储划分网格后目标区域信息
	Bit_QuadMeshPlane Bit_QMP = Bit_QuadMeshPlane();


	Bit_AimDataStructure TheBit_AimDataStructure = Bit_AimDataStructure( Aim_id , Aim_HitPosition , Aim_Long , Aim_Wide ,
		FirstNodeAfterDevide , FristElementAfterDevide , Length_N_02 , Length_N_13 , AimCenterPointLat , AimCenterPointLon , AimP );
	//将目标区域划分网格
	TheBit_FragmentAnalyse->AreaDividing( TheBit_AimDataStructure , Bit_QMP );

	//建立火箭弹数据结构
	//火箭弹部分信息初始化
	int Rock_Id = 1;
	double Rock_WarheadStaticAngle = _RockObject.Rock_WarheadStaticAngle/*1.0*/ , Rock_WarheadStaticAngleToCenter = _RockObject.Rock_WarheadStaticAngleToCenter/*1.0*/ , Rock_RocketVelocity = _RockObject.Rock_RocketVelocity/*300*/;
	//根据射程表线性插值得到落角，即火箭弹俯仰角（负）
	HAE_HitPointAnalysis *TheHAE_HitPointAnalysis = new HAE_HitPointAnalysis();
	//设置发射点经纬度（从界面获得）
	double FireLat = _RockObject.FireLat , FireLon = _RockObject.FireLon;
	//设置插值表数据个数
	int InterpolationNumber = _RockObject.InterpolationNumber;
	//设置射程插值表数组
	double *FireDistance = new double[InterpolationNumber];
	double *FallingAngle = new double[InterpolationNumber];
	for (int i = 0; i < InterpolationNumber;++i)
	{
		FireDistance[i] = _RockObject.FireDistance.at(i);
		FallingAngle[i] = _RockObject.FallingAngle.at(i);
	}


	//double FireDistance[8] = { 1000,2000,4000,5000,7000,8000,10000,20000 };
	////设置落角插值表数组
	//double FallingAngle[8] = { 10,12,20,30,35,38,40,42 };
	AdvancedMath *Compute = new AdvancedMath();
	double Rock_PitchingAngle_JiaoDu = TheHAE_HitPointAnalysis->ComputeFallAngleOnLoLA_Table( FireLon , FireLat , TheBit_AimDataStructure.Get_AimLon() , TheBit_AimDataStructure.Get_AimLat() ,
		InterpolationNumber , FireDistance , FallingAngle );
	double Rock_PitchingAngle_HuDu = Compute->AngleToRadian( Rock_PitchingAngle_JiaoDu );
	delete Compute;
	delete TheHAE_HitPointAnalysis;
	//根据地球两点经纬度计算两点方位角，即火箭弹偏航角

	CoordinatesPosition *CPCompute = new CoordinatesPosition();
	double Rock_YawAngle = CPCompute->AzimuthFromLongitudeAndLatitude(6378137 , 6356752.314 , FireLon , FireLat , TheBit_AimDataStructure.Get_AimLon() , TheBit_AimDataStructure.Get_AimLat() );
	//设置火箭弹CEP
	double Rock_CEP = _RockObject.Rock_CEP;//5;
	Bit_RocketDataStructure TheBit_RocketDataStructure = Bit_RocketDataStructure( Rock_Id , System_US , Rock_PitchingAngle_HuDu , Rock_YawAngle ,
		Rock_WarheadStaticAngle , Rock_WarheadStaticAngleToCenter , Rock_RocketVelocity , Rock_CEP );

	//计算炸点坐标（在火箭弹数据结构建立后，因调用火箭弹数据结构）
	//设置炸高期望与炸高标准差
	double BHE = _RockObject.BHE/*20*/ , BHD = _RockObject.BHD/*0.2*/;
	//考虑CEP后瞄准点在目标系内坐标
	CoordinatesPosition AimPWithCEP = TheBit_RocketAnalyse->AimPointInAim( TheBit_AimDataStructure.Get_AimPoint() , TheBit_RocketDataStructure );
	//炸点坐标
	Aim_HitPosition = TheBit_RocketAnalyse->BurstPoint( AimPWithCEP , BHE , BHD , TheBit_RocketDataStructure );
	TheBit_AimDataStructure.Set_HitPosition( Aim_HitPosition );

	//破片场信息初始化
	//破片数量
	int FragmentNumber = _RockObject.FragmentNumber;//300;
	//单枚破片数据结构初始地址
	Bit_FragmentDataStructure *TheBit_FragmentDataStructure = new Bit_FragmentDataStructure [FragmentNumber]();
	//Bit_FragmentDataStructureForAll TheBit_FragmentDataStructureForAll = Bit_FragmentDataStructureForAll ( FragmentNumber , TheBit_FragmentDataStructure );
	//计算破片初速
	ChargeData RocketWarheadChargeData = ChargeData( 0 , System_US , _RockObject.Density /*1680*/, _RockObject.ExplosionVelocity/*7000*/, _RockObject.ExplosionHeat/*4e7*/ ,_RockObject.ExplosinPressure/*24e9*/ );
	WarheadPowerAnalysisData RocketWarhead = WarheadPowerAnalysisData( 0 , System_US ,_RockObject.ShellMass_Clylinder/*100*/ ,_RockObject.ChargeMass_Clylinder/*50*/, _RockObject.AllMass_Whole/*180*/ , _RockObject.ChargeMass_Whole/*60*/ , RocketWarheadChargeData.Get_ChargeId() , 1 , _RockObject.ShellInterDiameter/*2.0M*/ , _RockObject.ShellOuterDiameter/*2.20M*/ , _RockObject.ShellBrokenDiameter/*2.5M*/ ,_RockObject.WarheadLength_Whole/*3*/ , _RockObject.WarheadLength_Clylinder/*3*/ );//只用部分参数（ShellMass_Clylinder，ChargeMass_Clylinder,WarheadLength_Whole）
	double Frag_Vel = TheBit_RocketAnalyse->ComputeFragmentVelocityViaGurney( RocketWarhead , RocketWarheadChargeData , System_US );
	ProbabilityAndRandom *PAR = new ProbabilityAndRandom();
	//产生均匀分布所用随机数，用于计算动态周向角
	double *RandomForUniformDistribution = new double[FragmentNumber]();
	bool Ran_TOF = PAR->SampleOnSampleNumber( FragmentNumber , RandomForUniformDistribution );
	//正态分布抽样计算静态方向角
	double *Frag_StaticDirectionalAngle_Initialization = new double[FragmentNumber]();
	TheBit_FragmentAnalyse->FragmentDirectionalAngle( TheBit_RocketDataStructure , FragmentNumber , Frag_StaticDirectionalAngle_Initialization );
	//初始化破片静态飞散角（0）;破片飞散距离（10000）（确定破片飞行方向）,先假设破片飞行无速度衰减，求出与区域交点;
	//破片质量（5），后续由程序计算质量
	double Frag_SDA = 0, Frag_dis = 10000, Frag_Mass = _RockObject.Frag_Mass /*5*/, Frag_ResidualVelocity_Initialization = 0;
	//初始化破片数据结构
	for( int i = 0 ; i < FragmentNumber ; i++ )
	{
		//破片Id
		TheBit_FragmentDataStructure[i].Set_FragmentID( i + 1 );
		//破片单位系
		TheBit_FragmentDataStructure[i].Set_FragmentUS( System_US );
		//破片质量
		TheBit_FragmentDataStructure[i].Set_Mass( Frag_Mass );
		//破片初速
		TheBit_FragmentDataStructure[i].Set_FragmentVelocity( Frag_Vel );
		//破片飞行距离
		TheBit_FragmentDataStructure[i].Set_FlyDistance( Frag_dis );
		//每个破片静态飞散角
		TheBit_FragmentDataStructure[i].Set_StaticDisporaAngle( Frag_SDA );
		TheBit_FragmentDataStructure[i].Set_DynamicCircleAngle( 2 * pi * RandomForUniformDistribution[i] );
		//正态分布抽样得到每个破片静态方向角
		TheBit_FragmentDataStructure[i].Set_StaticDirectonalAngle( Frag_StaticDirectionalAngle_Initialization[i] );
		//每个破片动态飞散速度（实际速度）(有问题：TheBit_FragmentDataStructure[i]正在初始化，里面的破片初速必须在这条之前初始化完毕)
		double Frag_FragmentRealVelocity__Initialization = TheBit_FragmentAnalyse->FragmentRealVelocity( TheBit_FragmentDataStructure[i] , TheBit_RocketDataStructure );
		TheBit_FragmentDataStructure[i].Set_FragmentDynamicVelocity( Frag_FragmentRealVelocity__Initialization );
		//每个破片动态方向角
		double Frag_DynamicDirectionalAngle__Initialization = TheBit_FragmentAnalyse->FragmentDynamicDirectionalAngle( TheBit_FragmentDataStructure[i] , TheBit_RocketDataStructure );
		TheBit_FragmentDataStructure[i].Set_DynamicDirectionalAngle( Frag_DynamicDirectionalAngle__Initialization );
		//每个破片在弹体坐标系内坐标(有问题：TheBit_FragmentDataStructure[i]正在初始化，里面的破片飞行距离必须在这条之前初始化完毕)
		CoordinatesPosition Frag_FragmentPositionInRocketCoordinate__Initialization = 
			TheBit_FragmentAnalyse->ComputeFragmentCoordinateInBodyCoordinate( TheBit_FragmentDataStructure[i] );
		TheBit_FragmentDataStructure[i].Set_FragmentPositionInRocketCoordinate( Frag_FragmentPositionInRocketCoordinate__Initialization );
		//每个破片剩余速度（初始化为0）
		TheBit_FragmentDataStructure[i].Set_FragmentResidualVelocity( Frag_ResidualVelocity_Initialization );
	}
	delete PAR;
	delete []RandomForUniformDistribution;
	delete []Frag_StaticDirectionalAngle_Initialization;

	//计算破片速度衰减所需参数初始化_得到破片剩余速度
	double SC = _RockObject.SC;//0.00307;//球形破片
	double ASL = _RockObject.ASL/*15*/ , RC = _RockObject.RC/*0.97*/;
	//计算破片速度衰减
	//建立存储破片与目标区域交点CoordinatesPosition数组
	CoordinatesPosition *Frag_MeetingPoint = new CoordinatesPosition[FragmentNumber]();

	////VR
	int AllElementsCount = Bit_QMP.Get_ElementNumber();
	Element_Surface_Quad *p = new Element_Surface_Quad[AllElementsCount];
	Bit_QMP.Get_ElementInPlane(p);

	for(int i =0; i < AllElementsCount; ++i)
	{
		GridUnit gu;
		gu.UnitNode = p[i];
		gu.UnitID = p[i].Get_id();
		UnitGridList.insert(std::pair<int,GridUnit>(gu.UnitID,gu));
	}
	delete [] p;

	double Frag_FragmentDamageCriterion = _RockObject.Frag_FragmentDamageCriterion/*78*/;
	//建立动态数组，存储每个破片与目标区域网格交汇的Id号
	int *IdOfMeeting = new int[FragmentNumber]();
	std::map<int,GridUnit>::iterator it_GridUnit;


	//建立存储破片是否命中网格动态数组（改成容器）
	//网格数量
	int EN = Bit_QMP.Get_ElementNumber();
	int *HON = new int[EN]();
	for (int k = 0 ; k < EN ; k++ )
	{
		HON[k] = 0;
	}

	//破片剩余速度初始化
	double ResidualVelocity = 0;
	std::vector<int>::const_iterator _cItor;
	//计算破片速度衰减，结合毁伤判据判断破片与网格相交情况及毁伤情况
	for ( int k = 0 ; k < FragmentNumber ; k++ )
	{
		//求取破片飞行轨迹线(基于目标坐标系)
		Line FragmentFlyLineInAim = TheBit_FragmentAnalyse->ComputeFragmentFlyLine( TheBit_FragmentDataStructure[k] , TheBit_RocketDataStructure , TheBit_AimDataStructure );

		FragMentLine _line;
		_line._PosBegin = TheBit_AimDataStructure.Get_HitPosition();
		CoordinatesPosition _pCoor;
		_pCoor.Set_x(FragmentFlyLineInAim.Get_Vector().Get_x()*0.03);
		_pCoor.Set_y(FragmentFlyLineInAim.Get_Vector().Get_y()*0.03);
		_pCoor.Set_z(FragmentFlyLineInAim.Get_Vector().Get_z()*0.03);

		_line._PosEnd = FragmentFlyLineInAim.Get_FristNode().Get_NodeCoordinates() + _pCoor;
		double v_x = _line._PosEnd.Get_x() - _line._PosBegin.Get_x();
		double v_y = _line._PosEnd.Get_y() - _line._PosBegin.Get_y();
		double v_z = _line._PosEnd.Get_z() - _line._PosBegin.Get_z();
		osg::Vec3d _PP(v_x,v_y,v_z);

		_PP = _PP/_PP.length();
		_line._PosV.Set_x(_PP.x());
		_line._PosV.Set_y(_PP.y());
		_line._PosV.Set_z(_PP.z());

		//判断该枚破片是否与目标所在平面存在交点
		bool WhetherMeeting = TheBit_FragmentAnalyse->MeetingOrNot( FragmentFlyLineInAim , TheBit_AimDataStructure );
		//cout<<WhetherMeeting;
		if ( WhetherMeeting == true )
		{
			Frag_MeetingPoint[k] = TheBit_FragmentAnalyse->ComputeMeetingPointWithArea( FragmentFlyLineInAim , TheBit_AimDataStructure );

			//判断交点是否在目标网格区域内
			if ( TheBit_FragmentAnalyse->InOrNot( FragmentFlyLineInAim , Bit_QMP) == true )
			{
				//破片飞行距离
				Frag_dis = Frag_MeetingPoint[k].Distance( TheBit_AimDataStructure.Get_HitPosition() );

				//计算破片速度衰减	
				//破片质量
				double Frag_Mass = TheBit_FragmentDataStructure[k].Get_Mass();
				//破片实际速度（动态飞散速度）
				double Frag_RealVelo = TheBit_FragmentDataStructure[k].Get_FragmentDynamicVelocity();
				//破片展现面积
				double FA = TheBit_RocketAnalyse->ComputeFragmentFrontalArea( SC , Frag_Mass , System_US );
				//当地空气密度
				double LAD = TheBit_RocketAnalyse->ComputeLocalAirDensity( ASL , System_US );
				//速度衰减系数
				double VAC = TheBit_RocketAnalyse->ComputeVelocityAttenuationCoefficient( RC , LAD , FA , Frag_Mass , System_US );
				//破片剩余速度
				ResidualVelocity = TheBit_RocketAnalyse->ComputeFragmentVelocityAttenuation( Frag_RealVelo , Frag_dis , VAC );
				//破片剩余速度写入破片数据结构
				TheBit_FragmentDataStructure[k].Set_FragmentResidualVelocity( ResidualVelocity );

				//判断破片对目标区域是否毁伤
				bool whetherDamage = TheBit_FragmentAnalyse->WhetherFragmentDamageAimArea( Frag_FragmentDamageCriterion , TheBit_FragmentDataStructure[k] );
				if ( whetherDamage == true )
				{
					IdOfMeeting[k] = TheBit_FragmentAnalyse->FragmentMeetWithArea( FragmentFlyLineInAim , TheBit_AimDataStructure , Bit_QMP );
					_line.FragAim = true;

					AimConvergenceID.push_back(IdOfMeeting[k]);
					it_GridUnit = UnitGridList.find(IdOfMeeting[k]);

					if (it_GridUnit != UnitGridList.end())
					{
						it_GridUnit->second.FragmentID.push_back(IdOfMeeting[k]);
						++it_GridUnit->second.FragmentsAmount;
						//////////////////////////根据破片个数确定单元毁伤等级
						it_GridUnit->second.DamageLevel = GetTheDamageLevel(it_GridUnit->second.FragmentsAmount);
					}

					HON[IdOfMeeting[k]] = 1;
					_AimFragmentLineList.push_back(_line);
				}
				else  //破片命中目标区域但不满足毁伤判据
				{
					_line.FragAim = false;
					_NDanamgeAimFragmentLineList.push_back(_line);
					IdOfMeeting[k] = -3;
				}
			}
			else  //破片与目标区域无交点
			{
				_line.FragAim = false;
				_NDanamgeAimFragmentLineList.push_back(_line);
				IdOfMeeting[k] = -2;
			}
		}
		else
		{
			_line.FragAim = false;
			_NAimFragmentLineList.push_back(_line);
			//破片与目标所在平面无交点，坐标被设置成( -1000000 , -1000000 , -1000000 )
			Frag_MeetingPoint[k] = CoordinatesPosition( -1000000 , -1000000 , -1000000 );

			IdOfMeeting[k] = -1;
		}
		//cout<<IdOfMeeting[k]<<endl;
	}
	delete []Frag_MeetingPoint;
	delete []TheBit_FragmentDataStructure;

	////冲击波作用
	////计数网格毁伤情况
	int EDONOfShockWave = 0;
	//建立计算需要的指针
	Bit_ShockWaveFieldAnalysis *SWFA = new Bit_ShockWaveFieldAnalysis( System_US );
	SpaceGeometry *SGT = new SpaceGeometry();
	Bit_PowerAnalysisBase *TheBit_PowerAnalysisBase = new Bit_PowerAnalysisBase( System_US );
	Bit_UnitsTransform *TheBit_UnitsTransform = new Bit_UnitsTransform();
	//带壳装药转化至裸露装药_System_US单位
	double ChargeEShell = TheBit_PowerAnalysisBase->ComputeChargeEquivalentMassWithShellOnWarD( 1 , RocketWarhead , RocketWarheadChargeData , 1 );
	//运动装药转化至静止_kg
	double ChargeStill = TheBit_PowerAnalysisBase->ComputeMotionChargeEquivalentMass_F1( ChargeEShell * System_US.Get_MassCoefficient() / 1000 ,
		TheBit_RocketDataStructure.Get_RocketVelocity() * TheBit_RocketDataStructure.Get_RocketUS().Get_VelocityCoefficient() * 1000 ,
		TheBit_UnitsTransform->EnergyGMmUsToKgMiS( RocketWarheadChargeData.Get_ExplosionHeatForC() ) );
	//计算TNT当量_kg
	double Charge_UnitI = TheBit_PowerAnalysisBase->ComputeTNTNLOnQv( ChargeStill ,
		TheBit_UnitsTransform->EnergyGMmUsToKgMiS( RocketWarheadChargeData.Get_ExplosionHeatForC() ) , 4479876 );
	//得到平面上单元
	Element_Surface_Quad *EIP = new Element_Surface_Quad[EN]();
	Bit_QMP.Get_ElementInPlane( EIP );
	//马赫反射临界角
	//double CAngleForMach = 0.22 * pi;
	double CAngleForMach = SWFA->ComputeMachReCriticalAngle( Charge_UnitI , BHE * System_US.Get_LengthCoefficient() / 1000 );
	//反射冲击波超压
	double RePressure = 0;
	//循环网格
	for ( int i = 0 ; i < EN ; i++ )
	{
		//计算每个网格第一个节点与爆心距离，并转化至国际单位制_m
		double DisFromHtoE = EIP[i].Get_Node_0().Get_NodeCoordinates().Distance( TheBit_AimDataStructure.Get_HitPosition() ) 
			* System_US.Get_LengthCoefficient() / 1000;
		//对比距离
		double ConstantD = SWFA->ComputeContrastDistance( Charge_UnitI , DisFromHtoE );
		//冲击波超压_MPa
		double ShockWaveP = SWFA->ComputeShockWavePressureOnCDis( 0.082 , 0.265 , 0.686 , 0 , 0 , 100000000 , ConstantD );
		//计算炸点与单元区域第一个节点连线与目标区域平面夹角，确定是否发生马赫反射
		//炸点与单元区域第一个节点连线方向向量
		CoordinatesPosition HAndEVector = CoordinatesPosition( ( EIP[i].Get_Node_0().Get_x() - TheBit_AimDataStructure.Get_HitPosition().Get_x() ) ,
			( EIP[i].Get_Node_0().Get_y() - TheBit_AimDataStructure.Get_HitPosition().Get_y() ) ,
			( EIP[i].Get_Node_0().Get_z() - TheBit_AimDataStructure.Get_HitPosition().Get_z() ) );
		//直线与平面夹角（锐角）
		double LAngleWithP = pi / 2 - SGT->AcuteAngleInTwoVetor( HAndEVector , CoordinatesPosition( 0 , 0 , 1 ) );
		if ( LAngleWithP < CAngleForMach || abs( LAngleWithP - CAngleForMach ) < 0.00000001 )
		{
			//发生正规斜反射
			//反射冲击波超压_MPa
			RePressure = SWFA->ComputeRegularObliqueReflectionPressure( 0.1 , LAngleWithP , ShockWaveP , 1.4 );
		} 
		else
		{
			//发生马赫反射
			//反射冲击波超压_MPa
			RePressure = SWFA->ComputeMachReflectionPressure( ShockWaveP , LAngleWithP );
		}
		////正压区作用时间_s
		//double PressureTimeP = 0.0015 * pow( DisFromHtoE[i] , -0.5 ) * pow( Charge_UnitI , -1.0/3.0 );

		//判断超压、反射超压，正压区作用时间是否达到毁伤判据
		if ( ShockWaveP > _RockObject.ShockWavePressure || RePressure > _RockObject.ShockWavePressure )
			//if ( ( ShockWaveP > 0.02 || RePressure > 0.02 ) && ( PressureTimeP > 0.01 ) )
		{
			//达到毁伤判据
			//EDONOfShockWave = EDONOfShockWave + 1;
			//网格对应的计量毁伤单位为1
			std::map<int,GridUnit>::iterator  it = UnitGridList.find(i);
			it->second.ShackDamageLevel = 1;
			HON[i] = 1;
		}
	}
	////cout<<EDONOfShockWave<<endl;

	//建立弹体坐标系（给显示）
	CoordinatesPosition Rocket_Origin = TheBit_AimDataStructure.Get_HitPosition();
	CoordinatesPosition Rocket_Vx = AimPWithCEP - TheBit_AimDataStructure.Get_HitPosition();

	double PitchAngle_ =  Rock_PitchingAngle_HuDu;   //俯仰

	//计算航向角
	double _lat = _RockObject.FireLat - _RockObject.AimLat;
	double _lon = _RockObject.FireLon - _RockObject.AimLon;
	double YawAngle_(0);
	if (_lat*_lon > 0)
	{
		YawAngle_ = osg::PI+std::atan(Rocket_Vx.Get_y()/Rocket_Vx.Get_x()); //偏航
	}
	else if (_lat*_lon <= 0)
	{
		YawAngle_ = std::atan(Rocket_Vx.Get_y()/Rocket_Vx.Get_x()); //偏航
	}
	

	//如果落角为0度，炸点坐标与落角90度相同，需将弹体坐标系X轴调整至水平
	if ( abs(TheBit_RocketDataStructure.Get_RocketPitchingAngle()) < 0.00000001 )
	{
		Rocket_Vx = CoordinatesPosition( 1 , 0 , 0 );
	}
	//CoordinatesPosition Rocket_Vy = CoordinatesPosition( 0 , 1 , 0 );
	//CoordinateSystem CS_2( 1 , Rocket_Origin , Rocket_Vx , Rocket_Vy );
	//Bit_CSWithExpAndUS Rocket_CSWithExpAndUS = Bit_CSWithExpAndUS( 2 , "弹体坐标系" , CS_2 , 
	//	"弹体坐标系的原点O为火箭弹质心。x轴为弹体外壳对称轴，指向火箭弹头部；y轴在火箭弹主对称面内垂直于x轴；z轴垂直于主对称面，顺着发射方向看过去，指向右方，构成右手坐标系。" ,
	//	System_US );

	//创建网格单元
	CoordinatesPosition CenterPoint(0,0,0);
	osg::Vec3 RotateAngle(0,0,osg::PI_2);
	std::string Aim = "Aim_";
	BulidCoordinate(RootScene,CenterPoint,RotateAngle,Aim); 
	BulidAimZoonGrid(RootScene,&TheBit_AimDataStructure,UnitGridList);
	////弹体
	osg::Vec3f RotateAngle_(0.0,PitchAngle_,YawAngle_);
	std::string Rock = "Rock_";
	BulidCoordinate(RootScene,TheBit_AimDataStructure.Get_HitPosition(),RotateAngle_,Rock);
	BulidProjectile(RootScene,RocketWarhead,TheBit_AimDataStructure.Get_HitPosition(),RotateAngle_);
	////碎片线
	BulidFragmentAimLineYDamage(RootScene,_AimFragmentLineList,TheBit_AimDataStructure.Get_HitPosition());
	BulidFragmentAimLineNoAttack(RootScene,_NAimFragmentLineList,TheBit_AimDataStructure.Get_HitPosition());
	BulidFragmentAimLineNoDamage(RootScene,_NDanamgeAimFragmentLineList,TheBit_AimDataStructure.Get_HitPosition());
	/*_pViewWidget = new ViewerWidget(RootScene);
	_pViewWidget->setAttribute(Qt::WA_TranslucentBackground, true);
	connect(_pViewWidget,SIGNAL(SendLevelAndColor(int,QColor)),this,SLOT(GetChangeLevelColor(int,QColor)));*/

	//毁伤面积计算
	DamageArea = (AimConvergenceID.size()-1)*Length_N_02*Length_N_13;

	//循环计算有破片命中且达到毁伤判据的网格数量
	for ( int q = 0 ; q < EN ; q++ )
	{
		if ( HON[q] == 1 )
		{
			DamaA = DamaA + 1;
		}
	}

	//目标区域总面积
	double AR = Aim_Wide* Aim_Long;
	//被毁伤区域总面积
	  DamageArea = DamaA * TheBit_AimDataStructure.Get_N_02() * TheBit_AimDataStructure.Get_N_13();
	//计算毁伤幅员
	  MassiveData =  DamageArea/AR;

	delete [] FireDistance;
	delete [] FallingAngle;
}
//获取单位系统设置
void OperationDisplay::GetUnitSeting(Bit_UnitSystem &unit)
{
	this->_UnitSystem = unit;
}
//获取火箭参数设置
void OperationDisplay::GetRockSeting(LGRockParameter& _object)
{
	_RockObject = _object;
}
//获取目标区域参数设置
void OperationDisplay::GetAreaZoneSeting(TargetAreaParameter& _object)
{
	_TargetArea = _object;
}
//获取更改等级的颜色
void OperationDisplay::GetChangeLevelColor(int Level,QColor pColor)
{
	int i = Level;
	QColor _p = pColor;
	float r,g,b;
	r = _p.red()/256.f;
	g = _p.green()/256.f;
	b = _p.blue()/256.f;

	_listColor.at(i-1).set(r,g,b,1.0);

	std::multimap<int,osg::Geometry*>::iterator _it = _listGeometry.begin();
	for (;_it != _listGeometry.end();++_it)
	{
		if (_it->first == Level)
		{
			osg::Geometry* _pp = _it->second;
			osg::Vec4Array *colorArray = (osg::Vec4Array*)(_pp->getColorArray());  
			if (colorArray)  
			{   
				(*colorArray)[0].set(r,g,b,1.0); 
				colorArray->dirty();
			}  
		}
	}
}
//返回毁伤面积
double OperationDisplay::GetDamageAreaData() const
{
	return DamageArea;
}
//
osg::Group* OperationDisplay::GetTheRootGroup()
{
	return RootScene;
}
//
double OperationDisplay::GetMassive() const
{
	return MassiveData;
}
//
void OperationDisplay::SetContrlType(int Itype)
{
	std::vector<LineUpDataCallBack*>::iterator it_ =  NodeCallBackVec.begin();
	for (; it_ != NodeCallBackVec.end();++it_)
	{
		(*it_)->ControlCall(Itype);
	}
	std::vector<ShockWaveCallBack*>::iterator it_Sh =  ShockWaveCallBackVec.begin();
	for (; it_Sh != ShockWaveCallBackVec.end();++it_Sh)
	{
		(*it_Sh)->ControlCall(Itype);
	}
};
//
void OperationDisplay::GetViewerWidget(ViewerWidget* pv)
{

};
//
ThreadRcokArea::ThreadRcokArea()
{
	pDialog = NULL;
	FunB = false;
	stopped = false;
};
//
ThreadRcokArea::~ThreadRcokArea()
{

};
void ThreadRcokArea::SetOperationDisplay(OperationDisplay *p)
{
	pDialog = p;
}
//
void ThreadRcokArea::run()
{
	if (!stopped)
	{
		if (pDialog != NULL)
		{
			pDialog->GetViewerWidget();
			stopped = true;
			FunB = true;
			emit EmitFuncOK(FunB);
		}
	}
};
//
bool ThreadRcokArea::GetFunc()
{
	return FunB;
};
//
void ThreadRcokArea::stop()
{
	stopped = true;
}