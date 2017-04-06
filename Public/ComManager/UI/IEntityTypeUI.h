/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体类型界面接口		                                        */
/* 时间： 2016-06-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENTITYTYPEUI_H_
#define _PUBLIC_IENTITYTYPEUI_H_

namespace VR_Soft
{
	class VRSOFT_DLL IEntityTypeUI 
	{
	public:
		// 析构函数
		virtual ~IEntityTypeUI(void) { }
		// 初始化
		virtual void Init(IEntityFactoryManager* pIEntityFactoryManager) = 0;
		// 添加一个实体
		virtual void UpdateNewItem(IEntityBaseFactory* pEntity) = 0;
		// 移除实体
		virtual void UpdateDelItem(IEntityBaseFactory* pEntity) = 0;
	};
}

#endif // !_PUBLIC_IENTITYTYPEUI_H_