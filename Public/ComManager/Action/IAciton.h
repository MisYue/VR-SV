/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������ӿ�			                                        */
/* ʱ�䣺 2016-06-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IACTION_H_
#define _PUBLIC_IACTION_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAction
	{
	public: 
		// ��������
		virtual ~IAction(void) { }
		// ��������
		virtual void SetName(const VRString& strName) = 0;
		// ��������
		virtual const VRString& GetName(void) const = 0;
		// ����ʱ��
		virtual void SetDateTime(const CDateTime& dt) = 0;
		// ���ʱ��
		virtual const CDateTime& GetDateTime(void) const = 0;
		// ���ý���ʱ��
		virtual bool SetEntDateTime(const CDateTime& dt) = 0;
		// ��ý���ʱ��
		virtual const CDateTime& GetEndDateTime(void) const = 0;
		// ����ʵ��
		virtual void SetEntity(IEntityBase* pIEntity) = 0;
		// ���ʵ��
		virtual IEntityBase* GetEntity(void) const = 0;
		// ��ʼ������
		virtual void Init(void) = 0;
		// ִ�ж���
		virtual void Execute(const CDateTime& dt) = 0;
		// ����Ƿ�ִ�н���
		virtual bool Executed(const CDateTime& dt ) const = 0;
	};
}

#endif // !_PUBLIC_IACTION_H_