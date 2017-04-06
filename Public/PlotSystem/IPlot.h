/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ͷ�ļ�			                                        */
/* ʱ�䣺 2016-08-10                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IPLOT_H_
#define _PUBLIC_IPLOT_H_

namespace VR_Soft
{
	class OSGRPLOT_DLL IPlot //: public IEntityBase
	{
	public:
		typedef std::vector<osg::Vec3d> ListPoints;
	public:
		// ��������
		virtual ~IPlot(void) { }
		// ���ID
		virtual uint64_t GetID(void) const = 0;
		// ��������
		virtual void SetName(const VRString& strName) = 0;
		// �������
		virtual VRString GetName(void) const = 0;
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
		// ����·������
		virtual void SetPathStrategy(const IPathStrategy* pIPathStratey) = 0;
		// ���·������
		virtual IPathStrategy* GetPathStrtegy(void) const = 0;
		// ������Ⱦ
		virtual void SetFeatureGeomtry(const IFeatureGeomtry* pIFeatureGeomtry) = 0;
		// �����Ⱦ
		virtual IFeatureGeomtry* GetFeatureGeomtry(void) const = 0;
	};
}

#endif