/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �״�Ӵ�������												*/
/* ʱ�䣺 2015-06-16                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _BASEELECATTRIBUTE_H_
#define _BASEELECATTRIBUTE_H_

#pragma once

namespace VR_Soft
{
	class CBaseElecAttribute : public CAttributeImp<IBaseElecAttribute>
	{
	public:
		// ���캯��
		explicit CBaseElecAttribute(void);
		// ��������
		virtual ~CBaseElecAttribute(void);

	public:
		// ���ð뾶
		virtual void SetRadius(float fRaius) = 0;
		// ��ð뾶
		virtual float GetRadius(void) const = 0;
		// ����ɨ���ٶ�
		virtual void SetScanSpeed(float fSpeed) = 0;
		// ���ɨ���ٶ�
		virtual float GetScanSpeed(void) const = 0;
		// ������Ⱦģʽ
		virtual void SetDrawMode(const DrawMode dm) = 0;
		// �����Ⱦģʽ
		virtual DrawMode GetDrawMode(void) const = 0;
		// ����������
		virtual void SetWireframeCount(int nCount) = 0;
		// ����������
		virtual int GetWireframeCount(void) const = 0;
		// ����ɨ�迪��
		virtual void SetScanState(bool bOpen) = 0;
		// ���ɨ�迪��
		virtual bool GetScanState(void) const = 0;

	private:
		double m_dRadius; // �뾶
		float m_fSpeed; // ɨ���ٶ�
		DrawMode m_dm; // ��Ⱦģʽ
		int m_nFrameCount; // ϸ�ָ���
		bool m_bOpen; // ɨ�迪��
	};

}

#endif // !_BASEELECATTRIBUTE_H_