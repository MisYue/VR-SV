/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �켣�㷨���Խӿ�		                                        */
/* ʱ�䣺 2015-08-04                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ITRAJECTORY_H_
#define _PUBLIC_ITRAJECTORY_H_

namespace VR_Soft
{
	struct TrajectoryInfo
	{
		double dt;			// ʱ��
		osg::Vec3d vGeoPos; // ��������
		osg::Vec3d vEcfPos; // �ع�ϵ�µ�λ����Ϣ
		osg::Vec3d vEcfVel; // �ع�ϵ�µ��ٶ���Ϣ
		osg::Vec3d vEciPos; // �ع�ϵ�µ�λ����Ϣ
		osg::Vec3d vEciVel; // �ع�ϵ�µ��ٶ���Ϣ
		osg::Vec3d vRot; // ��̬
	};

	class ITrajectoryEntity;

	class ITrajectory
	{
	public:
		typedef std::vector<TrajectoryInfo> ListTrajectoryInfo;

	public:
		// ��������
		virtual ~ITrajectory() { }
		// ��õ�������
		virtual const ListTrajectoryInfo& GetTrajectoryPoint(void) const = 0;
		// �����㷨
		virtual void AlgorithmTrajectoryPoint(void) = 0;
		// ���õ�������
		virtual void SetTrajectoryEntity(IEntityBase* pITrajectoryEntity) = 0;
	};
}

#endif // _PUBLIC_ITRAJECTORY_H_