/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  卫星两行根数													*/
/* 时间： 2015-11-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _TLE_H_
#define _TLE_H_

#pragma once

namespace VR_Soft
{
	class CSVTle : public ITle
	{
	public:
		explicit CSVTle(const VRString& strName, const VRString& strLine1, const VRString& strLine2);
		virtual ~CSVTle(void);

	public:
		// 获得名称
		virtual VRString &GetName(void) ;
		// 获得第一行数
		virtual VRString& GetLine1(void) ;
		// 获取第二行数
		virtual VRString& GetLine2(void) ;

	private:
		VRString m_strName;
		VRString m_strLine1;
		VRString m_strLine2;
	};
}


#endif // !_TLE_H_