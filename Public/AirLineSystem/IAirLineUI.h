/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ��ڽӿ�												*/
/* ʱ�䣺 2015-05-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IAIRLINEUI_H_
#define _IAIRLINEUI_H_

namespace VR_Soft
{
	class IAirLineUI
	{
	public:
		// ��������
		virtual ~IAirLineUI() { IAirLineManager::GetInstance().UnReginsterUI();  }
		// ��ʼ������
		virtual void InitAirLine(IAirLine* pIAirLine) = 0;
	};
}

#endif // _IAIRLINEUI_H_