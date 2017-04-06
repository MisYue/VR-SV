/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性项界面工厂接口                                        */
/* 时间： 2015-08-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IATTRIBUTEUIFACTORY_H_
#define _IATTRIBUTEUIFACTORY_H_

namespace VR_Soft
{
	class VRSOFT_DLL IAttributeUIFactory : public CSingleton<IAttributeUIFactory>
	{
	public:
		virtual ~IAttributeUIFactory() { }

		// 注册界面
		virtual void Register(IAttributeItemUI* pIAttributeItemUI) = 0;
		// 反注册界面
		virtual void UnRegister(IAttributeItemUI* pIAttributeItemUI) = 0;
		// 获得控件
		virtual IAttributeItemUI* GetContrl(IAttributeItem* pIAttributeItem) = 0;
	};
}

#endif // _IATTRIBUTEUIFACTORY_H_