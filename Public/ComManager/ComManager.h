/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��������ͷ�ļ�����	                                        */
/* ʱ�䣺 2015-05-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_COMMANAGER_H_
#define _PUBLIC_COMMANAGER_H_

#include "Tinyxml/XML.h" // XML �����ļ�
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
#include "VRVariant.h" // �ɱ����
#include "Property/Property.h" // ����
#include "Attribute/Attribute.h" // ����
#include "IState.h" // ״̬
#include "IStateMachine.h" // ״̬��
#include "IStrategy.h" // ����
#include "IStrategyManager.h" // ���Թ���
#include "Entity/Entity.h" // ʵ��
#include "Drawable/Drawable.h" // ��Ⱦ��
#include "Path/Path.h" // ·��

#include "IMessage.h" // ��Ϣϵͳ
#include "IMessageManager.h" // ��Ϣ����

#include "ITimer.h" // ��ʱ��
#include "ISimManager.h" // �������

// �¼�
#include "EventImp.h"
#include "IEvent.h"

// ·��
#include "ITrajectory.h"

#include "Action/Action.h"
#include "UI/UI.h"
#include "FeatureGeomtry/FeatureGeomtry.h"

#include "IComManager.h"

#endif // _PUBLIC_COMMANAGER_H_