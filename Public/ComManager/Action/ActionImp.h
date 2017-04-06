/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  命令模板类			                                        */
/* 时间： 2016-06-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ACTIONIMP_H_
#define _PUBLIC_ACTIONIMP_H_

namespace VR_Soft
{
	template<typename T>
	class CActionImp: public T
	{
	public:
		// 构造函数
		explicit CActionImp(void)
			: m_pIEntityBase(NULL),m_strName("")
		{
			m_dt = ISimManager::GetInstance().GetStartTime();
		}

		// 析构函数
		virtual ~CActionImp(void) { }

		// 设置名称
		virtual void SetName(const VRString& strName)
		{
			m_strName = strName;
		}
		// 设置名称
		virtual const VRString& GetName(void) const
		{
			return (m_strName);
		}

		// 设置时间
		virtual void SetDateTime(const CDateTime& dt)
		{
			m_dt = dt;
		}

		// 获得时间
		virtual const CDateTime& GetDateTime(void) const { return (m_dt); }

		// 设置结束时间
		virtual bool SetEndDateTime(const CDateTime& dt)
		{
			if (dt < m_dt)
			{
				IComManager::GetInstance().WriteLogMsg("指令设置时间不正确，结束时间应该大于开始时间", ERROR_MODEL_NULL);
				return (false);
			}
			else
			{
				m_Enddt = dt;
			}
			
			return (true);
		}

		// 获得结束时间
		virtual const CDateTime& GetEndDateTime(void) const { return (m_Enddt) ;}

		// 设置实体
		virtual void SetEntity(IEntityBase* pIEntity) { m_pIEntityBase = pIEntity; }

		// 获得实体
		virtual IEntityBase* GetEntity(void) const { return (m_pIEntityBase); }
		// 检测是否执行结束
		virtual bool Executed(const CDateTime& dt) const { return (dt > m_Enddt); }

	private:
		IEntityBase* m_pIEntityBase;
		CDateTime m_dt;
		CDateTime m_Enddt;
		VRString m_strName;
	};

}
#endif