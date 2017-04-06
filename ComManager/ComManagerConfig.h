/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理配置实现类                                            */
/* 时间： 2015-07-28                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#pragma once

namespace VR_Soft
{
	class CComManagerConfig : public IComManagerConfig
	{
	public:
		explicit CComManagerConfig(const VRString& strPath);
		virtual ~CComManagerConfig(void);

	public: 
		// 添加当前已添加的组件
		void AddComName(const VRString& strComName );
		// 移除当前已添加的组件
		void RemoveComName(const VRString& strComName);
		// 保存当前已经添加的名称
		void Sava(void);
		// 读取已添加的插件名称
		void ReadCom(void);

	public:
		// 初始化整个系统
		virtual void Init() ;
		// 获得执行路径
		virtual VRString GetCurPath(void) const;

	protected:
		// 获得全部路径
		VRString GetExePath(void) const;
		void Replace(char* szLine);
	protected:
		typedef std::vector<VRString> LstLoadedCom; // 保存已经加载的组件

	private:
		VRString m_strPath; // 可执行程序所在的路径
		mutable VRString m_strCurPath; // 当前的路径

		LstLoadedCom m_lstLoadedCom; // 当前加载的路径名称

		VR_AUTO_MUTEX
	};
}


