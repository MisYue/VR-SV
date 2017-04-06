/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ų�������												*/
/* ʱ�䣺 2015-08-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLI_IELECTDLL_H_
#define _PUBLI_IELECTDLL_H_

#include "../VRSoft.h"

// ������뵼��
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