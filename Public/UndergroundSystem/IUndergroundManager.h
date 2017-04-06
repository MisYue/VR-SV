/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���·���ϵͳ�ӿ�		                                        */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IUNDERGROUNDSYSTEM_H_
#define _PUBLIC_IUNDERGROUNDSYSTEM_H_

namespace VR_Soft
{
	const VRString UNDERGROUNDSYSTEM_TYPENAME = "UNDERGROUNDSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_UNDERGROUNDSYSTEM = "UNDERGROUNDSYSTEM";
	const VRString UNDERGROUNDSYSTEM_DISC = "���·���ϵͳ";

	class VRSOFT_PLUGIN_DLL IUndergroundManager : public CSingleton<IUndergroundManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~IUndergroundManager() { }
		// ������ʾ����ͼ����
		virtual void SetViewName(const VRString& strViewName = "mainView") = 0;
	};
}

#endif // _PUBLIC_IUNDERGROUNDSYSTEM_H_