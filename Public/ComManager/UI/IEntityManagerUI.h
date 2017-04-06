/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体管理界面接口		                                        */
/* 时间： 2016-06-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENTITYMANAGERUI_H_
#define _PUBLIC_IENTITYMANAGERUI_H_

namespace VR_Soft
{
	class VRSOFT_DLL IEntityManagerUI 
	{
	public:
		// 析构函数
		virtual ~IEntityManagerUI(void) { }
		// 初始化
		virtual void Init(IEntityManager* pIEntityManager) = 0;
		// 添加一个实体
		virtual void UpdateNewItem(IEntityBase* pEntity) = 0;
		// 移除实体
		virtual void UpdateDelItem(IEntityBase* pEntity) = 0;
		// 更改实体名称
		virtual void UpdateItem(IEntityBase* pEntity, const VRString& strOldName, const VRString& strNemName ) = 0;
	};
}

#endif // !_PUBLIC_IENTITYMANAGERUI_H_