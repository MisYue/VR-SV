/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  标绘管理系统类		                                        */
/* 时间： 2016-08-09                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PLOTSYSTEM_H_
#define _PLOTSYSTEM_H_

#pragma once

namespace VR_Soft
{
	class CPlotContrlHandle;

	class CPlotSystem : public IPlotManager
	{
	public:
		// 构造函数
		explicit CPlotSystem(const VRString& strName);
		// 析构函数
		virtual ~CPlotSystem(void);

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 初始化系统
		virtual void Init(void);

	public:
		// 创建标绘
		virtual IPlot* CreatePlot(const PLOT_MASK plotMask, const uint64_t ID, const VRString& strPlot = "Plot");
		// 设置视图名称
		virtual void SetViewerName(const VRString& strViewName);
		// 编辑标绘对象
		virtual void EidtPlot(IPlot* pIplot);

	public:
		SET_GET_PROPERTY(Name, VRString, str);

	private:
		VRString m_strName;

		CPlotContrlHandle* m_pPlotContrlHandle;
	};

	// 注册工厂类
	REGISTER_COMFACTORY(CPlotSystem, PlotManager, PLOTSYSTEM_TYPENAME, INSTANCE_NAME_PLOTSYSTEM, PLOTSYSTEM_DISC);
}


#endif // !_PLOTSYSTEM_H_