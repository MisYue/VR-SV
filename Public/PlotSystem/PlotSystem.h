/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ϵͳ��ͷ�ļ�����	                                        */
/* ʱ�䣺 2016-08-09                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_PLOTSYSTEM_H_
#define _PUBLIC_PLOTSYSTEM_H_

#include "../../Public/VRSoft.h"

// ���嵼����
#ifndef OSGPLOT_PLUGIN_EXPORT
#define OSGRPLOT_DLL VRSOFT_DLL_IMPORT
#else
#define OSGRPLOT_DLL VRSOFT_DLL_EXPORT
#endif 

#if defined(OSGEARTH) 

#include <osgEarthSymbology/Geometry>

#define OsgEarthGeomtry osgEarth::Symbology::Geometry

#else

#define OsgEarthGeomtry void

#endif

#include "IPlotContrlHandle.h"
#include "IPlot.h"
#include "IPlotManager.h"
#include "PlotImp.h"
#include "IPlaceFeatureGeomtry.h"


#endif // !_PUBLIC_PLOTSYSTEM_H_