/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  事件列表接口			                                        */
/* 时间： 2015-11-21                                                    */
/* 修改时间:                                                            */
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
		// 构造函数
		explicit CManipulatorManager(CRenderView* pRenderView);
		// 析构函数
		virtual ~CManipulatorManager(void);

	public:
		// 设置操作器
		virtual bool SetCurrentManipulator(const VRString& strManipulator);
		// 添加操作器
		virtual void AddManipulator(const VRString& strManipulator, osgGA::CameraManipulator* pCmp,  bool bSelect = false);
		// 获得操作器
		virtual osgGA::CameraManipulator* GetManipulator(const VRString& strManipulator) const;
		// 跟踪实体
		virtual void TrakerEntity(const uint64_t ID);
		// 跟踪实体
		virtual void TrakerEntity(const IEntityBase* pIEntity) ;

	protected:
		// 初始化
		void Init(void);

	private:
		ListManipulators m_lstManipulators; // 操作器的顺序
		osgGA::KeySwitchMatrixManipulator* m_pSwitchManipulator; // 开关操作器
		CRenderView* m_pRenderView; // 渲染窗口
	};
}

#endif