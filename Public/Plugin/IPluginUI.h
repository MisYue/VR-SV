/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���UI�ӿ�ͨ����չ�ӿ�ʵ��QT��������UI�ӿ�					*/
/* ʱ�䣺 2015-05-21                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IPLUGINUI_H_
#define _IPLUGINUI_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL IPluginUI
	{
	public:
		// ��ʼ������
		virtual void InitUI(void* param = NULL, int nParam = 0) { }
		// �������
		virtual const VRString GetUIName(void) const { return ("no ui"); }
		// ����UI
		virtual void Update(void* param = NULL, int nParam = 0 ) { }
		// ������ʼ��
		virtual void UnInit(void) { }
	};
}

#endif //_IPLUGINUI_H_