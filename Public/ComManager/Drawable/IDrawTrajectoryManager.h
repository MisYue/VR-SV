/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �켣��Ⱦ�����		                                        */
/* ʱ�䣺 2016-03-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IDRAWTRAJECTORY_H_
#define _PUBLICE_IDRAWTRAJECTORY_H_

namespace VR_Soft
{
	class ITrajectory;

	class IDrawTrajectory 
	{
	public:
		// ��������
		virtual ~IDrawTrajectory(void) { }
		// ��Ҫ���»���
		virtual void Update(void) = 0;
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void) = 0;
		// �����㷨����
		virtual void SetTrajectory(ITrajectory* pITrajectory) = 0;
		
	};
}

#endif // ! _PUBLICE_IDRAWTRAJECTORY_H_