/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  地磁系统接口			                                        */
/* 时间： 2015-11-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_EQUIPSYSTEM_H_
#define _PUBLIC_EQUIPSYSTEM_H_

#ifndef EQUIP_PLUGIN_EXPOT
#define EQUIP_DLL VRSOFT_DLL_IMPORT
#else
#define EQUIP_DLL VRSOFT_DLL_EXPORT
#endif

#include "../VRSoft.h"
#include "../Plugin/PluginDepined.h"
#include "IEquipManager.h"
#include "IEquip.h"
#include "IEquipPlugin.h"

#endif // !_PUBLIC_EQUIPSYSTEM_H_