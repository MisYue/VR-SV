/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������������ӿ�                                          */
/* ʱ�䣺 2015-07-23                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IPLUGINMANGERUI_H_
#define _IPLUGINMANGERUI_H_

namespace VR_Soft
{
	class IPluginManagerUI
	{
	public:
		// ��������
		virtual ~IPluginManagerUI(void) 
		{
			IComManager::GetInstance().GetComManagerUI()->UnRegisterUI(this);
		}
		// ��ʼ��
		virtual void InitUI(const IComManagerUI::PluginInfoList& lstPluginInfo) = 0;
	};
}

#endif // _IPLUGINMANGERUI_H_