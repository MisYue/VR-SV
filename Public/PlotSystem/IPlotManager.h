/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  标绘管理系统接口		                                        */
/* 时间： 2016-08-09                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IPLOTMANAGER_H_
#define _PUBLIC_IPLOTMANAGER_H_

#include "../../Public/VRSoft.h"



namespace VR_Soft
{
	const VRString PLOTSYSTEM_TYPENAME = "PLOTSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_PLOTSYSTEM = "PLOTSYSTEM";
	const VRString PLOTSYSTEM_DISC = "标绘系统";

	typedef unsigned int PLOT_MASK;

	class OSGRPLOT_DLL IPlotManager : public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~IPlotManager(void) { }
		// 创建标绘
		virtual IPlot* CreatePlot(const PLOT_MASK plotMask, const uint64_t ID, const VRString& strPlot = "Plot") = 0;
		// 设置视图名称
		virtual void SetViewerName(const VRString& strViewName) = 0;
		// 编辑标绘对象
		virtual void EidtPlot(IPlot* pIplot) = 0;
	};
}

#endif // !_PUBLIC_IPLOTMANAGER_H_