/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ݹ�ص��˶���		                                        */
/* ʱ�䣺 2016-06-06                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _GUIDANCEVISITOR_H_
#define _GUIDANCEVISITOR_H_

#pragma once

namespace VR_Soft
{
	class CGuidanceVisitor : public IEntityVisitor
	{
	public:
		// ���캯��
		CGuidanceVisitor(void);
		// ��������
		virtual ~CGuidanceVisitor(void);

	public:
		// ���õ�����
		void SetTrajectory(ITrajectory* pITrajctory);

	public:
		// ������
		virtual void Visit(IEntityBase* pIEntityBase);

	private:
		ITrajectory* m_pITrajectory;
		IEntityBaseAttribute* m_pIEntityBaseAttribute; // ģ�ͻ�������
	};
}


#endif // !_GUIDANCEVISITOR_H_