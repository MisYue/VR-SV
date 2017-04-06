/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  事件列表接口			                                        */
/* 时间： 2015-08-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _EVENTLIST_H_
#define _EVENTLIST_H_
#pragma once

namespace VR_Soft
{
	class CEventList : public CSingleton<CEventList>
	{
	public:
		// 对应视图的名称
		explicit CEventList(void);
		~CEventList(void);

		// 注册事件
		void RegisterEvent(IEvent* pEvnet, const VRString& strViewName = "mainView");
		// 反注册事件
		void UnRegisterEvent(IEvent* pEvnet, const VRString& strViewName = "mainView");

	protected:
		// 鼠标左键单击事件
		void OnClick(const VRString& strViewName = "mainView");
		// 鼠标左键按下
		virtual void OnLButtonDown(const float x, const float y, const VRString& strViewName = "mainView");
		// 鼠标左键弹起
		virtual void OnLButtonUp(const float x, const float y, const VRString& strViewName = "mainView");
		// 鼠标右键按下
		virtual void OnRButtonDown(const float x, const float y, const VRString& strViewName = "mainView");
		// 鼠标右键弹起
		virtual void OnRButtonUp(const float x, const float y, const VRString& strViewName = "mainView");
		// 键盘按下
		virtual void OnKeyDown(int keySymble, const VRString& strViewName = "mainView");


	private:
		typedef std::list<IEvent*> LstEvent;
		typedef std::map<VRString, LstEvent> MapStrEvents;


		MapStrEvents m_mapStrEvents; 
		bool m_bRemove; // 是否有删除值

		friend class CPickHeader;

		VR_AUTO_MUTEX
	};
}


#endif // _EVENTLIST_H_