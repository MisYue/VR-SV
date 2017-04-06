/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������ϵͳ�ӿ�		                                        */
/* ʱ�䣺 2016-08-09                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IPLOTMANAGER_H_
#define _PUBLIC_IPLOTMANAGER_H_

#include "../../Public/VRSoft.h"



namespace VR_Soft
{
	const VRString PLOTSYSTEM_TYPENAME = "PLOTSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_PLOTSYSTEM = "PLOTSYSTEM";
	const VRString PLOTSYSTEM_DISC = "���ϵͳ";

	typedef unsigned int PLOT_MASK;

	class OSGRPLOT_DLL IPlotManager : public IComManagerFace
	{
	public:
		// ��������
		virtual ~IPlotManager(void) { }
		// �������
		virtual IPlot* CreatePlot(const PLOT_MASK plotMask, const uint64_t ID, const VRString& strPlot = "Plot") = 0;
		// ������ͼ����
		virtual void SetViewerName(const VRString& strViewName) = 0;
		// �༭������
		virtual void EidtPlot(IPlot* pIplot) = 0;
	};
}

#endif // !_PUBLIC_IPLOTMANAGER_H_