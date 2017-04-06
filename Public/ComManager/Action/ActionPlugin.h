/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  指令插件头文件		                                        */
/* 时间： 2016-06-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_ACITONPLUGIN_H_
#define _PUBLIC_ACITONPLUGIN_H_ 

namespace VR_Soft
{
	class VRSOFT_DLL IActionFactory
	{
	public:
		// 析构函数
		virtual ~IActionFactory(void) { }
		// 获得名称
		virtual const VRString& GetName(void) const = 0;
		// 创建实体
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