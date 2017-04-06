/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �����豸����			                                        */
/* ʱ�䣺 2016-04-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _INPUTE_H_
#define _INPUTE_H_

namespace VR_Soft
{
	class CInpute : public IEvent
	{
	public:
		// ���캯��
		CInpute(void);
		// ��������
		virtual ~CInpute(void);

	public:
		// ��ʼ��
		virtual void Init(void) ;
		// �������Ƿ񵥻�
		virtual bool GetMouseButton(const MouseSymbol mouseSymbol) const ;
		// ����Ƿ�װ����
		virtual bool GetKey(const KeySymbol keySymbol) const ;
		// ������Ķ�άλ��
		virtual osg::Vec2d GetMousePosition2D(void) const ;
		// �������
		virtual void SetMouseButton(const MouseSymbol mouseSymbol);
		// �����Ƿ�װ����
		virtual void SetKey(const KeySymbol keySymbol) ;
		// ���õ�����
		virtual void SetMousePosition2D(const osg::Vec2d vPos);

	private:
		osg::Vec2d m_vPosition2D; // ��ά��
		KeySymbol m_keySymbol; // ���¼���
		MouseSymbol m_mouseSymbol; // �������
	};
}

#endif // !_INPUTE_H_