/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����๤������		                                        */
/* ʱ�䣺 2015-05-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _RADARFACTORY_H_
#define _RADARFACTORY_H_

#pragma once

namespace VR_Soft
{
	class CRadarFactory : public IEntityBaseFactory
	{
	public:
		explicit CRadarFactory(void);
		virtual ~CRadarFactory(void);

		// ��ȡ����
		virtual VRString GetEntiryBaseType(void) const;
		// ��������
		virtual IEntityBase* CreateEntityInstance(void);
		// �����������
		virtual VRString GetEntityBaseName(void);
	};
}

#endif // _RADARFACTORY_H_