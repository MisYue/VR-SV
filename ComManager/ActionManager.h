/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ָ�������			                                        */
/* ʱ�䣺 2016-06-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ACTIONMANAGER_H_
#define _ACTIONMANAGER_H_

#pragma once

#include<boost/unordered_map.hpp>  

namespace VR_Soft
{
	class CActionManager :	public IActionManager
	{
	public:
		// ���캯��
		explicit CActionManager(void);
		// ��������
		virtual ~CActionManager(void);

	public:
		// ���ָ��
		virtual void AddAction(IEntityBase* pIEnity, const VRString& strAciton) ;
		// �Ƴ�ָ��
		virtual void RemoveAction(IEntityBase* pIEnity, const int index) ;
		// ��ӹ���
		virtual void AddFactory(IActionFactory* pIActionFactory) ;
		// �Ƴ�����
		virtual void RemoveFactory(const VRString& strFactory) ;
		// ���ļ��м���ָ��dll�� 
		virtual void LoadAction(void) ;
		// ��ȡ���е�dllָ������
		virtual ListString GetAllActionDll(void) const ;
		// ��õ�ǰʵ���ָ��
		virtual ListString GetAllActionDll(IEntityBase* pIEntity) const ;
		// ���ָ��
		virtual IAction* GetAction(IEntityBase* pIEntity, const int index) const ;
		// �Ƴ�dll��
		virtual void RemoveActionDll(const VRString& strDll);
		// ִ��ָ��
		virtual void Execute(const CDateTime& dt) ;
		// ��ʼ��
		virtual void Init(void);

	protected:
		// ����dll��
		void LoadDll(const VRString& strDllPath);

	private:
	//	ListAction m_listAciton;

		typedef boost::unordered_map<VRString, CDyLib*> ListActionDlls;
		typedef boost::unordered_map<VRString, IActionFactory*> ListActionFactories; 
		typedef std::vector<IAction*> ListAction; // �����
		typedef boost::unordered_map<IEntityBase*, ListAction> ListEntityActions;

		ListActionDlls m_listActionDlls;
		ListActionFactories m_listActionFactorues;
		ListEntityActions m_listEntityAcitons;
		ListAction m_listSimAction; // ѭ����ָ��

		VR_AUTO_MUTEX
	};
}


#endif // !_ACTIONMANAGER_H_