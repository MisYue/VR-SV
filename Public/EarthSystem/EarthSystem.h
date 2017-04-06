/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  Earth头文件		                                            */
/* 时间： 2015-05-28                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_EARTHSYSTEM_H_
#define _PUBLIC_EARTHSYSTEM_H_

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"

// 定义导出宏
#ifndef EARTHSYSTEM_EXPORTS
#define OSGEARTH_DLL VRSOFT_DLL_IMPORT
#else
#define OSGEARTH_DLL VRSOFT_DLL_EXPORT
#endif 

#include "IEarth.h"
#include "IEarthManipulator.h"
#include "IEartManager.h"
#include "ISolarConfig.h"
#include "ISynchroManipManager.h"
#include "IEarthLayerManager.h"
#include "IFeature.h"
#include "IFeatureManager.h"

#endif // !_PUBLIC_EARTHSYSTEM_H_