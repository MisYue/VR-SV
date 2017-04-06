/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:   ����������ģ����	                                        */
/* ʱ�䣺 2015-08-31                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_COMMANAGERIMP_H_
#define _PUBLIC_COMMANAGERIMP_H_

namespace VR_Soft
{
	class CComManagerImp
	{
	public:
		template <class T>
		static T* GetComponent(const VRString& strInstanceName)
		{
			IComManagerFace* pIComFace = IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(strInstanceName);
			T* pIComponte = dynamic_cast<T*>(pIComFace);
			return (pIComponte);
		}
	};
}

#endif // _PUBLIC_COMMANAGERIMP_H_