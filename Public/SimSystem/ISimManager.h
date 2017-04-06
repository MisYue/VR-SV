/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ����ϵͳ���з���ʱ��Ͷ�ģ�͵��Ƚӿ�                  */
/* ʱ�䣺 2015-10-21                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ISIMMANAGERR_H_
#define _PUBLIC_ISIMMANAGERR_H_

namespace VR_Soft
{
	const VRString SIMSYSTEM_TYPENAME = "SIMSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_SIMSYSTEM = "SIMSYSTEM";
	const VRString SIMSYSTEM_DISC = "�������ϵͳ";

	// ����ʱ������
#if defined(_MSC_VER)
	typedef __int64 TIME_T;
#else
	typedef unsigned long long TIME_T;
#endif

	class ISimManager : public CSingleton<ISimManager>, public IComManagerFace
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
			Reset, // ����
			Close // �ر�
		};

	public:
		// ��������
		virtual ~ISimManager(void) { }
		// �����Ƿ�Ϊ������
		virtual void SetServer(const bool bServer) = 0;
		// �����Ƿ�Ϊ������
		virtual bool IsServer(void) const = 0;
		// ������������
		virtual void SetCmd(const SimCmd simCmd) = 0;
	};
}

#endif // _PUBLIC_ISIMMANAGERR_H_