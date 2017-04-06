/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �״�ӿ�														*/
/* ʱ�䣺 2015-05-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IRADAR_H_
#define _IRADAR_H_

#pragma once

#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osgSim/SphereSegment>

namespace VR_Soft
{
	extern VRString RADARTYPE;	
	class VRSOFT_PLUGIN_DLL IRadar : public IEntityBase
	{
	public:
		enum DrawMode
		{
			LINE_MODE = 0x01, // ��ģʽ
			FACE_MODE = 0x02, // ��ģʽ
			ALL_MODE = 0x04 // ȫ����Ⱦ
		};

	public:
		// ���ð뾶
		virtual void SetRadius(float fRaius) = 0;
		// ��ð뾶
		virtual float GetRadius(void) const = 0;
		// ����ɨ���ٶ�
		virtual void SetScanSpeed(float fSpeed) = 0;
		// ���ɨ���ٶ�
		virtual float GetScanSpeed(void) const = 0;
		// ������ɫ
		virtual void SetColor(const osg::Vec4& vFaceColor, const osg::Vec4& vScanColor) = 0;
		// �����ɫ
		virtual void GetColor(osg::Vec4& vFaceColor, osg::Vec4& vScanColor) = 0;
		// ������Ⱦģʽ
		virtual void SetDrawMode(const DrawMode dm) = 0;
		// �����Ⱦģʽ
		virtual DrawMode GetDrawMode(void) const = 0;
		// ����������
		virtual void SetWireframeCount(int nCount) = 0;
		// ����������
		virtual int GetWireframeCount(void) const = 0;
		// ����ɨ�迪��
		virtual void SetScanState(bool bOpen) = 0;
		// ���ɨ�迪��
		virtual bool GetScanState(void) const = 0;
	};
}

#endif