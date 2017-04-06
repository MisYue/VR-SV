/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备插件入口类												*/
/* 时间： 2016-04-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLI_IAIRLINEPPLUIN_H_
#define _PUBLI_IAIRLINPLUIN_H_

#include "../VRSoft.h"

namespace VR_Soft
{
#define INSTALL_AIRLINPLUGIN(export_marco, classname, basetype) \
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

#endif // !_PUBLI_IAIRLINPLUIN_H_