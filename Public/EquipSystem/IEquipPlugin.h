/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备插件入口类												*/
/* 时间： 2015-11-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLI_IEQUIPPLUIN_H_
#define _PUBLI_IEQUIPPLUIN_H_

#include "../VRSoft.h"

namespace VR_Soft
{
#define INSTALL_EQUIPPLUGIN(export_marco, classname, basetype) \
	EXTERN_CPP export_marco void InstallEquipPlugin(IEntityFactoryManager* pIEntiryFactoryManager) \
	{ \
	pIEntiryFactoryManager->RegisterFactory(CREATE_BASEENTITY_FACTORY(classname)); \
	}\
	EXTERN_CPP export_marco void UnInstallEquipPlugin(IEntityFactoryManager* pIEntiryFactoryManager) \
	{ \
	const VRString strType = basetype; \
	pIEntiryFactoryManager->UnRegisterFactory(strType); \
	}\

}

#endif // !_PUBLI_IEQUIPPLUIN_H_