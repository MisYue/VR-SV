/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ֱ�߱���ͷ�ļ�		                                        */
/* ʱ�䣺 2016-08-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PLOTLINE_H_
#define _PLOTLINE_H_

#pragma once

#include <osgEarthAnnotation/FeatureNode>

namespace VR_Soft
{
	class CPlotLine 
	{
	public:
		// ���캯��
		CPlotLine(IEntityBase* pIEntityBase);
		// ��������
		virtual ~CPlotLine(void);

	private:
		osgEarth::Annotation::FeatureNode* m_pFeatureNode;
	};

}


#endif // !_PLOTLINE_H_