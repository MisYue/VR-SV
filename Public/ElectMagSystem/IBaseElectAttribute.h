/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �״�Ӵ����Խӿ�												*/
/* ʱ�䣺 2015-06-16                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IBASEELECTATTRIBUTE_H_
#define _PUBLIC_IBASEELECTATTRIBUTE_H_

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL IBaseElecAttribute : public  IAttribute
	{
	public: 
		// ��������
		virtual ~IBaseElecAttribute(void) { }
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
	};
}

#endif // !_PUBLIC_IBASEELECTATTRIBUTE_H_