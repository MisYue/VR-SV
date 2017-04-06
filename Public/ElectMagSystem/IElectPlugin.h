/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  电磁插件入口类												*/
/* 时间： 2015-08-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLI_IELECTDLL_H_
#define _PUBLI_IELECTDLL_H_

#include "../VRSoft.h"

// 插件导入导出
#if defined(VRSOFT_ELECTPLUGIN_EXPORT)
# define VRSOFT_ELECTPLUGIN_DLL VRSOFT_DLL_EXPORT
#else
# define VRSOFT_ELECTPLUGIN_DLL VRSOFT_DLL_IMPORT
#endif

namespace VR_Soft
{
#define INSTALL_ELECTPLUGIN(classname, basetype) \
	EXTERN_CPP void VRSOFT_ELECTPLUGIN_DLL InstallElectPlugin(IEntityFactoryManager* pIEntiryFactoryManager) \
	{ \
		pIEntiryFactoryManager->RegisterFactory(CREATE_BASEENTITY_FACTORY(classname)); \
	}\
	EXTERN_CPP void VRSOFT_ELECTPLUGIN_DLL UnInstallElectPlugin(IEntityFactoryManager* pIEntiryFactoryManager) \
	{ \
		const VRString strType = basetype; \
		pIEntiryFactoryManager->UnRegisterFactory(strType); \
	}\

}

#endif //  _PUBLI_IELECTDLL_H_