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
//����Ŀ������
void OperationDisplay::BulidAimZoonGrid(osg::Group *root,Bit_AimDataStructure *AimLine,std::map<int,GridUnit> &ElementQuadList)
{
	osg::MatrixTransform *triangleMT = new osg::MatrixTransform;  
	triangleMT->setMatrix(osg::Matrix::translate(0.0, 0.0, 0.0));
	triangleMT->setName("AimMT"); 
	//������������
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
	//�ָ�����
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
//��������ϵ
void OperationDisplay::BulidCoordinate(osg::Group *root,CoordinatesPosition centerPoint,osg::Vec3 RotateAngle,std::string Ctype)
{
	double LengthAxis = 0;
	double TSize = 4.0;
	
	//���������ε�ƽ��(glTranslate)  
	osg::MatrixTransform *triangleMT_ = new osg::MatrixTransform; 

	if (Ctype == "Rock_")
	{
		TSize = 1.5;
		LengthAxis = 60.0;
		
		osg::Matrix matrix_yaw = osg::Matrix::rotate(RotateAngle[2],osg::Z_AXIS); //�����

		osg::Vec3f _vY(0.0,1.0,0.0);
		_vY = matrix_yaw*_vY;
		_vY.set(-_vY.x(),_vY.y(),_vY.z());

		osg::Matrix matrix_pitch = osg::Matrix::rotate(RotateAngle[1],_vY);//������

		triangleMT_->setMatrix(matrix_yaw*matrix_pitch*osg::Matrix::translate(osg::Vec3d(centerPoint.Get_x(),centerPoint.Get_y(),centerPoint.Get_z())));
	}
	else if (Ctype == "Aim_")
	{
		LengthAxis = AxisLength;
		triangleMT_->setMatrix(osg::Matrix::rotate(RotateAngle.x(),osg::X_AXIS,RotateAngle.y(),osg::Y_AXIS,RotateAngle.z(),osg::Z_AXIS)*osg::Matrix::translate(osg::Vec3d(centerPoint.Get_x(),centerPoint.Get_y(),centerPoint.Get_z()))); 
	}
	osg::ref_ptr<osgText::Font> font = osgText::readFontFile( "fonts/arial.ttf" );

	//��������ϵ��
	osg::Geometry *Xaxis_Geometry = new osg::Geometry;  
	osg::Geometry *Yaxis_Geometry = new osg::Geometry;
	osg::Geometry *Zaxis_Geometry = new osg::Geometry;


	//����������� 
	//X��
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

	//Y��
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

	//Z��
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

	//����X����ɫ  
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

	//�رչ���  
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
//��������
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
	
	osg::Matrix matrix_yaw = osg::Matrix::rotate(RotateAngle[2],osg::Z_AXIS); //�����
	osg::Vec3f _vY(0.0,1.0,0.0);
	_vY = matrix_yaw*_vY;
	_vY.set(-_vY.x(),_vY.y(),_vY.z());
	osg::Matrix matrix_pitch = osg::Matrix::rotate(RotateAngle[1],_vY);//������
	zoomMT_->setMatrix(matrix*matrix_yaw*matrix_pitch*osg::Matrix::translate(osg::Vec3d(Frag_HitPosition.Get_x(),Frag_HitPosition.Get_y(),Frag_HitPosition.Get_z())));
	zoomMT->setMatrix(matrix*matrix_yaw*matrix_pitch*osg::Matrix::translate(osg::Vec3d(Frag_HitPosition.Get_x(),Frag_HitPosition.Get_y(),Frag_HitPosition.Get_z())));

	//zoomMT_->setMatrix(osg::Matrix::rotate(RotateAngle.z(),osg::Z_AXIS,RotateAngle.y(),osg::Y_AXIS,RotateAngle.x(),osg::X_AXIS)*osg::Matrix::translate(Frag_HitPosition.Get_x(),Frag_HitPosition.Get_y(),Frag_HitPosition.Get_z()));
	root->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON); 
	root->addChild(zoomMT);
	zoomMT_->setNodeMask(0x00);
	root->addChild(zoomMT_);
};
//������Ƭ�����ߣ�û��ֹͣ
void OperationDisplay::BulidFragmentLine(osg::Group *root,CoordinatesPosition _p1,CoordinatesPosition _p2)
{
	//���������ε�ƽ��(glTranslate)  
	osg::MatrixTransform *triangleMT = new osg::MatrixTransform;  
	osg::ref_ptr<osgText::Font> font = osgText::readFontFile( "fonts/arial.ttf" );

	//��������ϵ��
	osg::Geometry *Xaxis_Geometry = new osg::Geometry;  


	//����������� 
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

	//����X����ɫ  
	osg::Vec4Array *RadColorArray = new osg::Vec4Array;  
	RadColorArray->push_back(osg::Vec4(1.0,0.0,0.0,1.0));
	Xaxis_Geometry->setColorArray(RadColorArray);  
	Xaxis_Geometry->setColorBinding(osg::Geometry::BIND_OVERALL);  


	Xaxis_Geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));


	osg::Geode *triangleGeode = new osg::Geode;  

	//�رչ���  
	triangleGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);  
	triangleGeode->addDrawable(Xaxis_Geometry);  
	triangleGeode->addDrawable(text_x);
	triangleMT->addChild(triangleGeode);  

	root->addChild(triangleMT);   
};
//������Ƭ��������Ŀ�꽻��
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
//������Ƭ��������δĿ�꽻��
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
//������Ƭ��������Ŀ�꽻�㣬��δ�л���Ч��
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
//��ȡ���˵ȼ�
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
//��ȡĿ��������ɫ
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
//�������
void OperationDisplay::InitPlotShrapnelLine()
{
	//�����洢�����������
	int DamaA = 0;

	std::vector<FragMentLine> _AimFragmentLineList;
	std::vector<FragMentLine> _NDanamgeAimFragmentLineList;
	std::vector<FragMentLine> _NAimFragmentLineList;


	std::vector<int> AimConvergenceID;
	std::map<int,GridUnit> UnitGridList;

	//����ϵͳ��λ��
	Bit_UnitSystem System_US = Bit_UnitSystem( _UnitSystem.Get_LengthUnit() , _UnitSystem.Get_MassUnit() , _UnitSystem.Get_TimeUnit() );
	//����ָ�����,���ں�������
	Bit_FragmentAnalyse *TheBit_FragmentAnalyse = new Bit_FragmentAnalyse( System_US );
	Bit_RocketAnalyse *TheBit_RocketAnalyse = new Bit_RocketAnalyse( System_US );


	//�����������ϵ
	CoordinatesPosition Earth_Origin = CoordinatesPosition( 0 , 0 , 0 );
	CoordinatesPosition Earth_V1 = CoordinatesPosition( 1 , 0 , 0 );
	CoordinatesPosition Earth_V2 = CoordinatesPosition( 0 , 1 , 0 );
	CoordinateSystem CS_0( 1 , Earth_Origin , Earth_V1 , Earth_V2 );
	Bit_CSWithExpAndUS Earth_CSWithExpAndUS = Bit_CSWithExpAndUS( 0 , "�������ϵ" , CS_0 , 
		"ԭ��Ϊ���ģ�X���ڳ��ƽ���뱾�������潻���ϣ�z���ؼ��᷽��y���ڳ��ƽ������x�ᡢz�������ֱ������ϵ" , System_US );
	//����Ŀ������ϵ
	CoordinatesPosition Aim_Origin = CoordinatesPosition( 0 , 0 , 0 );
	CoordinatesPosition Aim_V1 = CoordinatesPosition( 1 , 0 , 0 );
	CoordinatesPosition Aim_V2 = CoordinatesPosition( 0 , 1 , 0 );
	CoordinateSystem CS_1( 1 , Aim_Origin , Aim_V1 , Aim_V2 );
	Bit_CSWithExpAndUS Aim_CSWithExpAndUS = Bit_CSWithExpAndUS( 1 , "Ŀ������ϵ" , CS_1 , 
		"ԭ��ΪĿ��Ⱥ�������ģ�����Ŀ��ȺΪ������������Σ���x��y��ֱ�ƽ����Ŀ��Ⱥ�߽磬z�ᰴ��������ϵ��ֱ����" , System_US );

	//����Ŀ�����ݽṹ
	//��ʼ��ը�����꣨0,0,0������������õ�����Set����д�����ݽṹ
	CoordinatesPosition Aim_HitPosition( 0 , 0 , 0 );
	//������׼������(�ݶ���׼��ΪĿ�����ĵ�)
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
	//����Bit_QuadMeshPlane���󣬴洢���������Ŀ��������Ϣ
	Bit_QuadMeshPlane Bit_QMP = Bit_QuadMeshPlane();


	Bit_AimDataStructure TheBit_AimDataStructure = Bit_AimDataStructure( Aim_id , Aim_HitPosition , Aim_Long , Aim_Wide ,
		FirstNodeAfterDevide , FristElementAfterDevide , Length_N_02 , Length_N_13 , AimCenterPointLat , AimCenterPointLon , AimP );
	//��Ŀ�����򻮷�����
	TheBit_FragmentAnalyse->AreaDividing( TheBit_AimDataStructure , Bit_QMP );

	//������������ݽṹ
	//�����������Ϣ��ʼ��
	int Rock_Id = 1;
	double Rock_WarheadStaticAngle = _RockObject.Rock_WarheadStaticAngle/*1.0*/ , Rock_WarheadStaticAngleToCenter = _RockObject.Rock_WarheadStaticAngleToCenter/*1.0*/ , Rock_RocketVelocity = _RockObject.Rock_RocketVelocity/*300*/;
	//������̱����Բ�ֵ�õ���ǣ�������������ǣ�����
	HAE_HitPointAnalysis *TheHAE_HitPointAnalysis = new HAE_HitPointAnalysis();
	//���÷���㾭γ�ȣ��ӽ����ã�
	double FireLat = _RockObject.FireLat , FireLon = _RockObject.FireLon;
	//���ò�ֵ�����ݸ���
	int InterpolationNumber = _RockObject.InterpolationNumber;
	//������̲�ֵ������
	double *FireDistance = new double[InterpolationNumber];
	double *FallingAngle = new double[InterpolationNumber];
	for (int i = 0; i < InterpolationNumber;++i)
	{
		FireDistance[i] = _RockObject.FireDistance.at(i);
		FallingAngle[i] = _RockObject.FallingAngle.at(i);
	}


	//double FireDistance[8] = { 1000,2000,4000,5000,7000,8000,10000,20000 };
	////������ǲ�ֵ������
	//double FallingAngle[8] = { 10,12,20,30,35,38,40,42 };
	AdvancedMath *Compute = new AdvancedMath();
	double Rock_PitchingAngle_JiaoDu = TheHAE_HitPointAnalysis->ComputeFallAngleOnLoLA_Table( FireLon , FireLat , TheBit_AimDataStructure.Get_AimLon() , TheBit_AimDataStructure.Get_AimLat() ,
		InterpolationNumber , FireDistance , FallingAngle );
	double Rock_PitchingAngle_HuDu = Compute->AngleToRadian( Rock_PitchingAngle_JiaoDu );
	delete Compute;
	delete TheHAE_HitPointAnalysis;
	//���ݵ������㾭γ�ȼ������㷽λ�ǣ��������ƫ����

	CoordinatesPosition *CPCompute = new CoordinatesPosition();
	double Rock_YawAngle = CPCompute->AzimuthFromLongitudeAndLatitude(6378137 , 6356752.314 , FireLon , FireLat , TheBit_AimDataStructure.Get_AimLon() , TheBit_AimDataStructure.Get_AimLat() );
	//���û����CEP
	double Rock_CEP = _RockObject.Rock_CEP;//5;
	Bit_RocketDataStructure TheBit_RocketDataStructure = Bit_RocketDataStructure( Rock_Id , System_US , Rock_PitchingAngle_HuDu , Rock_YawAngle ,
		Rock_WarheadStaticAngle , Rock_WarheadStaticAngleToCenter , Rock_RocketVelocity , Rock_CEP );

	//����ը�����꣨�ڻ�������ݽṹ����������û�������ݽṹ��
	//����ը��������ը�߱�׼��
	double BHE = _RockObject.BHE/*20*/ , BHD = _RockObject.BHD/*0.2*/;
	//����CEP����׼����Ŀ��ϵ������
	CoordinatesPosition AimPWithCEP = TheBit_RocketAnalyse->AimPointInAim( TheBit_AimDataStructure.Get_AimPoint() , TheBit_RocketDataStructure );
	//ը������
	Aim_HitPosition = TheBit_RocketAnalyse->BurstPoint( AimPWithCEP , BHE , BHD , TheBit_RocketDataStructure );
	TheBit_AimDataStructure.Set_HitPosition( Aim_HitPosition );

	//��Ƭ����Ϣ��ʼ��
	//��Ƭ����
	int FragmentNumber = _RockObject.FragmentNumber;//300;
	//��ö��Ƭ���ݽṹ��ʼ��ַ
	Bit_FragmentDataStructure *TheBit_FragmentDataStructure = new Bit_FragmentDataStructure [FragmentNumber]();
	//Bit_FragmentDataStructureForAll TheBit_FragmentDataStructureForAll = Bit_FragmentDataStructureForAll ( FragmentNumber , TheBit_FragmentDataStructure );
	//������Ƭ����
	ChargeData RocketWarheadChargeData = ChargeData( 0 , System_US , _RockObject.Density /*1680*/, _RockObject.ExplosionVelocity/*7000*/, _RockObject.ExplosionHeat/*4e7*/ ,_RockObject.ExplosinPressure/*24e9*/ );
	WarheadPowerAnalysisData RocketWarhead = WarheadPowerAnalysisData( 0 , System_US ,_RockObject.ShellMass_Clylinder/*100*/ ,_RockObject.ChargeMass_Clylinder/*50*/, _RockObject.AllMass_Whole/*180*/ , _RockObject.ChargeMass_Whole/*60*/ , RocketWarheadChargeData.Get_ChargeId() , 1 , _RockObject.ShellInterDiameter/*2.0M*/ , _RockObject.ShellOuterDiameter/*2.20M*/ , _RockObject.ShellBrokenDiameter/*2.5M*/ ,_RockObject.WarheadLength_Whole/*3*/ , _RockObject.WarheadLength_Clylinder/*3*/ );//ֻ�ò��ֲ�����ShellMass_Clylinder��ChargeMass_Clylinder,WarheadLength_Whole��
	double Frag_Vel = TheBit_RocketAnalyse->ComputeFragmentVelocityViaGurney( RocketWarhead , RocketWarheadChargeData , System_US );
	ProbabilityAndRandom *PAR = new ProbabilityAndRandom();
	//�������ȷֲ���������������ڼ��㶯̬�����
	double *RandomForUniformDistribution = new double[FragmentNumber]();
	bool Ran_TOF = PAR->SampleOnSampleNumber( FragmentNumber , RandomForUniformDistribution );
	//��̬�ֲ��������㾲̬�����
	double *Frag_StaticDirectionalAngle_Initialization = new double[FragmentNumber]();
	TheBit_FragmentAnalyse->FragmentDirectionalAngle( TheBit_RocketDataStructure , FragmentNumber , Frag_StaticDirectionalAngle_Initialization );
	//��ʼ����Ƭ��̬��ɢ�ǣ�0��;��Ƭ��ɢ���루10000����ȷ����Ƭ���з���,�ȼ�����Ƭ�������ٶ�˥������������򽻵�;
	//��Ƭ������5���������ɳ����������
	double Frag_SDA = 0, Frag_dis = 10000, Frag_Mass = _RockObject.Frag_Mass /*5*/, Frag_ResidualVelocity_Initialization = 0;
	//��ʼ����Ƭ���ݽṹ
	for( int i = 0 ; i < FragmentNumber ; i++ )
	{
		//��ƬId
		TheBit_FragmentDataStructure[i].Set_FragmentID( i + 1 );
		//��Ƭ��λϵ
		TheBit_FragmentDataStructure[i].Set_FragmentUS( System_US );
		//��Ƭ����
		TheBit_FragmentDataStructure[i].Set_Mass( Frag_Mass );
		//��Ƭ����
		TheBit_FragmentDataStructure[i].Set_FragmentVelocity( Frag_Vel );
		//��Ƭ���о���
		TheBit_FragmentDataStructure[i].Set_FlyDistance( Frag_dis );
		//ÿ����Ƭ��̬��ɢ��
		TheBit_FragmentDataStructure[i].Set_StaticDisporaAngle( Frag_SDA );
		TheBit_FragmentDataStructure[i].Set_DynamicCircleAngle( 2 * pi * RandomForUniformDistribution[i] );
		//��̬�ֲ������õ�ÿ����Ƭ��̬�����
		TheBit_FragmentDataStructure[i].Set_StaticDirectonalAngle( Frag_StaticDirectionalAngle_Initialization[i] );
		//ÿ����Ƭ��̬��ɢ�ٶȣ�ʵ���ٶȣ�(�����⣺TheBit_FragmentDataStructure[i]���ڳ�ʼ�����������Ƭ���ٱ���������֮ǰ��ʼ�����)
		double Frag_FragmentRealVelocity__Initialization = TheBit_FragmentAnalyse->FragmentRealVelocity( TheBit_FragmentDataStructure[i] , TheBit_RocketDataStructure );
		TheBit_FragmentDataStructure[i].Set_FragmentDynamicVelocity( Frag_FragmentRealVelocity__Initialization );
		//ÿ����Ƭ��̬�����
		double Frag_DynamicDirectionalAngle__Initialization = TheBit_FragmentAnalyse->FragmentDynamicDirectionalAngle( TheBit_FragmentDataStructure[i] , TheBit_RocketDataStructure );
		TheBit_FragmentDataStructure[i].Set_DynamicDirectionalAngle( Frag_DynamicDirectionalAngle__Initialization );
		//ÿ����Ƭ�ڵ�������ϵ������(�����⣺TheBit_FragmentDataStructure[i]���ڳ�ʼ�����������Ƭ���о������������֮ǰ��ʼ�����)
		CoordinatesPosition Frag_FragmentPositionInRocketCoordinate__Initialization = 
			TheBit_FragmentAnalyse->ComputeFragmentCoordinateInBodyCoordinate( TheBit_FragmentDataStructure[i] );
		TheBit_FragmentDataStructure[i].Set_FragmentPositionInRocketCoordinate( Frag_FragmentPositionInRocketCoordinate__Initialization );
		//ÿ����Ƭʣ���ٶȣ���ʼ��Ϊ0��
		TheBit_FragmentDataStructure[i].Set_FragmentResidualVelocity( Frag_ResidualVelocity_Initialization );
	}
	delete PAR;
	delete []RandomForUniformDistribution;
	delete []Frag_StaticDirectionalAngle_Initialization;

	//������Ƭ�ٶ�˥�����������ʼ��_�õ���Ƭʣ���ٶ�
	double SC = _RockObject.SC;//0.00307;//������Ƭ
	double ASL = _RockObject.ASL/*15*/ , RC = _RockObject.RC/*0.97*/;
	//������Ƭ�ٶ�˥��
	//�����洢��Ƭ��Ŀ�����򽻵�CoordinatesPosition����
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
	//������̬���飬�洢ÿ����Ƭ��Ŀ���������񽻻��Id��
	int *IdOfMeeting = new int[FragmentNumber]();
	std::map<int,GridUnit>::iterator it_GridUnit;


	//�����洢��Ƭ�Ƿ���������̬���飨�ĳ�������
	//��������
	int EN = Bit_QMP.Get_ElementNumber();
	int *HON = new int[EN]();
	for (int k = 0 ; k < EN ; k++ )
	{
		HON[k] = 0;
	}

	//��Ƭʣ���ٶȳ�ʼ��
	double ResidualVelocity = 0;
	std::vector<int>::const_iterator _cItor;
	//������Ƭ�ٶ�˥������ϻ����о��ж���Ƭ�������ཻ������������
	for ( int k = 0 ; k < FragmentNumber ; k++ )
	{
		//��ȡ��Ƭ���й켣��(����Ŀ������ϵ)
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

		//�жϸ�ö��Ƭ�Ƿ���Ŀ������ƽ����ڽ���
		bool WhetherMeeting = TheBit_FragmentAnalyse->MeetingOrNot( FragmentFlyLineInAim , TheBit_AimDataStructure );
		//cout<<WhetherMeeting;
		if ( WhetherMeeting == true )
		{
			Frag_MeetingPoint[k] = TheBit_FragmentAnalyse->ComputeMeetingPointWithArea( FragmentFlyLineInAim , TheBit_AimDataStructure );

			//�жϽ����Ƿ���Ŀ������������
			if ( TheBit_FragmentAnalyse->InOrNot( FragmentFlyLineInAim , Bit_QMP) == true )
			{
				//��Ƭ���о���
				Frag_dis = Frag_MeetingPoint[k].Distance( TheBit_AimDataStructure.Get_HitPosition() );

				//������Ƭ�ٶ�˥��	
				//��Ƭ����
				double Frag_Mass = TheBit_FragmentDataStructure[k].Get_Mass();
				//��Ƭʵ���ٶȣ���̬��ɢ�ٶȣ�
				double Frag_RealVelo = TheBit_FragmentDataStructure[k].Get_FragmentDynamicVelocity();
				//��Ƭչ�����
				double FA = TheBit_RocketAnalyse->ComputeFragmentFrontalArea( SC , Frag_Mass , System_US );
				//���ؿ����ܶ�
				double LAD = TheBit_RocketAnalyse->ComputeLocalAirDensity( ASL , System_US );
				//�ٶ�˥��ϵ��
				double VAC = TheBit_RocketAnalyse->ComputeVelocityAttenuationCoefficient( RC , LAD , FA , Frag_Mass , System_US );
				//��Ƭʣ���ٶ�
				ResidualVelocity = TheBit_RocketAnalyse->ComputeFragmentVelocityAttenuation( Frag_RealVelo , Frag_dis , VAC );
				//��Ƭʣ���ٶ�д����Ƭ���ݽṹ
				TheBit_FragmentDataStructure[k].Set_FragmentResidualVelocity( ResidualVelocity );

				//�ж���Ƭ��Ŀ�������Ƿ����
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
						//////////////////////////������Ƭ����ȷ����Ԫ���˵ȼ�
						it_GridUnit->second.DamageLevel = GetTheDamageLevel(it_GridUnit->second.FragmentsAmount);
					}

					HON[IdOfMeeting[k]] = 1;
					_AimFragmentLineList.push_back(_line);
				}
				else  //��Ƭ����Ŀ�����򵫲���������о�
				{
					_line.FragAim = false;
					_NDanamgeAimFragmentLineList.push_back(_line);
					IdOfMeeting[k] = -3;
				}
			}
			else  //��Ƭ��Ŀ�������޽���
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
			//��Ƭ��Ŀ������ƽ���޽��㣬���걻���ó�( -1000000 , -1000000 , -1000000 )
			Frag_MeetingPoint[k] = CoordinatesPosition( -1000000 , -1000000 , -1000000 );

			IdOfMeeting[k] = -1;
		}
		//cout<<IdOfMeeting[k]<<endl;
	}
	delete []Frag_MeetingPoint;
	delete []TheBit_FragmentDataStructure;

	////���������
	////��������������
	int EDONOfShockWave = 0;
	//����������Ҫ��ָ��
	Bit_ShockWaveFieldAnalysis *SWFA = new Bit_ShockWaveFieldAnalysis( System_US );
	SpaceGeometry *SGT = new SpaceGeometry();
	Bit_PowerAnalysisBase *TheBit_PowerAnalysisBase = new Bit_PowerAnalysisBase( System_US );
	Bit_UnitsTransform *TheBit_UnitsTransform = new Bit_UnitsTransform();
	//����װҩת������¶װҩ_System_US��λ
	double ChargeEShell = TheBit_PowerAnalysisBase->ComputeChargeEquivalentMassWithShellOnWarD( 1 , RocketWarhead , RocketWarheadChargeData , 1 );
	//�˶�װҩת������ֹ_kg
	double ChargeStill = TheBit_PowerAnalysisBase->ComputeMotionChargeEquivalentMass_F1( ChargeEShell * System_US.Get_MassCoefficient() / 1000 ,
		TheBit_RocketDataStructure.Get_RocketVelocity() * TheBit_RocketDataStructure.Get_RocketUS().Get_VelocityCoefficient() * 1000 ,
		TheBit_UnitsTransform->EnergyGMmUsToKgMiS( RocketWarheadChargeData.Get_ExplosionHeatForC() ) );
	//����TNT����_kg
	double Charge_UnitI = TheBit_PowerAnalysisBase->ComputeTNTNLOnQv( ChargeStill ,
		TheBit_UnitsTransform->EnergyGMmUsToKgMiS( RocketWarheadChargeData.Get_ExplosionHeatForC() ) , 4479876 );
	//�õ�ƽ���ϵ�Ԫ
	Element_Surface_Quad *EIP = new Element_Surface_Quad[EN]();
	Bit_QMP.Get_ElementInPlane( EIP );
	//��շ����ٽ��
	//double CAngleForMach = 0.22 * pi;
	double CAngleForMach = SWFA->ComputeMachReCriticalAngle( Charge_UnitI , BHE * System_US.Get_LengthCoefficient() / 1000 );
	//����������ѹ
	double RePressure = 0;
	//ѭ������
	for ( int i = 0 ; i < EN ; i++ )
	{
		//����ÿ�������һ���ڵ��뱬�ľ��룬��ת�������ʵ�λ��_m
		double DisFromHtoE = EIP[i].Get_Node_0().Get_NodeCoordinates().Distance( TheBit_AimDataStructure.Get_HitPosition() ) 
			* System_US.Get_LengthCoefficient() / 1000;
		//�ԱȾ���
		double ConstantD = SWFA->ComputeContrastDistance( Charge_UnitI , DisFromHtoE );
		//�������ѹ_MPa
		double ShockWaveP = SWFA->ComputeShockWavePressureOnCDis( 0.082 , 0.265 , 0.686 , 0 , 0 , 100000000 , ConstantD );
		//����ը���뵥Ԫ�����һ���ڵ�������Ŀ������ƽ��нǣ�ȷ���Ƿ�����շ���
		//ը���뵥Ԫ�����һ���ڵ����߷�������
		CoordinatesPosition HAndEVector = CoordinatesPosition( ( EIP[i].Get_Node_0().Get_x() - TheBit_AimDataStructure.Get_HitPosition().Get_x() ) ,
			( EIP[i].Get_Node_0().Get_y() - TheBit_AimDataStructure.Get_HitPosition().Get_y() ) ,
			( EIP[i].Get_Node_0().Get_z() - TheBit_AimDataStructure.Get_HitPosition().Get_z() ) );
		//ֱ����ƽ��нǣ���ǣ�
		double LAngleWithP = pi / 2 - SGT->AcuteAngleInTwoVetor( HAndEVector , CoordinatesPosition( 0 , 0 , 1 ) );
		if ( LAngleWithP < CAngleForMach || abs( LAngleWithP - CAngleForMach ) < 0.00000001 )
		{
			//��������б����
			//����������ѹ_MPa
			RePressure = SWFA->ComputeRegularObliqueReflectionPressure( 0.1 , LAngleWithP , ShockWaveP , 1.4 );
		} 
		else
		{
			//������շ���
			//����������ѹ_MPa
			RePressure = SWFA->ComputeMachReflectionPressure( ShockWaveP , LAngleWithP );
		}
		////��ѹ������ʱ��_s
		//double PressureTimeP = 0.0015 * pow( DisFromHtoE[i] , -0.5 ) * pow( Charge_UnitI , -1.0/3.0 );

		//�жϳ�ѹ�����䳬ѹ����ѹ������ʱ���Ƿ�ﵽ�����о�
		if ( ShockWaveP > _RockObject.ShockWavePressure || RePressure > _RockObject.ShockWavePressure )
			//if ( ( ShockWaveP > 0.02 || RePressure > 0.02 ) && ( PressureTimeP > 0.01 ) )
		{
			//�ﵽ�����о�
			//EDONOfShockWave = EDONOfShockWave + 1;
			//�����Ӧ�ļ������˵�λΪ1
			std::map<int,GridUnit>::iterator  it = UnitGridList.find(i);
			it->second.ShackDamageLevel = 1;
			HON[i] = 1;
		}
	}
	////cout<<EDONOfShockWave<<endl;

	//������������ϵ������ʾ��
	CoordinatesPosition Rocket_Origin = TheBit_AimDataStructure.Get_HitPosition();
	CoordinatesPosition Rocket_Vx = AimPWithCEP - TheBit_AimDataStructure.Get_HitPosition();

	double PitchAngle_ =  Rock_PitchingAngle_HuDu;   //����

	//���㺽���
	double _lat = _RockObject.FireLat - _RockObject.AimLat;
	double _lon = _RockObject.FireLon - _RockObject.AimLon;
	double YawAngle_(0);
	if (_lat*_lon > 0)
	{
		YawAngle_ = osg::PI+std::atan(Rocket_Vx.Get_y()/Rocket_Vx.Get_x()); //ƫ��
	}
	else if (_lat*_lon <= 0)
	{
		YawAngle_ = std::atan(Rocket_Vx.Get_y()/Rocket_Vx.Get_x()); //ƫ��
	}
	

	//������Ϊ0�ȣ�ը�����������90����ͬ���轫��������ϵX�������ˮƽ
	if ( abs(TheBit_RocketDataStructure.Get_RocketPitchingAngle()) < 0.00000001 )
	{
		Rocket_Vx = CoordinatesPosition( 1 , 0 , 0 );
	}
	//CoordinatesPosition Rocket_Vy = CoordinatesPosition( 0 , 1 , 0 );
	//CoordinateSystem CS_2( 1 , Rocket_Origin , Rocket_Vx , Rocket_Vy );
	//Bit_CSWithExpAndUS Rocket_CSWithExpAndUS = Bit_CSWithExpAndUS( 2 , "��������ϵ" , CS_2 , 
	//	"��������ϵ��ԭ��OΪ��������ġ�x��Ϊ������ǶԳ��ᣬָ������ͷ����y���ڻ�������Գ����ڴ�ֱ��x�᣻z�ᴹֱ�����Գ��棬˳�ŷ��䷽�򿴹�ȥ��ָ���ҷ���������������ϵ��" ,
	//	System_US );

	//��������Ԫ
	CoordinatesPosition CenterPoint(0,0,0);
	osg::Vec3 RotateAngle(0,0,osg::PI_2);
	std::string Aim = "Aim_";
	BulidCoordinate(RootScene,CenterPoint,RotateAngle,Aim); 
	BulidAimZoonGrid(RootScene,&TheBit_AimDataStructure,UnitGridList);
	////����
	osg::Vec3f RotateAngle_(0.0,PitchAngle_,YawAngle_);
	std::string Rock = "Rock_";
	BulidCoordinate(RootScene,TheBit_AimDataStructure.Get_HitPosition(),RotateAngle_,Rock);
	BulidProjectile(RootScene,RocketWarhead,TheBit_AimDataStructure.Get_HitPosition(),RotateAngle_);
	////��Ƭ��
	BulidFragmentAimLineYDamage(RootScene,_AimFragmentLineList,TheBit_AimDataStructure.Get_HitPosition());
	BulidFragmentAimLineNoAttack(RootScene,_NAimFragmentLineList,TheBit_AimDataStructure.Get_HitPosition());
	BulidFragmentAimLineNoDamage(RootScene,_NDanamgeAimFragmentLineList,TheBit_AimDataStructure.Get_HitPosition());
	/*_pViewWidget = new ViewerWidget(RootScene);
	_pViewWidget->setAttribute(Qt::WA_TranslucentBackground, true);
	connect(_pViewWidget,SIGNAL(SendLevelAndColor(int,QColor)),this,SLOT(GetChangeLevelColor(int,QColor)));*/

	//�����������
	DamageArea = (AimConvergenceID.size()-1)*Length_N_02*Length_N_13;

	//ѭ����������Ƭ�����Ҵﵽ�����оݵ���������
	for ( int q = 0 ; q < EN ; q++ )
	{
		if ( HON[q] == 1 )
		{
			DamaA = DamaA + 1;
		}
	}

	//Ŀ�����������
	double AR = Aim_Wide* Aim_Long;
	//���������������
	  DamageArea = DamaA * TheBit_AimDataStructure.Get_N_02() * TheBit_AimDataStructure.Get_N_13();
	//������˷�Ա
	  MassiveData =  DamageArea/AR;

	delete [] FireDistance;
	delete [] FallingAngle;
}
//��ȡ��λϵͳ����
void OperationDisplay::GetUnitSeting(Bit_UnitSystem &unit)
{
	this->_UnitSystem = unit;
}
//��ȡ�����������
void OperationDisplay::GetRockSeting(LGRockParameter& _object)
{
	_RockObject = _object;
}
//��ȡĿ�������������
void OperationDisplay::GetAreaZoneSeting(TargetAreaParameter& _object)
{
	_TargetArea = _object;
}
//��ȡ���ĵȼ�����ɫ
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
//���ػ������
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