/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������������������	                                        */
/* ʱ�䣺 2016-05-31                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _BALLMISSILEATTRIBUTE_H_
#define _BALLMISSILEATTRIBUTE_H_

#pragma once

#include <osg/Geode>
#include <osg/Geometry>

namespace VR_Soft
{
/*
	class CBallMissileAttribute // : public CAttributeImp<IPathAttribute>
	{
	public:
		CBallMissileAttribute(IEntityBase* pIEntityBase);
		virtual ~CBallMissileAttribute(void);

	public:
		// ��ʼ��
		virtual void Init();
		// ���º���
		virtual void Update();
		// �Ƿ��ƶ�
		virtual bool IsMove(void) const { return (false); }
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void) ;

	public:
		// ���һ�������������
		virtual void AddKeyPoint(const osg::Vec3d& vPos);
		// �Ƴ�һ����
		virtual void RemoveKeyPoint(const int index);
		// ���ĵ�
		virtual void ChangeKeyPoint(const int index, const osg::Vec3d& vPos);
		// ���ĳһ���ؼ���
		virtual osg::Vec3d GetKeyPoint(int index) const;
// 		// ���·���ؼ���
// 		virtual const ListPoints& GetKeyPoints(void) const;
// 		// ���·����
// 		virtual const ListPoints& GetPathPoints(void) const ;
		// ���ָ��·����
		virtual osg::Vec3d GetPathPoint(const int index) const;

	public:
		// �Ƿ�༭
		void SetEnableEdit(bool bEdit);
		// ����Ƿ�༭
		bool GetEnableEdit(void) const;
		// ���ÿ�ʼ��
		void SetStartPoint(const osg::Vec3d& vStart);
		// ��ÿ�ʼ��
		osg::Vec3d GetStartPoint(void) const;
		// ���ý�����
		void SetEndPoint(const osg::Vec3d& vEnd) ;
		// ��ý�����
		osg::Vec3d GetEndPoint(void) const;
		// ������ߵ�
		void SetHeight(double dHeight);
		// �����ߵ�
		double GetHeight(void) const;
		// ������Ⱦ��
		void UpdateDrawable( void );
	public:
		// ��������
		DECLARE_PROPERTY(CBallMissileAttribute, bool, Edit);
		DECLARE_PROPERTY(CBallMissileAttribute, osg::Vec3d, StartPoint);
		DECLARE_PROPERTY(CBallMissileAttribute, osg::Vec3d, EndPoint);
		DECLARE_PROPERTY(CBallMissileAttribute, double, Height);

	protected:
		// ��ʼ����Ⱦ��
		void InitDrawable();

	private:
		bool m_bEdit; // �༭
		osg::Vec3d m_vStart; // ��ʼ��
		osg::Vec3d m_vStop; // ������
		double m_dHeight; // �߶�

		osg::Geode* m_pGeode; // ��Ⱦ��

		ListPoints m_listPoints;
		ListPoints m_listDrawPoints; 

		osg::Geometry* m_pLineGeometry; // ������
	};
	*/
}

#endif //  _BALLMISSILEATTRIBUTE_H_