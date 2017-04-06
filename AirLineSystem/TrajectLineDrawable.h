/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �����														*/
/* ʱ�䣺 2016-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _TRAJECTLINEDRAWABLE_H_
#define _TRAJECTLINEDRAWABLE_H_

#pragma once

#include <osg/Geode>

namespace VR_Soft
{
	class CTrajectLineDrawable : public CAttributeImp<IDrawAttribute>
	{
	public:
		// ���캯��
		CTrajectLineDrawable(void);
		// ��������
		virtual ~CTrajectLineDrawable(void);

	public:
		// ����
		virtual void Update(void);
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void);
		// �����㷨����
		virtual void SetTrajectory(ITrajectory* pITrajectory) ;

	protected:
		// ��ʼ����Ⱦ��
		bool InitDrawabel(void);

		// ��ö���
		osg::Vec3Array* GetVertexArrays(ITrajectory* pITrajectory) const;

	private:
		osg::Geode* m_pGeode;
		bool m_bUpdate;

		ITrajectory* m_pITrajectory;
	};
}


#endif // !_TRAJECTLINEDRAWABLE_H_