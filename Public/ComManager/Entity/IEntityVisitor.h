/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����ʻ���			                                        */
/* ʱ�䣺 2016-06-06                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IENTITYVISITOR_H_
#define _IENTITYVISITOR_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL IEntityVisitor
	{
	public:
		// ��������
		virtual ~IEntityVisitor() { }
		// ���ʽӿ� 
		virtual void Visit(IEntityBase* pIEntityBase) = 0;
	};
}

#endif // _IENTITYVISITOR_H_