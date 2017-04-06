/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线系统入口接口												*/
/* 时间： 2015-05-22                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IAIRLINEUI_H_
#define _IAIRLINEUI_H_

namespace VR_Soft
{
	class IAirLineUI
	{
	public:
		// 析构函数
		virtual ~IAirLineUI() { IAirLineManager::GetInstance().UnReginsterUI();  }
		// 初始化航线
		virtual void InitAirLine(IAirLine* pIAirLine) = 0;
	};
}

#endif // _IAIRLINEUI_H_