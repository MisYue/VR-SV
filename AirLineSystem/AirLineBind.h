/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���߰���		                                            */
/* ʱ�䣺 2015-11-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _AIRLIEBIND_H_
#define _AIRLIEBIND_H_

namespace VR_Soft
{
	class CAirLineBind : public IAirLineBind
	{
	public:
		CAirLineBind(void);
		~CAirLineBind(void);

	public:
		// �󶨺���
		virtual void Bind(IEntityBase* pIEntity, IAirLine* pIAriLine);
		// �����
		virtual void UnBind(IEntityBase* pIEntity, IAirLine* pIAriLine);
		// ��ú���
		virtual IAirLine* GetAirLine(IEntityBase* pIEntity) const;

	private:
		ListAirLineBinds m_lstAirLineBinds;
	};

}

#endif
