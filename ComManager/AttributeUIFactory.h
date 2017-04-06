/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性项界面工厂	                                        */
/* 时间： 2015-08-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ATTRIBUTEUIFACTORY_H_
#define _ATTRIBUTEUIFACTORY_H_
#pragma once

namespace VR_Soft
{
	class CAttributeUIFactory : public IAttributeUIFactory
	{
	public:
		explicit CAttributeUIFactory(void);
		virtual ~CAttributeUIFactory(void);

		// 注册界面
		virtual void Register(IAttributeItemUI* pIAttributeItemUI);
		// 反注册界面
		virtual void UnRegister(IAttributeItemUI* pIAttributeItemUI);
		// 获得控件
		virtual IAttributeItemUI* GetContrl(IAttributeItem* pIAttributeItem);

	protected: 
		typedef boost::unordered_map<int, IAttributeItemUI*> AttributItemUIs;

	private:
		AttributItemUIs m_attributeItemUis;

		VR_AUTO_MUTEX
	};
}


#endif // _ATTRIBUTEUIFACTORY_H_