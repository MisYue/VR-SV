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
		virtual bool setMode(bool bUseLight = false, bool bUseBlend = true){return (true);}			//���ù������ϵ�״̬
		virtual bool setDrawMask(eDrawMask mask){return (true);}										//��ʾ����

		//���º����У�RadiusӦ�������ã�GridӦ��Area����ã��״���Ļ�����á���������󣬻᷵��false��
		//����densityΪ��ʾ���ȣ�ǰ׺ h - HORIZONTAL  v - VERTICAL��
		virtual bool setRadius(double radius){return (true);}											//ɨ��뾶
		virtual bool setDirection(osg::Vec3d up, osg::Vec3d front){return (true);}						//�����״������������еķ���
		virtual bool setArea(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor){return (true);}				//�����ɨ�������
		virtual bool setRay(double hMin, double hMax, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor){return (true);}				//ĳʱ�̿�ɨ�赽������
		virtual bool setGrid(int hDensity, int vDensity, double lineWidth , osg::Vec4d gridColor){return (true);}						//����ɨ������������������
		virtual bool setLoopTime(eSpyType spyType, eLoopType loopType, double loopTime){return (true);}								//����ɨ������

		virtual bool setPhasedArrayRay(double hRange, double vMin, double vMax, int density , osg::Vec4d surfaceColor, osg::Vec4d sideColor){return (true);}				//ĳʱ�̿�ɨ�赽������
		virtual void setPhasedArrayLoopTime(){}																			//�����

		//�״���Ļ���
		virtual bool setSpyNode(osg::Node * pSpyNode , osg::Node * pNoSpyNode = NULL){return (true);}			//������Ҫɨ��Ľڵ����Ҫ�ų��Ľڵ�
		virtual bool setScreen(eSpyType spyType, int rDensity, int aDensity, osg::Vec2d screenCenter = osg::Vec2d( 150.0, 150.0), double screenRadius = 150){return (true);}
		// ��ȡ��Ⱦ�ڵ�
		virtual osg::Node* GetDrawObj(osgEarth::MapNode* pMapNode);
		// ��ȡ��Ⱦ�ڵ�
		virtual osg::Node* GetDrawObj(void);
		// �������
		virtual const VRString GetEntityType(void) const;
		// ��������
		virtual void SetName(const VRString& strName);

		//registerObserver/unregisterObserver
		
		// ��ʼ��
		virtual void Init(void);
		// ����ģ��
		virtual void EntityUpdate(double dt);
		// �������Զ���
		virtual IAttribute* CreateAttribute(void);
		// ɨ����Ⱦ
		virtual void ScanRender(void) { }

	public:
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine);

	public:
		// ��Ⱦ����
		void DrawFx(void);

	protected:
		// ��������������վ���
		virtual void GetMatrixInEarth(const osg::Vec3& vPositon)  { }

	private:
		/*osg::ref_ptr<*/osg::MatrixTransform/*> */ *m_pMt;
		osg::Geode* m_pGeode;

		osgEarth::Annotation::ModelNode* m_pModelNode;
	};

	// ע�Ṥ����
	REGISTER_BASEENTITY_FACTORY(CGroundRadar, "GroundRadar");
}


#endif //_GROUNDRADAR_H_

