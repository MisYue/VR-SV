#include "../../Public/VRSoft.h"
#include "Inpute.h"

namespace VR_Soft
{
	// ���캯��
	CInpute::CInpute(void)
	{
		Init();
	}

	// ��������
	CInpute::~CInpute(void)
	{
	}

	// ��ʼ��
	void CInpute::Init(void)
	{
		m_vPosition2D = osg::Vec2d(0.0, 0.0);
		m_mouseSymbol = MS_NULL;
		m_keySymbol = KEY_NULL;
	}

	// �������Ƿ񵥻�
	bool CInpute::GetMouseButton(const MouseSymbol mouseSymbol) const
	{
		if (m_mouseSymbol == mouseSymbol)
		{
			return (true);
		}

		return (false);
	}

	// ����Ƿ�װ����
	bool CInpute::GetKey(const KeySymbol keySymbol) const
	{
		if (m_keySymbol == keySymbol)
		{
			return (true);
		}

		return (false);
	}

	// ������Ķ�άλ��
	osg::Vec2d CInpute::GetMousePosition2D(void) const
	{
		return (m_vPosition2D);
	}

	// �������
	void CInpute::SetMouseButton(const MouseSymbol mouseSymbol)
	{
		m_mouseSymbol = mouseSymbol;
	}

	// �����Ƿ�װ����
	void CInpute::SetKey(const KeySymbol keySymbol)
	{
		m_keySymbol = keySymbol;
	}

	// ���õ�����
	void CInpute::SetMousePosition2D(const osg::Vec2d vPos)
	{
		m_vPosition2D = vPos;
	}

}
