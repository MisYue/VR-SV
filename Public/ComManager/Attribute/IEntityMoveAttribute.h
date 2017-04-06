/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ���˶����Խӿ���	                                        */
/* ʱ�䣺 2016-06-8	                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IENTITYMOVETTRIBUTE_H_
#define _PUBLICE_IENTITYMOVETTRIBUTE_H_

namespace VR_Soft
{
	class IPath;

	class VRSOFT_DLL IEntityMoveAttribute : public IAttribute
	{
	public:
		// ��������
		virtual ~IEntityMoveAttribute(void) { }
		// ��ʼ����ʼ��ֵ // ��ģ�ͳ���Ŀ��λ��
		virtual void InitMove(void) = 0;
		// ����ʵ���ٶ�
		virtual void SetVelocity(const double dVelocity) = 0;
		// ���ʵ���ٶ�
		virtual double GetVelocity(void) const = 0;
		// ��������ٶ�
		virtual void SetMaxVelocity(const double vVelocity) = 0;
		// �������ٶ�
		virtual double GetMaxVelocity(void) const = 0;
		// ���ü��ٶ�
		virtual void SetAcceleration(const double vAcceleration) = 0;
		// ��ü��ٶ�
		virtual double GetAcceleration(void) const = 0;
		// ����Ŀ��λ��
		virtual void SetTragetPosition(const osg::Vec3d& vPos) = 0;
		// ���Ŀ��λ��
		virtual osg::Vec3d GetTragetPosition(void) const = 0;
		// ���õ�ǰ����λ��
		virtual void SetIndex(const int index) = 0;
		// ��õ�ǰ����λ��
		virtual int GetIndex(void) const = 0;
		// ����·��
		virtual void SetMovePath(IPath* pIPath) = 0;
		// ���·��
		virtual IPath* GetMovePath(void) const = 0;
	};
}

#endif // !_PUBLICE_IENTITYMOVETTRIBUTE_H_