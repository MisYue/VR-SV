#include <list>
#include <map>
#include "../../Public/RenderSystem/RenderSystem.h"
#include "EventList.h"


namespace VR_Soft
{
	CEventList::CEventList(void) : m_bRemove(false)
	{
	}


	CEventList::~CEventList(void)
	{
	}

	// 注册事件
	void CEventList::RegisterEvent(IEvent* pEvnet, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// 查询是否存在当前视图的注册存在
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			LstEvent lstEnvent;
			lstEnvent.push_back(pEvnet);
			m_mapStrEvents[strViewName] = lstEnvent;
			return;
		}
		
		itor->second.push_back(pEvnet);
	}

	// 反注册事件
	void CEventList::UnRegisterEvent(IEvent* pEvnet, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// 查询是否存在当前视图的注册存在
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			return;
		}

		LstEvent& lstEvent = itor->second;
		LstEvent::iterator evnetItor = std::find(lstEvent.begin(), lstEvent.end(), pEvnet);
		lstEvent.remove(*evnetItor);

		m_bRemove = true;
	}

	void CEventList::OnClick(const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// 查询对应的视图名称
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// 无当前的视图
			IComManager::GetInstance().WriteLogMsg("当前视图不存在或者无人订阅", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// 遍历事件列表
		for (LstEvent::iterator itor = lstEvent.begin(); lstEvent.end() != itor; )
		{
	/*		(*itor)->OnClick();
			if (!m_bRemove)
			{
				++itor;
			}
			m_bRemove = false;*/
		}
	}

	// 鼠标左键按下
	void CEventList::OnLButtonDown(const float x, const float y, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// 查询对应的视图名称
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// 无当前的视图
			IComManager::GetInstance().WriteLogMsg("当前视图不存在或者无人订阅", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// 遍历事件列表
		for (LstEvent::iterator itor = lstEvent.begin(); lstEvent.end() != itor; )
		{
	/*		(*itor)->OnLButtonDown(x, y);
			if (!m_bRemove)
			{
				++itor;
			}
			m_bRemove = false;*/
		}
	}

	// 鼠标左键弹起
	void CEventList::OnLButtonUp(const float x, const float y, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// 查询对应的视图名称
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// 无当前的视图
			IComManager::GetInstance().WriteLogMsg("当前视图不存在或者无人订阅", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// 遍历事件列表
		for (LstEvent::iterator itor = lstEvent.begin(); lstEvent.end() != itor; )
		{
		/*	(*itor)->OnLButtonUp(x, y);

			if (!m_bRemove)
			{
				++itor;
			}
			m_bRemove = false;*/
		}
	}

	// 鼠标右键按下
	void CEventList::OnRButtonDown(const float x, const float y, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// 查询对应的视图名称
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// 无当前的视图
			IComManager::GetInstance().WriteLogMsg("当前视图不存在或者无人订阅", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// 遍历事件列表
		int index = 0;
		for (LstEvent::iterator itor = lstEvent.begin(); lstEvent.end() != itor && lstEvent.size() > 0; )
		{
			//(*itor)->OnRButtonDown(x, y);

			//if (!m_bRemove)
			//{
			//	++index;
			//	++itor;
			//}
			//else
			//{
			//	if (index == lstEvent.size())
			//	{
			//		break;
			//	}
			//	//itor;
			//}
			//m_bRemove = false;
		}
	}

	// 鼠标右键弹起
	void CEventList::OnRButtonUp(const float x, const float y, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// 查询对应的视图名称
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// 无当前的视图
			IComManager::GetInstance().WriteLogMsg("当前视图不存在或者无人订阅", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// 遍历事件列表
		for (LstEvent::iterator itor = lstEvent.begin(); lstEvent.end() != itor; )
		{
	/*		(*itor)->OnRButtonUp(x, y);

			if (!m_bRemove)
			{
				++itor;
			}
			m_bRemove = false;*/
		}
	}

	// 键盘按下
	void CEventList::OnKeyDown(int keySymble, const VRString& strViewName /*= "mainView"*/)
	{
		VR_MUTEX_AUTO;

		// 查询对应的视图名称
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// 无当前的视图
			IComManager::GetInstance().WriteLogMsg("当前视图不存在或者无人订阅", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// 遍历事件列表
		for (LstEvent::iterator itor = lstEvent.begin(); lstEvent.end() != itor; )
		{
	/*		(*itor)->OnKeyDown(keySymble);

			if (!m_bRemove)
			{
				++itor;
			}
			m_bRemove = false;*/
		}
	}

}
