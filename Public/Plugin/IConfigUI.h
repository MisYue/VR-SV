/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������ӿ�			                                        */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ICONFIGUI_H_
#define _ICONFIGUI_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL IConfigUI : public IPluginUI
	{
	public:
		// ����
		virtual ~IConfigUI() {}
		// ��ʼ��
		virtual void InitUI(void* param = NULL) = 0;
	};
}

#endif // _ICONFIGUI_H_