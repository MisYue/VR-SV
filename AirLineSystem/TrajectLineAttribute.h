/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �����������			                                        */
/* ʱ�䣺 2016-05-24                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _TRAJECTLINEATTRIBUTE_H_
#define _TRAJECTLINEATTRIBUTE_H_

#pragma once

#include <osg/Geode>

namespace VR_Soft
{
/*	class CTrajectLineAttribute // : public CAttributeImp<IPathAttribute>
	{
	public:
		// ���캯��
		explicit CTrajectLineAttribute(IEntityBase* pIEntityBase);
		// ��������
		virtual ~CTrajectLineAttribute(void);
		
	public:
		// ��ʼ��
		virtual void Init();
		// �Ƿ��ƶ�
		virtual bool IsMove(void) const { return (false); }
		// ����
		virtual void Update(void) ;
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

	protected:
		// ������Ⱦ��
		void UpdateDrawable(void);
		

	public:
		// �Ƿ�༭
		void SetEnableEdit(bool bEdit);
		// ����Ƿ�༭
		bool GetEnableEdit(void) const;
		// ��ȡ����״̬
		bool GetLight(void) const;
		// ���ù���״̬
		void SetEnableLight(bool bLight);
		// ��ȡ�Ƿ���ʾ
		bool GetShowSate(void) const;
		// �����Ƿ���ʾ
		void SetShowSate(bool bShow);

	public:
		// ��������
		DECLARE_PROPERTY(CTrajectLineAttribute, bool, Edit);
		DECLARE_PROPERTY(CTrajectLineAttribute, bool, Light);
		DECLARE_PROPERTY(CTrajectLineAttribute, bool, Show);

	protected:
		// ��ʼ����Ⱦ��
		void InitDrawable();

	private:
		bool m_bEdit; // �༭
		bool m_bLight; // ����
		bool m_bShow; // �Ƿ�����
		osg::Geode* m_pGeode; // ��Ⱦ��

// 		ListPoints m_listPoints;
// 		ListPoints m_listDrawPoints; 

		osg::Geometry* m_pLineGeometry; // ������
	};
*/
}

#endif //! _TRAJECTLINEATTRIBUTE_H_
