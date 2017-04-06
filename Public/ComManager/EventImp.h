/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �¼��ӿ�ģ��		                                            */
/* ʱ�䣺 2015-08-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _EVENTIMP_H_
#define _EVENTIMP_H_


namespace VR_Soft
{
	template <class T>
	class CEventImp : public T
	{
	public:
		virtual ~CEventImp() { }

	public:
		// �����������¼�
		virtual void OnClick(void) { }
		// ����������
		virtual void OnLButtonDown(const float x, const float y) { }
		// ����������
		virtual void OnLButtonUp(const float x, const float y) { }
		// ����Ҽ�����
		virtual void OnRButtonDown(const float x, const float y) { }
		// ����Ҽ�����
		virtual void OnRButtonUp(const float x, const float y) { }
		// ���̰���
		virtual void OnKeyDown(int key) { }
	};
}

#endif // _EVENTIMP_H_