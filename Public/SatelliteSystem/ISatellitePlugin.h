/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ����������												*/
/* ʱ�䣺 2015-11-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ISATELLITEPLUGIN_H_
#define _PUBLICE_ISATELLITEPLUGIN_H_

namespace VR_Soft
{
#define INSTALL_SATELLITEPLUGIN(export_marco, classname, basetype) \
	EXTERN_CPP export_marco void InstallSatellitePlugin(IEntityFactoryManager* pIEntiryFactoryManager) \
	{ \
	pIEntiryFactoryManager->RegisterFactory(CREATE_BASEENTITY_FACTORY(classname)); \
}\
	EXTERN_CPP export_marco void UnInstallSatellitePlugin(IEntityFactoryManager* pIEntiryFactoryManager) \
	{ \
	const VRString strType = basetype; \
	pIEntiryFactoryManager->UnRegisterFactory(strType); \
}\

}

#endif