/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ͬ��������������	                                            */
/* ʱ�䣺 2016-07-01                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_SYNCHROMANIPMANNAGER_H_
#define _PUBLIC_SYNCHROMANIPMANNAGER_H_

#include <osgEarth/Viewpoint>

namespace VR_Soft
{
	class OSGEARTH_DLL ISynchroManIpManager : public CSingleton<ISynchroManIpManager>
	{
	public:
		// ��������
		virtual ~ISynchroManIpManager(void) { }
		// �����ӵ�
		virtual void SetViewPoint(const osgEarth::Viewpoint& vp, double duration_s =0.0) = 0;
		// ����ӵ�
		virtual osgEarth::Viewpoint GetViewPoint(void) const = 0;
		// ����ʵ��ģ��
		virtual void SetTrackEntity(const uint64_t uID) = 0;
		// �Ͽ�����ģ��
		virtual void BreakTrackEntity(void) = 0;

	};
}

#endif // !_PUBLIC_SYNCHROMANIPMANNAGER_H_