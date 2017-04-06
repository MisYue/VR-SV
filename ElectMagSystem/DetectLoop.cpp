#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/ElectMagSystem/IRadar.h"
#include "RadarAttribute.h"
#include "RadarFactory.h"
#include "DetectLoop.h"

#include <osg/LineWidth>
#include <osg/AnimationPath>
#include <osg/Geometry>
#include <osg/MatrixTransform>
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

//------------------------------

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/PlaneIntersector>

namespace VR_Soft
{
	class SpyCallback : public osg::NodeCallback
	{
	public:
		SpyCallback(DetectLoop * pIRadar, DetectLoop::eSpyType spyType, 
			osg::ref_ptr<osg::AnimationPath> animationPath, 
			int hDensity, int vDensity,
			float loopTime)
		{
			_pIRadar = pIRadar;
			_spyType = spyType;
			_pAnimationPath = animationPath;
			_hDensity = hDensity;
			_vDensity = vDensity;
			_loopTime = loopTime;

			_previous = 0.0;
			_currTime = 0.0;

			_nIndex = 1;

			_deltaEndT = 0.0;

			_bReset = false;
		}

	public:
		virtual void operator() (osg::Node * node, osg::NodeVisitor * nv)
		{
			const osg::FrameStamp* f = nv->getFrameStamp();
			float dt = f->getSimulationTime() - _previous;

			osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform *>(node);

			if(!pat) 
				return;

			if (_pIRadar->_pSSArea && _pIRadar->_pSSRay)
			{
			}

			_currTime += dt;

			double deltaTime = _loopTime  / (_hDensity * _vDensity);

			osg::AnimationPath::ControlPoint cp;
			osg::AnimationPath::TimeControlPointMap::const_iterator second = _pAnimationPath->getTimeControlPointMap().lower_bound(_currTime);

			if (second == _pAnimationPath->getTimeControlPointMap().begin())
			{
				cp = second->second;

				pat->setAttitude(cp.getRotation());
			}
			else if (second == _pAnimationPath->getTimeControlPointMap().end())
			{
				if (!_bReset)
				{
					second--;

					cp = second->second;

					pat->setAttitude(cp.getRotation());

					if (_spyType == DetectLoop::GRID_INTERVAL_VERTICAL ||
						_spyType == DetectLoop::GRID_INTERVAL_N )
					{
						_nIndex++;

						float azmin, azmax, elevmin, elevmax;
						_pIRadar->_pSSArea->getArea(azmin, azmax, elevmin, elevmax);

						float deltaV = (elevmax - elevmin) / _vDensity;

						float azminRay, azmaxRay, elevminRay, elevmaxRay;
						_pIRadar->_pSSRay->getArea(azminRay, azmaxRay, elevminRay, elevmaxRay);

						int nCol = (_nIndex - 1) / _vDensity;
						int nRow = (_nIndex - 1) % _vDensity;

						if (_spyType == DetectLoop::GRID_INTERVAL_N)
						{
							if (nCol % 2 != 0)
							{
								nRow = _vDensity - nRow - 1;
							}
						}

						_pIRadar->_pSSRay->setArea(azminRay, azmaxRay, elevmin + deltaV * nRow, elevmin + deltaV * (nRow + 1));
					}

					_bReset = true;

					_deltaEndT = 0.0;
				}
				else
				{
					_deltaEndT += dt;

					if (_deltaEndT > deltaTime)
					{
						_bReset = false;

						_currTime = 0.0;

						_nIndex = 1;

						float azmin, azmax, elevmin, elevmax;
						_pIRadar->_pSSArea->getArea(azmin, azmax, elevmin, elevmax);

						float deltaV = (elevmax - elevmin) / _vDensity;

						float azminRay, azmaxRay, elevminRay, elevmaxRay;
						_pIRadar->_pSSRay->getArea(azminRay, azmaxRay, elevminRay, elevmaxRay);

						_pIRadar->_pSSRay->setArea(azminRay, azmaxRay, elevmin, elevmin + deltaV);
					}
				}
			}
			else
			{
				second--;

				double t1 = second->first;

				if (_spyType == DetectLoop::GRID_INTERVAL_Z ||
					_spyType == DetectLoop::GRID_INTERVAL_HORIZONTAL )
				{
					double t2 = deltaTime * _hDensity * _nIndex;

					if (t1 > t2)
					{
						_nIndex++;

						float azmin, azmax, elevmin, elevmax;
						_pIRadar->_pSSArea->getArea(azmin, azmax, elevmin, elevmax);

						float deltaV = (elevmax - elevmin) / _vDensity;

						float azminRay, azmaxRay, elevminRay, elevmaxRay;
						_pIRadar->_pSSRay->getArea(azminRay, azmaxRay, elevminRay, elevmaxRay);

						_pIRadar->_pSSRay->setArea(azminRay, azmaxRay, elevmin + deltaV * (_nIndex - 1), elevmin + deltaV * _nIndex);
					}
				}
				else if (_spyType == IRadar::GRID_INTERVAL_VERTICAL ||
					_spyType == IRadar::GRID_INTERVAL_N )
				{
					double t2 = deltaTime * _nIndex;

					if (t1 > t2)
					{
						_nIndex++;

						float azmin, azmax, elevmin, elevmax;
						_pIRadar->_pSSArea->getArea(azmin, azmax, elevmin, elevmax);

						float deltaV = (elevmax - elevmin) / _vDensity;

						float azminRay, azmaxRay, elevminRay, elevmaxRay;
						_pIRadar->_pSSRay->getArea(azminRay, azmaxRay, elevminRay, elevmaxRay);

						int nCol = (_nIndex - 1) / _vDensity;
						int nRow = (_nIndex - 1) % _vDensity;

						if (_spyType == IRadar::GRID_INTERVAL_N)
						{
							if (nCol % 2 != 0)
							{
								nRow = _vDensity - nRow - 1;
							}
						}

						_pIRadar->_pSSRay->setArea(azminRay, azmaxRay, elevmin + deltaV * nRow, elevmin + deltaV * (nRow + 1));
					}
				}

				cp = second->second;

				pat->setAttitude(cp.getRotation());
			}

			_previous = f->getSimulationTime();

			traverse(node, nv);
		}

	private:
		osg::ref_ptr<DetectLoop> _pIRadar;
		DetectLoop::eSpyType	_spyType;
		osg::ref_ptr<osg::AnimationPath> _pAnimationPath;
		float _previous;
		float _currTime;
		int _hDensity; 
		int _vDensity;
		float _loopTime;

		int _nIndex;

		bool _bReset;

		float _deltaEndT;;
	};



	//---------------------------

	DetectLoop::DetectLoop(void)
	{
		_pSSArea = NULL;
		_pSSRay = NULL;
		_pSSGrid = NULL;

		_pRoot = new osg::MatrixTransform;
		_pRot_V_PAT = new osg::PositionAttitudeTransform;
		_pRot_H_PAT = new osg::PositionAttitudeTransform;

		_radius = -1.0;

		_pRot_V_PAT->addChild(_pRay = new osg::Group);
		_pRot_H_PAT->addChild(_pRot_V_PAT);
		_pRoot->addChild(_pRot_H_PAT);
		_pRoot->addChild(_pArea = new osg::Group);
		_pRoot->addChild(_pGrid = new osg::Group);

		_pArea->setNodeMask(0);

		_pRay->setNodeMask(0);
		//_pRay->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);

		_pGrid->setNodeMask(0);

		addChild(_pRoot);
	}

	DetectLoop::~DetectLoop(void)
	{
		// 获得父类
		osg::Node::ParentList parentList = getParents();
		// 遍历节点从父类中删除自身
		for (osg::Node::ParentList::iterator itor = parentList.begin(); \
			parentList.end() != itor; ++itor)
		{
			(*itor)->removeChild(this);
		}
	}

	bool DetectLoop::setMode(bool bUseLight, bool bUseBlend)
	{
		_pRoot->getOrCreateStateSet()->setMode(GL_LIGHTING	, bUseLight ? osg::StateAttribute::ON : osg::StateAttribute::OFF);
		_pRoot->getOrCreateStateSet()->setMode(GL_BLEND		, bUseBlend ? osg::StateAttribute::ON : osg::StateAttribute::OFF);
		return true;
	}

	bool DetectLoop::setSpyNode(osg::Node * pSpyNode , osg::Node * pNoSpyNode)
	{
// 		_pSpyNode = pSpyNode;
// 		_pNoSpyNode = pNoSpyNode;
		return true;
	}

	bool DetectLoop::setRadius(double radius)
	{
		if (radius < 0)
			return false;

		_radius = radius;
		return true;
	}

	bool DetectLoop::setDirection(osg::Vec3d up, osg::Vec3d front)
	{
		osg::Matrixd rotUpMat, rotFrontMat;
		rotUpMat.makeRotate(osg::Vec3d(osg::Z_AXIS) , up );
		osg::Vec3d axes;
		axes = osg::Y_AXIS * rotUpMat;
		rotFrontMat.makeRotate(axes, front);
		_pRoot->setMatrix(rotUpMat * rotFrontMat);
		return true;
	}

	bool DetectLoop::setDrawMask(eDrawMask mask)
	{
		_pRay->setNodeMask((mask & RAY) == 0 ? 0 : -1);
		_pArea->setNodeMask((mask & AREA) == 0 ? 0 : -1);
		_pGrid->setNodeMask((mask & GRID) == 0 ? 0 : -1);

		return true;

		return true;
	}

	//射线，扫描束
	bool DetectLoop::setRay(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor)
	{
		_pRay->removeChildren(0, _pRay->getNumChildren());
		if (_radius < 0 || fabs(vMin) > 90.0 || fabs(vMax) > 90.0 || vMax < vMin)
			return false;

		osg::ref_ptr<osgSim::SphereSegment> pSS = new osgSim::SphereSegment;
		pSS->setCentre(osg::Vec3d(0.0, 0.0, 0.0));
		pSS->setRadius(_radius);
		pSS->setSurfaceColor(surfaceColor);
		pSS->setSideColor(sideColor);
		pSS->setSpokeColor(sideColor);
		pSS->setDensity(density);					//待定
		pSS->setDrawMask(osgSim::SphereSegment::DrawMask(osgSim::SphereSegment::SURFACE | osgSim::SphereSegment::SIDES | osgSim::SphereSegment::SPOKES));

		pSS->setArea(osg::inDegrees(hMin), osg::inDegrees(hMax), osg::inDegrees(vMin), osg::inDegrees(vMax));

		_pSSRay = pSS;

		_pRay->addChild(pSS.get());;

		return true;
	}

	//扫描射线的显示与隐藏
	// void DetectLoop::setRayShow(bool bShow)
	// {
	// 	int nCount = _pRay->getNumChildren();
	// 	for(int i = 0; i < nCount; i++)
	// 	{
	// 		osg::Node* pNode = _pRay->getChild(i);
	// 		if(bShow)
	// 		{
	// 			pNode->setNodeMask(0xff);
	// 		}
	// 		else
	// 		{
	// 			pNode->setNodeMask(0x00);
	// 		}
	// 	}
	// }

	/**
	*	绘制包落
	*	参数：hRange                包落大小，如90度，180度
	*	参数：vMin					起始角度
	*	参数：vMax					终点角度
	*   参数：density				基准角
	*   参数：surfaceColor          包落颜色
	*   参数：sideColor             起始边颜色
	*/
	bool DetectLoop::setArea(double hMin, double hMax, double vMin, double vMax,  int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor)
	{
		_pArea->removeChildren(0, _pArea->getNumChildren());
		if (_radius < 0 || fabs(vMin) > 90.0 || fabs(vMax) > 90.0 || vMax < vMin)
			return false;

		osg::ref_ptr<osgSim::SphereSegment> pSS = new osgSim::SphereSegment;
		pSS->setCentre(osg::Vec3d(0.0, 0.0, 0.0));
		pSS->setRadius(_radius);
		pSS->setSurfaceColor(surfaceColor);
		pSS->setSideColor(sideColor);
		pSS->setSpokeColor(sideColor);
		pSS->setDensity(density);					//待定
		pSS->setDrawMask(osgSim::SphereSegment::DrawMask(osgSim::SphereSegment::SURFACE | osgSim::SphereSegment::SIDES | osgSim::SphereSegment::SPOKES));

		pSS->setArea(osg::inDegrees(hMin), osg::inDegrees(hMax), osg::inDegrees(vMin), osg::inDegrees(vMax));

		_pSSArea = pSS;

		return _pArea->addChild(pSS);
	}

	bool DetectLoop::setGrid(int hDensity, int vDensity, double lineWidth ,osg::Vec4d gridColor )
	{
		_pGrid->removeChildren(0, _pGrid->getNumChildren());
		osg::ref_ptr<osgSim::SphereSegment> pSS = NULL;

		if (_pArea->getNumChildren() == 1)
			pSS = dynamic_cast<osgSim::SphereSegment *>(_pArea->getChild(0));
		else
			return false;

		if (pSS == NULL || hDensity < 1 || vDensity < 1)
			return false;

		float azmin, azmax, elevmin, elevmax;
		pSS->getArea(azmin, azmax, elevmin, elevmax);

		double delta_az = (azmax - azmin) / hDensity;
		double delta_elev = (elevmax - elevmin) / vDensity;

		osg::ref_ptr<deprecated_osg::Geometry> pGeometry = new deprecated_osg::Geometry;
		osg::Vec3Array * coords = new osg::Vec3Array;
		osg::UIntArray * coordIndices = new osg::UIntArray;

		osg::Vec3d pt;
		for (int i = 0; i <= hDensity ; ++i)
		{
			for (int j = 0; j <= vDensity ; ++j)
			{
				pt[0] = sin(azmin + delta_az * i) * cos(elevmin + delta_elev * j);
				pt[1] = cos(azmin + delta_az * i) * cos(elevmin + delta_elev * j);
				pt[2] = sin(elevmin + delta_elev * j);
				coords->push_back( pt * (_radius) );

				if ( i != hDensity && j != vDensity)
				{
					//懒得算了，公共线段画两遍吧
					coordIndices->push_back( (vDensity + 1) * i + j + 1);
					coordIndices->push_back( (vDensity + 1) * i + j);
					coordIndices->push_back( (vDensity + 1) * i + j);
					coordIndices->push_back( (vDensity + 1) * (i + 1) + j);
					coordIndices->push_back( (vDensity + 1) * (i + 1) + j);
					coordIndices->push_back( (vDensity + 1) * (i + 1) + j + 1);
					coordIndices->push_back( (vDensity + 1) * (i + 1) + j + 1);
					coordIndices->push_back( (vDensity + 1) * i + j + 1);
				}
			}
		}

		pGeometry->setVertexArray(coords);
		pGeometry->setVertexIndices(coordIndices);
		pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES , 0 , coordIndices->size()));

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(gridColor);
		pGeometry->setColorArray(colors);
		pGeometry->setColorBinding(deprecated_osg::Geometry::BIND_OVERALL);

		osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
		pGeode->addDrawable(pGeometry);
		_pGrid->addChild(pGeode);

		_pSSGrid = pGeode;

		osg::ref_ptr<osg::LineWidth> pLW = new osg::LineWidth;
		pLW->setWidth(lineWidth);	
		_pGrid->getOrCreateStateSet()->setAttribute(pLW);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	//扫描束运动
	//////////////////////////////////////////////////////////////////////////
	bool DetectLoop::setLoopTime(eSpyType spyType, eLoopType loopType, double loopTime)
	{
		osg::ref_ptr<osgSim::SphereSegment> pSS = NULL;

		if (_pArea->getNumChildren() == 1)
			pSS = dynamic_cast<osgSim::SphereSegment *>(_pArea->getChild(0));
		else
			return false;

		float azmin, azmax, elevmin, elevmax;
		pSS->getArea(azmin, azmax, elevmin, elevmax);

		double rayAZ = 0.0;
		double rayEle = 0.0;

		float azminRay, azmaxRay, elevminRay, elevmaxRay;
		azminRay = azmaxRay = elevminRay = elevmaxRay = 0.0;

		if (_pRay->getNumChildren() == 1)
		{
			osg::ref_ptr<osgSim::SphereSegment> pSS = dynamic_cast<osgSim::SphereSegment *>(_pRay->getChild(0));

			pSS->getArea(azminRay, azmaxRay, elevminRay, elevmaxRay);

			rayAZ = azmaxRay - azminRay;
			rayEle = elevmaxRay - elevminRay;
		}

		osg::AnimationPath::LoopMode loopMode;

		if (loopType == FIXED)
			return true;
		else if (loopType == SWING)
		{
			loopMode = osg::AnimationPath::SWING;
		}
		else if (loopType == LOOP)
		{
			loopMode = osg::AnimationPath::LOOP;
		}
		else
		{
			return false;
		}

		osg::ref_ptr<osg::AnimationPath> pAnimationPath = new osg::AnimationPath;
		pAnimationPath->setLoopMode(loopMode);

		osg::Vec3 position (0.0, 0.0, 0.0);

		if (spyType == HORIZONTAL)
		{
			int numSamples = 64;
			osg::Vec3 axes;
			double min , delta;

			axes = osg::Z_AXIS;
			min = azmin;
			delta = (azmax - azmin - rayAZ) / numSamples;

			osg::Quat rotation;

			for (int i = 0; i <= numSamples ; ++i)
			{
				double angle = min + delta * i;
				rotation.makeRotate(-angle, axes);

				pAnimationPath->insert(loopTime * i / numSamples, osg::AnimationPath::ControlPoint(position, rotation) );
			}

			_pRot_H_PAT->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
		}
		else if (spyType == GRID_CONTINU_Z ||
			spyType == GRID_INTERVAL_Z )
		{
			int hDensity = (azmax - azmin) / rayAZ;
			int vDensity = (elevmax - elevmin) / rayEle;

			double deltaP = (elevmax - elevmin) / vDensity;
			double deltaH = (azmax - azmin) / hDensity;

			int nIndex = 0;

			for (int nI = 1; nI <= vDensity ; ++nI)
			{
				if (nI % 2 == 0)
				{
					for (int nJ = hDensity-1; nJ >= 0 ; nJ--)
					{
						double angleH = azmin + deltaH * nJ;
						double angleP = elevmin + deltaP * (nI-1);

						osg::Quat rotation;

						if (spyType == GRID_CONTINU_Z)
						{
							rotation = osg::Quat(angleP, osg::X_AXIS ) * osg::Quat(-angleH, osg::Z_AXIS );
						}
						else if(spyType == GRID_INTERVAL_Z )
						{
							rotation = osg::Quat(-angleH, osg::Z_AXIS );
						}

						double time = loopTime * nIndex / (hDensity * vDensity);
						pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(position, rotation) );

						nIndex++;
					}
				}
				else
				{
					for (int nJ = 0; nJ < hDensity ; ++nJ)
					{
						double angleH = azmin + deltaH * nJ;
						double angleP = elevmin + deltaP * (nI-1);

						osg::Quat rotation;

						if (spyType == GRID_CONTINU_Z)
						{
							rotation = osg::Quat(angleP, osg::X_AXIS ) * osg::Quat(-angleH, osg::Z_AXIS );
						}
						else if(spyType == GRID_INTERVAL_Z )
						{
							rotation = osg::Quat(-angleH, osg::Z_AXIS );
						}

						double time = loopTime * nIndex / (hDensity * vDensity);
						pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(position, rotation) );

						nIndex++;
					}
				}
			}

			if (spyType == GRID_CONTINU_Z)
			{
				_pRot_H_PAT->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
			}
			else if(spyType == GRID_INTERVAL_Z )
			{
				_pRot_H_PAT->setUpdateCallback(new SpyCallback(this, spyType, pAnimationPath, hDensity, vDensity, loopTime));
			}
		}
		else if (spyType == GRID_CONTINU_HORIZONTAL ||
			spyType == GRID_INTERVAL_HORIZONTAL )
		{
			int hDensity = (azmax - azmin) / rayAZ;
			int vDensity = (elevmax - elevmin) / rayEle;

			double deltaP = (elevmax - elevmin) / vDensity;
			double deltaH = (azmax - azmin) / hDensity;

			int nIndex = 0;

			for (int nI = 1; nI <= vDensity ; ++nI)
			{
				for (int nJ = 0; nJ < hDensity ; ++nJ)
				{
					double angleH = azmin + deltaH * nJ;
					double angleP = elevmin + deltaP * (nI-1);

					osg::Quat rotation;

					if (spyType == GRID_CONTINU_HORIZONTAL)
					{
						rotation = osg::Quat(angleP, osg::X_AXIS ) * osg::Quat(-angleH, osg::Z_AXIS );
					}
					else if(spyType == GRID_INTERVAL_HORIZONTAL )
					{
						rotation = osg::Quat(-angleH, osg::Z_AXIS );
					}

					double time = loopTime * nIndex / (hDensity * vDensity);
					pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(position, rotation) );

					nIndex++;
				}
			}

			if (spyType == GRID_CONTINU_HORIZONTAL)
			{
				_pRot_H_PAT->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
			}
			else if(spyType == GRID_INTERVAL_HORIZONTAL )
			{
				_pRot_H_PAT->setUpdateCallback(new SpyCallback(this, spyType, pAnimationPath, hDensity, vDensity, loopTime));
			}
		}
		else if (spyType == GRID_CONTINU_VERTICAL ||
			spyType == GRID_INTERVAL_VERTICAL )
		{
			int hDensity = (azmax - azmin) / rayAZ;
			int vDensity = (elevmax - elevmin) / rayEle;

			double deltaP = (elevmax - elevmin) / vDensity;
			double deltaH = (azmax - azmin) / hDensity;

			int nIndex = 0;

			for (int nI = 1; nI <= hDensity ; ++nI)
			{
				for (int nJ = 0; nJ < vDensity ; ++nJ)
				{
					double angleH = azmin + deltaH * (nI - 1);
					double angleP = elevmin + deltaP * nJ;

					osg::Quat rotation;

					if (spyType == GRID_CONTINU_VERTICAL)
					{
						rotation = osg::Quat(angleP, osg::X_AXIS ) * osg::Quat(-angleH, osg::Z_AXIS );
					}
					else if(spyType == GRID_INTERVAL_VERTICAL )
					{
						rotation = osg::Quat(-angleH, osg::Z_AXIS );
					}

					double time = loopTime * nIndex / (hDensity * vDensity);
					pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(position, rotation) );

					nIndex++;
				}
			}

			if (spyType == GRID_CONTINU_VERTICAL)
			{
				_pRot_H_PAT->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
			}
			else if(spyType == GRID_INTERVAL_VERTICAL )
			{
				_pRot_H_PAT->setUpdateCallback(new SpyCallback(this, spyType, pAnimationPath, hDensity, vDensity, loopTime));
			}
		}
		else if (spyType == GRID_CONTINU_N ||
			spyType == GRID_INTERVAL_N )
		{
			int hDensity = (azmax - azmin) / rayAZ;
			int vDensity = (elevmax - elevmin) / rayEle;

			double deltaP = (elevmax - elevmin) / vDensity;
			double deltaH = (azmax - azmin) / hDensity;

			int nIndex = 0;

			for (int nI = 1; nI <= hDensity ; ++nI)
			{
				if (nI % 2 == 0)
				{
					for (int nJ = vDensity-1; nJ >= 0 ; nJ--)
					{
						double angleH = azmin + deltaH * (nI - 1);
						double angleP = elevmin + deltaP * nJ;

						osg::Quat rotation;

						if (spyType == GRID_CONTINU_N)
						{
							rotation = osg::Quat(angleP, osg::X_AXIS ) * osg::Quat(-angleH, osg::Z_AXIS );
						}
						else if(spyType == GRID_INTERVAL_N )
						{
							rotation = osg::Quat(-angleH, osg::Z_AXIS );
						}

						double time = loopTime * nIndex / (hDensity * vDensity);
						pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(position, rotation) );

						nIndex++;
					}
				}
				else
				{
					for (int nJ = 0; nJ < vDensity ; ++nJ)
					{
						double angleH = azmin + deltaH * (nI - 1);
						double angleP = elevmin + deltaP * nJ;

						osg::Quat rotation;

						if (spyType == GRID_CONTINU_N)
						{
							rotation = osg::Quat(angleP, osg::X_AXIS ) * osg::Quat(-angleH, osg::Z_AXIS );
						}
						else if(spyType == GRID_INTERVAL_N )
						{
							rotation = osg::Quat(-angleH, osg::Z_AXIS );
						}

						double time = loopTime * nIndex / (hDensity * vDensity);
						pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(position, rotation) );

						nIndex++;
					}
				}
			}

			if (spyType == GRID_CONTINU_N)
			{
				_pRot_H_PAT->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
			}
			else if(spyType == GRID_INTERVAL_N )
			{
				_pRot_H_PAT->setUpdateCallback(new SpyCallback(this, spyType, pAnimationPath, hDensity, vDensity, loopTime));
			}
		}
		else
			return false;

		return true;
	}

	//相控阵
	bool DetectLoop::setPhasedArrayRay(double hRange, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor)
	{
		int numHCount = hRange / 5.0;
		int numVCount = (vMax - vMin) / 5.0;

		for(int i = 0; i < numVCount; i++)
		{
			for(int j = 0; j < numHCount; j++)
			{
				osg::ref_ptr<osgSim::SphereSegment> pSS = new osgSim::SphereSegment;
				pSS->setCentre(osg::Vec3d(0.0, 0.0, 0.0));
				pSS->setRadius(_radius);
				pSS->setSurfaceColor(surfaceColor);
				pSS->setSideColor(sideColor);
				pSS->setSpokeColor(sideColor + osg::Vec4d(0.05, 0.05, 0.05, 0.0));
				pSS->setDensity(density);					//待定
				pSS->setDrawMask(osgSim::SphereSegment::DrawMask(osgSim::SphereSegment::SURFACE | osgSim::SphereSegment::SIDES | osgSim::SphereSegment::SPOKES));

				double delteH = osg::inDegrees(hRange) / 2.0 * j;
				pSS->setArea(delteH * -1.0, delteH , osg::inDegrees(5.0*i), osg::inDegrees(5.0*(i+1)));

				_pRay->addChild(pSS.get());

			}
		}

		return true;
	}

	//相控阵
	void DetectLoop::setPhasedArrayLoopTime()
	{
		osg::ref_ptr<osgSim::SphereSegment> pSS = NULL;
		if (_pArea->getNumChildren() == 1)
			pSS = dynamic_cast<osgSim::SphereSegment *>(_pArea->getChild(0));
		else
			return ;

		float azmin, azmax, elevmin, elevmax;
		pSS->getArea(azmin, azmax, elevmin, elevmax);
		int numSamples = 64;
		//////////////////////////////////////////////////////////////////////////
		int nCount = _pRay->getNumChildren();
		for(int i = 0; i < nCount; i++)
		{
			osg::Node* pNode = _pRay->getChild(i);

			osg::MatrixTransform* pTransform = new osg::MatrixTransform;

			osg::Quat rot(osg::DegreesToRadians(30.0) ,osg::Vec3(0.0f,1.0f,0.0f),
				osg::DegreesToRadians(0.0),osg::Vec3(1.0f,0.0f,0.0f),
				osg::DegreesToRadians(30.0),osg::Vec3(0.0f,0.0f,1.0f));

			pTransform->setMatrix( osg::Matrix::rotate(rot) );
			pTransform->addChild(pNode);
			_pRay->addChild(pTransform);
		}
	}

	bool DetectLoop::setScreen(eSpyType spyType, int rDensity, int aDensity, osg::Vec2d screenCenter, double screenRadius)
	{
		/*_pScreen->removeChildren(0, _pScreen->getNumChildren());
		if (_radius < 0 || rDensity < 1 || aDensity < 1)
			return false;

		//雷达表盘
		osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
		{
			osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;

			osg::ref_ptr<osgSim::SphereSegment> pSS = NULL;
			if (_pArea->getNumChildren() == 1)
				pSS = dynamic_cast<osgSim::SphereSegment *>(_pArea->getChild(0));
			else
				return false;

			if (pSS == NULL || rDensity < 1 || aDensity < 1)
				return false;

			float azmin, azmax, elevmin, elevmax;
			pSS->getArea(azmin, azmax, elevmin, elevmax);

			double min, max;
			if (spyType == HORIZONTAL)
			{
				min = azmin;
				max = azmax;
			}
			else if (spyType == VERTICAL)
			{
				min = elevmin;
				max = elevmax;
			}
			else
			{
				return false;
			}


			osg::Vec3Array * coords = new osg::Vec3Array;
			pGeometry->setVertexArray(coords);

			osg::Vec3d pt;
			int density = 36;

			//圆弧
			double delta = (max - min) / density;
			for (int i = 0; i < rDensity ; ++i)
			{
				double radius = _radius * (i+1) / rDensity;
				for (int j = 0; j <= density ; ++j)
				{
					if (spyType == HORIZONTAL)
					{
						pt[0] = cos(min + delta * j + osg::PI_2) * radius;
						pt[1] = sin(min + delta * j + osg::PI_2) * radius;
						pt[2] = 0.0;
					}
					else if (spyType == VERTICAL)
					{
						pt[0] = 0.0;
						pt[1] = cos(min + delta * j ) * radius;
						pt[2] = sin(min + delta * j ) * radius;;
					}
					else
						return false;

					coords->push_back(pt);
				}
			}

			for (int i = 0; i < rDensity; ++i)
			{
				pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP , (density + 1) * i , density + 1));
			}

			//半径
			delta = (max - min) / aDensity;
			for (int i = 0; i <= aDensity ; ++i)
			{
				if (spyType == HORIZONTAL)
				{
					pt[0] = cos(min + delta * i + osg::PI_2) * _radius;
					pt[1] = sin(min + delta * i + osg::PI_2) * _radius;
					pt[2] = 0.0;
				}
				else if (spyType == VERTICAL)
				{
					pt[0] = 0.0;
					pt[1] = cos(min + delta * i) * _radius;
					pt[2] = sin(min + delta * i) * _radius;
				}
				else
					return false;

				coords->push_back(osg::Vec3d(0.0, 0.0, 0.0));
				coords->push_back(pt);
			}
			pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES , (density + 1) * rDensity , (aDensity + 1) * 2));

			osg::Vec4Array* colors = new osg::Vec4Array;
			colors->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
			pGeometry->setColorArray(colors);
			pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

			pGeode->addDrawable(pGeometry);

		}

		//指针
		osg::ref_ptr<osg::PositionAttitudeTransform> pPAT = new osg::PositionAttitudeTransform;
		{
			osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
			osg::Vec3Array * coords = new osg::Vec3Array;
			coords->push_back(osg::Vec3d(0.0, 0.0, 0.0));
			coords->push_back(osg::Vec3d( 0.0,_radius, 0.0));
			pGeometry->setVertexArray(coords);
			pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES , 0, 2));

			osg::Vec4Array* colors = new osg::Vec4Array;
			colors->push_back(osg::Vec4(0.0, 1.0, 1.0, 1.0));
			pGeometry->setColorArray(colors);
			pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

			osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
			pGeode->addDrawable(pGeometry);
			pPAT->addChild(pGeode);
		}

		//HUD相机
		osg::ref_ptr<osg::Camera> pCamera = new osg::Camera;
		{
			osg::Vec3d center = pGeode->getBoundingBox().center();
			double radius = pGeode->getBoundingBox().radius();
			pCamera->setProjectionMatrixAsOrtho2D( -radius, radius, -radius, radius );
			pCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

			if (spyType == HORIZONTAL)
				pCamera->setViewMatrixAsLookAt(center + osg::Z_AXIS, center, osg::Y_AXIS);
			else if (spyType == VERTICAL)
				pCamera->setViewMatrixAsLookAt(center + osg::X_AXIS, center, osg::Z_AXIS);
			else
				return false;

			pCamera->setViewport(screenCenter.x() - screenRadius , screenCenter.y() - screenRadius ,screenRadius * 2, screenRadius * 2);
			pCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
			pCamera->setRenderOrder(osg::Camera::POST_RENDER);
			pCamera->setAllowEventFocus(false);
			pCamera->addChild(pGeode);
			pCamera->addChild(pPAT);

			pCamera->addChild(_pScreenFlash = new osg::Geode);	//屏幕上的点

			osg::ref_ptr<osg::NodeCallback> pCB = NULL;
			if (spyType == HORIZONTAL)
				pCB = _pRot_H_PAT->getUpdateCallback();
			else if (spyType == VERTICAL)
				pCB = _pRot_V_PAT->getUpdateCallback();
			else
				return false;

			if (pCB)
				pPAT->setUpdateCallback(pCB);
			else
				return false;
		}

		_pScreen->addChild(pCamera);

		//设置回调
		if (_pSpyNode)
			_pScreen->setUpdateCallback(new SpyCallback(this , spyType));
		else
			_pScreen->setUpdateCallback(NULL);
			*/
		return true;
	}

	bool DetectLoop::screenFlash(osg::Vec3d pt, double radius)
	{
		//暂未加特效
		/*if (_pScreenFlash->getNumDrawables() > 1)
			_pScreenFlash->removeDrawables(0);

		_pScreenFlash->addDrawable(new osg::ShapeDrawable(new osg::Sphere(pt ,radius),_pHints));*/

		return true;
	}

	osg::Node* DetectLoop::GetDrawObj(osgEarth::MapNode* pMapNode)
	{
		osgEarth::Symbology::Style style;
		style.getOrCreate<osgEarth::Symbology::ModelSymbol>()->setModel(this);
		osgEarth::Annotation::ModelNode* pModelNode = new osgEarth::Annotation::ModelNode(pMapNode, style);

		pModelNode->setName(this->getName());
		return (pModelNode);
	}

	// 获得渲染节点
	osg::Node* DetectLoop::GetDrawObj(void)
	{
		return (this);
	}

	// 获得类型
	const VRString DetectLoop::GetEntityType(void) const
	{
		return ("radarType");
	}

	// 设置名称
	void DetectLoop::SetName(const VRString& strName)
	{
		IRadar::SetName(strName);
		
		setName(strName);
	}

	osg::BoundingSphere DetectLoop::computeBound() const
	{
		osg::BoundingSphere bs = _pRoot->getBound();
		// 计算包围盒
		/*int nRadius = bs.radius();
		bs.set(osg::Vec3(0.0, 0.0, 0.0), _radius);*/

		return (bs);
	}

	// 初始化
	void DetectLoop::Init(void)
	{
		setMode(false, true);

		setDrawMask(IRadar::DRAW_ALL);
		setDirection(osg::Z_AXIS, osg::Y_AXIS);

		setRadius( 500000.0 );
		setArea( 0.0, 120.0 , 0.0, 40.0, 100, osg::Vec4d(0.5, 0.8, 0.4, 0.3), osg::Vec4d(0.3, 0.2, 0.4 ,0.0));
		setGrid(24 , 8, 1 , osg::Vec4d(0.5, 0.8, 0.1, 0.3));
		setRay(0.0, 5.0, 0.0, 5.0, 4 , osg::Vec4d(0.5, 0.8, 0.4, 0.2), osg::Vec4d(0.5, 0.8, 0.4 ,0.2));

		setLoopTime(IRadar::GRID_CONTINU_HORIZONTAL, IRadar::LOOP , 40.0);
	}

	// 创建属性对象
	IAttribute* DetectLoop::CreateAttribute(void)
	{
		return (new CRadarAttribute(this, "Radar"));
	}

	// 初始化状态机
	void DetectLoop::InitStateMachine(IStateMachine* pIStateMachine)
	{

	}
}