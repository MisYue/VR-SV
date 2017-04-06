/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ʵ��������                                                */
/* ʱ�䣺 2015-05-14                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _CCOMINSTANCEENUMERATOR_H_
#define _CCOMINSTANCEENUMERATOR_H_

#pragma once

namespace VR_Soft
{
	class CComInstanceEnumerator : public IComInstanceMerator
	{
	public:
		// ���캯��
		explicit CComInstanceEnumerator(void);
		// ��������
		virtual ~CComInstanceEnumerator(void);
		// ��ӹ���
		virtual void AddFactory(IComFactory* pIComFactory);
		// ɾ������
		virtual void RemoveFactory(IComFactory* pIComFactory);

	public:
		// �������
		virtual IComManagerFace* CreateComInstance(const VRString& strTypeName, const VRString& strInstnaceName);
		// ��ò��ʵ��
		virtual IComManagerFace* GetComInstance(const VRString& strInstane) const;

	protected:
		typedef std::map<VRString, IComManagerFace*> MapStrInstance;
		typedef std::list<IComFactory*> ComFactoryList;

	private:
		MapStrInstance m_mapStrInstance; // ʵ������
		ComFactoryList m_comFactorys; // �����б�
		unsigned long m_nInstanceCreateCount; // ���������

		VR_AUTO_MUTEX
	};
}


#endif // _CCOMINSTANCEENUMERATOR_H_

