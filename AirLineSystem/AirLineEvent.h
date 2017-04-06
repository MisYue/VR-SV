/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ͼ������		                                            */
/* ʱ�䣺 2015-05-19                                                    */
/* �޸�ʱ��:                                                            */
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
		// ����������
		virtual void OnLButtonDown(const float x, const float y);
		// ����������
		virtual void OnRButtonDown(const float x, const float y);
	};
}

#endif // _AIRLINEEVENT_H_