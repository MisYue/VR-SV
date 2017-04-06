#ifndef _GROUNDRADAR_H_
#define _GROUNDRADAR_H_
#pragma once

#include <osg/MatrixTransform>

namespace osgEarth
{
	namespace Annotation
	{
		class ModelNode;
	}
}

namespace VR_Soft
{
	class CGroundRadar : public IRadar
	{
	public:
		explicit CGroundRadar(void);
		virtual ~CGroundRadar(void);

	public:
		virtual bool setMode(bool bUseLight = false, bool bUseBlend = true){return (true);}			//设置光照与混合的状态
		virtual bool setDrawMask(eDrawMask mask){return (true);}										//显示类型

		//以下函数中，Radius应最先设置，Grid应在Area后调用，雷达屏幕最后调用。如参数错误，会返回false。
		//参数density为显示精度，前缀 h - HORIZONTAL  v - VERTICAL。
		virtual bool setRadius(double radius){return (true);}											//扫描半径
		virtual bool setDirection(osg::Vec3d up, osg::Vec3d front){return (true);}						//设置雷达在世界坐标中的方向
		virtual bool setArea(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor){return (true);}				//整体可扫描的区域
		virtual bool setRay(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor){return (true);}				//某时刻可扫描到的区域
		virtual bool setGrid(int hDensity, int vDensity, double lineWidth , osg::Vec4d gridColor){return (true);}						//整体扫描区域外包面的网格线
		virtual bool setLoopTime(eSpyType spyType, eLoopType loopType, double loopTime){return (true);}								//设置扫描类型

		virtual bool setPhasedArrayRay(double hRange, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor){return (true);}				//某时刻可扫描到的区域
		virtual void setPhasedArrayLoopTime(){}																			//相控阵

		//雷达屏幕相关
		virtual bool setSpyNode(osg::Node * pSpyNode , osg::Node * pNoSpyNode = NULL){return (true);}			//设置需要扫描的节点和需要排除的节点
		virtual bool setScreen(eSpyType spyType, int rDensity, int aDensity, osg::Vec2d screenCenter = osg::Vec2d( 150.0, 150.0), double screenRadius = 150){return (true);}
		// 获取渲染节点
		virtual osg::Node* GetDrawObj(osgEarth::MapNode* pMapNode);
		// 获取渲染节点
		virtual osg::Node* GetDrawObj(void);
		// 获得类型
		virtual const VRString GetEntityType(void) const;
		// 设置名称
		virtual void SetName(const VRString& strName);

		//registerObserver/unregisterObserver
		
		// 初始化
		virtual void Init(void);
		// 更新模型
		virtual void EntityUpdate(double dt);
		// 创建属性对象
		virtual IAttribute* CreateAttribute(void);
		// 扫描渲染
		virtual void ScanRender(void) { }

	public:
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine);

	public:
		// 渲染包络
		void DrawFx(void);

	protected:
		// 获得依赖地球最终矩阵
		virtual void GetMatrixInEarth(const osg::Vec3& vPositon)  { }

	private:
		/*osg::ref_ptr<*/osg::MatrixTransform/*> */ *m_pMt;
		osg::Geode* m_pGeode;

		osgEarth::Annotation::ModelNode* m_pModelNode;
	};

	// 注册工厂类
	REGISTER_BASEENTITY_FACTORY(CGroundRadar, "GroundRadar");
}


#endif //_GROUNDRADAR_H_

