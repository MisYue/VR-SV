/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  两行根数														*/
/* 时间： 2015-11-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PULIC_ITLE_H_
#define _PULIC_ITLE_H_

namespace VR_Soft
{
	class ITle
	{
	public:
		// 析构函数
		virtual ~ITle(void) { }
		// 获得名称
		virtual VRString &GetName(void) = 0;
		// 获得第一行数
		virtual VRString& GetLine1(void) = 0;
		// 获取第二行数
		virtual VRString& GetLine2(void) = 0;
	};

}

#endif // !_PULIC_ITLE_H_