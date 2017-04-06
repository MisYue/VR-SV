/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������				                                        */
/* ʱ�䣺 2015-08-04                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _AIRLINE_H_
#define _AIRLINE_H_

#pragma once

#include <osgEarthSymbology/Style>

namespace osgEarth
{
	namespace Annotation
	{
		class FeatureNode;
	}

	namespace Symbology
	{
		class LineString;
	}

	namespace Features
	{
		class Feature;
	}
}

namespace VR_Soft
{
	class CTrajectLine : public ITrajectory
	{

	public:
		explicit CTrajectLine(void);
		virtual ~CTrajectLine(void);

	public:
		// ��ʼ��
		virtual void Init(void);
		// ��õ�������
		virtual const ListTrajectoryInfo& GetTrajectoryPoint(void) const ;
		// �����㷨
		virtual void AlgorithmTrajectoryPoint(void);
		// ���õ�������
		virtual void SetTrajectoryEntity(IEntityBase* pITrajectoryEntity) ;

	public: 
		// ��ӵ�
		virtual void AddAirLinePoint(const TrajectoryInfo& airLinePoint);
		// �Ƴ���
		virtual void RemoveAirLinePoint(const int index);
		//����㵽�ļ���
		virtual void Save(const VRString& strFile) const ;
		// ���ļ�����
		virtual void Load(const VRString& strFile) { }
		// �༭״̬����
		virtual void EnableEidt(bool bEidt);
		// ��ñ༭״̬
		virtual bool EidtState(void) const ;

	public:
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine);

	protected:
		// ��������������վ���
		virtual void GetMatrixInEarth(const osg::Vec3& vPositon) { }
		osgEarth::Symbology::Style BuildStyle(void);


	private: 
		bool m_bEidt; // �༭״̬
//		LstAirLinePoint m_lstAirPoint; // ���߹ؼ���
		osgEarth::Annotation::FeatureNode* m_pFeatureNode; // �ߵĽڵ�
		osgEarth::Features::Feature* m_pFeature; // ��ʽ
		osgEarth::Symbology::LineString* m_pLineString; // �߶���

		ITrajectory::ListTrajectoryInfo m_listTrajectroryPoint; // �켣���ݶ���
		IEntityBase* m_pIEntityBase;

		VR_AUTO_MUTEX;

	};

}

#endif // _AIRLINE_H_