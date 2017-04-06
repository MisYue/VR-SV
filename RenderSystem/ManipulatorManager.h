/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �¼��б�ӿ�			                                        */
/* ʱ�䣺 2015-11-21                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _MANIPULATORMANAGER_H_
#define _MANIPULATORMANAGER_H_

namespace osgGA
{
	class KeySwitchMatrixManipulator;
}

namespace VR_Soft
{
	class CRenderView;

	class CManipulatorManager : public IManipulatorManager
	{
		typedef std::map<VRString, osgGA::CameraManipulator*> ListManipulators;
	public:
		// ���캯��
		explicit CManipulatorManager(CRenderView* pRenderView);
		// ��������
		virtual ~CManipulatorManager(void);

	public:
		// ���ò�����
		virtual bool SetCurrentManipulator(const VRString& strManipulator);
		// ��Ӳ�����
		virtual void AddManipulator(const VRString& strManipulator, osgGA::CameraManipulator* pCmp,  bool bSelect = false);
		// ��ò�����
		virtual osgGA::CameraManipulator* GetManipulator(const VRString& strManipulator) const;
		// ����ʵ��
		virtual void TrakerEntity(const uint64_t ID);
		// ����ʵ��
		virtual void TrakerEntity(const IEntityBase* pIEntity) ;

	protected:
		// ��ʼ��
		void Init(void);

	private:
		ListManipulators m_lstManipulators; // ��������˳��
		osgGA::KeySwitchMatrixManipulator* m_pSwitchManipulator; // ���ز�����
		CRenderView* m_pRenderView; // ��Ⱦ����
	};
}

#endif