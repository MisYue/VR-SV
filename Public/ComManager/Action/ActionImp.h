/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ģ����			                                        */
/* ʱ�䣺 2016-06-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ACTIONIMP_H_
#define _PUBLIC_ACTIONIMP_H_

namespace VR_Soft
{
	template<typename T>
	class CActionImp: public T
	{
	public:
		// ���캯��
		explicit CActionImp(void)
			: m_pIEntityBase(NULL),m_strName("")
		{
			m_dt = ISimManager::GetInstance().GetStartTime();
		}

		// ��������
		virtual ~CActionImp(void) { }

		// ��������
		virtual void SetName(const VRString& strName)
		{
			m_strName = strName;
		}
		// ��������
		virtual const VRString& GetName(void) const
		{
			return (m_strName);
		}

		// ����ʱ��
		virtual void SetDateTime(const CDateTime& dt)
		{
			m_dt = dt;
		}

		// ���ʱ��
		virtual const CDateTime& GetDateTime(void) const { return (m_dt); }

		// ���ý���ʱ��
		virtual bool SetEndDateTime(const CDateTime& dt)
		{
			if (dt < m_dt)
			{
				IComManager::GetInstance().WriteLogMsg("ָ������ʱ�䲻��ȷ������ʱ��Ӧ�ô��ڿ�ʼʱ��", ERROR_MODEL_NULL);
				return (false);
			}
			else
			{
				m_Enddt = dt;
			}
			
			return (true);
		}

		// ��ý���ʱ��
		virtual const CDateTime& GetEndDateTime(void) const { return (m_Enddt) ;}

		// ����ʵ��
		virtual void SetEntity(IEntityBase* pIEntity) { m_pIEntityBase = pIEntity; }

		// ���ʵ��
		virtual IEntityBase* GetEntity(void) const { return (m_pIEntityBase); }
		// ����Ƿ�ִ�н���
		virtual bool Executed(const CDateTime& dt) const { return (dt > m_Enddt); }

	private:
		IEntityBase* m_pIEntityBase;
		CDateTime m_dt;
		CDateTime m_Enddt;
		VRString m_strName;
	};

}
#endif