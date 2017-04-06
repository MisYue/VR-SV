/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ʵ��														*/
/* ʱ�䣺 2016-04-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _SATELLITETRAJECTORYDRAW_H_
#define _SATELLITETRAJECTORYDRAW_H_

#pragma once

#include <osg/Geode>
#include <osg/MatrixTransform>

namespace VR_Soft
{
	class CSatalliteTrajectoryDraw : public IDrawTrajectory
	{
	public:
		// ���캯��
		explicit CSatalliteTrajectoryDraw();
		// ��������
		~CSatalliteTrajectoryDraw(void);

	public:
		// ����
		virtual void Update(void);
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void);
		// �����㷨����
		virtual void SetTrajectory(ITrajectory* pITrajectory) ;

	public:
		// ������ת����
		void UpdateMatrix(double dt);
	protected:
		// ��ʼ����Ⱦ��
		bool InitDrawabel(void);

		// ��ö���
		osg::Vec3Array* GetVertexArrays(ITrajectory* pITrajectory) const;


	private:
		osg::Geode* m_pGeode;
		bool m_bUpdate;
		osg::MatrixTransform* m_pMt;

		ITrajectory* m_pITrajectory;
	};

}

#endif // !_SATELLITETRAJECTORYDRAW_H_