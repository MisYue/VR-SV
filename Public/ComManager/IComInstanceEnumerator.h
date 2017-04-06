/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ʵ��������ӿ�                                            */
/* ʱ�䣺 2015-05-14                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ICOMINSTANCEENUMERATOR_H_
#define _ICOMINSTANCEENUMERATOR_H_

namespace VR_Soft
{
	class VRSOFT_DLL IComInstanceMerator : public CSingleton<IComInstanceMerator>
	{
	public:
		// ��������
		virtual ~IComInstanceMerator(void) { }
		// �������
		virtual IComManagerFace* CreateComInstance(const VRString& strTypeName, const VRString& strInstnaceName) = 0;
		// ��ò��ʵ��
		virtual IComManagerFace* GetComInstance(const VRString& strInstane) const = 0;
		// ��ӹ���
		virtual void AddFactory(IComFactory* pIComFactory) = 0;
		// ɾ������
		virtual void RemoveFactory(IComFactory* pIComFactory) = 0;
	};
}


#endif // _ICOMINSTANCEENUMERATOR_H_