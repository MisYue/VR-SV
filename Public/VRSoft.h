/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���õĽӿ�			                                        */
/* ʱ�䣺 2015-05-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _VRSOFT_H_
#define _VRSOFT_H_

#include <assert.h>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// ����boost_1_58_0�� 
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/make_unique.hpp>

#include "VRConfig.h"
#include "ErrorInfo.h"
#include "Include/SingleTmp.h"
#include "Thread/VRThread.h"
#include "Plugin/IPlugin.h"
#include "Plugin/IComManagerFace.h"
#include "Plugin/IComFactory.h"
#include "Plugin/IComManagerFaceImp.h"
#include "Plugin/IConfig.h"
#include "Plugin/IPluginUI.h"
#include "Plugin/IConfigUI.h"

#include "ComManager/ComManager.h" // ����������


#endif