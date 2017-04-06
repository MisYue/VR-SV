#pragma once

namespace VR_Soft
{
	class CSignalWave : public osg::MatrixTransform , public ICommonWave
	{
	public:
		explicit CSignalWave(void);
		virtual ~CSignalWave(void);

		//radius 底面圆形的半径，sampleVerticesCount 圆形使用多边形模拟的采样点数量， delta_offset采样起始点的角度偏移量。
		virtual bool createShape( double radius_start , double radius_end, eShapeType type, int sampleVerticesCount = 32 , double delta_offset = 0.0 );
		//colorMask由低位向高位，对应发射方向。bit为1时取primaryColor，为0时取secondaryColor。textureHeight为这张纹理贴到物体上的物理高度。

		virtual bool setTexture( osg::Vec4 color, int colorMask, double textureHeight );

		//跑过一个纹理所需时间，单位秒。
		//开始传输，输入当前时间，返回上一次使用的时间。
		virtual double startTrans(double loopTime_s);
		//停止传输，返回当前时间。
		virtual void stopTrans();

		//改变起点、终点，直角坐标系。
		virtual bool setPosition(osg::Vec3d start, osg::Vec3d end);

		virtual osg::Node* GetDrawObj(osgEarth::MapNode* pMapNode); // 获取渲染节点
		virtual osg::Node* GetDrawObj(void); // 获取渲染节点
		// 获得类型
		virtual const VRString GetEntityType(void) const;
		// 设置名称
		virtual void SetName(const VRString& strName);

		//registerObserver/unregisterObserver
		//virtual osg::BoundingSphere computeBound() const;
		// 初始化
		virtual void Init(void);
		// 创建属性对象
		virtual IAttribute* CreateAttribute(void);

	public:
		// 初始化状态机
		virtual void InitStateMachine(IStateMachine* pIStateMachine);

	protected:
		// 获得依赖地球最终矩阵
		virtual void GetMatrixInEarth(const osg::Vec3& vPositon)  { }

	private:

		int		_sampleVerCnt;			//圆的采样点数
		double	_objHeight;			//圆锥或圆柱的高度。用于纹理坐标计算。
		double	_TexHeight;			//纹理的物理高度，用于纹理移动。

		osg::ref_ptr<osg::Geode> _pGeode;

		eShapeType _eShapeType;

	private:
		class SignalCallBack : public osg::Drawable::UpdateCallback
		{
		public:
			SignalCallBack();
			virtual void update(osg::NodeVisitor * nv, osg::Drawable * drawable);

			double			_loopTime;
			osg::Timer		clock;
			osg::Timer_t	lastTime;
		};
	};

	// 注册工厂类
	REGISTER_BASEENTITY_FACTORY(CSignalWave, "commontType");
}

