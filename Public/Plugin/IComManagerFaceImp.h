/************************************************************************/
/* ���ߣ� LJ		                                                    */
/* ��;:  ����ӿ�ģ��			                                        */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ICOMMANAGERFACEIMP_H_
#define _ICOMMANAGERFACEIMP_H_

#pragma once

#include "../VRConfig.h"

namespace VR_Soft
{
	template <typename T>
	class IComManagerFaceImp
	{
	public:
		// ��������
		virtual ~IComManagerFaceImp() {}
		// ���û�ȡ����
		SET_GET_PROPERTY(Name, VRString, str);
		
	private:
		VRString m_strName; // ����ӿ�����
	};
}

#endif