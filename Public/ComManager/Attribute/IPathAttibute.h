/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ���˶�·�����Խӿ�                                          */
/* ʱ�䣺 2016-06-8	                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IPATHATTRIBUTE_H_
#define _PUBLICE_IPATHATTRIBUTE_H_

namespace VR_Soft
{
	class VRSOFT_DLL IPathAttribute : public IDrawAttribute
	{
	public:
		typedef std::vector<osg::Vec3d> ListPoints;
	public:
		// ��������
		virtual ~IPathAttribute(void) { }
		// ���һ�������������
		virtual void AddKeyPoint(const osg::Vec3d& vPos) = 0;
		// �Ƴ�һ����
		virtual void RemoveKeyPoint(const int index) = 0;
		// ���ĵ�
		virtual void ChangeKeyPoint(const int index, const osg::Vec3d& vPos) = 0;
		// ���ĳһ���ؼ���
		virtual osg::Vec3d GetKeyPoint(int index) const = 0;
		// ���·���ؼ���
		virtual const ListPoints& GetKeyPoints(void) const = 0;
		// ���·����
		virtual const ListPoints& GetPathPoints(void) const = 0;
		// ���ָ��·����
		virtual osg::Vec3d GetPathPoint(const int index) const = 0;
	};
}

#endif // !_PUBLICE_IPATHATTRIBUTE_H_