/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��������ӿ�		                                        */
/* ʱ�䣺 2015-09-08                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _CANDIDATASMANAGER_H_
#define _CANDIDATASMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CCandidatasManager
	{
	public:
		explicit CCandidatasManager(void);
		~CCandidatasManager(void);

		// ��Ӵ�ѡ��
		void Add(const Candidatas& candidata);
		// �Ƴ���ѡ��
		void Remove(VRString& strName);
		// �Ƿ�Ϊ��
		bool Empty(void) const ;
		// �������ƻ��ֵ
		Candidatas GetCandidata(const VRString& strName, bool& b);
		// ��ȡ���е�ֵ
		const IAttributeItem::LstCandidatas& GetCandidatas(void) const;
		// ��õ�ǰѡ������
		int SelectCandidata(void) const;
		// ����ѡ������
		void SetSelect(const int index);
		// ��ÿɱ�ζ���
		VRVariant GetVariant(void) const;

	protected:
		// ��ǰ���Ѿ�����ͬ������
		bool IsHave(const VRString& strName);
		// ��ǰ���Ѿ�����ͬ������
		bool IsHave(const Candidatas& candidata);

	private:
		IAttributeItem::LstCandidatas m_lstCandidatas; // ��ǰѡ���б�

	};
}


#endif // _CANDIDATASMANAGER_H_