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

	// ע���¼�
	void CEventList::RegisterEvent(IEvent* pEvnet, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// ��ѯ�Ƿ���ڵ�ǰ��ͼ��ע�����
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

	// ��ע���¼�
	void CEventList::UnRegisterEvent(IEvent* pEvnet, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// ��ѯ�Ƿ���ڵ�ǰ��ͼ��ע�����
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

		// ��ѯ��Ӧ����ͼ����
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// �޵�ǰ����ͼ
			IComManager::GetInstance().WriteLogMsg("��ǰ��ͼ�����ڻ������˶���", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// �����¼��б�
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

	// ����������
	void CEventList::OnLButtonDown(const float x, const float y, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// ��ѯ��Ӧ����ͼ����
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// �޵�ǰ����ͼ
			IComManager::GetInstance().WriteLogMsg("��ǰ��ͼ�����ڻ������˶���", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// �����¼��б�
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

	// ����������
	void CEventList::OnLButtonUp(const float x, const float y, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// ��ѯ��Ӧ����ͼ����
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// �޵�ǰ����ͼ
			IComManager::GetInstance().WriteLogMsg("��ǰ��ͼ�����ڻ������˶���", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// �����¼��б�
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

	// ����Ҽ�����
	void CEventList::OnRButtonDown(const float x, const float y, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// ��ѯ��Ӧ����ͼ����
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// �޵�ǰ����ͼ
			IComManager::GetInstance().WriteLogMsg("��ǰ��ͼ�����ڻ������˶���", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// �����¼��б�
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

	// ����Ҽ�����
	void CEventList::OnRButtonUp(const float x, const float y, const VRString& strViewName)
	{
		VR_MUTEX_AUTO;

		// ��ѯ��Ӧ����ͼ����
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// �޵�ǰ����ͼ
			IComManager::GetInstance().WriteLogMsg("��ǰ��ͼ�����ڻ������˶���", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// �����¼��б�
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

	// ���̰���
	void CEventList::OnKeyDown(int keySymble, const VRString& strViewName /*= "mainView"*/)
	{
		VR_MUTEX_AUTO;

		// ��ѯ��Ӧ����ͼ����
		MapStrEvents::iterator itor = m_mapStrEvents.find(strViewName);
		if (m_mapStrEvents.end() == itor)
		{
			// �޵�ǰ����ͼ
			IComManager::GetInstance().WriteLogMsg("��ǰ��ͼ�����ڻ������˶���", ERROR_NOT_FIND);
			return;
		}

		LstEvent& lstEvent = itor->second;
		// �����¼��б�
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
