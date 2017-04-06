/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  通信波接口			                                        */
/* 时间： 2015-06-18                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PULBIC_ICOMMONWAVE_H_
#define _PULBIC_ICOMMONWAVE_H_

#include <osg/MatrixTransform>
#include <osg/Geode>


namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL ICommonWave : public CEntityBaseImp<IEntityBase>
	{
	public:
		enum eShapeType		
		{
			Shape_Circle = 1,
			Shape_Triangle = 2,
			Shape_Quad = 3
		};

	public:
		virtual ~ICommonWave() { };
		//radius 底面圆形的半径，sampleVerticesCount 圆形使用多边形模拟的采样点数量， delta_offset采样起始点的角度偏移量。
		virtual bool createShape( double radius_start , double radius_end, eShapeType type, int sampleVerticesCount = 32 , double delta_offset = 0.0 ) = 0;
		//colorMask由低位向高位，对应发射方向。bit为1时取primaryColor，为0时取secondaryColor。textureHeight为这张纹理贴到物体上的物理高度。

		virtual bool setTexture( osg::Vec4 color, int colorMask, double textureHeight ) = 0;

		//跑过一个纹理所需时间，单位秒。
		//开始传输，输入当前时间，返回上一次使用的时间。
		virtual double startTrans(double loopTime_s) = 0;
		//停止传输，返回当前时间。
		virtual void stopTrans() = 0;

		//改变起点、终点，直角坐标系。
		virtual bool setPosition(osg::Vec3d start, osg::Vec3d end) = 0;
	};
}

#endif // _PULBIC_ICOMMONWAVE_H_