/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʱ��ϵͳ�������ӿ�		                                    */
/* ʱ�䣺 2015-09-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ITIMEMANAGER_H_
#define _PUBLIC_ITIMEMANAGER_H_

namespace VR_Soft
{
	const VRString TIMESYSTEM_TYPENAME = "TIMESYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_TIMESYSTEM = "TIMESYSTEM";
	const VRString TIMESYSTEM_DISC = "ʱ��ϵͳ";

	class ITimeManager : public CSingleton<ITimeManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~ITimeManager() { }
		// ���ʱ�䷵���ַ���
		virtual ITimer* GetTime(void)  = 0;
		// ����
		virtual void Quicken(void) = 0;
		// ����
		virtual void Moderate(void) = 0;
		// ��ͣ
		virtual void Suspend(void) = 0;
		// �ָ�
		virtual void Recover(void) = 0;
		// ֹͣ����λ��
		virtual void Stop(void) = 0;
		// ��ʼ
		virtual void Start(void) = 0;
		// ��ת
		virtual void Jump(struct tm& t) = 0;
	};
}

#endif // _PUBLIC_ITIMEMANAGER_H_