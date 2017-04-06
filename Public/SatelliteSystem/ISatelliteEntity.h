/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ���ӿ�														*/
/* ʱ�䣺 2015-11-19                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PULIC_ISATELLITE_H_
#define _PULIC_ISATELLITE_H_

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL ISatelliteEntity : public IEntityBase
	{
	public:
		// ��������
		virtual ~ISatelliteEntity(void) { }

	public:
		// �����㷨����
		virtual void SetTrajectory(ITrajectory* pITrajectory)  = 0;
		// ����㷨����
		virtual ITrajectory* GetTrajectory(void)  = 0;
		// ���ɹ��
		virtual void GenerateTrajectory(void) = 0;
		// �������и���
		virtual void SetTle(ITle* pITle) = 0;
		// ������и���
		virtual ITle* GetTle(void) const = 0;

	};


}

#endif // !_PULIC_ISATELLITE_H_