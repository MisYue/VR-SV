/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���и���														*/
/* ʱ�䣺 2015-11-19                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PULIC_ITLE_H_
#define _PULIC_ITLE_H_

namespace VR_Soft
{
	class ITle
	{
	public:
		// ��������
		virtual ~ITle(void) { }
		// �������
		virtual VRString &GetName(void) = 0;
		// ��õ�һ����
		virtual VRString& GetLine1(void) = 0;
		// ��ȡ�ڶ�����
		virtual VRString& GetLine2(void) = 0;
	};

}

#endif // !_PULIC_ITLE_H_