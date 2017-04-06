/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������ӿ�		                                        */
/* ʱ�䣺 2015-11-21                                                    */
/* �޸�ʱ��:                                                            */
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
		// ��������
		virtual ~IManipulatorManager(void) { }
		// ���ò�����
		virtual bool SetCurrentManipulator(const VRString& strManipulator) = 0;
		// ��Ӳ�����
		virtual void AddManipulator(const VRString& strManipulator, osgGA::CameraManipulator* pCmp, bool bSelect = false) = 0;
		// ��ò�����
		virtual osgGA::CameraManipulator* GetManipulator(const VRString& strManipulator) const = 0;
		// ����ʵ��
		virtual void TrakerEntity(const uint64_t ID) = 0;
		// ����ʵ��
		virtual void TrakerEntity(const IEntityBase* pIEntity) = 0;
	};
}

#endif // !_PUBLICE_IMANIPULATORMANAGER_H_