/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �켣��Ⱦ�������		                                        */
/* ʱ�䣺 2016-03-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IDRAWTRAJECTORYATTRIBUTE_H_
#define _PUBLICE_IDRAWTRAJECTORYATTRIBUTE_H_

namespace VR_Soft
{
	class ITrajectory;

	class IDrawTrajectoryAttribute : public IDrawAttribute
	{
	public:
		// ��������
		virtual ~IDrawTrajectoryAttribute(void) { }
		// ���ù켣
		virtual void SetTrajectory(ITrajectory* pITrajectory) = 0;
		// ��ù켣
		virtual ITrajectory* GetTrajectory(void) const = 0;	
	};
}

#endif // ! _PUBLICE_IDRAWTRAJECTORYATTRIBUTE_H_