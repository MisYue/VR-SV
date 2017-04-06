/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  属性相关浏览			                                        */
/* 时间： 2016-09-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PROPERTYBROWSER_H_
#define _PROPERTYBROWSER_H_

#pragma once

namespace VR_Soft
{
	////////////////////////////////界面交互属性//////////////////////////////////////////
	class CAbstracUItPropertyManager;
	class CUIPropertyPrivate;

	class CUIProperty
	{
	public:
		typedef std::vector<CUIProperty* > ListUIProperty;

	public: 
		// 析构函数
		virtual ~CUIProperty(void);
		// 获得属性列表
		ListUIProperty GetSubProperties(void) const;
		// 获得管理属性管理
		CAbstracUItPropertyManager* GetPropertyManager(void) const;

		// 获得提示信息
		VRString GetToolTip(void) const;
		// 获得状态栏信息
		VRString GetStatusTip(void) const;
		// 获得介绍信息
		VRString GetWhatsThis(void) const;
		//获得属性名称
		VRString PropertyName(void) const;
		// 获得是否禁用
		bool IsEnabled(void) const;
		// 是否改进
		bool IsModified(void) const;
		// 判断是否有值
		bool HasValue(void) const;
		// 文本内容
		VRString GetValueText(void) const;
		// 比对函数 和其它属性比对
		virtual bool Compare(const CUIProperty& other) const;

	public:
		// 设置工具提示信息
		void SetToolTip(const VRString& strText);
		// 设置状态栏提示信息
		void SetStatusTip(const VRString& strText);
		// 设置介绍信息
		void SetWhatsThis(const VRString& strText);
		// 设置属性名称
		void SetPropertyName(const VRString& strText);
		// 设置是否禁用
		void SetEnabled(const bool bEnable);
		// 设置是否改进
		void SetModified(bool bModified);

	public:
		// 获得是否含有子属性
		bool IsSubProperty(void) const;
		// 添加子属性
		void AddSubProperty(CUIProperty* pProperty) ;
		// 在某属性之后插入属性
		void InsertSubProperty(CUIProperty* pProperty, CUIProperty* pAfterProperty);
		// 移除属性
		void RemoveSubProperty(CUIProperty* pProperty);

	protected:
		// 构造函数
		explicit CUIProperty(CAbstracUItPropertyManager* pManager);
		// 属性值改变
		void PropertyChanged(void);

	private:
		friend class CAbstracUItPropertyManager;
		CUIPropertyPrivate* m_pPtr;
	};

	///////////////////////////////CAbstracUItPropertyManager///////////////////////////////////////////
	class CAbstracUItPropertyManagerPrivate;
	class  CAbstracUItPropertyManager
	{
	public:
		// 构造函数
		explicit CAbstracUItPropertyManager(void);
		// 析构函数
		~CAbstracUItPropertyManager();
		// 获得所有属1性
		std::set<CUIProperty *> GetProperties() const;
		// 清空属性值
		void Clear() const;
		// 添加属性
		CUIProperty *AddProperty(const VRString &strName = VRString());
/*Q_SIGNALS:

		void propertyInserted(CUIProperty *property,
			CUIProperty *parent, CUIProperty *after);
		void propertyChanged(CUIProperty *property);
		void propertyRemoved(CUIProperty *property, CUIProperty *parent);
		void propertyDestroyed(CUIProperty *property);
		*/
	protected:
		// 是否有属性
		virtual bool HasValue(const CUIProperty *pProperty) const;
		// 获得属性值文本
		virtual VRString GetValueText(const CUIProperty *pProperty) const;
		// 初始化属性
		virtual void InitializeProperty(CUIProperty *property) = 0;
		// 卸载初始化
		virtual void UninitializeProperty(CUIProperty *pProperty);
		// 创建属性
		virtual CUIProperty* CreateProperty(void);

	private:
		friend class CUIProperty;
		CAbstracUItPropertyManagerPrivate *m_pPtr;
		DECLARE_PRIVATE(CAbstracUItPropertyManager)
		DISABLE_COPY(CAbstracUItPropertyManager)
	};

	class CAbstractUIPropertyBrowser;
	class CBrowserItemPrivate;

	class  CBrowserItem
	{
	public:
		// 获得属性
		CUIProperty *GetProperty() const;
		// 获得父项
		CBrowserItem *GetParent() const;
		// 获得子项
		std::list<CBrowserItem *> GetChildren() const;
		// 获得浏览项
		CAbstractUIPropertyBrowser *GetBowser() const;
	private:
		// 构造函数
		explicit CBrowserItem(CAbstractUIPropertyBrowser *pBrowser, CUIProperty *pProperty, CBrowserItem *parent);
		// 析构函数
		~CBrowserItem();
		CBrowserItemPrivate *m_pPtr;
		friend class CAbstractUIPropertyBrowser;
	};

	class CPropertyBrowser
	{
	public:
		CPropertyBrowser(void);
		virtual ~CPropertyBrowser(void);
	};
}


#endif // !_PROPERTYBROWSER_H_