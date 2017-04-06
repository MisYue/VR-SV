/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ͨ�Ų��ӿ�			                                        */
/* ʱ�䣺 2015-06-18                                                    */
/* �޸�ʱ��:                                                            */
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
		//radius ����Բ�εİ뾶��sampleVerticesCount Բ��ʹ�ö����ģ��Ĳ����������� delta_offset������ʼ��ĽǶ�ƫ������
		virtual bool createShape( double radius_start , double radius_end, eShapeType type, int sampleVerticesCount = 32 , double delta_offset = 0.0 ) = 0;
		//colorMask�ɵ�λ���λ����Ӧ���䷽��bitΪ1ʱȡprimaryColor��Ϊ0ʱȡsecondaryColor��textureHeightΪ�����������������ϵ�����߶ȡ�

		virtual bool setTexture( osg::Vec4 color, int colorMask, double textureHeight ) = 0;

		//�ܹ�һ����������ʱ�䣬��λ�롣
		//��ʼ���䣬���뵱ǰʱ�䣬������һ��ʹ�õ�ʱ�䡣
		virtual double startTrans(double loopTime_s) = 0;
		//ֹͣ���䣬���ص�ǰʱ�䡣
		virtual void stopTrans() = 0;

		//�ı���㡢�յ㣬ֱ������ϵ��
		virtual bool setPosition(osg::Vec3d start, osg::Vec3d end) = 0;
	};
}

#endif // _PULBIC_ICOMMONWAVE_H_