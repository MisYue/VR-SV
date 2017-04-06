/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ʵ�幹����												*/
/* ʱ�䣺 2016-04-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _SATELLITEENTITYBUILDER_H_
#define _SATELLITEENTITYBUILDER_H_

#pragma once

namespace VR_Soft
{
	class CSatelliteEntity;

	class CSatelliteEntityBuilder : public IEntityBulider
	{
	public:
		// ���캯��
		CSatelliteEntityBuilder(void);
		// ��������
		virtual ~CSatelliteEntityBuilder(void);

	public:
		// ������Ⱦ��������
		virtual void CreateDrawManager(void);
		// ������Ⱦ����
		virtual void CreateDrawAttribute(void);
		// ��������������
		virtual void CreateAttribute(void) ;
		// �������
		virtual VRString CreateEntityName(void) const ;
		// ��ò�Ʒ
		virtual IEntityBase* GetEntity(void);
		// �Ƿ񴴽��˶����� ����true �򴴽�
		virtual bool IsCreateMoveAttribute(void) ;

	private:
		CSatelliteEntity* m_pSatelliteEntity;
		static unsigned int m_index;
	};

	// ע�Ṥ��
	REGISTER_BASEENTITY_FACTORY(CSatelliteEntityBuilder, "����");
}


#endif // !_SATELLITEENTITYBUILDER_H_