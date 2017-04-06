/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �¼��б�ӿ�			                                        */
/* ʱ�䣺 2015-08-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _EVENTLIST_H_
#define _EVENTLIST_H_
#pragma once

namespace VR_Soft
{
	class CEventList : public CSingleton<CEventList>
	{
	public:
		// ��Ӧ��ͼ������
		explicit CEventList(void);
		~CEventList(void);

		// ע���¼�
		void RegisterEvent(IEvent* pEvnet, const VRString& strViewName = "mainView");
		// ��ע���¼�
		void UnRegisterEvent(IEvent* pEvnet, const VRString& strViewName = "mainView");

	protected:
		// �����������¼�
		void OnClick(const VRString& strViewName = "mainView");
		// ����������
		virtual void OnLButtonDown(const float x, const float y, const VRString& strViewName = "mainView");
		// ����������
		virtual void OnLButtonUp(const float x, const float y, const VRString& strViewName = "mainView");
		// ����Ҽ�����
		virtual void OnRButtonDown(const float x, const float y, const VRString& strViewName = "mainView");
		// ����Ҽ�����
		virtual void OnRButtonUp(const float x, const float y, const VRString& strViewName = "mainView");
		// ���̰���
		virtual void OnKeyDown(int keySymble, const VRString& strViewName = "mainView");


	private:
		typedef std::list<IEvent*> LstEvent;
		typedef std::map<VRString, LstEvent> MapStrEvents;


		MapStrEvents m_mapStrEvents; 
		bool m_bRemove; // �Ƿ���ɾ��ֵ

		friend class CPickHeader;

		VR_AUTO_MUTEX
	};
}


#endif // _EVENTLIST_H_