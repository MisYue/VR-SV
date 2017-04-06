/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ����������												*/
/* ʱ�䣺 2016-04-01                                                    */
/* �޸�ʱ��:                                                            */
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