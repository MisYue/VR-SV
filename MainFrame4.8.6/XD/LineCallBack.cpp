#include "LineCallBack.h"
void LineUpDataCallBack::update(osg::NodeVisitor* nv, osg::Drawable* drawable)
{
	if (conType == 1)
	{
		osg::Geometry *geometry = dynamic_cast<osg::Geometry*>(drawable);  
		if (geometry)
		{
			if (LoopTimes <= 500)
			{
				    ++LoopTimes;
					//总体区域网格
				    int i = 0; 
					osg::Vec3Array *ScatteredVertexArray = dynamic_cast<osg::Vec3Array*>(geometry->getVertexArray()); 
					std::vector<FragMentLine>::iterator it_ =  p_AimFragmeList.begin();
					for (;it_ != p_AimFragmeList.end();++it_)
					{
						(*ScatteredVertexArray)[i].set(it_->_PosBegin.Get_x(),it_->_PosBegin.Get_y(),it_->_PosBegin.Get_z());
						(*ScatteredVertexArray)[i++].set(it_->_PosBegin.Get_x()+it_->_PosV.Get_x()*LoopTimes,it_->_PosBegin.Get_y()+it_->_PosV.Get_y()*LoopTimes,it_->_PosBegin.Get_z()+it_->_PosV.Get_z()*LoopTimes);
						i++;
					}
					ScatteredVertexArray->dirty();
			}
		}
	}
}
//
void LineUpDataCallBack::ControlCall(int i_conType)
{
	conType = i_conType;
	if (conType == 3)
	{
		LoopTimes = 0;
	}
}
//
void ShockWaveCallBack::operator()(osg::Node* node,osg::NodeVisitor *nv)
{
	if (conType == 1)
	{
		osg::MatrixTransform* pmat = dynamic_cast<osg::MatrixTransform*>(node);
		if (pmat)
		{
			if (LoopTimes <= 480)
			{
				LoopTimes += 1;
					int a = pmat->getNumChildren();
					for (int i = 1; i < a;++i)
					{
						osg::Node*_ll = pmat->getChild(i);
						if (_ll->getName() == "ShackWaveNode")
						{
							pmat->removeChild(_ll);
							break;
						}
					}
					osg::Geode *triangleGeode = new osg::Geode;
					osg::ShapeDrawable *SphereDrawable = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(p_HitPostion.Get_x(),p_HitPostion.Get_y(),p_HitPostion.Get_z()), LoopTimes));  
					 SphereDrawable->setCullingActive(false);

					SphereDrawable->setColor( osg::Vec4(0.0f, 0.0f, 0.0f, 0.2f) );   // alpha value  

					osg::StateSet* stateset = SphereDrawable->getOrCreateStateSet();  

					osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();  // blend func      
					blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);         
					blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);          
					stateset->setAttributeAndModes( blendFunc );  
					stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);  

					triangleGeode->setName("ShackWaveNode");
					triangleGeode->addDrawable(SphereDrawable);
					pmat->addChild(triangleGeode);  
			}
		}
		traverse(node,nv);
	}
}
//
void ShockWaveCallBack::ControlCall(int i_conType)
{
	conType = i_conType;

	if (conType == 3)
	{
		LoopTimes = 0;
	}
}