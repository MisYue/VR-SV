#ifndef _ICOMMANAGERFACE_H_
#define _ICOMMANAGERFACE_H_

#pragma once

#include "IComManagerFaceImp.h"

namespace VR_Soft
{
	class VRSOFT_DLL IComManagerFace //: public IComManagerFaceImp<IComManagerFace>
	{
	public:
		// ��������
		virtual ~IComManagerFace(void) { }
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const = 0;
		// ��������г�ʼ��
		virtual void Init(void) = 0;
	public:
		// ���û�ȡ����
		SET_GET_PROPERTY_INTERFACE(Name, VRString);
		// static const VRString COM_TYPE_NAME;
	};
}
#endif