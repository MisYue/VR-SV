/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������ӿ���                                                */
/* ʱ�䣺 2015-07-28                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ICOMMANAGERCOFIG_H_
#define _ICOMMANAGERCOFIG_H_

namespace VR_Soft
{
	class VRSOFT_DLL IComManagerConfig
	{
	public:
		// ��������
		virtual ~IComManagerConfig() { }
		// ��ʼ������ϵͳ
		virtual void Init() = 0;
		// ���·��
		virtual VRString GetCurPath(void) const = 0;		
	};
}

#endif // _ICOMMANAGERCOFIG_H_