/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������ϵͳ��		                                        */
/* ʱ�䣺 2016-08-09                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���캯��
		explicit CPlotSystem(const VRString& strName);
		// ��������
		virtual ~CPlotSystem(void);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��ʼ��ϵͳ
		virtual void Init(void);

	public:
		// �������
		virtual IPlot* CreatePlot(const PLOT_MASK plotMask, const uint64_t ID, const VRString& strPlot = "Plot");
		// ������ͼ����
		virtual void SetViewerName(const VRString& strViewName);
		// �༭������
		virtual void EidtPlot(IPlot* pIplot);

	public:
		SET_GET_PROPERTY(Name, VRString, str);

	private:
		VRString m_strName;

		CPlotContrlHandle* m_pPlotContrlHandle;
	};

	// ע�Ṥ����
	REGISTER_COMFACTORY(CPlotSystem, PlotManager, PLOTSYSTEM_TYPENAME, INSTANCE_NAME_PLOTSYSTEM, PLOTSYSTEM_DISC);
}


#endif // !_PLOTSYSTEM_H_