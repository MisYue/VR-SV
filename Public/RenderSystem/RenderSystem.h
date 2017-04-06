/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  视图插件的头文件集合	                                        */
/* 时间： 2015-05-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_RENDERSYSTEM_H_
#define _PUBLIC_RENDERSYSTEM_H_

#include "../../Public/VRSoft.h"

// 定义导出宏
#ifndef OSGRENDER_PLUGIN_EXPORT
#define OSGRENDER_DLL VRSOFT_DLL_IMPORT
#else
#define OSGRENDER_DLL VRSOFT_DLL_EXPORT
#endif 

#include "IRenderViewUI.h"
#include "IRenderView.h"
#include "IRenderViewUI.h"
#include "IViewManager.h"
#include "IManipulatorManager.h"
#include "IScreenHUD.h"
#include "IScreenHUDManager.h"
#include "IRenderManager.h"
#include "IDrawAttributeFactory.h"
#include "IMeshManager.h"

#endif // _PUBLIC_RENDERSYSTEM_H_