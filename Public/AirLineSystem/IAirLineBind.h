/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���߰󶨽ӿ�		                                            */
/* ʱ�䣺 2015-11-25                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IAIRLINEBIND_H_
#define _PUBLIC_IAIRLINEBIND_H_

namespace VR_Soft
{
	class IAirLineBind
	{
	public:
		typedef std::list<IEntityBase* > ListEntityBases;
		typedef std::map<IAirLine*, ListEntityBases> ListAirLineBinds;

	public:
		virtual ~IAirLineBind() { }
		// �󶨺���
		virtual void Bind(IEntityBase* pIEntity, IAirLine* pIAriLine) = 0;
		// �����
		virtual void UnBind(IEntityBase* pIEntity, IAirLine* pIAriLine) = 0;
		// ��ú���
		virtual IAirLine* GetAirLine(IEntityBase* pIEntity) const = 0;
	};
}

#endif // !_PUBLIC_IAIRLINEBIND_H_