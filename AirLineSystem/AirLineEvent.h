/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  视图适配器		                                            */
/* 时间： 2015-05-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _AIRLINEEVENT_H_
#define _AIRLINEEVENT_H_

#pragma once

namespace VR_Soft
{
	class CAirLineEvent : public CEventImp<IEvent>
	{
	public:
		explicit CAirLineEvent(void);
		virtual ~CAirLineEvent(void);

	public:
		// 鼠标左键按下
		virtual void OnLButtonDown(const float x, const float y);
		// 鼠标左键弹起
		virtual void OnRButtonDown(const float x, const float y);
	};
}

#endif // _AIRLINEEVENT_H_