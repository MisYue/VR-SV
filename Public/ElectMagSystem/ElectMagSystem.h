/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �ش�ϵͳ�ӿ�			                                        */
/* ʱ�䣺 2015-06-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_ELECTMAGSYSTEM_H_
#define _PUBLIC_ELECTMAGSYSTEM_H_

#ifndef ELECTMAG_PLUGIN_EXPOT
#define ELECTMAG_DLL VRSOFT_DLL_IMPORT
#else
#define ELECTMAG_DLL VRSOFT_DLL_EXPORT
#endif

#include "../VRSoft.h"
#include "../Plugin/PluginDepined.h"
#include "IElecMagManager.h"
#include "IRadar.h"
#include "IElectPlugin.h"
#include "IBaseElectAttribute.h"

#endif // _PUBLIC_ELECTMAGSYSTEM_H_