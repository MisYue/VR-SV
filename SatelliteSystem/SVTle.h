/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������и���													*/
/* ʱ�䣺 2015-11-19                                                    */
/* �޸�ʱ��:                                                            */
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
		// �������
		virtual VRString &GetName(void) ;
		// ��õ�һ����
		virtual VRString& GetLine1(void) ;
		// ��ȡ�ڶ�����
		virtual VRString& GetLine2(void) ;

	private:
		VRString m_strName;
		VRString m_strLine1;
		VRString m_strLine2;
	};
}


#endif // !_TLE_H_