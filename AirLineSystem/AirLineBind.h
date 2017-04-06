/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线绑定类		                                            */
/* 时间： 2015-11-25                                                    */
/* 修改时间:                                                            */
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
		// 绑定航线
		virtual void Bind(IEntityBase* pIEntity, IAirLine* pIAriLine);
		// 解除绑定
		virtual void UnBind(IEntityBase* pIEntity, IAirLine* pIAriLine);
		// 获得航线
		virtual IAirLine* GetAirLine(IEntityBase* pIEntity) const;

	private:
		ListAirLineBinds m_lstAirLineBinds;
	};

}

#endif
