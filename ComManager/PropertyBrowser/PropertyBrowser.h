/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������			                                        */
/* ʱ�䣺 2016-09-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PROPERTYBROWSER_H_
#define _PROPERTYBROWSER_H_

#pragma once

namespace VR_Soft
{
	////////////////////////////////���潻������//////////////////////////////////////////
	class CAbstracUItPropertyManager;
	class CUIPropertyPrivate;

	class CUIProperty
	{
	public:
		typedef std::vector<CUIProperty* > ListUIProperty;

	public: 
		// ��������
		virtual ~CUIProperty(void);
		// ��������б�
		ListUIProperty GetSubProperties(void) const;
		// ��ù������Թ���
		CAbstracUItPropertyManager* GetPropertyManager(void) const;

		// �����ʾ��Ϣ
		VRString GetToolTip(void) const;
		// ���״̬����Ϣ
		VRString GetStatusTip(void) const;
		// ��ý�����Ϣ
		VRString GetWhatsThis(void) const;
		//�����������
		VRString PropertyName(void) const;
		// ����Ƿ����
		bool IsEnabled(void) const;
		// �Ƿ�Ľ�
		bool IsModified(void) const;
		// �ж��Ƿ���ֵ
		bool HasValue(void) const;
		// �ı�����
		VRString GetValueText(void) const;
		// �ȶԺ��� ���������Աȶ�
		virtual bool Compare(const CUIProperty& other) const;

	public:
		// ���ù�����ʾ��Ϣ
		void SetToolTip(const VRString& strText);
		// ����״̬����ʾ��Ϣ
		void SetStatusTip(const VRString& strText);
		// ���ý�����Ϣ
		void SetWhatsThis(const VRString& strText);
		// ������������
		void SetPropertyName(const VRString& strText);
		// �����Ƿ����
		void SetEnabled(const bool bEnable);
		// �����Ƿ�Ľ�
		void SetModified(bool bModified);

	public:
		// ����Ƿ���������
		bool IsSubProperty(void) const;
		// ���������
		void AddSubProperty(CUIProperty* pProperty) ;
		// ��ĳ����֮���������
		void InsertSubProperty(CUIProperty* pProperty, CUIProperty* pAfterProperty);
		// �Ƴ�����
		void RemoveSubProperty(CUIProperty* pProperty);

	protected:
		// ���캯��
		explicit CUIProperty(CAbstracUItPropertyManager* pManager);
		// ����ֵ�ı�
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
		// ���캯��
		explicit CAbstracUItPropertyManager(void);
		// ��������
		~CAbstracUItPropertyManager();
		// ���������1��
		std::set<CUIProperty *> GetProperties() const;
		// �������ֵ
		void Clear() const;
		// �������
		CUIProperty *AddProperty(const VRString &strName = VRString());
/*Q_SIGNALS:

		void propertyInserted(CUIProperty *property,
			CUIProperty *parent, CUIProperty *after);
		void propertyChanged(CUIProperty *property);
		void propertyRemoved(CUIProperty *property, CUIProperty *parent);
		void propertyDestroyed(CUIProperty *property);
		*/
	protected:
		// �Ƿ�������
		virtual bool HasValue(const CUIProperty *pProperty) const;
		// �������ֵ�ı�
		virtual VRString GetValueText(const CUIProperty *pProperty) const;
		// ��ʼ������
		virtual void InitializeProperty(CUIProperty *property) = 0;
		// ж�س�ʼ��
		virtual void UninitializeProperty(CUIProperty *pProperty);
		// ��������
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
		// �������
		CUIProperty *GetProperty() const;
		// ��ø���
		CBrowserItem *GetParent() const;
		// �������
		std::list<CBrowserItem *> GetChildren() const;
		// ��������
		CAbstractUIPropertyBrowser *GetBowser() const;
	private:
		// ���캯��
		explicit CBrowserItem(CAbstractUIPropertyBrowser *pBrowser, CUIProperty *pProperty, CBrowserItem *parent);
		// ��������
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