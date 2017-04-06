/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体管理常用接口			                                    */
/* 时间： 2015-05-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_ENTITYSYSTEM_H_
#define _PUBLIC_ENTITYSYSTEM_H_

#include "IAttribute.h" // 属性接口
#include "AttributeImp.h" // 属性接口模板
#include "IAttributeManager.h" // 属性管理
#include "IEntityComponent.h" // 实体管理
#include "IEntityBase.h" // 实体接口
#include "IEntityBaseFactory.h" // 实体工厂接口
#include "IEntityRenderBase.h" // 渲染实体接口
#include "IEntityComposite.h" // 实体组件接口
#include "IAttributeUI.h" // 属性界面接口
#include "IEntityManager.h" // 接口实现
#include "EntityBaseFactoryImp.h" // 实体工厂模板
#include "AttributeItemImp.h" // 属性模板
#include "IEntityFactoryManager.h" // 实体工厂管理类
#include "IAttributeItemUI.h" // 属性控件接口
#include "AttributeItemUIImp.h" // 接口模板
#include "AttributeItemUIImp.h" // 接口模板
#include "IAttributeUIFactory.h" // 属性项界面工厂
#include "IState.h" // 状态
#include "IStateMachine.h" // 状态机
#include "IStrategy.h" // 策略
#include "IStrategyManager.h" // 策略管理
#include "IEntityID.h"

#endif //_PUBLIC_ENTITYSYSTEM_H_