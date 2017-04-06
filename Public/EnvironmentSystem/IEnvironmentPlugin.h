/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������������												*/
/* ʱ�䣺 2015-11-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IENVIRONMENTPLUGIN_H_
#define _PUBLICE_IENVIRONMENTPLUGIN_H_

namespace VR_Soft
{
#define INSTALL_ENVIRONMENTPLUGIN(export_marco, classname, basetype) \
	EXTERN_CPP export_marco void InstallEnvironmentPlugin(IEntityFactoryManager* pIEntiryFactoryManager) \
	{ \
	pIEntiryFactoryManager->RegisterFactory(CREATE_BASEENTITY_FACTORY(classname)); \
}\
	EXTERN_CPP export_marco void UnInstallEnvironmentPlugin(IEntityFactoryManager* pIEntiryFactoryManager) \
	{ \
	const VRString strType = basetype; \
	pIEntiryFactoryManager->UnRegisterFactory(strType); \
}\

}

#endif // !_PUBLICE_IENVIRONMENTPLUGIN_H_