#ifndef _PLUGINDEPIEND_H_
#define _PLUGINDEPIEND_H_

#pragma once

#ifdef _DEBUG

// ���������VRSOFT_EXPORT
#ifndef VRSOFT_EXPORT
#pragma comment(lib, "../Corelib/Debug/ComManager.lib")
#endif

// ���ÿ���
#ifndef VRSOFT_TOOLCLASS_EXPORT
//#pragma comment(lib, "../Corelib/Debug/ToolClass.lib")
#endif

#else


#ifndef VRSOFT_EXPORT
#pragma comment(lib, "../Corelib/Release/ComManager.lib")
#endif

#endif

#endif // _PLUGINDEPIEND_H_