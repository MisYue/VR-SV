/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����๤������		                                        */
/* ʱ�䣺 2015-05-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IENTITYBASEFACTORY_H_
#define _IENTITYBASEFACTORY_H_

#pragma once

namespace VR_Soft
{
	class IEntityBulider;

	class IEntityBaseFactory
	{
	public:
		// ��������
		virtual ~IEntityBaseFactory() { }
		// ��ȡ����
		virtual VRString GetEntiryBaseType(void) const = 0;
		// ��������
		virtual IEntityBulider* CreateEntityBuilder(void) = 0;


	public:
		static int m_nCount;
	};

	// �������������
#define CREATE_ENTITYBASE_FACTORY(functionname) EXTERN_CPP VRSOFT_DLL IEntityBaseFactory* functionname(void);

}

#endif // _IENTITYBASEFACTORY_H_