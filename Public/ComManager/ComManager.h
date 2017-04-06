/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理的头文件集合	                                        */
/* 时间： 2015-05-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_COMMANAGER_H_
#define _PUBLIC_COMMANAGER_H_

#include "Tinyxml/XML.h" // XML 解析文件
#include "IConfigFile.h"
#include "Convert.h"
#include "TimePoint.h"
#include "DyLib.h"
#include "FileOperetor.h"
#include "FileUtil.h"
#include "VRStringUtil.h"
#include "VRSoftThread.h"
#include "GUID.h"

#include "TimeUtil.h"
#include "DateTime.h"

#include "IComInstanceEnumerator.h"
#include "IConfigManager.h"
#include "IComManagerUI.h"
#include "IComManagerConfig.h"
#include "ComManagerImp.h"
#include "ILog.h"
#include "ILogManager.h"
#include "IMessageManager.h"
#include "VRVariant.h" // 可变参类
#include "Property/Property.h" // 属性
#include "Attribute/Attribute.h" // 属性
#include "IState.h" // 状态
#include "IStateMachine.h" // 状态机
#include "IStrategy.h" // 策略
#include "IStrategyManager.h" // 策略管理
#include "Entity/Entity.h" // 实体
#include "Drawable/Drawable.h" // 渲染体
#include "Path/Path.h" // 路径

#include "IMessage.h" // 消息系统
#include "IMessageManager.h" // 消息管理

#include "ITimer.h" // 计时器
#include "ISimManager.h" // 仿真管理

// 事件
#include "EventImp.h"
#include "IEvent.h"

// 路径
#include "ITrajectory.h"

#include "Action/Action.h"
#include "UI/UI.h"
#include "FeatureGeomtry/FeatureGeomtry.h"

#include "IComManager.h"

#endif // _PUBLIC_COMMANAGER_H_