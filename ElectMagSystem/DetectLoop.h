#pragma once

#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osgSim/SphereSegment>


//�ݲ�֧��ˮƽ����ֱ����ͬʱʹ�á���ֱ����δ���ϸ����
namespace VR_Soft
{
	class DetectLoop : public osg::MatrixTransform , public IRadar
	{
		friend class SpyCallback;
	public:
		explicit DetectLoop(void);
		virtual ~DetectLoop(void);

	public:

		virtual bool setMode(bool bUseLight = false, bool bUseBlend = true);			//���ù������ϵ�״̬
		virtual bool setDrawMask(eDrawMask mask);										//��ʾ����

		//���º����У�RadiusӦ�������ã�GridӦ��Area����ã��״���Ļ�����á���������󣬻᷵��false��
		//����densityΪ��ʾ���ȣ�ǰ׺ h - HORIZONTAL  v - VERTICAL��
		virtual bool setRadius(double radius);											//ɨ��뾶
		virtual bool setDirection(osg::Vec3d up, osg::Vec3d front);						//�����״������������еķ���
		virtual bool setArea(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor);				//�����ɨ�������
		virtual bool setRay(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor);				//ĳʱ�̿�ɨ�赽������
		virtual bool setGrid(int hDensity, int vDensity, double lineWidth , osg::Vec4d gridColor);						//����ɨ������������������
		virtual bool setLoopTime(eSpyType spyType, eLoopType loopType, double loopTime);								//����ɨ������

		virtual bool setPhasedArrayRay(double hRange, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor);				//ĳʱ�̿�ɨ�赽������
		virtual void setPhasedArrayLoopTime();																			//�����

		//�״���Ļ���
		virtual bool setSpyNode(osg::Node * pSpyNode , osg::Node * pNoSpyNode = NULL);			//������Ҫɨ��Ľڵ����Ҫ�ų��Ľڵ�
		virtual bool setScreen(eSpyType spyType, int rDensity, int aDensity, osg::Vec2d screenCenter = osg::Vec2d( 150.0, 150.0), double screenRadius = 150);
		
		// �������
		virtual const VRString GetEntityType(void) const;
		// ��������
		virtual void SetName(const VRString& strName);

		//registerObserver/unregisterObserver
		virtual osg::BoundingSphere computeBound() const;
		// ��ʼ��
		virtual void Init(void);
		 // ��ȡ��Ⱦ�ڵ�
		virtual osg::Node* GetDrawObj(osgEarth::MapNode* pMapNode);
		// �����Ⱦ�ڵ�
		virtual osg::Node* GetDrawObj(void);
		// �������Զ���
		virtual IAttribute* CreateAttribute(void);
		// ɨ����Ⱦ
		virtual void ScanRender(void) { }
	public:
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine);

	protected:

		bool screenFlash(osg::Vec3d pt, double radius);		//�����ֵ�Ŀ����ʾ���״���Ļ�ϡ���Ӧ��ӹ۲����б�ɨ�赽����ʱ֪ͨ��λ�úͰ뾶��

	protected:
		// ��������������վ���
		virtual void GetMatrixInEarth(const osg::Vec3& vPositon)  { }


	private:
		osg::ref_ptr<osg::MatrixTransform> _pRoot;		

		//�״�ɨ�跶Χ
		osg::ref_ptr<osg::PositionAttitudeTransform> _pRot_V_PAT;			//��ֱ�任�ڵ�
		osg::ref_ptr<osg::PositionAttitudeTransform> _pRot_H_PAT;			//ˮƽ�任�ڵ�

		double _radius;

		osg::ref_ptr<osg::Group> _pArea;
		osg::ref_ptr<osg::Group> _pRay;
		osg::ref_ptr<osg::Group> _pGrid;

	public:
		osg::ref_ptr<osgSim::SphereSegment> _pSSArea;
		osg::ref_ptr<osgSim::SphereSegment> _pSSRay;
		osg::ref_ptr<osg::Geode> _pSSGrid;
	};

	// ע�Ṥ����
	REGISTER_BASEENTITY_FACTORY(DetectLoop, "radarType");
}

