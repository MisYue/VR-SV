/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ָ����ͷ�ļ�		                                        */
/* ʱ�䣺 2016-06-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_ACITONPLUGIN_H_
#define _PUBLIC_ACITONPLUGIN_H_ 

namespace VR_Soft
{
	class VRSOFT_DLL IActionFactory
	{
	public:
		// ��������
		virtual ~IActionFactory(void) { }
		// �������
		virtual const VRString& GetName(void) const = 0;
		// ����ʵ��
		virtual IAction* CreateInstance(void) = 0;
	};

#define DEFINED_ACTIONFACTORY(EXPORT_DLL, CLASSNAME, ACTIONNAME)						\
	class EXPORT_DLL CLASSNAME##Factory : public IActionFactory							\
	{																					\
	public:																				\
		CLASSNAME##Factory(void):m_strActionName(ACTIONNAME) { }						\
		virtual ~CLASSNAME##Factory(void) { }											\
		virtual const VRString& GetName(void) const { return (m_strActionName); }		\
		virtual IAction* CreateInstance(void) { return (new CLASSNAME); }				\
	private:																			\
		VRString m_strActionName;														\
	};																					\
	EXTERN_CPP EXPORT_DLL void DllInstallAction(void)									\
	{																					\
		IActionFactory* pIActionFactory = new CLASSNAME##Factory;						\
		IActionManager::GetInstance().AddFactory(pIActionFactory);						\
	}																					\
	EXTERN_CPP EXPORT_DLL void DllUnInstallPlugin(void)									\
	{																					\
		IActionManager::GetInstance().RemoveFactory(ACTIONNAME);						\
	}																					
}

#endif // !_PUBLIC_ACITONPLUGIN_H_