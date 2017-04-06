/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  操作器管理接口		                                        */
/* 时间： 2015-11-21                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IMANIPULATORMANAGER_H_
#define _PUBLICE_IMANIPULATORMANAGER_H_

namespace osgGA
{
	class KeySwitchMatrixManipulator;
	class CameraManipulator;
}

namespace VR_Soft
{
	class OSGRENDER_DLL IManipulatorManager
	{
	public:
		// 析构函数
		virtual ~IManipulatorManager(void) { }
		// 设置操作器
		virtual bool SetCurrentManipulator(const VRString& strManipulator) = 0;
		// 添加操作器
		virtual void AddManipulator(const VRString& strManipulator, osgGA::CameraManipulator* pCmp, bool bSelect = false) = 0;
		// 获得操作器
		virtual osgGA::CameraManipulator* GetManipulator(const VRString& strManipulator) const = 0;
		// 跟踪实体
		virtual void TrakerEntity(const uint64_t ID) = 0;
		// 跟踪实体
		virtual void TrakerEntity(const IEntityBase* pIEntity) = 0;
	};
}

#endif // !_PUBLICE_IMANIPULATORMANAGER_H_