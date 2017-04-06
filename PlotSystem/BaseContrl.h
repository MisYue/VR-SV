/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���Ƶ�ͷ�ļ�			                                        */
/* ʱ�䣺 2016-08-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _BASECONTRL_H_
#define _BASECONTRL_H_

#pragma once

#include <vector>
#include <osg/Vec3d>


namespace VR_Soft
{
	class CPlotStrategy;

	class CBaseContrl
	{
	public:
		typedef std::vector<osg::Vec3d> ListContrlPoint;

	public:
		CBaseContrl(CPlotStrategy* pPlotStrategy);
		~CBaseContrl(void);

		// ���¹�������
		void RebuildPlotStategy(void);
		// �ж��Ƿ��������
		bool IsEndDraw( void );
		// �����Ƿ��������
		inline void SetEndDraw(bool bEndDraw) { m_bEndDraw = bEndDraw; }
		// ��껬��
		void AddMouseMovePoint(const osg::Vec3d& vMousePoint);
	public:
		// �������
		virtual void AddMousePoint(const osg::Vec3d& vMousePoint);

		// ���¼���
		virtual void Rebuild(void);
		
	protected:
		ListContrlPoint m_mouseContrlPoint;
		ListContrlPoint m_keyContrlPoint;

		CPlotStrategy* m_pPlotStrategy;
		bool m_bEndDraw;
		bool m_bPress;
	};
}


#endif // !_BASECONTRL_H_