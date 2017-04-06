#pragma once

#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osgSim/SphereSegment>


//暂不支持水平、垂直方向同时使用。垂直方向未经严格测试
namespace VR_Soft
{
	class DetectLoop : public osg::MatrixTransform , public IRadar
	{
		friend class SpyCallback;
	public:
		explicit DetectLoop(void);
		virtual ~DetectLoop(void);

	public:

		virtual bool setMode(bool bUseLight = false, bool bUseBlend = true);			//设置光照与混合的状态
		virtual bool setDrawMask(eDrawMask mask);										//显示类型

		//以下函数中，Radius应最先设置，Grid应在Area后调用，雷达屏幕最后调用。如参数错误，会返回false。
		//参数density为显示精度，前缀 h - HORIZONTAL  v - VERTICAL。
		virtual bool setRadius(double radius);											//扫描半径
		virtual bool setDirection(osg::Vec3d up, osg::Vec3d front);						//设置雷达在世界坐标中的方向
		virtual bool setArea(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor);				//整体可扫描的区域
		virtual bool setRay(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor);				//某时刻可扫描到的区域
		virtual bool setGrid(int hDensity, int vDensity, double lineWidth , osg::Vec4d gridColor);						//整体扫描区域外包面的网格线
		virtual bool setLoopTime(eSpyType spyType, eLoopType loopType, double loopTime);								//设置扫描类型

		virtual bool setPhasedArrayRay(double hRange, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor);				//某时刻可扫描到的区域
		virtual void setPhasedArrayLoopTime();																			//相控阵

		//雷达屏幕相关
		virtual bool setSpyNode(osg::Node * pSpyNode , osg::Node * pNoSpyNode = NULL);			//设置需要扫描的节点和需要排除的节点
		virtual bool setScreen(eSpyType spyType, int rDensity, int aDensity, osg::Vec2d screenCenter = osg::Vec2d( 150.0, 150.0), double screenRadius = 150);
		
		// 获得类型
		virtual const VRString GetEntityType(void) const;
		// 设置名称
		virtual void SetName(const VRString& strName);

		//registerObserver/unregisterObserver
		virtual osg::BoundingSphere computeBound() const;
		// 初始化
		virtual void Init(void);
		 // 获取渲染节点
		virtual osg::Node* GetDrawObj(osgEarth::MapNode* pMapNode);
		// 获得渲染节点
		virtual osg::Node* GetDrawObj(void);
		// 创建属性对象
		virtual IAttribute* CreateAttribute(void);
		// 扫描渲染
		virtual void ScanRender(void) { }
	public:
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine);

	protected:

		bool screenFlash(osg::Vec3d pt, double radius);		//将发现的目标显示在雷达屏幕上。还应添加观察者列表，扫描到物体时通知其位置和半径。

	protected:
		// 获得依赖地球最终矩阵
		virtual void GetMatrixInEarth(const osg::Vec3& vPositon)  { }


	private:
		osg::ref_ptr<osg::MatrixTransform> _pRoot;		

		//雷达扫描范围
		osg::ref_ptr<osg::PositionAttitudeTransform> _pRot_V_PAT;			//垂直变换节点
		osg::ref_ptr<osg::PositionAttitudeTransform> _pRot_H_PAT;			//水平变换节点

		double _radius;

		osg::ref_ptr<osg::Group> _pArea;
		osg::ref_ptr<osg::Group> _pRay;
		osg::ref_ptr<osg::Group> _pGrid;

	public:
		osg::ref_ptr<osgSim::SphereSegment> _pSSArea;
		osg::ref_ptr<osgSim::SphereSegment> _pSSRay;
		osg::ref_ptr<osg::Geode> _pSSGrid;
	};

	// 注册工厂类
	REGISTER_BASEENTITY_FACTORY(DetectLoop, "radarType");
}

