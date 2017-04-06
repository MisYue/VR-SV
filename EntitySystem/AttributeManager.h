/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����Թ���ʵ����	                                        */
/* ʱ�䣺 2015-06-02                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ATTRIBUTEMANAGER_H_
#define _ATTRIBUTEMANAGER_H_

#pragma once

namespace VR_Soft
{
	class IEntityBase;
	/*class IAttribute;*/

	class CAttributeManager : public IAttributeManager
	{
	public:
		// ���캯��
		explicit CAttributeManager(void);
		// ��������
		virtual ~CAttributeManager(void);

		// ע����洰��
		virtual void RegisterUI(IAttributeUI* pIAttributeUI);
		// ��ע����洰��
		virtual void UnRegisterUI(IAttributeUI* pIAttributeUI);
		// ���õ�ǰ������
		virtual void SetCurrentEntityBase(IEntityBase* pIEntityBase);
		// ������Խӿ�
		virtual void AddAttribute(IAttribute* pIAttribute);
		// �������������
		virtual IAttributeItem* CreateAttributeItem(IAttribute* pIAttribute,const VRString& strItemName, const VRString& strText, const VRString& strUntil,\
			const VRVariant& var, const Contrl ct =  CTRL_SPINBOX);
		// ����������
		virtual void UpdateAttributeItem(const IAttributeItem* pIAttributeItem);

	protected:
		// ����UI
		void UpdateAttributeUI(const IAttribute* pIAttribute);

	protected:
		typedef std::map<IEntityBase*, IAttribute*> MapEntityAttribute;
		typedef std::vector<IAttributeUI*> VctAttributeUI;

	private:
		MapEntityAttribute m_mapEntityAttribute; // ģ�������б�
		VctAttributeUI m_vecAttributeUI; // ���漯��
		IEntityBase* m_pICurEntityBase; // ��ǰģ���б�

		VR_AUTO_MUTEX
	};
}


#endif // _ATTRIBUTEMANAGER_H_