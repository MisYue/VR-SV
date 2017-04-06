/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ʵ��ӿ���												*/
/* ʱ�䣺 2015-05-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IAIRLINEENTITY_H_
#define _PUBLIC_IAIRLINEENTITY_H_

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL ITrajectoryLineEntity : public IEntityBase
	{
	public:
		// ��������
		virtual ~ITrajectoryLineEntity(void) {  }
		// ���ʵ���������
		virtual void AddEntityBase(IEntityBase* pIEntityBase) = 0;
		// �Ƴ�ʵ��
		virtual void RemoveEntityBase(IEntityBase* pIEntityBase) = 0;
		// ������е�ʵ��
		virtual std::vector<IEntityBase* > GetAllEntity(void) const = 0;
		// ��ʼ������
		// virtual void InitAirLine(IAirLine* pIAirLine) = 0;
	};
}

#endif // _PUBLIC_IAIRLINEENTITY_H_