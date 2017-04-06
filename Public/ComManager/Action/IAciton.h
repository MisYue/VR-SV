/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  命令基类接口			                                        */
/* 时间： 2016-06-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IACTION_H_
#define _PUBLIC_IACTION_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAction
	{
	public: 
		// 析构函数
		virtual ~IAction(void) { }
		// 设置名称
		virtual void SetName(const VRString& strName) = 0;
		// 设置名称
		virtual const VRString& GetName(void) const = 0;
		// 设置时间
		virtual void SetDateTime(const CDateTime& dt) = 0;
		// 获得时间
		virtual const CDateTime& GetDateTime(void) const = 0;
		// 设置结束时间
		virtual bool SetEntDateTime(const CDateTime& dt) = 0;
		// 获得结束时间
		virtual const CDateTime& GetEndDateTime(void) const = 0;
		// 设置实体
		virtual void SetEntity(IEntityBase* pIEntity) = 0;
		// 获得实体
		virtual IEntityBase* GetEntity(void) const = 0;
		// 初始化动作
		virtual void Init(void) = 0;
		// 执行动作
		virtual void Execute(const CDateTime& dt) = 0;
		// 检测是否执行结束
		virtual bool Executed(const CDateTime& dt ) const = 0;
	};
}

#endif // !_PUBLIC_IACTION_H_