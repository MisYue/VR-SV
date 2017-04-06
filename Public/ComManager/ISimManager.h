/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������ӿ�			                                        */
/* ʱ�䣺 2015-08-31                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ISIMMANAGER_H_
#define _PUBLICE_ISIMMANAGER_H_

namespace VR_Soft
{
	class VRSOFT_DLL ISimManager : public CSingleton<ISimManager>
	{
	public:
		// ö������
		enum SimCmd
		{
			Start, // ��������
			Pause, // ������ͣ
			Accelerate, // ����
			Decelerate, // ����
			Stop, // ֹͣ
			Reset // ����
		};

	public:
		virtual ~ISimManager() { }
		// ���÷��濪ʼʱ��
		virtual void SetBeginTime(const CDateTime& dtStart) = 0;
		// ���ý���ʱ��
		virtual void SetEndTime(const CDateTime& dtStop) = 0;
		// ��÷��濪ʼʱ��
		virtual CDateTime GetStartTime(void) const = 0 ;
		// ��ý���ʱ��
		virtual CDateTime GetEndTime(void) const = 0;
		// ���ÿ�ʼʱ��ͽ���ʱ��
		virtual void SetSimTimRange(const CDateTime& dtStart, const CDateTime& dtStop) = 0;
		// ��ÿ�ʼʱ��ͽ���ʱ��
		virtual void GetSimTimRange(CDateTime& dtStart, CDateTime& dtStop) const = 0;
		// ����ʱ��ָ��
		virtual void SetSimCmd(SimCmd simCmd) = 0 ;
		// ��÷���ָ��
		virtual SimCmd  GetSimCmd(void) const = 0 ;
		// ����ʱ�䲽��
		virtual void SetTimeStep(int nStep) = 0 ;
		// ���ʱ�䲽��
		virtual int GetTimeStep(void) const = 0 ;
		// ��ȡ����ʱ��
		virtual const CDateTime& GetSimTime(void) const = 0 ;
		// ����ʱ����ת
		virtual bool JumpSimTime(const CDateTime& dt) = 0;
	};
}

#endif // _PUBLICE_ISIMMANAGER_H_