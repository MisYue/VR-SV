/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�嵼����			                                        */
/* ʱ�䣺 2016-03-23                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ENTITYDIRCTOR_H_
#define _ENTITYDIRCTOR_H_

#pragma once

namespace VR_Soft
{
	class CEntityDirctor
	{
	public:
		// ���캯��
		CEntityDirctor(IEntityBulider* pIEntityBulider);
		// ��������
		~CEntityDirctor(void);

		// ����
		IEntityBase* Construct();

	private:
		IEntityBulider* m_pIEntityBulider;
	};
}


#endif //! _ENTITYDIRCTOR_H_