/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线绑定接口		                                            */
/* 时间： 2015-11-25                                                    */
/* 修改时间:                                                            */
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
		// 绑定航线
		virtual void Bind(IEntityBase* pIEntity, IAirLine* pIAriLine) = 0;
		// 解除绑定
		virtual void UnBind(IEntityBase* pIEntity, IAirLine* pIAriLine) = 0;
		// 获得航线
		virtual IAirLine* GetAirLine(IEntityBase* pIEntity) const = 0;
	};
}

#endif // !_PUBLIC_IAIRLINEBIND_H_