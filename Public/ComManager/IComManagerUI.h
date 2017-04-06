/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������ӿ�                                              */
/* ʱ�䣺 2015-07-23                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ICOMMANAGERUI_H_
#define _ICOMMANAGERUI_H_

namespace VR_Soft
{
	class IPluginManagerUI;

	class IComManagerUI
	{

	public: 
		enum LoadType
		{
			Default = 0x0001, // Ĭ�ϼ��� ���ܱ��
			Loaded = 0x0002, // �Ѿ�����
			UnLoad = 0x0004// δ����
		};

		typedef struct PluginInfo_TYP
		{
			IPlugin* _pPlugin; // ���ָ��
			int _loadType; // ��չ

			PluginInfo_TYP():_pPlugin(NULL), _loadType(UnLoad)
			{

			}

			PluginInfo_TYP(IPlugin* pPlugin):_pPlugin(pPlugin), _loadType(UnLoad)
			{

			}

			bool operator==(IPlugin* pPlugin)
			{
				return (pPlugin == _pPlugin);
			}

		}PluginInfo, *PTR_PluginInfo;

		typedef std::list<PluginInfo> PluginInfoList;

	public:
		// ��������
		virtual ~IComManagerUI() { }

		// ͨ������ע����
		virtual void InstallPlugin(const VRString& strPluginName) = 0;
		// ͨ������ж�ز��
		virtual void UnInstallPlugin(const VRString& strPluginName) = 0;
		// ע�ᴰ��
		virtual void RegisterUI(IPluginManagerUI* pIPluginManagerUI) = 0;
		// ��ע�ᴰ��
		virtual void UnRegisterUI(IPluginManagerUI* pIPluginManagerUI) = 0;
	};
}

#endif