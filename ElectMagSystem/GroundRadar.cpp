#define VRSOFT_PLUGIN_EXPORT
#include <fstream>
#include <stdio.h>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>
#include <osg/FrontFace>
#include <osg/CullFace>
#include <osg/Depth>
#include <osgFX/Scribe>
#include <osgDB/ReadFile>

#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/ElectMagSystem/IRadar.h"
#include "RadarAttribute.h"
#include "GroundRadarAttribute.h"
#include "GroundRadar.h"

#include <osgEarth/MapNode>
#include <osgEarth/SpatialReference>
#include <osgEarthUtil/ExampleResources>
#include <osgEarthSymbology/Style>
#include <osgEarthAnnotation/ModelNode>
#include <osgEarthSymbology/IconSymbol>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthSymbology/LineSymbol>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthUtil/AnnotationEvents>
#include <osgEarthAnnotation/HighlightDecoration>

namespace VR_Soft
{
	class CTuren : public osg::NodeCallback
	{
	public:
		CTuren():m_angle(0.0)
		{

		}

		virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
		{
			osg::MatrixTransform* mt = dynamic_cast<osg::MatrixTransform*>(node);
			if (NULL == mt)
			{
				traverse(node, nv);
			}

			if ((m_angle += 1.0) >= 360.0f)
			{
				m_angle = 0.0f;
			}

			mt->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(m_angle), 0.0, 0.0, 1.0));

			traverse(node, nv);
		}

	private:
		float m_angle;
	};

	CGroundRadar::CGroundRadar(void):m_pMt(new osg::MatrixTransform)
	{
		
	}


	CGroundRadar::~CGroundRadar(void)
	{
		m_pGeode->removeDrawables(0, m_pGeode->getNumDrawables());
		 // 删除所有的子节点
		m_pMt->removeChild(0, m_pMt->getNumChildren());
		// 获得父类
		osg::Node::ParentList parentList = m_pMt->getParents();
		// 遍历节点从父类中删除自身
		for (osg::Node::ParentList::iterator itor = parentList.begin(); \
			parentList.end() != itor; ++itor)
		{
			(*itor)->removeChild(m_pMt);
		}

		//m_pMt = NULL;
	}

	// 获取渲染节点
	osg::Node* CGroundRadar::GetDrawObj(osgEarth::MapNode* pMapNode)
	{
		osgEarth::Symbology::Style style;
		style.getOrCreate<osgEarth::Symbology::ModelSymbol>()->setModel(m_pMt);
		m_pModelNode = new osgEarth::Annotation::ModelNode(pMapNode, style);

		m_pModelNode->setName(m_pMt->getName());
		return (m_pModelNode);
	} 

	// 获取渲染节点
	osg::Node* CGroundRadar::GetDrawObj(void)
	{
		return (m_pMt);
	} 

	// 获得类型
	const VRString CGroundRadar::GetEntityType(void) const
	{
		return ("GroundRadar");
	}

	// 设置名称
	void CGroundRadar::SetName(const VRString& strName)
	{
		IRadar::SetName(strName);
	}

	// 初始化
	void CGroundRadar::Init(void)
	{
		FILE *file = NULL;
		file = fopen("D:/GroundRadar.dat", "r");
		/*std::ifstream in("D:/GroundRadar.dat");
		if (!in.is_open())
		{
		return;
		}*/

		if (NULL == file)
		{
			return;
		}

		osg::Group* pRoot = new osg::Group;
		m_pMt->addChild(pRoot);

		osg::Vec2Array* vecData = new osg::Vec2Array;
		// 读取模型数据
 		while(!feof(file))
 		{
 			float x, y;
 			fscanf(file, "%f %f",&x, &y);//in >> x >> y;
 
 			y *= 10;
 			vecData->push_back(osg::Vec2(x, y));
 		}



		const int nCount = (int)vecData->size() / 2;

		{
			osg::MatrixTransform* mt = new osg::MatrixTransform;
			pRoot->addChild(mt);
			osg::Geode* geode = new osg::Geode;
			mt->addUpdateCallback(new CTuren);
			mt->addChild(geode);
			for (int index = 0; index < 6; ++index)
			{
				double dTheta = osg::DegreesToRadians(0.0 + index * 120.0f );

				osg::Vec3Array* verArray = new osg::Vec3Array;
				verArray->push_back(osg::Vec3(0.0, 0.0, 0.0));

				for (int anlge = 0; anlge < nCount; ++anlge)
				{
					const osg::Vec2 vec = vecData->at(anlge);
					const float x = vec.x();
					double phi = osg::DegreesToRadians(x);

					osg::Vec3 ver;
					ver.x() = vec.y() * cos(dTheta) * cos(phi);
					ver.y() = vec.y() * sin(dTheta) * cos(phi);
					ver.z() = vec.y() * sin(phi) * 3;
					verArray->push_back(ver);
				}

				osg::Geometry* pGeo = new osg::Geometry;
				pGeo->setVertexArray(verArray);
				osg::Vec4Array* colorArray = new osg::Vec4Array;
				colorArray->push_back(osg::Vec4(1.0, 0.0, 0.3, 0.7));
				pGeo->setColorArray(colorArray);
				pGeo->setColorBinding(osg::Geometry::BIND_OVERALL);

				pGeo->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_FAN, 0, verArray->size()));
				geode->addDrawable(pGeo);

				//pGeo->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
				pGeo->getOrCreateStateSet()->setRenderBinDetails(10, "DepthSortedBin");
				pGeo->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
				pGeo->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
				//pGeo->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
			}
		}

		int m_nNumSplit = 60;
		int nNumRows = m_nNumSplit + 1;
		int nNumCols = nCount + 2;
		int nNumVerts = nNumRows * nNumCols;

		osg::Vec3Array* boud = new osg::Vec3Array;

		osg::Vec3Array* boudNor = new osg::Vec3Array;

		const double dDeltaAngle = (360.0f)/m_nNumSplit;

		for (int row = 0; row < nNumRows; ++row)
		{
			double dTheta = osg::DegreesToRadians((float)row * dDeltaAngle);
			boud->push_back(osg::Vec3(0,0,0));
			for (int anlge = 0; anlge < nCount; ++anlge)
			{
				const osg::Vec2 vec = vecData->at(anlge);
				const float x = vec.x();
				double phi = osg::DegreesToRadians((float)x);

				osg::Vec3 ver;
				ver.x() = vec.y() * cos(dTheta) * cos(phi);
				ver.y() = vec.y() * sin(dTheta) * cos(phi);
				ver.z() = vec.y() * sin(phi) * 3;
				boud->push_back(ver);

				ver.y() = -ver.y();
				ver.normalize();
				boudNor->push_back(ver);
			}
			boud->push_back(osg::Vec3(0,0,0));
		}

		m_pGeode = new osg::Geode;
		osg::Geometry* pGeo = new osg::Geometry;

		pGeo->setUseDisplayList(true);
		pGeo->setUseVertexBufferObjects(true);

		osg::Vec4Array* colorArray = new osg::Vec4Array;
		colorArray->push_back(osg::Vec4(0.30, 1.0, 0.3, 0.3));
		pGeo->setColorArray(colorArray);
		pGeo->setColorBinding(osg::Geometry::BIND_OVERALL);

		pGeo->setNormalArray(boudNor);
		pGeo->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

		int nNumquads = (nNumRows - 1) * ( nNumCols -1);
		int nNumIndices = nNumquads * 4;

		osg::DrawElements* pDE = new osg::DrawElementsUShort(GL_QUADS);
		pDE->reserveElements(nNumIndices);
		for (int z = 0; z < nNumRows - 1 ; ++z)
		{
			for (int x = 0; x < nNumCols - 1 ; ++x)
			{
				int xstart = x + z * nNumCols;

				pDE->addElement(xstart);
				pDE->addElement(xstart + 1);
				pDE->addElement(xstart + nNumCols + 1);
				pDE->addElement(xstart + nNumCols);
			}
		}
		boud->setVertexBufferObject(new osg::VertexBufferObject);
		pDE->setElementBufferObject(new osg::ElementBufferObject);

		osgUtil::SmoothingVisitor::smooth(*pGeo);

		pGeo->addPrimitiveSet(pDE);
		pGeo->setVertexArray(boud);
		// 
		pGeo->getOrCreateStateSet()->setAttributeAndModes(new osg::CullFace(osg::CullFace::FRONT), \
			osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
		pGeo->getOrCreateStateSet()->setAttributeAndModes(new osg::FrontFace(osg::FrontFace::COUNTER_CLOCKWISE));

		m_pGeode->addDrawable(pGeo);
		osg::Depth* pDepth = new osg::Depth;
		pDepth->setWriteMask(false);
		m_pGeode->getOrCreateStateSet()->setAttributeAndModes(pDepth, osg::StateAttribute::ON);

		pGeo->getOrCreateStateSet()->setRenderBinDetails(11, "DepthSortedBin");
		pGeo->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		pGeo->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

		pRoot->addChild(m_pGeode);

		DrawFx();
	}

	void CGroundRadar::DrawFx(void)
	{
		osgFX::Scribe* ps = new osgFX::Scribe;
		ps->addChild(m_pGeode);
		m_pMt->addChild(ps);
	}

	// 更新模型
	void CGroundRadar::EntityUpdate(double dt)
	{
		IRadar::EntityUpdate(dt);
		// 更新名称
		m_pGeode->setName(GetAttribute()->GetName());
		// 获取半径
		int nRadius = GetAttribute()->GetItem("radius")->GetValueToInt();

		osg::Vec3 position = GetAttribute()->GetItem("position")->GetValueToVec3();

		//osg::Matrix matrix = osg::Matrix::translate(position);
	

		//// 判断是否放在地球上
		//if (IsEarthEnable())
		//{
		//	double x, y, z;
		//	CConvert::LatLongHeightToWord(position.x(), position.y(), position.z(), x, y, z);

		//	matrix = osg::Matrix::translate(x, y, z);
		//}

		// 设置缩放
		m_pMt->setMatrix(osg::Matrix::scale(nRadius, nRadius, nRadius) * osg::Matrix::rotate(osg::Quat(0.0f, 0.0f, 0.0f, 1.0f)));
		if (NULL != m_pModelNode)
		{
			m_pModelNode->setPosition(osgEarth::GeoPoint(m_pModelNode->getMapNode()->getMapSRS(), position));
		}
		m_pMt->dirtyBound();
	}

	// 创建属性对象
	IAttribute* CGroundRadar::CreateAttribute(void)
	{
		return (new CGroundRadarAttribute(this, "GroundRadar"));
	}

	// 初始化状态机
	void CGroundRadar::InitStateMachine(IStateMachine* pIStateMachine)
	{

	}
}

