/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  环境系统入口接口												*/
/* 时间： 2015-11-24                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ENVIRONMENTMANAGER_H_
#define _PUBLICE_ENVIRONMENTMANAGER_H_

namespace VR_Soft
{
	const VRString ENVIRONEMNTSYSTEM_TYPENAME = "ENVIRONEMNTSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_ENVIRONEMNTSYSTEM = "ENVIRONEMNTSYSTEM";
	const VRString ENVIRONEMNTSYSTEM_DISC = "环境系统";

	class IEnvironmentManager : public CSingleton<IEnvironmentManager>, public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~IEnvironmentManager(void) { }
		// 获得默认状态
		virtual IState* GetDefultState(void) = 0;
	};
}

#endif // !_PUBLICE_ENVIRONMENTMANAGER_H_