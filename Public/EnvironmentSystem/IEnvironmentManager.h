/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ��ڽӿ�												*/
/* ʱ�䣺 2015-11-24                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ENVIRONMENTMANAGER_H_
#define _PUBLICE_ENVIRONMENTMANAGER_H_

namespace VR_Soft
{
	const VRString ENVIRONEMNTSYSTEM_TYPENAME = "ENVIRONEMNTSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_ENVIRONEMNTSYSTEM = "ENVIRONEMNTSYSTEM";
	const VRString ENVIRONEMNTSYSTEM_DISC = "����ϵͳ";

	class IEnvironmentManager : public CSingleton<IEnvironmentManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~IEnvironmentManager(void) { }
		// ���Ĭ��״̬
		virtual IState* GetDefultState(void) = 0;
	};
}

#endif // !_PUBLICE_ENVIRONMENTMANAGER_H_