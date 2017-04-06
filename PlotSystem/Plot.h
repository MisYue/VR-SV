/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ͷ�ļ�			                                        */
/* ʱ�䣺 2016-08-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PLOT_H_
#define _PLOT_H_
#endif //  _PLOT_H_

#pragma once

namespace VR_Soft
{
	class CPlot : public CPlotImp<IPlot>
	{
	public:
		// ���캯��
		CPlot(const uint64_t ID, const VRString& strName);
		// ��������
		virtual ~CPlot(void);

	public:
		
		void Rebuild( const std::vector<osg::Vec3d>& listPlotPoints );
	

	};
}


